# 范围for语句

遍历容器或其他序列的所有元素，范围for语句(range of statement)的 **语法形式** 是：

```
for (declaration : expression)
    statement
```

- **expression** 必须为一个序列，如初始值列表{"12", "fdsa", "qwer"}、数组或者vector、string等类型的对象，
  这些类型的共同点是能返回迭代器的begin和end成员

- **declaration** 定义一个变量，序列中的每个元素都得能转换成该变量的类型，可以使用auto类型说明符

例子：

```
vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

//如果要对序列中的元素进行写操作，可以将范围变量声明为引用类型
for (auto &r : v)
    r *= 2;
```

范围for语句的定义来源于与之等价的传统for语句：

```
for (auto beg = v.begin(), end = v.end(); beg != end; ++beg)
{
    auto &r = *beg;
    r *= 2;
}
```

**!!Note：**

  范围for语句中不能增加vector对象(或其他容器)的元素，因为在范围for语句中，预存了end()的值。
  一旦在序列中添加(删除)元素，end函数的值就可能变得无效了 **(迭代器失效)**
