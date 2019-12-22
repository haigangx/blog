# 条款35：考虑virtual函数以外的其他选择

virtual函数意味着运行时绑定，GameCharacter是一个游戏内的角色基类，每个角色拥有成员函数healthValue，表示人物的健康程度，由于每个人物的健康指数有不同的计算方式，所以将healthValue声明为virtual是非常简单普遍的做法：

```
class GameCharacter {
public:
    //返回人物健康指数，derived class可重新定义
    virtual int healthValue() const;  
};
```
下面考虑用virtual函数以外的其他选择实现这种效果：

- ## 藉由Non-virtual Interface手法实现[Template Method模式]()

**Non-virtual Interface**指保留healthValue为public成员函数，但让它成为non-virtual，并调用一个private virtual函数（如doHealthValue）进行实际工作：
```
class GameCharacter {
public:
    //derived class不能重新定义healthValue
    int healthValue() const {
        ...     //处理事前工作
        int retVal = doHealthValue();
        ...     //处理事后工作
        return retVal;
    }
private:
    //derived class可重新定义doHealthValue
    virtual int doHealthValue() const;
};
```

这种“令客户通过public non-virtual成员函数间接调用private virtual函数”的设计称为**non-virtual interface(NVI)手法**，它是**Template Method设计模式**的一种实现，这个non-virtual函数(headlthValue)称为virtual函数的外覆器(wrapper)。

需要注意：

  - **NVI手法优点：** non-virtual成员函数可以在virtual函数被调用前和调用后处理一些事前工作和时候工作，外覆器headlthValue确保在一个virtual函数被调用之前设定好适当场景，并在调用结束之后清理场景。

    **事前工作**包括：锁定互斥器、制造运转日志记录项、验证class约束条件、验证函数先决条件等。

    **事后工作**包括：互斥器解除锁定、验证函数的事后条件、再次验证class约束条件等。
    
  - NVI手法允许derived class重新定义private virtual函数，从而赋予它们“如何实现机能”的控制能力，但base class保留诉说“函数何时被调用的权利”
  
  - NVI手法下没有必要让virtual函数一定是private，也可以是protected，视具体情况而定。有时候virtual函数必须定义为public，如具备多态性质的base class的析构函数，这时候就不能实施NVI手法了


- ## 藉由Function Pointer实现[Strategy模式]()

这种设计主张“人物健康指数的计算与人物类型无关”，这样的计算完全不需要“人物”这个成分，例如我们可能会要求每个人物的构造函数接受一个指针，指向一个健康计算函数，而我们可以调用该函数进行实际计算：

```
class GameCharacter;
//计算健康指数的缺省算法
int defaultHealthCalc( const GameCharacter );
class GameCharacter {
public:
    typedef int (*HealthCalcFunc)(const GameCharacter&);
    explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc)
      : healthFunc(hcf)
    {}
    int healthValue() const
    { return healthFunc(*this); }
    ...
private:
    HealthCalcFunc healthFunc;
};
```
这个做法是**Strategy设计模式**的简单应用，拿它和“植基于GameCharacter继承体系内之virtual函数”的做法比较，有以下**弹性**：

  - **同一人物类型之不同实体可以有不同的健康计算函数**，如：
    
    ```
    class EvilBadGuy : public GameCharacter {
    public:
        explicit EvilBadyGuy(HealthCalcFunc hcf = defaultHealthCalc)
          : GameCharacter(hcf)
        {...}
        ...
    };
    int loseHealthQuickly(const GameCharacter&);  //健康计算函数1
    int loseHealthSlowly(const GameCharacter&);  //健康计算函数2
    
    EvilBadyGuy ebg1(loseHealthQuickly);  //相同类型的人物搭配
    EvilBadGuy ebg2(loseHealthSlowly);  //不同的健康计算方式
    ```
  
  - **某已知人物之健康指数计算函数可在运行期变更**，如：
  
    GameCharacter可提供一个成员函数setHealthCalculator，用来替换当前的健康计算函数
  
