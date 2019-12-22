# 条款05：了解C++默默编写并调用哪些函数

> 需要重写

- 写一个空类，如果你自己没声明，编译器就会为这个类声明(只有当这些函数被调用时才创建)一个**copy构造函数**，一个**copy assignment操作符**和一个**析构函数**，此外如果你没有声明任何构造函数，编译器也会为你声明一个**default构造函数**，所有这些函数都是public和inline的。

- 编译器版本的copy构造函数和copy assignment操作符只是单纯的将来源对象的每一个non-static成员变量拷贝到目标对象

- 编译器拒绝为“内含reference成员”和“内含const成员”的classes中声明默认copy assignment操作符，如果需要赋值操作，必须自己定义copy assignment操作符

- 如果某个base classes将copy assignment操作符声明为private，编译器将拒绝为其derived classes生成一个copy assignment操作符
