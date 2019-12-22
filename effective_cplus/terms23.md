# 条款23：宁以non-member、non-friend替换member函数

想象有个class用来表示浏览器。该class可能提供的众多函数中，有一些用来清除下载元素高速缓存区(cache of downloaded elements)、
清除访问过的URLs的历史记录(history of visited URLs)，以及移除系统中的所有cookies

```
class WebBrowser
{
public:
    ...
    void clearCache();
    void clearHistory();
    void removeCookies();
    ...
};
```

许多客户会想一整个执行所有这些动作，因此WebBrowser也提供一个member函数clearEverything()：

```
class WebBrowser
{
public:
    ...
    void clearEverything(); //调用clearCache,clearHistory,removeCookies
};
```

当然，这一机能也可由一个non-member函数调用适当的member函数而提供出来：

```
void clearBrower(WebBrowser& wb)
{
    wb.clearCache();
    wb.clearHistory();
    wb.removeCookies();
}
```

non-member函数clearBrowser优于member函数的clearEverything，原因如下：

从封装的角度来看：面向对象的守则要求数据应该尽可能被封装，对象内，如果有越少的代码可以看到数据，那说明越多的数据被封装，
对于封装的数据我们可以有很大的弹性去改变它，良好的封装性可以使我们拥有尽可能大的改变事物的能力而只影响有限客户
如果一个member函数并不需要访问类的private变量，那它就可以改写为non-member函数来提高封装性，因为在两者提供相同功能的情况下，
可以带来较大封装性的是non-member non-friend函数，因为它并不增加“能够访问class内之private成分”的函数数量
所以non-member non-friend函数相对于member函数具有更加好的封装性

**non-member函数放置的位置：**

- 一般来说，因为在意封装性而让函数“成为class的non-member”并不意味着它“不可以是另一个class的member”，
我们可以令clearBrowser成为某工具(utility class)的一个static member函数，只要它不是WebBrowser的一部分(或成为其friend)，
就不会影响WebBrowser的private成员封装性

- C++中可以将clearBrowser成为一个non-member函数并且位于WebBrowser所在的同一namespac(命名空间)内：

```
namespace WebBrowserStuff
{
    class WebBrowser( ... );
    void clearBrowser( WebBrowser& wb );
}
```

因为namespace和classes不同，前者可以跨越多个源码文件而后者不能，所以可以将类的核心机能与类的各种其他功能的便利函数相互分离，使其脱离编译相依，如：
一个像WebBrowser这样的class可能拥有大量便利函数，某些与书签有关，某些与打印有关，还有一些与cookie的管理有关...，通常大多数用户只对其中某些感兴趣，
没有道理一个只对书签相关便利函数感兴趣的用户却与例如一个cookie相关便利函数发生编译相依关系。分离它们的最直接的办法就是
将书签相关便利函数声明于一个头文件，将cookie相关便利函数声明于另一个头文件，再将打印相关便利函数声明于第三个头文件，依此类推：

```
//头文件"webbrowser.h" —— 这个头文件针对class WebBrowser自身及WebBrowser核心机能
namespace WebBrowserStuff
{
    class WebBrowser{ ... };
    ...     //核心机能，例如几乎所有客户都需要的non-member函数
}

//头文件"webbrowserbookmarks.h"
namespace WebBrowserStuff
{
    ...     //与书签相关的便利函数
}

//头文件"webbrowsercookies.h"
namespace WebBrowserStuff
{
    ...     //与cookies相关的遍历函数
}
```

**Remember：**

宁可拿non-member non-friend函数替换member函数，这样做可以增加封装性、包裹弹性(packaging flexibility)和机能扩充性
