信号是由用户、系统或者进程发送给目标的信息，以通知目标进程某个状态的改变或系统异常。Linux信号可由如下条件产生：

* 对于前台进程，用户可以通过输入特殊的终端字符来为其发送信号，比如输入Ctrl+C发送中断信号
* 系统异常。比如浮点异常或非法内存段访问
* 系统状态变化。比如alarm定时器到期引起的SIGALRM信号
* 运行kill命令或调用kil函数

服务器程序必须处理(或至少忽略)一些常见信号，以免异常终止

## 发送信号

#include <sys/types.h>
#include <signal.h>
int kill( pid_t pid, int sig );

pid参数及含义：

pid参数	含义
pid > 0	发给PID为pid的进程
pid = 0	发给本进程组内的其他进程
pid = -1	发送给除init进程外的所有进程，但发送者需要拥有对目标进程发送信号的权限
pid < -1	发送给组ID为-pid的进程组的所有成员
Linux定义的信号值都大于0，将sig取0，kill并不发送任何信号但是可以以此来检测目标进程或进程组是否存在，因为kill函数会在信号发送之前进行检查工作，不过这种检测方式并不可靠:
PID回绕导致被检测的PID并不是我们期望的进程的PID
这种检测并非原子操作
kill函数成功返回0，失败返回-1并设置errno
errno	含义
EINVAL	无效的信号
EPERM	该进程没有权限发送信号给任何一个目标进程
ESRCH	目标进程或进程组不存在


## 信号处理方式

信号处理函数原型如下：
#include <signal.h>
typedef void (*__sighandler_t) ( int );
信号处理函数只带有一个整形参数，该参数用来指示类型。信号处理函数应该是可重入的，否则很容易引发一些竞态条件。所以在信号处理函数中严禁调用一些不安全的函数
bits/signum.h头文件中定义了信号的两种其他处理方式——SIG_IGN和SIG_DEL:
#include <bits/signum.h>
#define SIG_DFL ((__sighandle_t) 0)
#define SIG_IGN ((__sighandle_t) 1)
SIG_IGN：忽略目标信号
SIG_DFL：使用信号的默认处理方式，默认处理方式有：结束进程(Term)、忽略信号(Ign)、结束进程并生成核心转储文件(Core)、暂停进程(Stop)、继续进程(Cont)

## Linux信号

Linux的可用信号都定义在bits/signum.h头文件中，其中包括标准信号和POSIX实时信号。
标准信号见下表：
信号	起源	默认行为	含义
SIGHUP	POSIX	Term	控制终端挂起
SIGINT	ANSI	Term	键盘输入以中断进程(Ctrl+C)
SIGQUIT	POSIX	Core	键盘输入使进程退出(Ctrl+\)
SIGILL	ANSI	Core	非法指令
SIGTRAP	POSIX	Core	断点陷阱，用于调试
SIGABRT	ANSI	Core	进程调用abort函数时生成该信号
SIGIOT	4.2BSD	Core	和SIGABRT相同
SIGBUS	4.2BSD	Core	总线错误，错误内存访问
SIGFPE	ANSI	Core	浮点异常
SIGKILL	POSIX	Term	终止一个进程(不可被捕获或忽略)
SIGUSR1	POSIX	Term	用户自定义信号之一
SIGSEGV	ANSI	Core	非法内存段引用
SIGUSR2	POSIX	Term	用户自定义信号之二
SIGPIPE	POSIX	Term	往读端被关闭的管道或者socket连接中写数据
SIGALRM	POSIX	Term	由alarm或setitimer设置的实时闹钟超时引起
SIGTERM	ANSI	Term	终止进程，kill命令默认发送该信号
SIGSTKFLT	Linux	Term	早期的Linux使用该信号来报告数学协处理器栈错误
SIGCLD	System V	Ign	和SIGCHLD相同
SIGCHLD	POSIX	Ign	子进程状态发生变化(退出或暂停)
SIGCONT	POSIX	Cont	启动被暂停的进程(Ctrl+Q),如果目标进程未处于暂停状态，则信号被忽略
SIGSTOP	POSIX	Stop	暂停进程(Ctrl+S)(不可被捕获或忽略)
SIGTSTP	POSIX	Stop	挂起进程(Ctrl+Z)
SIGTTIN	POSIX	Stop	后台进程试图从终端读取输入
SIGTTOU	POSIX	Stop	后台进程试图往终端输出内容
SIGURG	4.2BSD	Ign	socket连接上接收到紧急数据
SIGXCPU	4.2BSD	Core	进程的CPU使用时间超过其软限制
SIGXFSZ	4.2BSD	Core	文件尺寸超过其软限制
SIGVTALRM	4.2BSD	Term	与SIGALRM类似，不过它只统计本进程用户空间代码的运行时间
SIGPROF	4.2BSD	Term	与SIGALRM类似，它同时统计用户代码和内核的运行时间
SIGWINCH	4.3BSD	Ign	终端窗口大小发生变化
SIGPOLL	System V	Term	与SIGIO类似
SIGIO	4.2BSD	Term	IO就绪，比如socket上发生可读事件、可写事件。因为TCP服务器可触发SIGIO的条件很多，故而SIGIO无法在TCP服务器中使用。SIGIO信号可用在UDP服务器中，不过也非常少见
SIGPWR	System V	Term	对于使用UPS(Uninterruptable Power Supply)的系统，当电池电量过低时，SIGPWR信号将被触发
SIGSYS	POSIX	Core	非法系统调用
SIGUNUSED	
Core	保留，通常和SIGSYS效果相同
与网络编程密切相关的几个信号：SIGHUP、SIGPIPE、SIGURG

## 中断系统调用

如果程序在执行处于阻塞状态的系统调用时接收到信号，并且我们为该信号设置了信号处理函数，则默认情况下系统调用将被中断，并且errno被设置为EINTR。可以使用sigaction函数为信号设置SA_RESTART标志以自动重启被该信号中断的系统调用
对于默认行为是暂停进程的信号(如SIGSTOP、SIGTTIN)，如果没有为它们设置信号处理函数，则他们也可以中断某些系统调用(ex:connect、epoll_wait)。POSIX没有规定这种行为，这是Linux独有的

