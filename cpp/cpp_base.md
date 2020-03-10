# C++基础

## C

<details>
<summary>可变参函数</summary>

# 可变参数函数

可变参数函数是指一个函数拥有不定引数，即是它接受一个可变数目的参数

## 可变参函数编写

在C语言中，C标准函式库的`stdarg.h`标头档定义了提供可变参数函数使用的宏。在C++，应该使用标头档`cstdarg`。

要创建一个可变参数函数，必须把省略号（...）放到参数列表后面。函数内部必须定义一个`va_list`变量。然后使用宏`va_start`、`va_arg`和`va_end`来读取

- va_list，用来接受"..."代表的全部参数。
- va_start(va_list, type)：初始化va_list声明的变量。type可以是int，也可以是char等类型。
- va_arg(va_list, returnType)：参数1是va_list声明的变量，参数2是从参数1中获取到的类型，即是"..."传入的类型。并且是指针指向va_list的下一个数据。
- va_end(va_list)：清空va_list变量，使得指针不可用，和va_start配对使用。

[参考教程](https://blog.csdn.net/qq_16628781/article/details/72717008)

</details>

<details>
<summary>C的预处理</summary>

# C的预处理

[菜鸟教程-C预处理器](https://www.runoob.com/cprogramming/c-preprocessors.html)

</details>

<details>
<summary>C语言switch case语句中定义变量问题</summary>

# C语言switch case语句中定义变量问题

这个问题需要分开讨论，C 语言和 C++ 的标准定义是不同的。

## 1. C++

```
int Caset(int a) {
    switch (a) {
        case 1:
            int b = 1;
            std::cout<<"a==1: "<<b<<std::endl;
            break;
        case 2:
            b = 2;
            std::cout<<"a==2: "<<b<<std::endl;
            break;
    }
}
```
编译报错信息为

```
simple.cc:35:9: error: cannot jump from switch statement to this case label
      case 2:
      ^
simple.cc:32:17: note: jump bypasses variable initialization
          int b = 1;
              ^
```

也就是说，跳到 case2 的这个地方，忽略了对于 b 这个变量的初始化，这个很直观，就是在这里我找不到 b。

那么如果改成

```
int Caset(int a) {
    switch (a) {
        case 1:
            int b;
            b = 1;
            std::cout<<"a==1: "<<b<<std::endl;
            break;
        case 2:
            b = 2;
            std::cout<<"a==2: "<<b<<std::endl;
            break;
    }
}
```

顺利成功，没有报错，如果 a 为 2，那么输出 b 也是 2，说明逻辑没有问题。那么问题来了，b 在前面声明，为什么后面可以用到呢，
因为 switch-case 的逻辑控制就是用 label 来标记跳转的，而不是别的复杂的逻辑控制，所以 b 的作用域是在整个 switch 的花括号内，
关于这个问题见知乎讨论[请教switch内部的变量定义问题](https://www.zhihu.com/question/23051685)

## 2. C语言

上面两种写法统统出错，
```
void Caset(int a) {
    switch (a) {
        case 1:
            /* one style */
            int b;
            b = 1;
            
            /* another style */
            int b = 1;

            printf("1: %d", b);
            break;
        case 2:
            b = 2;
            printf("2: %d", b);
            break;
    }
}
```

两种写法都错，报错信息：

```
	main.c:12:13: error: expected expression
        int b; 
        ^
	main.c:13:13: error: use of undeclared identifier 'b'
        b = 1;
        ^
```

意思是说，此处需要一个表达式（expression），而不是一个变量声明初始化。有一个很黑客的做法，如下：

```
void Caset(int a) {
    switch (a) {
        case 1:
            ; 
            int b = 1;
            // b = 1;

            printf("1: %d \n", b);
            break;
        case 2:
            b = 2;
            printf("2: %d \n", b);
            break;
    }
}
```

这个很不能理解了，其实也就是说保证 case 后面跟着的确实是 expression 即可。考虑一下 C++ 代码出现的问题：跳过变量的声明？C 语言中同样跳过，
但是编译器不认为这个是错误，而且逻辑上面也是没有问题的，在后面的 case 中可以正常给变量赋值，但是如果 case2 中，我不是给 b 赋值，
而是直接访问 b，那返回的数值就是一个随机的错误的数据了，我在我的电脑上使用 gcc 编译，若直接读取数据，得到的是 0，当然编译通过，连警告都没有。

当然我认为这样的代码可读性差，比较好的做法可以是将声明变量的事情放在头上做

```
void Caset(int a) {
    switch (a) {
        int b;
        case 1:
            b = 1;
            // b = 1;
            printf("1: %d \n", b);
            break;
        case 2:
            b = 2;
            printf("2: %d \n", b);
            break;
    }
}
```

但是要留心， switch 和 case 之前那块地方也就只能写写这样的声明，写别的表达式，赋值啊什么的，统统是不会生效的。

</details>

<details>
<summary>宏中使用do{}while(0)的好处</summary>

[参考](https://blog.csdn.net/jk110333/article/details/8562078)

</details>


## C++

<details>
<summary>智能指针</summary>

# 智能指针

## shared_ptr

### 初始化：

当创建智能指针时，必须提供额外的信息——指针可以指向的类型：

#### shared_ptr的几个正确初始化方式：

- shared_ ptr<string> p1;      //p1使用默认初始化，保存一个NULL指针

-  shared_ptr<string> p2(new string("hello")); //使用new返回的指针初始化智能指针

- 智能指针接受指针参数的构造函数是explicit的，所以不能将一个内置指针隐式转换为智能指针

  如：
  ```
  shared_ptr<string> p3 = new string("hello");    //错误的初始化方式
  基于同样的原因：一个返回shared_ptr的函数不能在其返回语句中隐式转换一个普通指针，如：
  share_ptr<int> clone(int p) {
      return new int(p);      //必须使用return shared_ptr<int>(new int(p));
  }

  ```

### 自定义删除器：

默认情况下：一个用来初始化智能指针的普通指针必须指向动态内存，因为智能指针默认使用delete释放它所关联的对象

我们可以将智能指针绑定到一个指向其他类型的资源的指针上，但是为了这样做，必须提供自己的操作来替delete

例：

```
struct struct_s
{
    int i;
};
void delete_struct(struct_s* p)
{
    printf("the deleter\n");
    free(p);
    p = NULL;
}
int main()
{
    struct_s* t = (struct_s*)malloc( sizeof(struct_s) );
    shared_ptr<struct_s> sp(t, delete_struct);
    return 0;
}
```

shared_ptr常用操作：

- p：将p用作一个条件判断，若p指向一个对象，则为true

- *p：解引用p，获得它指向的对象

- p->mem：等价于(*p).mem

- p.get()：返回p中保存的指针，尽量避免直接使用指针

- swap(p, q)：交换p和q中的指针，等价于p.swap(q)

- make_shared<T>(args)：返回一个shared_ptr，指向一个动态分配的类型为T的对象。使用arg初始化此对象，通常使用auto定义一个对象来保存make_shared的结果

- shared_ptr<T>p(q)：shared_ptr的拷贝构造函数，会递增q中的计数器

- p = q：shared_ptr的赋值操作函数，赋值会递减p的计数器，同时递增q的计数器

- p.unique()：若p.use_count()为1，返回true；否则返回false

- p.use_count()：返回p的引用计数

shared_ptr的析构函数会递减它所指的对象的引用计数。如果引用计数变为0，shared_ptr的析构函数就会销毁对象并释放它占用的内存

使用智能指针可以保证即使程序发生异常，资源也能被正常释放，因为即使发生异常局部对象也会被销毁

程序使用动态内存的三种原因：

- 程序不知道自己需要使用多少对象
- 程序不知道所需对象的准确类型
- 程序需要在多个对象间共享数据


智能指针陷阱：

* 不使用相同的内置指针值初始化(或reset)多个智能指针
* 不delete get()返回的指针
* 不使用get初始化或reset另一个智能指针
* 如果你使用get()返回的指针，记住当前最后一个对应的智能指针销毁后，你的指针就变得无效了
* 如果你使用智能指针管理的资源不是new分配的内存，记住传递给它一个删除器

## unique_ptr

unique_ptr拥有它所指向的对象，同一时刻只能有一个unique_ptr指向一个给定对象，当unique_ptr被销毁时，它所指向的对象也被销毁

* 和shared_ptr一样，初始化unique_ptr必须采用直接初始化方式：
    ```
    unique_ptr<double> p1;  //指向一个double的unique_ptr
    unique_ptr<int> p2(new int(42));    //p2指向一个值为42的int
    ```

* unique_ptr不支持普通的拷贝或赋值操作：

    ```
    unique_ptr<string> p1(new string("helloworld"));
    unique_ptr<string> p2(p1);      //错误：unique_ptr不支持拷贝
    unique_ptr<string> p3;
    p3 = p2;        //错误：unique_ptr不支持赋值
    ```

* 可以通过release接口或reset接口将指针的所有权从一个(非const)unique_ptr转移给另一个unique
    ```
    //将所有权从p1转移给p2
    unique_ptr<string> p2(p1.release());    //release将p1置空
    unique_ptr<string> p3(new string("Trex"));
    //将所有权从p3转移给p2
    p2.reset(p3.release());     //reset释放了p2原来指向的内存
    ```

* 传递unique_ptr参数和返回unique_ptr

    不能拷贝unique_ptr的规则有一个例外：我们可以拷贝或赋值一个将要被销毁的unique_ptr，如：
    ```
    unique_ptr<int> clone(int p)
    {
        //正确
        return unique_ptr<int>(new int(p));
    }
    还可以返回一个局部对象的拷贝：
    unique_ptr<int> clone(int p)
    {
        unique_ptr<int> ret(new int(p));
        //...
        return ret;
    }
    ```

* 向unique_ptr传递删除器

    和shared_ptr传递删除器不同，unique_ptr必须再尖括号中unique_ptr指向类型之后提供删除器类型，如：
    ```
    //p指向一个类型为objT的对象，并使用一个类型为delT的对象释放objT对象
    //它会调用一个名为fcn的delT类型对象
    unique_ptr<objT, delT> p(new objT, fcn);
    ```

## weak_ptr

weak_ptr指向由一个shared_ptr管理的对象，将一个weak_ptr绑定到一个shared_ptr不会改变shared_ptr的引用计数，即使有weak_ptr指向对象，对象也还是会被释放

weak_ptr支持的操作：

- weak_ptr<T> w           空weak_ptr可以指向类型为T的对象

- weak_ptr<T> w(sp)       与shared_ptr sp指向相同对象的weak_ptr。T必须能转换为sp指向的类型

- w = p                   p可以是一个shared_ptr或一个weak_ptr。赋值后w与p共享对象

- w.reset()               将w置空

- w.use_count()           与w共享对象的shared_ptr的数量

- w.expired()             若w.use_count()为0，返回true，否则返回false

- w.lock()                如果expired为true，返回一个空shared_ptr；否则返回一个指向w的对象的shared_ptr


创建一个weak_ptr时，需要用一个shared_ptr来初始化它：

```
auto p = make_shared<int>(42);
weak_ptr<int> wp(p);    //wp弱共享p；p的引用计数未改变
lock()：此函数检查weak_ptr指向的对象是否仍存在，如果存在，lock返回一个指向共享对象的shared_ptr
if ( shared_ptr<int> np = wp.lock() )
{
    //只有lock调用为true时才会进入if语句体,在if中，使用np访问共享对象是安全的
}
```

</details>

<details>
<summary>operator new、operator new[]、operator delete、operator delete[]、placement new</summary>

# operator new、operator new[]、operator delete、operator delete[]、placement new

## new表达式和delete表达式的行为：

- **当我们使用一条new表达式时，实际执行了三步操作：**

  ```
  //new表达式
  string *sp = new string("a value"); //分配并初始化一个string对象
  string *arr = new string[10];       //分配10个默认初始化的string对象
  ```

  - new表达式调用一个名为operator new(或者operator new[])的标准库函数。该函数负责分配一块足够大的、原始的、
    未命名的内存空间以便存储特定类型的对象(或对象数组)

  - 编译器运行相应的构造函数以构造这些对象，并为其传入初始值

  - 对象被分配了空间并构造完成，返回一个指向该对象的指针

- **当我们使用一条delete表达式删除一个动态分配的对象时，实际执行了两步操作：**

  ```
  delete sp;      //销毁*sp，然后释放sp指向的内存空间
  delete [] arr;  //销毁数组中的元素，然后释放对应的内存空间
  ```

  - 对sp所指对象或者arr所指的数组中的元素执行对应的析构函数

  - 编译器调用名为operator delete(或operator delete[])的标准库函数释放内存空间

- **我们可以自定义operator new和operator delete这两个函数的行为，但是无法定义new表达式和delete表达式的行为**

  如果用户希望自己控制内存分配的过程，则需要自定义自己的 **operator new函数** 和 **operator delete函数**

  应用程序可以在全局作用域中定义operator new函数和operator delete函数，也可以将它们定义为成员函数，用户查找可供调用的operator函数的规则是：

  - 如果被分配(释放)的对象是类类型，则编译器首先在类及其基类的作用域中查找

  - 否则，编译器在全局作用域查找匹配的函数，

  如果编译器找到了用户自定义的版本，则使用该版本执行new表达式或delete表达式；如果没找到，则使用标准库定义的版本

  可以使用作用域运算符令new表达式或delete表达式忽略定义在类中的函数，直接执行全局作用域中的版本，例如：
  ::new只在全局作用域中查找匹配的operator new函数，::delete也一样

  标准库中operator new函数和operator delete函数的8个重载版本：

  ```
  //这些版本可能抛出异常
  void *operator new(size_t);                 //分配一个对象
  void *operator new[](size_t);              //分配一个数组
  void *operator delete(void*) noexcept;      //释放一个对象
  void *operator delete[](void*) noexcept;   //释放一个数组
  ```

  ```
  //这些版本承认不会抛出异常
  void *operator new(size_t, nothrow_t&) noexcept;
  void *operator new[](size_t, nothrow_t&) noexcept;
  void *operator delete(void*, nothrow_t&) noexcept;
  void *operator delete[](void*, nothrow_t&) noexcept;
  ```

  - 类型nothrow_t是定义在new头文件中的一个struct，在这个类型中不包含任何成员，用户通过这个对象来请求new的非抛出版本

  - 当将上述运算符函数定义为类成员时，它们是隐式静态的，无须显式声明static，因为operator new用在对象构造之前
    而operator delete用在对象销毁之后，所以这两个成员(new和delete)必须是静态的，而且它们不能操纵类的任何数据成员

  **自定义的operator new和operator delete的一种简单方式：**

  ```
  //使用malloc和free开辟释放空间
  void *operator new(size_t size)
  {
      if (void *mem = malloc(size))
          return mem;
      else
          throw bad_alloc();
  }
  void operator delete(void *mem) noexcept 
  {
      free(mem);
  }
  ```

## 定位new表达式：

- **定位new允许我们在一个特定的、预先分配的内存地址上构造对象**

  ```
  new (place_address) type
  new (place_address) type (initializers)
  new (place_address) type [size]
  new (place_address) type [size] {braced initializer list}
  ```

  - place_address必须为一个指针
  - initializers中提供一个(可能为空)的以逗号分隔的初始值列表，该初始值用于构造新分配的对象

- **显式的析构函数调用：**

  例：

  ```
  string *sp = new string("a value");     //分配并初始化一个string对象
  sp->~string();      //显式调用析构函数
  ```

  调用析构函数可以清楚给定的对象但是不会释放该对象所在的空间。如果需要的话，我们可以重新使用该空间

</details>

<details>
<summary>函数返回数组指针类型</summary>

# 函数返回数组指针类型

- **数组指针**

  ```
  int arr[10];        //arr是一个含有10个整数的数组
  int *p1[10];        //p1是一个含有10个指针的数组
  int (*p1)[10];      //*p1是一个含有10个整数的数组，p1是指向该数组的指针
  ```

  以此类推，如果函数func的返回值是一个指针p，p指向的是一个含有10个整数的数组，则func的声明如下：

  ```
  int ( *func(int i) )[10];
  ```

- **类型别名**

  ```
  typedef int arrT[10];   //arrT是类型别名，它表示的类型是含有10个整数的数组
  using arrT = int[10];   //arrT的等价声明，C++11新用法
  arrT* func(int i);      //func返回一个指向含有10个整数的数组的指针
  ```

- **C++11尾置返回类型**

  ```
  auto func(int i) -> int(*)[10]; //func接受一个int类型的实参，返回一个指针，该指针指向含有10个整数的数组
  ```

  将函数的返回类型放在形参列表之后，并在本该出现返回类型的地方放置一个auto

  关于C++11尾置返回类型的更多信息参考 [C++11/尾置返回类型](../C%2B%2B11/%E5%B0%BE%E7%BD%AE%E8%BF%94%E5%9B%9E%E7%B1%BB%E5%9E%8B.md)

</details>

<details>
<summary>extern关键字</summary>

</details>

<details>
<summary>移植C/C++</summary>

# 移植C/C++

### itoa移植到Linux

```
char *  itoa ( int value, char * str, int base );
```
base代表进制，可取2、6、10等

```
sprintf(str,"%d",value) converts to decimal base.
sprintf(str,"%x",value) converts to hexadecimal base.
sprintf(str,"%o",value) converts to octal base.
```

### __int64

```
#include <inttypes.h>
typedef int64_t __int64;
```

[移植c/c++代码](https://www.ibm.com/developerworks/cn/aix/library/au-porting/index.html)

</details>

<details>
<summary>nullptr和NULL</summary>

# nullptr和NULL

[知乎：为什么建议你用nullptr而不是NULL](https://zhuanlan.zhihu.com/p/79883965)

</details>

<details>
<summary>枚举类型前置声明</summary>

# 前向声明枚举类型enum

https://cloud.tencent.com/developer/ask/51491

</details>


## C++11

<details>
<summary>auto类型说明符</summary>

# auto类型说明符

- auto让编译器通过初始值来推算变量的类型，所以 **auto定义的变量必须有初始值**

- **auto一般会忽略顶层const，同时底层const被保留下来**

  - 顶层const：指针本身是个常量

  - 底层const：指针所指对象是个常量

- **如果希望推断出来auto类型是一个顶层const，则需要明确指出：**

  ```
  const auto f = ci;  //ci的推演类型为int，f是const int
  ```

- **可以将引用类型设为auto：**

  ```
  auto &g = ci;
  auto &h = 42;   //错误，不能为非常量绑定字面值
  const auto &h = 42; //正确，为常量引用绑定字面值
  ```

- **要在一条语句中定义多个变量，切记，符号&和*只从属于某个声明符，而非基本数据类型的一部分，并且初始值必须是同一类型**

</details>

<details>
<summary>lamdba表达式</summary>

# lambda表达式

**可调用对象：** 对于一个对象或表达式，如果可以对其使用调用运算符()，则称它为可调用的

目前为止，一共有四种可调用对象：

- 函数 
- 函数指针 
- 重载了函数调用运算符的类(仿函数) 
- lambda表达式

lambda表达式表示一个可调用的代码单元，可以理解为一个未命名的内联函数：

与普通函数类似，lambda表达式具有一个返回类型(必须是尾置返回类型)、一个参数列表、一个函数体，形式如下：

```
[capture list](parameter list) -> return type {function body};
```

实例：

```
auto f = [] {return 42;}
```

## lambda的理解：

- 当定义一个lambda时，编译器生成一个与lambda对应的新的(未命名的)类类型

- 可以将lambda作为一个函数参数传递，可以这样理解，当向一个函数传递一个lambda时，同时定义了一个新类型和该类型的一个对象：
  传递的参数就是编译器生成的该类类型的未命名对象

- 类似的，当使用auto定义一个用lambda初始化的变量时，定义了一个从lambda生成的类型的对象

- 默认情况下，捕获列表中的变量都被从lambda生成的类包含到了其数据成员中，类似于普通类的数据成员，lambda的数据成员也在lambda对象创建时被初始化

- 可以忽略参数列表和返回类型，但必须永远包含捕获列表和函数体

## 要素：

- **捕获列表(capture list)：**

  lambda通过将所在函数的局部变量包含在捕获列表中来指出将会使用这些变量

  一个lambda只有在其捕获列表中捕获一个它所在函数中的局部变量，才能在函数体中使用这些变量

  - 空捕获列表[]：表示此lambda不实用它所在函数中的任何局部变量

  - 值捕获：被捕获的变量的值是在lambda创建时拷贝，而不是调用时拷贝，因此随后对该变量的修改不会影响到lambda内对应的值
    
    ```
    void fcn1() {
        size_t v1 = 42; //函数fcn1内的局部变量
        auto f = [v1] {return v1;}; //捕获v1，将v1拷贝到名为f的可调用对象  f.v1 = v1
        v1 = 0;
        auto j = f();  //j为42，f保存了我们创建它是v1的值
    }
    ```

  - 引用捕获：
    
    ```
    void fcn2() {
        size_t v1 = 42; //局部变量
        auto f2 = [&v1] {return v1;};   //对象f2包含v1的引用  f.v1 = &v1;
        v1 = 0;
        auto j = f2();  //j为0
    }
    ```
    
    **Note：** 如果采用引用方式捕获一个变量，就必须确保被引用的对象在lambda执行的时候是存在的

  - 隐式捕获：让编译器根据lambda体中的代码来推断我们要使用哪些变量
    
    在捕获列表中写一个&或=指示编译器推断捕获列表：
    
    - &告诉编译器采用捕获引用方式
    - =表示采用值捕获方式

  - 混合使用隐式捕获和显式捕获
    
    当混合使用隐式捕获和显式捕获时，捕获列表的第一个元素必须是&或=，此符号指定了默认捕获方式为引用或值，
    跟随&或=的显式捕获列表中的变量必须使用与隐式捕获不同的方式。即：
    
    - `[&, identifier_list]`：如果隐式捕获采用引用方式(&)，则显式捕获命令变量indntifier_list必须采用值方式，因此变量名字前不能使用&。
    - `[=, identifier_list]`：如果隐式捕获采用的是值方式(=)，则显式捕获命令变量indentifier_list必须采用引用方式，因此变量名字前使用&

  - 可变lambda
  
    默认情况下，对于一个值被拷贝的变量，lambda不会改变其值，如果我们希望能改变一个捕获变量的值，就必须在参数列表后加上关键字mutable，
    因此可变lambda不能省略参数列表：
    
    ```
    void fcn3() {
        size_t v1 = 42;
        auto f = [v1] () mutable {return ++v1;};
        v1 = 0;
        auto j = f();   //j为43
    }
    ```
    
    一个引用捕获的变量是否可以修改依赖于此引用指向的是一个const类型还是非const类型：
    
    ```
    void fcn4() {
        size_t v1 = 42; //v1为非const变量
        auto f2 = [&v1] {return ++v1;};
        v1 = 0;
        auto j = f2();  //j为1
    }
    ```

- **return type：**

  返回类型必须使用尾置返回类型(C++/C++11/尾置返回类型)

  如果忽略返回类型，lambda根据函数体中的代码推断出返回类型：

  - 如果函数体中只有一条return语句，则返回类型从返回的表达式类型推断而来
  - 如果lambda体包含return之外的任何语句，则编译器假定此lambda返回void

  例子：

  函数f返回i的绝对值：

  - 只有一条return语句，无需指定lambda的返回类型，可以通过条件运算符的类型推断出来

    ```
    auto f = [](int i) { return i < 0 ? -i : i; };  
    ```

  - 将条件表达式写成等价的if语句，就会产生编译错误

    ```
    auto f = [](int i) { 
        if (i < 0)
            return -i;  
        else
            return i; 
    }   //产生编译错误
    ```

    这时需要使用尾置返回类型为lambda定义返回类型：

    ```
    auto f = [](int i) -> int { 
        if (i < 0)
            return -i;  
        else
            return i; 
    } 
    ```

- **parameter list：**

  lambda不能使用默认参数，一个lambda调用的实参数目永远与形参数目相等

- **function body和普通函数相同**

</details>

<details>
<summary>使用using进行别名声明</summary>

# 使用using进行别名声明(alias declaration)

```
typedef double wages;    //wages是double的同义词，要用double的地方都可以使用wages
using wages = double;    //使用using定义别名，wages也是double的同义词
```
</details>

<details>
<summary>范围for语句</summary>

# 范围for语句

遍历容器或其他序列的所有元素，范围for语句(range of statement)的 **语法形式** 是：

```
for (declaration : expression)
    statement
```

- **expression** 必须为一个序列，如初始值列表{"12", "fdsa", "qwer"}、数组或者vector、string等类型的对象，
  这些类型的共同点是能返回迭代器的begin和end成员

- **declaration** 定义一个变量，序列中的每个元素都得能转换成该变量的类型，可以使用auto类型说明符

例子：

```
vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

//如果要对序列中的元素进行写操作，可以将范围变量声明为引用类型
for (auto &r : v)
    r *= 2;
```

范围for语句的定义来源于与之等价的传统for语句：

```
for (auto beg = v.begin(), end = v.end(); beg != end; ++beg)
{
    auto &r = *beg;
    r *= 2;
}
```

**!!Note：**

  范围for语句中不能增加vector对象(或其他容器)的元素，因为在范围for语句中，预存了end()的值。
  一旦在序列中添加(删除)元素，end函数的值就可能变得无效了 **(迭代器失效)**

</details>

<details>
<summary>尾置返回类型</summary>

</details>

<details>
<summary>random获取随机值</summary>

# Random获取随机值

[参考](https://www.jianshu.com/p/05863a00af8d)

</details>

<details>
<summary>std::move()</summary>

</details>

<details>
<summary>std::mutex</summary>

https://en.cppreference.com/w/cpp/thread/mutex

</details>

<details>
<summary>使用std::unique_lock和std::lock_guard管理std::mutex</summary>

# 使用std::unique_lock和std::lock_guard管理std::mutex

[参考](https://www.cnblogs.com/fnlingnzb-learner/p/9542183.html)

</details>

<details>
<summary>std::thread</summary>

</details>

## C++20(可能有的特性)

<details>
<summary>反射</summary>

</details>


## 常用API

<details>
<summary>C++ to_string函数</summary>

# to_string()

- **函数原型：**

  ```
  string to_string (int val);
  string to_string (long val);
  string to_string (long long val);
  string to_string (unsigned val);
  string to_string (unsigned long val);
  string to_string (unsigned long long val);
  string to_string (float val);
  string to_string (double val);
  string to_string (long double val);
  ```

- **功能：**

  将数值转化为字符串。返回对应的字符串。

- **例子：**

  ```
  #include <iostream>   
  #include <string>     
  using namespace std;

  int main()
  {
      string pi = "pi is " + std::to_string(3.1415926);
      string perfect = to_string(1 + 2 + 4 + 7 + 14) + " is a perfect number";
      cout << pi << '\n';
      cout << perfect << '\n';
      return 0;
  }
  ```

</details>

<details>
<summary>向上取整floor和向下取整ceil</summary>

# floor()和ceil()

- **向下取整：floor函数**

  floor(x)，其功能是“向下取整”，或者说“向下舍入”，即取不大于x的最大整数（与“四舍五入”不同，下取整是直接取按照数轴上最接近要求值的左边值）

  ```
  #include <math.h>
  double floor( double arg );
  ```

  例:

  ```
  floor(3.14) = 3.0
  floor(9.999999) = 9.0
  floor(-3.14) = -4.0
  floor(-9.999999) = -10.0
  ```

- **向上取整：ceil函数**

  ceil(x)，其功能是向上取整，即取大于或者等于指定表达式的最小整数，即取按照数轴上最接近要求值的右边值

  ```
  #include <math.h>
  double ceil( double x );
  ```

  例：

  ```
  ceil(3.14) = 4.0
  ceil(9.999999) = 10
  ceil(-3.14) = -3.0
  ceil(-9.999999) = -9.0
  ```

</details>

<details>
<summary>C sprintf和snprint</summary>

# sprintf和snprintf

- **sprintf函数：**

  ```
  #include <string>
  int sprintf(char *str, const char &format, ...);
  ```

  sprintf是字符串格式化命令，主要功能是把格式化的数据写入字符串str中，返回值为写入str的字节数，结束字符‘\0’不计入内。
  其中， str是指要写入的缓冲区，format控制要写入str中数据的格式，例如%s、%d、%x等。

- **snprintf函数：**

  ```
  int snprintf(char *str, size_t size, const char *format, ...);
  ```

  snprintf是字符串格式化命令，主要功能是把格式化的数据写入字符串str中，最多写size个字节，
  包括自动添加在字符串末尾处的结束字符‘\0’;返回值为写入str的字节数，包括结束字符‘\0’。

**Note：** 考虑到安全问题，应尽量使用sprintf代替snprintf

  sprintf可能会引起数组越界，如：

  ```
  char name1[6] = {'\0'}; //只能存储最多5个普通字符和末尾'\0'
  char name2[6] = {'\0'};

  //输出hello!，name1内存:hello!，末尾的'\0'保存到name1之外的第一个空间
  //如果此时name1相邻的内存中有数据，它将被结束字符'\0'覆盖，造成异常，但是这种异常不会引起编译器报错
  sprintf(name1, "%s", "hello!");
  ```    

  使用snprintf解决越界问题：
  ```
  snprintf(name2, sizeof(name2), "%s", "hello!"); //输出hello，name2内存中保存为hello'\0'
  ```

</details>
