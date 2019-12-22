# 条款17：以独立语句将newed对象置入智能指针

假设有个函数用来揭示处理程序的优先级，另一个函数用来在某动态分配所得的widget上进行某些带有优先级的处理：

```
int priority();
void processWidget(std::tr1::shared_ptr<Widget> pw, int priority);
```

**错误的调用方式：**

```
processWidget(new Widget, priority());
```

应该使用：

```
processWidget(std::tr1::shared_ptr<Widget>(new Widget), priority()); //相对较好的调用方式，但仍可能发生内存泄漏问题
```

**C++函数参数初始化顺序不确定导致可能发生内存泄漏问题：**

在调用：

```
processWidget(std::tr1::shared_ptr<Widget>(new Widget), priority());
```
中，C++对参数的核算需要经过三个部分：**new Widget**，**调用tr1::shared_ptr的构造函数**，**调用priority()**

C++仅保证new Widget操作先于调用tr1::shared_ptr的构造函数，对于具体顺序并不做要求：

所以存在一种顺序：

  1. 执行new Widget
  2. 调用priority
  3. 调用tr1::shared_ptr的构造函数
  
这个时候，一旦在对priority调用期间发生异常，new Widget返回的指针将遗失，因为它还没有被交由智能指针管理

综上，导致内存泄漏的原因是在“资源被创建”和“资源被转换为资源管理对象”两个时间点之间有可能发生异常干扰

**解决方案：**

使用分离语句：

```
std::tr1::shared_ptr<Widget> pw(new Widget);    //在单独语句中完成“资源创建”并且“将资源交由资源管理对象管理”
processWidget( pw, priority() );    //绝对不会导致内存泄漏
```
