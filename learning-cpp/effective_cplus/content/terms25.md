# 条款25：考虑写出一个不抛异常的swap函数

如果swap的缺省实现码对你的class或class template提供可接受的效率，你不需要额外做任何事。任何尝试置换(swap)那种对象的人都会取得缺省版本，
而那将有良好的运作。

如果swap缺省实现版的效率不足(几乎总是意味着你的class或template使用了某种pimpl手法)，试着做以下事情：

- 提供一个public swap成员函数，让它高效地置换你的类型的两个对象值，这个函数绝对不该抛出异常

- 在你的class或template所在的命名空间内提供一个non-member swap，并令它调用上述swap成员函数

- 如果你正编写一个class(非class template)，为你的class特化std::swap。并令它调用你的swap成员函数

最后，如果你调用swap，请确认包含一个using声明式，以便让std::swap在你的函数内曝光可见，然后不加任何namespace修饰符，赤裸裸地调用swap

```
namespace WidgetStuff
{
    ...
    template<typename T>
    class Widget { ... };       //内含swap成员函数
    ...
    template<typename T>
    void swap(Widget<T>& a, Widget<T>& b)
    { a.swap(b); }     //non-member swap函数，这里并不属于std命名空间
    ...
}
template<typename T>
void doSomething(T& obj1, T& obj2)
{
    using std::swap;        //令std::swap在此函数内可用
    ...
    swap(obj1, obj2);       //为T型对象调用最佳swap版本
}
```

编译器看到对swap的调用，会按照C++名称查找法则找到swap函数的定义：

1. 首先会查找global作用域或者T所在命名空间内的任何为类型T特化的swap：
2. 如果T是Widget并位于命名空间WidgetStuff内，编译器会使用"实参取决之查找规则"找出WidgetStuff内的swap。
3. 如果没有T专属之swap存在，编译器就使用std内的swap，这得感谢using声明式让std::swap在函数内曝光，即使如此编译器还是比较喜欢std::swap的T专属特化版，而非一般化的那个templae，所以如果你已针对T将std::swap特化，特化版会被编译器挑中
  
