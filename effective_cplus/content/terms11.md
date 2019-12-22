# 条款11：在operator=中处理“自我赋值”


自我赋值可能发生的时机：

```
Widget w; w = w;
a[i] = a[j];    //有可能i==j
*px = *py;      //px == py
```

## 方法：

假设建立一个class用来保存一个指针指向一块动态分配的位图(bitmap):

```
class Bitmap { ... };
class Widget {
    ...
private:
    Bitmap* pb;
};
```

- 版本一：不具备“自我赋值安全性”和“异常安全性”的版本
  ```
  Widget& Widget::operator=(const Widget& rhs) {
      delete pb;
      pb = new Bitmap(*rhs.pb);
      return *this;
  }
  ```
  
  不具备“自我赋值安全性”：如果rhs和*this是同一个对象，那么delete pb不止销毁当前对象的bitmap，它也销毁了rhs的bitmap

- 版本二：证同测试来具备“自我赋值安全性”
  ```
  Widget& Widget::operator=(const Widget& rhs) {
      if (this == &rhs) return *this;     //证同测试
          delete pb;
      pb = new Bitmap(*rhs.pb);
      return *this;
  }
  ```
  具备“自我赋值安全性”但不具备“异常安全性”：如果new Bitmap失败导致异常(内存不足或copy 构造函数抛出异常)，pb将指向一块删除的内存地址，这样的指针有害

- 版本三：让operator=具备“异常安全性”往往自动获得“自我赋值安全性的”回报，因此对“自我赋值”的态度是倾向于不去管它，把焦点放在实现“异常安全性”上
  ```
  Widget& Widget::operator=(const Widget& rhs) {
      Bitmap* pOrig = pb;
      pb = new Bitmap(*rhs.pb);
      delete pOrig;
      return *this;
  }
  ```

- 版本四：copy and swap手法
  ```
  void Widget::swap(Widget& rhs); //交换*this和rhs的数据
  Widget& Widget::operator=(const Widget& rhs) {
      Widget temp(rhs);
      swap(temp);
      return *this;
  }
  ```
