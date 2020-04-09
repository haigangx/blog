# 条款20：宁以pass-by-reference-to-const替代pass-by-value

- 尽量以pass-by-reference-to-const替换pass-by-value。前者通常比较高效，并可避免切割问题(slicing problem)
  
  切割问题(slicing problem)：当一个derived class对象以by value方式传递并被视为一个base class对象，base class的copy构造函数会被调用，
  而造成此对象的行为像个“derived class对象”的哪些特化性质全被切割掉了，仅仅留下一个base class对象

- 以上规则并不适用于内置类型，以及STL的迭代器和函数对象。对它们而言，pass-by-value往往比较适当
