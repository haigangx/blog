# GDB调试工具

<!-- TOC -->

- [一、命令行GDB调试](#一命令行gdb调试)
    - [1. 常用命令](#1-常用命令)
    - [2. gdb调试多进程](#2-gdb调试多进程)
    - [3. gdb调试多线程](#3-gdb调试多线程)
    - [4. 调试core dump](#4-调试core-dump)
        - [4.1 造成segment fault，产生core dump的可能原因](#41-造成segment-fault产生core-dump的可能原因)
        - [4.2 配置操作系统使其产生core文件](#42-配置操作系统使其产生core文件)
        - [4.3 用gdb查看core文件](#43-用gdb查看core文件)
        - [4.4 使用core文件定位core dump位置](#44-使用core文件定位core-dump位置)
    - [5. 调试宏](#5-调试宏)
    - [6. 源文件](#6-源文件)
    - [7. 条件断点](#7-条件断点)
    - [8. 命令行参数](#8-命令行参数)
    - [9. x命令](#9-x命令)
    - [10. command命令](#10-command命令)
    - [11. 调试脚本](#11-调试脚本)
- [2. 图像界面调试](#2-图像界面调试)
    - [2.1 gdb自带的tui](#21-gdb自带的tui)
    - [2.2 在浏览器显示调试界面---gdbgui](#22-在浏览器显示调试界面---gdbgui)
        - [2.2.1 安装：](#221-安装)
        - [2.2.2 使用：](#222-使用)
- [3. 调试命令](#3-调试命令)

<!-- /TOC -->

## 一、命令行GDB调试

使用gdb调试，编译时要用-g选项，并使用-O级优化

### 1. 常用命令

| 命令 | 简写 | 命令说明 |
| :--- | :--- | :------- |
| list | l | 显示多行源代码 |
| break n | b n | 在第n行设置断点 |
| break if | b if | 当满足某个条件时停止 |
| delete n | d n | 删除断点 |
| disable |  | 禁用断点 |
| enable |  | 启用断点 |
| info | i | 描述程序状态，比如：i break显示有哪些断点 |
| run | r | 开始运行程序 |
| display | disp | 跟踪查看某个变量，每次停下来都显示其值 |
| print | p | 打印内部变量值 |
| watch |  | 监视变量新旧值变化 |
| step | s | 下一步 |
| next | n | 下一条语句 |
| continue | c | 继续运行程序，直到遇到下一个断点 |
| finish |  | 跳出当前函数 |
| set var name = v |  | 设置变量的值 |
| backtrace | bt | 查看堆栈 |
| start |  | 开始执行程序，在main函数的第一条语句前停下 |
| frame | f | 查看栈帧 |
| quit | q | 离开gdb |
| edit |  | 在gdb中进行编辑 |
| whatis |  | 查看变量的类型 |
| search |  | 搜索源文件中的文本 |
| file |  | 装入需要调试的程序 |
| kill |  | 终止正在调试的程序 |


### 2. gdb调试多进程

1. 先运行服务器，然后找到目标子进程的PID，再将其附加(attach)到gdb调试器
  ```
  attach <pid>
  ```

2. 调试器选项`follow-work-mode`
  `follow-fork-mode`选项允许我们选择程序在执行fork系统调用之后是继续调试父进程还是调试子进程，在启动gdb之后通过下面的命令设置：
  ```
  set follow-fork-mode child  //调试子进程
  set follow-fork-mode parent //调试父进程
  ```
3. 调试器选项`detach-on-fork`
  `detach-on-fork`选项指示gdb在fork后调试某个进程时，是断开(detach)另一个进程的调试还是交给gdb控制
  ```
  set detach-on-fork [on|off]
  ```
  - on：表示断开另一个进程
  - off：gdb将控制父进程和子进程。当follow-frok-mode指定的进程被调试时，另一个进程处于暂停(suspended)状态

### 3. gdb调试多线程

gdb有一组命令可辅助多线程程序的调试：

- info threads：显式当前可调试的所有线程。gdb会为每个线程分配一个ID，我们可以使用这个ID来操作对应的线程，ID前有*号的线程是当前被调试的线程

- thread ID：调试目标ID指定的线程

- set scheduler-locking [off|on|step]：调试多线程程序时，默认除了被调试的线程在执行外，其他线程也在继续执行。通过这个命令可以只让被调试的线程运行：

  该命令设置scheduler-locking的值：
  - off代表不锁定任何线程，即所有线程都可以继续执行
  - on表示只有当前调试线程会继续执行
  - step表示在单步执行时，除了next过一个函数的情况(这其实是一个设置断点然后continue的行为)以外，只有当前线程执行

调试进程池和线程池程序时：可以先将池中的进程个数或线程个数减少至1，以观察程序逻辑是否正确，然后逐步增加进程和线程的数量，以调试进程或线程的同步是否正确

### 4. 调试core dump

core dump又叫核心转储, 当程序运行过程中发生异常, 程序异常退出时, 由操作系统把程序当前的内存状况存储在一个core文件中, 叫core dump. (linux中如果内存越界会收到SIGSEGV信号，然后就会core dump)

#### 4.1 造成segment fault，产生core dump的可能原因

- 内存访问越界

  - 由于使用错误的下标，导致数组访问越界

  - 搜索字符串时，依靠字符串结束符来判断字符串是否结束，但是字符串没有正常的使用结束符

  - 使用strcpy, strcat, sprintf, strcmp, strcasecmp等字符串操作函数，将目标字符串读/写爆。应该使用strncpy, strlcpy, strncat, strlcat, snprintf, strncmp, strncasecmp等函数防止读写越界。

- 多线程程序使用了线程不安全的函数

- 多线程读写的数据未加锁保护。对于会被多个线程同时访问的全局数据，应该注意加锁保护，否则很容易造成core dump

- 非法指针

  - 使用空指针

  - 随意使用指针转换。一个指向一段内存的指针，除非确定这段内存原先就分配为某种结构或类型，或者这种结构或类型的数组，否则不要将它转换为这种结构或类型的指针，而应该将这段内存拷贝到一个这种结构或类型中，再访问这个结构或类型。这是因为如果这段内存的开始地址不是按照这种结构或类型对齐的，那么访问它时就很容易因为bus error而core dump.

- 堆栈溢出.不要使用大的局部变量（因为局部变量都分配在栈上），这样容易造成堆栈溢出，破坏系统的栈和堆结构，导致出现莫名其妙的错误。

#### 4.2 配置操作系统使其产生core文件

首先通过ulimit命令查看一下系统是否配置支持了dump core的功能。通过ulimit -c或ulimit -a，可以查看core file大小的配置情况，如果为0，则表示系统关闭了dump core。可以通过ulimit -c unlimited来打开。 **若发生了段错误，但没有core dump，可能是由于系统禁止core文件的生成。**

解决方法:
```
$ulimit -c unlimited　　（只对当前shell进程有效）
```
或在~/.bashr*　的最后加入： ulimit -c unlimited （一劳永逸）

查看系统是否禁止core文件生成：

```
\# ulimit -c

0

$ ulimit -a

core file size          (blocks, -c) 0

data seg size           (kbytes, -d) unlimited

file size               (blocks, -f) unlimited
```

#### 4.3 用gdb查看core文件

发生core dump之后, 用gdb进行查看core文件的内容, 以定位文件中引发core dump的行.

```
gdb [exec file]  \[ core file]
```

如: 

```
gdb ./test test.core
```

#### 4.4 使用core文件定位core dump位置

先使用命令 gdb [exec file]  \[ core file]查看core文件，然后输入where命令，gdb就会输出coredump的位置。


### 5. 调试宏

调试宏需要gcc在编译时加上`-ggdb3`参数，然后可以使用下面的gdb宏调试命令来查看宏：

- info macro：查看这个宏在哪些文件被引用，以及宏定义是什么样的
- macro：查看宏展开的样子

### 6. 源文件

有时候使用gdb调试提示找不到源文件，这时候需要注意两点：

- 编译时是否加-g参数以及保护debug信息
- 源码路径是否设置正确，可以使用gdb的`directory`命令来设置源文件的目录

### 7. 条件断点

```
break [where] if [condition]
```

### 8. 命令行参数

如果调试的程序运行时需要命令行参数，有两种方法设置：

- gdb命令行的`-args`参数
- gdb环境中`set args`命令

### 9. x命令

无需变量名查看内存

### 10. command命令

command命令可以将一组gdb命令打包，当断点到达时，自动执行command打包的gdb命令

### 11. 调试脚本

优点：

- 自己定义一些方便的命令，比如打印STL容器中的内容
- 不用每次打开gdb都要重新打一次断点

使用方法：

一般有三种方法：https://blog.csdn.net/cnsword/article/details/16337031

好用的调试脚本推荐：

- 查看STL容器：http://www.yolinux.com/TUTORIALS/src/dbinit_stl_views-1.03.txt
- gdb init：https://github.com/gdbinit/Gdbinit/blob/master/gdbinit

参考：

[gdb中应该知道的几个调试方法](https://coolshell.cn/articles/3643.html)

[使用gdb调试多进程程序](https://www.ibm.com/developerworks/cn/linux/l-cn-gdbmp/index.html)

## 2. 图像界面调试

### 2.1 gdb自带的tui

```
gdb --tui a.out
```

更具体的使用方法参考[该博客](https://blog.csdn.net/xu415/article/details/19021759)

### 2.2 在浏览器显示调试界面---gdbgui

[Github项目地址](https://github.com/cs01/gdbgui)

#### 2.2.1 安装：

```
curl https://raw.githubusercontent.com/cs01/pipx/master/get-pipx.py | python3

pipx install gdbgui
```

#### 2.2.2 使用：

```
gdbgui -p 10001 -r "a.out"
```
-p 制定端口号 -r 表示远程remote调试

运行之后就可以在本地浏览器调试服务器程序

[参考教程](https://blog.csdn.net/songchuwang1868/article/details/86132281)

## 3. 调试命令

- 查看vector内容

```
*(YOURVECTOR._M_impl._M_start)@(YOURVECTOR.size())
```