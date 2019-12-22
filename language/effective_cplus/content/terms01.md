# 条款01：视C++为一个语言联邦

  今天的C++已经是个 **多重泛型编程语言(multiparadigm programming language)** ，一个同时支持 **过程形式(procedural)** 、 **面向对象形式(object-oriented)** 、 **函数形式(functional)** 、 **泛型形式(generic)** 、 **元编程形式(metaprogramming)** 的语言。



  为了理解C++，最简单的办法是**将C++视为一个由相关语言组成的联邦而非单一语言**，在其某个次语言(sublanguage)中，各种守则与通例都倾向于简单、直观易懂，并且容易记住，C++的次语言有四种：

  - **C** ：
  
    区块(block)、语句(statements)、预处理(preprocessor)、内置数据类型(built-in data types)、数组(arrays)、指针(pointers)等等来自于C
 
  - **Object-Oriented C++** ：
  
    classes、封装(encapsulation)、继承(inheritance)、多态(polymorphism)、virtual函数(动态绑定)等等面向对象设计守则
  
  - **Template C++** ：
  
    C++的泛型编程(generic programming)部分，template metaprogramming(TMP, 模板元编程)
  
  - **STL** ：
  
    STL是个template程序库，拥有容器(containers)、迭代器(iterators)、算法(algorithms)等非常有用的工具
