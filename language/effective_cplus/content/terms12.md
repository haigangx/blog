# 条款12：复制对象时勿忘每一个成分

> 需要重写

- copy构造函数和copy assignment函数等copying函数应保证对所有的成员变量进行拷贝，
  如果遗漏某些成员变量，编译器不会产生任何错误或警告，同时如果你为class添加一个成员变量，必须记得同时修改copying函数

- 当为一个子类编写copying函数时，确保调用所有base classes内的适当的copying函数

- 不要尝试以某个copying函数实现另一个copying函数，应该将共同机能放进第三个函数中，并有两个copying函数共同调用
