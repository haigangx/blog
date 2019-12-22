# Linux调试工具

[参考教程](https://blog.csdn.net/paladinzh/article/details/91354900)https://www.jianshu.com/p/55cf1fa7a467

## 输出log

最简单快捷的调试方式，可以快速定位bug，可以利用文本分析工具awk/sed/grep快速在大量日志中找到错误信息

## GDB

GDB调试查看[这篇文章](command/gdb.md)

## strace

strace是用来跟踪系统调用的工具。

它最简单的用途是跟踪一个程序整个生命周期里所有的系统调用，并把调用参数和返回值以文本的方式输出。

strace还可以跟踪发给进程的信号。支持attach正在运行的进程strace -p <pid>，当多线程环境下，需要跟踪某个线程的系统调用，可以先ps -efL | grep <process name>查找出该进程，然后调用starace -p <pid>进行分析

strace用法请看[这篇文章](command/strace.md)

## pstack
用来跟踪进程栈，比如我们发现一个服务一直处于work状态（如假死状态，好似死循环），使用这个命令就能轻松定位问题所在；可以在一段时间内，多执行几次pstack，若发现代码栈总是停在同一个位置，那个位置就需要重点关注，很可能就是出问题的地方

pstack用法请看[这篇文章](command/pstack.md)

## core dump文件
在进程收到某些信号而终止运行时，将此时进程地址空间的内容以及有关进程状态的其他信息写到core文件中，例如我们平时的非法访问内存产生segment fault错误，利用gdb可以查看到到底是哪里发生了异常。有时候可以人为的向进程发送信号kill -11 <pid>，查看此时系统运行的状态，例如多线程下程序突然停住了，此时就可能发生了死锁，可以人为的产生信号，再来分析core dump。

## valgrind
包含很多工具：

Memcheck。这是valgrind应用最广泛的工具，一个重量级的内存检查器，能够发现开发中绝大多数内存错误使用情况，比如：使用未初始化的内存，使用已经释放了的内存，内存访问越界等。这也是本文将重点介绍的部分。

Callgrind。它主要用来检查程序中函数调用过程中出现的问题。

Cachegrind。它主要用来检查程序中缓存使用出现的问题。

Helgrind。它主要用来检查多线程程序中出现的竞争问题。

Massif。它主要用来检查程序中堆栈使用中出现的问题。

Extension。可以利用core提供的功能，自己编写特定的内存调试工具。

默认使用的就是memcheck工具，在c++中指针的使用，一不留神就会产生异常，就可以利用memcheck进行检查。个人一般用--track-origins=yes来定位未初始化变量的位置。

valgrind用法请看[这篇文章](command/valgrind.md)

## tcpdump

抓包用的，在开发网络应用的时候很给力,结合awk/sed/grep可以快速查找网络数据包

tcpdump用法请看[这篇文章](command/tcpdump.md)
