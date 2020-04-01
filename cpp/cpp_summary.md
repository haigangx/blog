<details>
<summary>正确编写operator=</summary>

# 正确编写operator=

本篇总结为自定义类编写operator=函数时要注意的各种问题

首先要明确，如果你没有为某个类声明operator=函数，编译器在需要该函数时将为其声明一个编译器版本的operator=函数。

大多数情况下，编译器版本的operator=都可以工作的很好，但是，如果遇到以下情况，你就必须自己编写operator=函数

</details>

<details><summary>C++实现不可被拷贝的类</summary>

在C++中，类的拷贝主要是通过拷贝构造函数和赋值函数，再者就是为拷贝专门实现的成员方法

由于拷贝构造函数和赋值函数在用户没有提供的情况下由C++编译器自动生成，而且是public成员，因此默认的C++类都有拷贝功能

若让一个C++类不能被拷贝，可显式地声明类的拷贝构造函数和赋值函数为私有函数，从而达到该类不可被拷贝的目的

下面简单的提供一个基类，任何需要提供不可被拷贝功能的C++类只需从此类派生即可

```
/*
 * 通过私有化拷贝构造函数和赋值函数从而达到对象不可被拷贝的目的
 * 任何需提供不能被拷贝功能的类可以直接从CNonCopyable派生即可
 */
class CNonCopyable
{
private:
    CNonCopyable(const CNonCopyable&);
    const CNonCopyable& operator=(const CNonCopyable&);

protected:
    CNonCopyable() {}
    ~CNonCopyable() {}
};
```

</details>

<details><summary>C++编译器为一个空类做了哪些事</summary>

</details>