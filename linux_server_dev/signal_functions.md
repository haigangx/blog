# 信号函数

## signal系统调用

为一个信号设置处理函数：
#include <signal.h>
_sighandler_t signal( int sig, _sighandler_t _handler );
sig：要捕获的信号类型
_handler：_sighandler_t类型的函数指针，用于指定信号sig的处理函数
返回值：前一次调用signal函数时传入的函数指针，或者是信号sig对应的默认处理函数指针SIG_DEF
signal函数出错时返回SIG_ERR并设置errno


# sigaction系统调用

设置信号处理函数更健壮的接口：
#include <signal.h>
int sigaction( int sig, const struct sigaction* act, struct sigaction* oact );
sig：指定要捕获的信号类型
act：新的信号处理方式
oact：先前的信号处理方式
sigaction结构体类型如下：
struct sigaction
{
#ifndef __USE_POSIX199309
    union
    {
        _sighandler_t sa_handler;
        void (*sa_sigaction)(int, siginfo_t*, void*);
    }__sigaction_handler;
#define sa_handler  __sigaction_handler.sa_handler
#define sa_sigaction __sigaction_handler.sa_sigaction
#else
    _sighandler_t sa_handler;
#endif
    _sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer) (void);
};
sa_handler：指定信号处理函数
sa_mask：设置进程的信号掩码(在进程原有信号掩码的基础上增加信号掩码)，这些信号不会发送给进程
sa_flags：设置程序收到信号时的行为，可取值见下表：
选项	含义
SA_NOCLDSTOP	如果sig参数为SIGCHLD，则该标志表示子进程暂时不生成SIGCHLD信号
SA_NOCLDWAIT	如果sig参数为SIGCHLD，则该标志表示子进程结束不产生僵尸进程
SA_SIGINFO	使用sa_sigaction作为信号处理函数(而不是sa_handler)
SA_ONSTACK	调用由sigaltstack函数设置的可选信号栈上的信号处理函数
SA_RESTART	重新调用被该信号终止的系统调用
SA_NODEFER	当接收到信号并进入其信号处理函数时，不屏蔽该信号。默认情况下，我们期望进程在处理一个信号时不再接收到同种信号，否则将引起一些竞态条件
SA_RESETHAND	信号处理函数执行完以后，恢复信号的默认处理方式
SA_INTERRUPT	 中断系统调用
SA_NOMASK	同SA_NODEFER
SA_ONESHOT	同SA_RESETHAND
SA_STACK	同SA_ONSTACK
sa_restorer：过时不再使用
sigaction成功返回0，失败返回-1并设置errno
