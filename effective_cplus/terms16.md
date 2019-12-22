# 条款16：成对使用new和delete时要采取相同形式

**核心：如果你在new表达式中使用[]，必须在相应的delete表达式中也使用[]。如果你在new表达式中不使用[]，一定不要在相应的delete表达式中使用[]**

使用new创建单个对象或者使用new []创建对象数组的内存结构通常如下图：

![单一对象和对象数组内存结构](img/terms16_1.png)

```
std::string* stringPtr1 = new std::string;
std::string* stringPtr2 = new std::string[100];
...
delete stringPtr1;      //删除一个对象
delete [] stringPtr2;   //删除一个由对象组成的数组
```

- 如果对stringPtr1调用delete []：结果未定义，但如果内存布局如上图，delete会读取若干内存并将它解释为"数组大小"，然后开始多次调用析构函数，浑然不知它所处理的那块内存不但不是个数组，也或许它正在销毁自己并未持有的某种类型的对象

- 如果对stringPtr2调用delete：结果未定义，但即有可能导致太少的析构函数被调用

编码过程中要清楚的知道某个指针构造时采用的new形式，并且使用相匹配的delete来析构：

但是如果使用typedef常常会使得这个问题很难明白，例：

```
typedef std::string AddressLines[4];
//使用了typedef, new AddressLines等价于 new std::string[4]
std::string* pa1 = new AddressLines;    
//必须使用匹配“数组形式”的delete：
delete pa1;     //行为未定义
delete [] pa1;  //good
```

上述情况容易引起混淆，为避免这种不清晰的情况，尽量不要对数组形式采用typedef动作