同时，这个做法相较之virtual函数也有一些**问题**：

  - 如果计算该人物的健康必须依靠人物的某些non-public信息，这个做法就不太完美，解决之法是通过弱化class的封装，或将健康计算函数声明为class的friend函数，或者为class中的non-public信息提供public访问方式，这会**降低class的封装性**

- ## 藉由[tr1:function]()完成Strategy模式

可以将前例中的healthFunc函数指针改为一个类型为tr1::function的对象，这样的对象可持有任何可调用物(callable entity，也就是函数指针、函数对象、或成员函数指针)，只要其签名式兼容于需求端，将上例的设计改为使用tr1::function:

```
class GameCharacter; 
int defaultHealthCalc(const GameCharacter& gc);
class GameCharacter {
public:
    //HealthCalcFunc可以是任何"可调用物"(callable entity)，可被调用并接受
    //任何兼容于GameCharacter之物，返回任何兼容于int的东西
    typedef std::tr1::function<int (const GameCharacter&)> HealthCalcFunc;
    explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc)
      : healthFunc(hcf)
    {}
    int healthValue() const
    { return healthFunc(*this); }
    ...
private:
    HealthCalcFunc healthFunc;
};
```
和前一个设计相比，这个设计唯一的不同是GameCharacter如今持有一个tr1::function对象，相当于一个指向函数的泛化指针，这个改变如此细小以至于这两个设计几乎相同，这个设计在“指定健康计算函数”这件事上有惊人的弹性

```
short calcHealth(const GameCharacter&);  //健康计算函数，返回non-int

struct HealthCalcultor {    //为计算健康而设计的函数对象
    int operator()(const GameCharacter&) const 
    { ... }
};

class GameLevel {
public:
    //成员函数，用以计算健康
    float health(const GameCharacter&) const;  //注意其返回non-int
};

//一个具体的人物类型
class EvilBadGuy : public GameCharacter {
    ...
};

//另一个人物类型
class EyeCandyCharacter : public GameCharacter {
    ...
};

//人物1使用calcHealth函数计算健康函数
EvilBadGuy ebg1(calcHealth);    

//人物2使用某个函数对象计算健康指数
EyeCandyCharacter eccl(HealthCalculator());  

//人物3使用某个成员函数计算健康指数
GameLevel currentLevel;
...
EvilBadGuy ebg2(
  std::tr1::bind(&GameLevel::health, currentLevel, _1)
);
```
[C++11：std::tr1::bind函数]()

解释如何计算ebg2的健康指数：为了计算ebg2的健康指数，应该使用GameLevel class的成员函数health，GameLevel::health虽然宣称自己接受一个参数const GameCharacter&，但是实际使用中它其实接受两个参数，有一个隐式参数this，但是GameCharacters的健康计算函数只接受一个参数，不能直接使用GameLevel::health初始化ebg2，所以必须对其进行转化，让它不再接受两个参数，转而接受单一参数，bind函数来完成这个任务，就本例来说我们将currentLevel绑定为GameLevel对象，让它在“每次GameLevel::health被调用以计算ebg2的健康”时替换this的位置，它指出ebg2的健康计算函数应该总是以currentLevel作为GameLevel对象

- ## 古典的Strategy模式

传统的strategy模式的做法会将健康计算函数做成一个分离的继承体系中的virtual成员函数。设计结果如下：

缺图，后补

```
class GameCharacter;
class HealthCalcFunc {
public:
    ...
    virtual int calc(const GameCharacter& gc) const
    { ... }
    ...
};

HealthCalcFunc defaultHealthCalc;

class GameCharacter {
public:
    explicit GameCharacter(HealthCalcFunc *phcf = &defaultHealthCalc)
      : pHealthCalc(phcf)
    {}
    int healthValue() const
    { return pHealthCalc->calc(*this); }
    ...
private:
    HealthCalcFunc *pHealthCalc;
};
```
优点：

 - 熟悉标准Strategy模式的人很容易辨认它
 - 提供“将一个即有的健康算法纳入使用”的可能性——只需为HealthCalcFunc继承体系添加一个derived class
