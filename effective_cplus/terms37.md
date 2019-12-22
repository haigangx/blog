# 条款37：绝不重新定义继承而来的缺省参数值

条款36已经说了，重新定义一个继承而来的non-virtual函数永远是错误的，所以本条款的讨论局限于“继承一个带有缺省参数值的virtual函数”

```
class Shape {
public:
  enum ShapeColor {Red, Green, Blue};
  virtual void draw(ShapeColor color = Red) const = 0;
};

class Rectangle : public Shape {
public:
  //重定义了缺省参数值，错误
  virtual void draw(ShapeColor color = Green) const,
};

class Circle : public Shape {
public:
  //
  virtual void draw(ShapeColor color) const;
};

```

```
Shape* ps;
Shape* pc = new Circle;
Shape* pr = new Rectangle;

pc->draw();
pr->draw();

Circle* pcc = new Circle;
Rectangle* prr = new Rectangle;

pcc->draw();
prr->draw();
```

上例中，pa，pc，pr都被声明为pointer-to-Shape类型，所以它们的 **静态类型** 都为Shape * ，所谓静态类型，就是对象在程序中被声明时的类型

对象的 **动态类型(dynamic type)** 是指目前所指对象类型，以上例来说，pc的动态类型为`Circle*`，pr的的动态类型为`Rectangle*`，ps没有动态类型

virtual函数系动态绑定而来，意思是调用一个virtual函数时，究竟调用哪一份函数实现代码，取决于发出调用的那个对象的动态类型，如下：
```
pc->draw(Shape::Red);  //调用Circle::draw(Shape::Red)
pr->draw(Shape::Red);  //调用Rectangle::draw(Shape::Red)
```

这些都是再平常不过的virtual函数的特性，但是，当考虑到带有缺省参数值的virtual函数时，由于virtual函数是动态绑定，而缺省参数值却是静态绑定，意思是你可能会在**调用一个定义于derived class内的virtual函数的同时，却使用base class为它所指定的缺省参数值**
```
pr->draw();   //调用Rectangle::draw(Shape::Red)
```

## 问题

上例中，pr的动态类型是Rectangle* ，调用的是Rectangle的virtual函数，从代码中看，Rectangle::draw函数的缺省参数值应该是GREEN，但由于pr的静态类型是Shape* ，所以 **此调用的缺省参数值来自于Shape class而不是Rectangle class** ，这个结果绝对出乎意料，而且这种情况不仅局限于指针，再reference下问题同样存在

C++之后会出现这种令人费解的运行结果，原因是为了保证运行期效率，C++使用虚表的结构保证了virtual函数动态绑定，这在一定程度上使得程序的执行速度变慢，而如果编译器使用某种方法也使得缺省参数值动态绑定，这将比目前的"在编译器决定"的机制更慢更复杂

## 解决方案

如果有时我们必须为某个virtual函数指定默认参数，同时又不想让derived class发生"重定义继承而来的的缺省参数值"，可以参考[条款35]()来考虑为virtual函数寻找一个替代设计

如可以采用NVI(non-virtual interface)手法：令base class内的一个public non-virtual函数调用private virtual函数，后者可被derived classes重新定义，例：
```
class Shape {
public:
    enum ShapeColor { Red, Green, Blue };
    //non-virtual
    void draw(ShapeColor color = Red) const
    {
        doDraw(color);  //调用virtual
    }
    ...
private:
    virtual void doDraw(ShapeColor color) const = 0;
};

class Rectangle : public Shape {
public:
    ...
private:
    //不须指定缺省参数值
    virtual void doDraw(ShapeColor color) const;
};
```
这个设计很清楚的使得draw函数的color缺省参数值总是为Red

