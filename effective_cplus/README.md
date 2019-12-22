## 《Effective C++》学习总结

- 让自己习惯C++

  * [条款01：视c++为一个语言联邦](terms01.md)
  * [条款02：尽量以const, enum, inline替换#define](terms02.md)
  * [条款03：尽可能使用const](terms03.md)
  * [条款04：确定对象被使用前已先被初始化](terms04.md)

- 构造/析构/赋值运算

  * [条款05：了解C++默默编写并调用哪些函数](terms05.md)
  * [条款06：若不想使用编译器自动生成的函数，就该明确拒绝](terms06.md)
  * [条款07：为多态基类声明virtual析构函数](terms07.md)
  * [条款08：别让异常逃离析构函数](terms08.md)
  * [条款09：绝不在构造和析构过程中调用virtual函数](terms09.md)
  * [条款10：令operator=返回一个reference to * this](terms10.md)
  * [条款11：在operator=中处理“自我赋值”](terms11.md)
  * [条款12：复制对象时勿忘每一个成分](terms12.md)

- 资源管理

  * [条款13：以对象管理资源](terms13.md)
  * [条款14：在资源管理类中小心coping行为](terms14.md)
  * [条款15：在资源管理类中提供对原始资源的访问](terms15.md)
  * [条款16：成对使用new和delete时要采取相同形式](terms16.md)
  * [条款17：以独立语句将newed对象置入智能指针](terms17.md)

- 设计与生命

  * [条款18：让接口容易被正确使用，不易被误用](terms18.md)
  * [条款19：设计class犹如设计type](terms19.md)
  * [条款20：宁以pass-by-reference-to-const替代pass-by-value](terms20.md)
  * [条款21：必须返回对象时，别妄想返回其reference](terms21.md)
  * [条款22：将成员变量声明为private](terms22.md)
  * [条款23：宁以non-member、non-friend替换member函数](terms23.md)
  * [条款24：若所有参数皆需类型转换，请为此采用non-member函数](terms24.md)
  * [条款25：考虑写出一个不抛异常的swap函数](terms25.md)

- 实现

  * [条款26：尽可能延后变量定义式的出现时间](terms26.md)
  * [条款27：尽量少做转型动作](terms27.md)
  * [条款28：避免返回handles指向对象内部成分](terms28.md)
  * [条款29：为“异常安全”而努力是值得的](terms29.md)
  * [条款30：透彻了解inlining的里里外外](terms30.md)
  * [条款31：将文件间的编译依存关系降至最低](terms31.md)

- 继承与面向对象设计

  * [条款32：确定你的public继承塑模出is-a关系](terms32.md)
  * [条款33：避免遮掩继承而来的名称](terms33.md)
  * [条款34：区分接口继承和实现继承](terms34.md)
  * [条款35：考虑virtual函数以外的其他选择](terms35.md)
  * [条款36：绝不重定义继承而来的non-virtual函数](terms36.md)
  * [条款37：绝不重新定义继承而来的缺省参数值](terms37.md)
  * [条款38：通过符合塑模出has-a或"根据某物实现出"](terms38.md)
  * [条款39：明智而审慎地使用private继承](terms39.md)
  * [条款40：明智而审慎地使用多重继承](terms40.md)

- 模板与泛型编程

  * [条款41：了解隐式接口和编译器多态](terms41.md)
  * [条款42：了解typename的双重意义](terms42.md)
  * [条款43：学习处理模板化基类内的名称](terms43.md)
  * [条款44：将与参数无关的代码抽离templates](terms44.md)
  * [条款45：运用成员函数模板接收所有兼容类型](terms45.md)
  * [条款46：需要类型装换时轻微模板定义非成员函数](terms46.md)
  * [条款47：请使用traits classes表现类型信息](terms47.md)
  * [条款48：认识template元编程](terms48.md)

- 定制new和delete

  * [条款49：了解new-handler的行为](terms49.md)
  * [条款50：了解new和delete的合理替换时机](terms50.md)
  * [条款51：编写new和delete时需固守常规](terms51.md)
  * [条款52：写了placement new也要写placement delete](terms52.md)

- 杂项讨论

  * [条款53：不要轻忽编译器的警告](terms53.md)
  * [条款54：让自己熟悉包括TR1在内的标准程序库](terms54.md)
  * [条款55：让自己熟悉Boost](terms55.md)
