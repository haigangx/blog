# lambda表达式

<!-- TOC -->

- [一、可调用对象](#一可调用对象)
- [二、lambda的理解](#二lambda的理解)
- [三、lambda 的四个要素](#三lambda-的四个要素)
    - [1. 捕获列表(capture list)](#1-捕获列表capture-list)
    - [2. return type](#2-return-type)
    - [3. parameter list](#3-parameter-list)
    - [4. function body](#4-function-body)
- [四、相关信息](#四相关信息)

<!-- /TOC -->
 
## 一、可调用对象

**可调用对象：** 对于一个对象或表达式，如果可以对其使用调用运算符()，则称它为可调用的

目前为止，一共有四种可调用对象：

- 函数 
- 函数指针 
- 重载了函数调用运算符的类(仿函数) 
- lambda表达式

lambda表达式表示一个可调用的代码单元，可以理解为一个未命名的内联函数：

与普通函数类似，lambda 表达式具有一个返回类型(必须是 [尾置返回类型](./尾置返回类型.md) )、一个参数列表、一个函数体，形式如下：

```c++
[capture list](parameter list) -> return type {function body};
```

实例：

```c++
auto f = [] {return 42;}
```

## 二、lambda的理解

- 当定义一个 lambda 时，编译器生成一个与 lambda 对应的新的(未命名的)类类型

- 可以将 lambda 作为一个函数参数传递，可以这样理解，当向一个函数传递一个 lambda 时，同时定义了一个新类型和该类型的一个对象：
  传递的参数就是编译器生成的该类类型的未命名对象

- 类似的，当使用 auto 定义一个用 lambda 初始化的变量时，定义了一个从 lambda 生成的类型的对象

- 默认情况下，捕获列表中的变量都被从 lambda 生成的类包含到了其数据成员中，类似于普通类的数据成员，lambda 的数据成员也在 lambda 对象创建时被初始化

- 可以忽略参数列表和返回类型，但必须永远包含捕获列表和函数体

## 三、lambda 的四个要素

### 1. 捕获列表(capture list)

lambda 通过将所在函数的局部变量包含在捕获列表中来指出将会使用这些变量

一个 lambda 只有在其捕获列表中捕获一个它所在函数中的局部变量，才能在函数体中使用这些变量

- 空捕获列表 `[]`：表示此 lambda 不实用它所在函数中的任何局部变量

- 值捕获 `[n]`：被捕获的变量的值是在 lambda 创建时拷贝，而不是调用时拷贝，因此随后对该变量的修改不会影响到 lambda 内对应的值
  
  ```
  void fcn1() {
      size_t v1 = 42; //函数fcn1内的局部变量
      auto f = [v1] {return v1;}; //捕获v1，将v1拷贝到名为f的可调用对象  f.v1 = v1
      v1 = 0;
      auto j = f();  //j为42，f保存了我们创建它是v1的值
  }
  ```

- 引用捕获 `[&n]`：
  
  ```
  void fcn2() {
      size_t v1 = 42; //局部变量
      auto f2 = [&v1] {return v1;};   //对象f2包含v1的引用  f.v1 = &v1;
      v1 = 0;
      auto j = f2();  //j为0
  }
  ```
  
  > **Note！** 如果采用引用方式捕获一个变量，就必须确保被引用的对象在lambda执行的时候是存在的

- 隐式捕获 `[&]` 或 `[=]`：让编译器根据 lambda 体中的代码来推断我们要使用哪些变量
  
  在捕获列表中写一个 `&` 或 `=` 指示编译器推断捕获列表：
  
  - `&` 告诉编译器采用捕获引用方式
  - `=` 表示采用值捕获方式

- 混合使用隐式捕获和显式捕获
  
  当混合使用隐式捕获和显式捕获时，捕获列表的第一个元素必须是 `&` 或 `=`，此符号指定了默认捕获方式为引用或值，
  跟随 `&` 或 `=` 的显式捕获列表中的变量必须使用与隐式捕获不同的方式。即：
  
  - `[&, identifier_list]`：如果隐式捕获采用引用方式 ( & )，则显式捕获命令变量 `indntifier_list` 必须采用值方式，因此变量名字前不能使用 `&`
  - `[=, identifier_list]`：如果隐式捕获采用的是值方式 ( = )，则显式捕获命令变量 `indentifier_list` 必须采用引用方式，并且不能包括 `this`，因此变量名字前必须使用 `&`

- 可变 lambda

  默认情况下，对于一个值被拷贝的变量，lambda 不会改变其值，如果我们希望能改变一个捕获变量的值，就必须在参数列表后加上关键字 mutable，
  因此可变 lambda 不能省略参数列表：
  
  ```
  void fcn3() {
      size_t v1 = 42;
      auto f = [v1] () mutable {return ++v1;};
      v1 = 0;
      auto j = f();   //j为43
  }
  ```
  
  一个引用捕获的变量是否可以修改依赖于此引用指向的是一个 **const 类型** 还是 **非 const 类型**：
  
  ```
  void fcn4() {
      size_t v1 = 42; //v1为非const变量
      auto f2 = [&v1] {return ++v1;};
      v1 = 0;
      auto j = f2();  //j为1
  }
  ```

### 2. return type

返回类型必须使用尾置返回类型(C++/C++11/尾置返回类型)

如果忽略返回类型，lambda 根据函数体中的代码推断出返回类型：

- 如果函数体中只有一条 return 语句，则返回类型从返回的表达式类型推断而来
- 如果 lambda 体包含 return 之外的任何语句，则编译器假定此 lambda 返回 void

例子：

函数 f 返回 i 的绝对值：

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

### 3. parameter list

lambda 不能使用默认参数，一个 lambda 调用的实参数目永远与形参数目相等

### 4. function body

function body 和普通函数相同

## 四、相关信息

- 可以使用 [function类模板](./function类模板.md) 保存 lambda 表达式

