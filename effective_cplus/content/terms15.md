# 条款15：在资源管理类中提供对原始资源的访问

  使用资源管理类如智能指针管理指针时，常常需要直接访问原始资源，这时候需要一个函数将资源管理对象转换为其所内含的原始资源，
有两种做法达到此目的： **显式转换** 和 **隐式转换**

## 以智能指针为例：

- **显式转换：** tr1::shared_ptr和auto_ptr中都提供get函数来返回智能指针内部的原始指针

  缺点：每次需要原始指针时都需要调用API接口，频繁的调用是一个不太友好的设计
  
  例：类Font为一个资源管理类，其中的原始资源为FontHandle类
  
  ```
  class Font {
  public:
      explicit Font(FontHandle fh) : f(fh) {}     //获得资源
      ~Font() { releaseFont(f); }     //释放资源
  private:
      FontHandle f;
  };
  为Font添加一个get函数来提供显式转换：
  class Font {
  public:
      ...
      FontHandle get() const { return f; }    //显式转换函数
      ...
  };
  ```
  
- **隐式转换：** 在资源管理类中提供与底层原始资源对应的类型转换函数
  
  例：为Font类添加一个FontHandle转换函数
  
  ```
  class Font {
  public:
      ...
      operator FontHandle() const { return f; }   //隐式转换函数
      ...
  };
  ```
  
  优点：相对于显式转换使用起来更加自然
  
  缺点：隐式转换可能在不被期望发生的情况下发生，而且很难察觉到，如下：
  
  ```
  FontHandle getFont() { return FontHandle(); }
  Font f1( getFont() );
  ...
  FontHandle f2 = f1;     //原意是要拷贝一个Font对象，现在反而先将f1隐式转换为FontHandle然后才复制它
  ```
  
## 选择：

选择 **显式转换函数** 还是 **隐式转换函数** 取决于该资源管理类被设计执行的特定工作，以及它被使用的情况：
    
- 接口的一个设计理念是“使接口更容易被正确使用，而不容易被误用”，从这个角度而言，显式转换是一个更好的选择；

- 然而，如果从使用起来更加自然友好，那么隐式转换是一个更好的选择

## 总结：

显式转换更安全，隐式转换更方便
