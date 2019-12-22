# 条款06：若不想使用编译器自动生成的函数，就该明确拒绝


不希望类支持copy构造函数和copy assignment操作符，则可以：

- 将copy构造函数和copy assignment声明为私有并且只定义不声明，只定义不声明是为了防止友元函数或者成员函数调用它(调用一个只定义未声明的函数会获得一个链接错误)

- 构造一个uncopyable类，然后将你不希望支持copy构造和copy assignment操作符的类继承于uncopyable类

  **原理：**
  uncopyable类的copy构造函数和copy assignment操作符声明为私有，编译器在调用一个“编译器版本”的copy构造函数和copy assignment操作符时，会尝试调用其base class的对应函数，这些调用会被拒绝

  ```
  class uncopyable {
  protected:
      uncopyable() {}
      ~uncopyable() {}
  private:
      uncopyable(const uncopyable&);
      uncopyable operator=(const uncopyable&);
  };
  ```
  参考：Boost库中的noncopyable
