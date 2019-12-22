# 条款07：为多态基类声明virtual析构函数

**问题：**

```
class Base{
public:
    Base();
    ~Base();
};
class Derived : public Base { ... };

Base *ptk = new Derived();
delete ptk;
```

如上所示，delete ptk会导致程序只调用Base的析构函数，导致Derived部分占用的内存泄漏

**解决：**

- polymorphic(带多态性质的) base classes应该声明一个virtual析构函数。如果class带有任何virtual函数，它就应该拥有一个virtual析构函数

- classes的设计目的如果不是作为base classes使用，或不是为了具备多态性(polymorphically)，就不该声明virtual析构函数

**Note：** 针对上述的第二点，滥用virtual析构函数可能会导致类的size变大，因为使用virtual函数会导致类中多出来虚表和虚指针

**其他：**

- 有时候你希望拥有抽象class，但手上又没有任何pure virtual函数，可以为该抽象class声明一个pure virtual析构函数，但是你同时还必须为这个pure virtual析构函数提供一份定义。
因为析构函数的运作方式是，最深层派生的那个class其析构函数最先被调用，然后其每一个base class的析构函数被调用。
  ```
  class AbstractClass {
  public:
      virtual ~AbstractClass() = 0;
  }
  AbstractClass::~AbstractClass() {}  //析构函数的定义
  ```
  
- 当你企图继承所有STL容器如vector, list, set, tr1::unordered_map等或任何其他“带有non-virtual析构函数”的class时，放弃吧，因为当调用析构函数会导致一些不明确的行为。
