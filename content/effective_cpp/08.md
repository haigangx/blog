# 条款08：别让异常逃离析构函数

## 为什么说“别让异常逃离析构函数”？

**让异常逃离析构函数可能使程序出现`过早结束`或`不明确行为`的风险**

```
class Widget {
public:
    ...
    ~Widget() { ... }   //假设这里可能产生一个异常
};
void doSomething() {
    std::vector<Widget> v;
    ...   //v在这里自动销毁，v中包含多个Widget
            //如果析构第一个Widget时发生异常，那么程序会过早结束，其余的Widget不会被释放
}
```

## 怎么做？

```
//这个class用来管理DBConnection对象
class DBConn {
public:
    ...
    ~DBConn() {   //确保数据库连接总是会被关闭
        db.close();  //调用close可能会发生异常
    }
private:
    DBConnection db;
};
```

- **析构函数可以捕捉异常，然后吞下它们（不传播）或结束程序**

  - close()抛出异常就使用abort()结束异常
  
    ```
    DBConn::~DBConn() {
        try { db.close(); }
        catch (...) {
            记录close调用失败
            std::abort();
        }
    }
    ```
    适用于异常对于程序是致命的，发生该异常程序将无法继续执行，强迫程序强制结束是比程序继续运行导致不明确行为更好的选择。
  
  - 吞下因调用close()而发生的异常
  
    ```
    DBConn::~DBConn() {
        try { db.close(); }
        catch (...) {
            记录close调用失败
        }
    }
    ```
    适用于发生该异常程序还是可以可靠的运行下去，好于程序“过早退出”或“发生不明确行为”

- **提供一个普通函数执行可能会发生异常的操作**

  一个更加好的策略是重新设计DBConn的接口，使其调用者有机会对可能出现的问题做出反应，
  例如DBConn自己可以提供一个close函数，调用者就有机会处理数据库关闭可能遇到的异常，
  如果调用者未主动调用close关闭数据库，说明调用者对于数据库关闭发生的异常并不感兴趣，
  所以关闭动作交给DBConn的析构函数并且使用上面两个方法处理可能发生的异常
  
  ```
  class DBConn {
  public:
      ...
      void close() {  //提供给调用者的新函数
          db.close();
          closed = true;
      }
      ~DBConn() {
          if (!closed) {
              try {
                  db.close();   //关闭连接(如果调用者未关闭的话)
              }
              catch (...) {
                  处理并记录close的调用失败
                  ...
              }
          }
      }
  private:
      DBConnection db;
      bool closed;
  };
  ```

**总结：**

- 析构函数绝对不要吐出异常。如果一个被析构函数调用的函数可能抛出异常，析构函数应该捕捉任何异常，然后吞下它们（不传播）或结束程序

- 如果客户需要对某个操作函数运行期间抛出的异常做出反应，那么class应该提供一个普通函数（而非在析构函数中）执行该操作
