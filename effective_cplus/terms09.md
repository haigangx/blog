# 条款09：绝不在构造和析构过程中调用virtual函数

```
class Transaction {
public:
    Transaction() {
        ...
        logTransaction();
    }
    virtual void logTransaction() const = 0;
    ...
};
class BuyTransaction : public Transaction {
public:
    virtual void logTransaction() const {...}
    ...
};
class SellTransaction : public Transaction {
public:
    virtual void logTransaction() const {...}
    ...
};

BuyTransaction b;
```

写出上面代码的本意是希望**构造b的时候，在父类Transaction的构造函数中调用BuyTransaction版本的logTransaction函数**

然而，事与愿违，因为此时在基类中调用的logTransaction函数并非BuyTransaction版本，而是父类版本中的，
而父类中的logTransaction只有声明没有定义，所以会引发类似“对象未初始化”的错误

显然，通过上面的例子我们了解到**base classes构造期间，virtual函数绝不会下降到derived classes阶层**

原因：

  - 一个好的理由是由于base class构造函数的执行更早于derived class构造函数，当base class构造函数执行时derived class的成员变量尚未初始化，
  如果此期间调用的virtual函数下降至derived classes阶层，要知道derived class的函数几乎必然取用local成员变量，而那些成员变量尚未初始化，
  这将会引起“要求使用对象内部尚未初始化的成分”的错误
  - 更根本的原因：在derived class对象的base class构造期间，对象的类型是base class而不是derived class。
  不只是virtual函数会被编译器解析至(resolve to)base class，若使用运行期类型信息(runtime type information,例如dynamic_cast和typeid)，
  也会把对象视为base class类型。
     
    本例中，当Transaction构造函数正执行起来打算初始化"BuyTransaction对象内的base class成分"时，该对象的类型是Transaction。
    那是一个c++次成分(条款01)的态度，这样对待是合理的：这个对象内的"BuyTransaction专属成分"尚未被初始化，
    所以面对它们，最安全的做法就是视它们不存在，对象在derived class构造函数开始执行前不会成为一个derived class对象。

同样的道理也适用于析构函数：**一旦derived class析构函数开始执行，对象内的derived class成员变量便呈现未定义值，所以C++视它们仿佛不再存在。
进入base class析构函数后对象就成为一个base class对象，而C++的任何部分包括virtual函数、dynamic_casts等等也就那么看待它。**

确保避免程序在构造函数中直接或者间接调用virtual函数(间接调用例如：在构造函数中调用init函数，init函数为non-virtual函数，init函数中调用virtual函数logTransaction()，这种情况下编译器无法察觉)

问题：
  ***如何避免在构造函数中调用virtual函数并且确保每次一有Transaction继承体系上的对象被创建时，就会有适当版本的logTransaction被调用？***

**可行的方案：**
在class Transaction内将logTransaction函数改为non-virtual，然后要求derived class构造函数传递必要信息给Transaction构造函数，而后那个构造函数便可安全的调用non-virtua logTransaction
