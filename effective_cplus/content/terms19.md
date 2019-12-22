# 条款19：设计class犹如设计type

当你定义一个新class时，也就新定义了一个type，因此你应该带着和“语言设计者当初设计语言内置类型时”一样的谨慎来研讨class的设计
设计一个新type之前，确保你已经考虑好以下讨论主题：

- **新的type的对象应该如何被创建和销毁？**
  
  确定是否需要重写内存分配函数operator new, operator new[], operator delete, operator delete[]以及class的构造函数和析构函数的编写

- **对象的初始化和赋值的差别？**
  
  对象的初始化和赋值分别对应的函数调用为构造函数和operator=，确保这两个调用的行为

- **新type的对象被pass by value时的行为？**

  copy构造函数用来定义一个type的pass by value该如何实现

- **新type的合法值？**

  新type的对象可以取到的合法值的数值集要明确，而且必须在成员函数(特别是构造函数、赋值操作符、"setter"函数)中进行错误检查工作

- **新type是否继承于其他type或者允许其他type继承？**

  如果新class继承于已有的class，那么就会受到原有class的设计的束缚，特别是受到“它们的函数是virtual或non-virtual”的影响
  
  如果你允许其他class继承于你的class，那会影响你所声明的函数——尤其是析构函数——是否为virtual

- **新type需要什么样的转换？**

  如果你希望允许类型T1之物隐式转换为类型T2之物，就必须在class T1内写一个类型转换函数(operator T2)或在class T2内写一个non-explicit-one-argument(可被单一实参调用)的构造函数

- **什么样的操作符和函数对此新type是合理的？**

  你将为你的class声明哪些member函数

- **什么样的标准函数应该驳回？**

  将不支持的标准函数设为private，例如：如不支持拷贝构造，便将拷贝构造函数设为private

- **谁该取用新type的成员？**

  想好新type的哪些成员是public，哪些是protected，哪些是private
  
  哪些class或functions应该是friend的

- **什么是新type的未声明接口(undeclared interface)?它对效率、异常安全性以及资源运用(如多任务锁定和动态内存)提供何种保证？你在这些方面提供的保证将为你的class实现代码加上相应的约束条件**

- **你的新type有多么一般化？**

  或许你其实并非定义一个新type，而是定义一整个type家族，果真如此你就不该定义一个新class，而是应该定义一个新的class template

- **你真的需要一个新type吗？**
