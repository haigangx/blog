# 条款13：以对象管理资源

## 问题：

```
class Investment { ... };
Investment* createInvestment(); //工厂函数返回Investment指针
void f()
{
    Investment* pInv = createInvestment();  //调用factory函数
    ...
    delete pInv;    //通过factory函数返回的Investment*要自己释放
}
```

**可能发生内存泄漏的情况：**

- 如果...区域内一个过早的return语句被执行，程序将不会执行最后的delete pInv，导致内存泄漏

- 软件的后期维护中，可能会有某些人添加return语句或者控制流发生变化的语句导致delete语句无法执行

因此，单纯依赖“f总是会执行delete语句”是行不通的

## 解决：

**解决想法：** 把资源放进对象内，我们便可倚赖C++的“析构函数自动调用机制”确保资源被释放

具体解决办法例子：

- **auto_ptr** ：特性：若通过copy构造函数或copy assignment操作符复制它们，它们就变成null，而复制所得的指针将取得资源的唯一拥有权

  ```
  std::auto_ptr<Investment> pInv(createInvestment()); //使用auto_ptr

  std::auto_ptr<Investment> pInv1(pInv);      //使用pInv拷贝构造pInv1，导致pInv1指向对象而pInv指向null
  std::auto_ptr<Investment> pInv2 = pInv1;    //pInv2指向对象，而pInv指向null
  ```

  缺点：auto_ptr保证受auto_ptr管理的资源必须绝对没有一个以上的auto_ptr同时指向它，这并非普通指针的正常行为，所以并非管理动态分配资源的神兵利器

- auto_ptr的替代方案“ **引用计数型智慧指针** (reference-counting smart pointer:RCSP)”:

  ```
  tr1::shared_ptr：tr1:shared_ptr支持追踪共有多少对象指向某笔资源，并在无人指向它时自动删除该资源
  std::tr1::shared_ptr<Investment> pInv(createInvestment());
  ```

  缺点：无法打破环状引用(cycle of reference, 例如两个其实已经没被使用的对象彼此互指，因此双方好像还处在“被使用”状态)

- auto_ptr和tr1::shared_ptr两者都在其析构函数内做delete而不是delete[]动作，这意味着在动态分配而来的array上不能使用auto_ptr或tr1::shared_ptr，然而这种错误的用法仍然能通过编译
针对数组的、类似于auto_ptr和tr1::shared_ptr的智能指针有 **boost::scoped_array和boost::shared_array**

## 结论：

- 获得资源后立刻放进管理对象中，如auto_ptr或tr1::shared_ptr

- 管理对象运行析构函数确保资源释放

## 相关

- [智能指针总结](../C++/SmartPointer.md)
