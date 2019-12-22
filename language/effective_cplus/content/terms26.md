# 条款26：尽可能延后变量定义式的出现时间

只要你定义了一个变量而其类型带有一个构造函数或析构函数，那么当程序控制流(control flow)到达这个变量定义式时，你便得承受构造成本；
当这个变量离开其作用域时，你便得承受析构成本。即使这个变量最终并未被使用，仍需耗费这些成本，所以你应该尽可能避免这种情形

例：

```
//过早定义变量"encrypted"
std::string encryptPassword(const std::string& password)
{
    using namespace std;
    string encrypted;   //如果下面发生异常，encrypted在函数就没有被使用，却仍然付出了构造成本和析构成本
    if (password.length() < MinPasswordLength)
    {
        throw logic_error("Password is too short");
    }
    ...     //使用encrypted
    return encrypted;
}
```

```
//延后"encrypted"的定义，直到真正需要它
std::string encryptPassword(const std::string& password)
{
    using namespace std;
    if (password.length() < MinPasswordLength)
    {
        throw logic_error("Password is too short");
    }
    string encrypted; 
    ...     //使用encrypted
    return encrypted;
}
```

尽可能延后：你不只应该延后变量的定义，直到非得使用该变量的前一刻为止，甚至应该尝试延后这份定义直到能够给它初值实参为止。
   如果这样，不仅能够避免构造(和析构)非必要对象，还可以避免无意义的default构造行为

例：

```
//该函数延后了"encrypted"的定义，但无意义的构造行为使得它仍然效率低落
std::string encryptPassword(const std::string& password)
{
    ...
    std::string encrypted;  //无意义的构造行为
    encrypted = password;   //赋值行为
    encrypt(encrypted);
    return encrypted;
}

//跳过毫无意义的default构造过程，
std::string encryptPassword(const std::string& password)
{
    ...
    std::string encrypted(password);  
    encrypt(encrypted);
    return encrypted;
}
```

循环：如果变量只在循环内使用，那么把它定义于循环外并每次循环迭代时赋值好还是把它定义于循环内好？

```
//方法A：定义于循环外
Widget w;
for (int i = 0; i < n; ++i)
{
    w = ...;
    ...
}
//方法B：定义于循环内
for (int i = 0; i < n; ++i)
{
    Widget w(...);
    ...
}
```

两种方法各自的代价分析：

- 方法A：1个构造函数 + 1个析构函数 + n个赋值操作

- 方法B：n个构造函数 + n个析构函数

选用A：

(1)赋值成本低于"构造+析构"

(2)正在处理代码效率高敏感的部分

否则，选用B
