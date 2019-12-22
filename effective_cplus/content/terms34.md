# 条款43：区分接口继承和实现继承

public继承由两部分组成：函数接口继承和函数实现继承

- ## 声明一个pure virtual函数的目的是为了让derived class只继承函数接口

- ## 声明(非纯)impure virtual函数的目的，是让derived class继承该函数的接口和缺省实现

  允许impure virtual函数同时指定函数声明和函数缺省行为，会有可能造成危险。

  例如：某航空公司有A型和B型两种飞机，两者以相同的方式飞行，因此设计出这样的继承体系：

  ```
  class Airport { ... };
  class Airplane {
  public:
      virtual void fly(const Airport& destination);
      ...
  };
  void Airplane::fly(const Airport& destination)
  {
      缺省代码，将飞机飞至指定的目的地
  }

  class ModelA : public Airplane { ... };
  class ModelB : public Airplane { ... };
  ```
  为了表示所有飞机都一定能飞，并阐明“不同型飞机原则上需要不同的fly实现”，Airplane::fly被声明为virtual。然而为了避免在ModelA和ModelB中撰写相同代码，缺省飞行行为由Airplane::fly提供，它同时被ModelA和ModelB继承。

  现在假设，该航空公司又新购一种新式C型飞机，C型的飞行方式和A型、B型不同，假设在设计时，因为着急让新飞机上线，竟忘记了重新定义其fly函数：
  ```
  class ModelC : public Airplane {
      ...   //未声明fly函数
  };
  ```
  此时，调用ModelC.fly()时，将采用和A型、B型相同的飞行模式飞行，这将酿成大灾难。

  **问题不在于Airplane::fly有缺省行为，而在于ModelC在未明白说出“我要”的情况下就继承了该缺省行为**，所以我们最好做到**在Derived class明确要求时提供缺省实现，否则免谈**，使用***为纯虚函数增加缺省实现**可以解决这个问题：
  
  ```
  
  class Airplane {
  public:
      virtual void fly(const Airport& destination) = 0;
      ...
  };

  void Airplane::fly(const Airport& destination)  //pure virtual函数实现
  {
      缺省实现，将飞机飞至指定目的地
  }

  class ModelA : public Airplane {
  public:
      virtual void fly(const Airport& destination)
      { Airplane::fly(destination); }
      ...
  };

  class ModelB : public Airplane {
  public:
      virtual void fly(const Airport& destination)
      { Airplane::fly(destination); }
      ...
  };


  class ModelC : public Airplane {
  public:
      virtual void fly(const Airport& destination)
      ...
  };
  void ModelC::fly(const Airport& destination)
  {
      将C型飞机飞至指定目的地
  }
  
  ```

- ## 声明non-virtual函数的目的是为了令derived class继承函数的接口及一份强制性实现
