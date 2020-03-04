# 条款27：尽量少做转型动作

**通常有三种不同的形式可以写出相同转型动作：**

- C风格的转型动作看起来像是这样：

  ```
  (T)expression     //将expression转型为T
  ```

- 函数风格的转型动作：

  ```
  T(expression)     //将expression转型为T
  ```

  这两种形式并无差别，纯粹只是小括号摆放位置不同而已，称此二种形式为"旧式转换"(old-style casts)

- C++提供四种新式转型(new-style or C++-style casts)

  ```
  const_cast<T>(expression)
  dynamic_casst<T>(expression)
  reinterpret_cast<T>(expression)
  static_cast<T>(expression)
  ```

  这四种转型各有其不同的用处：
  - const_cast被用来做对象的常量性移除。也是唯一有此能力的C++-style转型操作符

  - dynamic_casst主要用来执行"安全向下转型"(safe downcasting)，也就是用来决定某对象是否归属继承体系中的某个类型。唯一无法用旧式语法执行的动作，也是唯一可能耗费重大运行成本的转型动作

  - reinterpret_cast意图执行低级转型，实际动作可能取决于编译器，这也就表示它不可移植，例如将一个pointer to int转型为int，这一类转型在低级代码以外很少见

  - static_cast强迫隐式转换，例如将non-const对象转为const对象，或将int转换为double等。也可以用来执行上述多种转换的反向转换，例如将void*指针转为typed指针，将pointer-to-base转为pointer-to-derived，但它无法将const转为non-const——这个只有const_cast才能办到

  旧式转换仍旧合法，但是新式转换更受欢迎。原因：

  - 很容易在代码中辨识出来，因而得以简化“找出类型系统在哪个地点被破坏”的过程
  - 各转型动作的目标越窄化，编译器越可能诊断出错误的运用，举例：如果你打算将常量性去掉，除非使用新式转型中的const_cast否则无法编译

**Note:**

- **错误的观念：转型其实什么都没做，只是告诉编译器把某种类型看作另一种类型**

  任何一个类型转换(不论是通过转型操作而进行的显式转换，或通过编译器完成的隐式转换)往往真的令编译器编译出运行期间执行的代码。

  例1：

  ```
  int x, y;
  ...
  double d = static_cast<double>(x) / y;  //x除以y，使用浮点数乘法
  ```

  将int转型为double几乎肯定会产生一些代码，因为在大部分计算器体系结构种，int的底层描述不同于double的底层表述。

  例2：

  ```
  class Base { ... };
  class Derived : public Base { ... };
  Derived d;
  Base* pb = &d;      //隐式将Derived* 转换为Base*
  ```

  这里表面来看我们不过是建立一个base class指针指向一个derived class对象，但有时候上述的两个指针值并不相同。这种情况下会有一个偏移量(offset)在运行期间被施行于Derived*指针上，用以取得正确的Base*指针值

- **尽可能避免转型动作，转型容易导致我们写出某些似是而非的代码**

  例：

  ```
  class Window 
  {
  public:
      virtual void onResize() { ... }
      ...
  };
  class SpecialWindow : public Window
  {
  public:
      virtual void onResize()     //子类的onResize执行时要求先执行基类的onResize方法 
      {
          static_cast<Window>(*this).onResize();  //企图将this指针转换为Window来调用onResize，这不可行
          ...
      }
      ...
  };
  ```

  上述代码的预期行为是：将*this转型为Window，对函数onResize的调用也因此调用了Window::onResize()。
  但是，这恰恰带来了问题static_cast<Window>(*this)的行为与预想的不同，这个转型等价于Window(*this)，
  这相当于调用Window基类的拷贝构造函数生成了一个基类的临时对象，对这个临时对象调用onResize函数，
  而并非对this指针指向的对象身上执行基类的onResize操作

  解决办法就是拿掉转型操作，代之以你真正想说的话

- **注重效率的代码中避免使用dynamic_cast**

  dynamic_cast的许多实现版本执行速度非常慢。通常你之所以要使用dynamic_cast，是因为你想在一个你认定为derived class对象
  身上执行derived class操作函数，但你的手上却只有一个“指向base”的pointer或reference，你只能靠它们来处理对象

  有两个办法可以解决这种情况来代替使用dynamic_cast：

  - 使用容器并在其中存储直接指向derived class对象的指针(如智能指针)

    例：

    ```
    //错误的做法
    class Window { ... };
    class SpecialWindow : public Window 
    {
    public:
        void blink();
        ...
    };
    typedef std::vector<std::tr1::shared_ptr<Window> > VPW;
    VPW winPtrs;
    ...
    for (VPW::iterator iter = winPtrs.begin(); iter != winPtrs.end(); ++iter)
    {
        if (SpecialWindow* psw = dynamic_casst<SpecialWindow>(iter->get()))
            psw->blink();
    }
    ```

    ```
    //正确的写法：
    typedef std::vector<std::tr1::shared_ptr<SpecialWindow> > VPSW;
    VPSW winPtrs;
    ...
    for (VPSW::iterator iter = winPtrs.begin(); iter != winPtrs.end(); ++iter)
        (*iter)->blink();
    ```

  - 另一种做法可让你通过base class接口处理"所有可能之各种Window派生类"，那就是在base class内提供virtual函数做你想对各个Window派生类做的事。

    例：

    ```
    class Window
    {
    public:
        virtual void blink() {  }
        ...
    };
    class SpecialWindow : public Window
    {
    public:
        virtual void blink() { ... }
        ...
    };
    typedef std::vector<std::tr1::shared_ptr<Window> > VPW;
    VPW winPtrs;
    ...
    for (VPSW::iterator iter = winPtrs.begin(); iter != winPtrs.end(); ++iter)
        (*iter)->blink();
    ```

    绝对避免所谓的“连串dynamic_cast”，如：

    ```
    class Window { ... };
    typedef std::vector<std::tr1::shared_ptr<Window> > VPW;
    VPW winPtrs;
    ...
    for (VPSW::iterator iter = winPtrs.begin(); iter != winPtrs.end(); ++iter)
    {
        if (SpecialWindow1 *psw1 = dynamic_casst<SpecialWindow1*>(iter->get())) 
        { ... }
        else if (SpecialWindow1 *psw1 = dynamic_casst<SpecialWindow1*>(iter->get())) 
        { ... }
        else if (SpecialWindow1 *psw1 = dynamic_casst<SpecialWindow1*>(iter->get())) 
        { ... }
        ...
    }
    ```

    这样产生的代码又大又慢，而且基础不稳。

**Remember：**

  优良的C++代码很少使用转型
