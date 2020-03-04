# 创建线程和结束线程

1、pthread_create：创建一个线程：
#include <pthread.h>
int pthread_create( pthread_t* thread, const pthread_attr_t* attr, void* (*start_routine)(void *), void* arg );
thread：新线程的标识符，后续pthread_*函数通过它来引用新线程，类型pthread_t定义如下：
#inclue <bits/pthreadtypes.h>
typedef unsigned long int pthread_t;
pthread_t是一个整数类型，实际上Linux几乎所有的资源标识符都是一个整型数，比如socket、各种System V IPV标识符等
attr：设置新线程的属性，传递NULL表示使用默认线程属性。
start_routine和arg：分别指定新线程将运行的函数及其参数
pthread_create成功时返回0，失败时返回错误码
一个用户可以打开的线程数量不能炒作RLIMIT_NPROC软资源限制，此外系统上所有用户能创建的线程总数也不能超过/proc/sys/kernel/threads-max内核参数所定义的值

2、pthread_exit：退出线程
线程创建好之后，内核就调度内核线程执行start_routine函数指针所指向的函数，在线程函数结束时调用pthread_exit函数来保证线程安全退出：
#include <pthread.h>
void pthread_exit( void* retval );
retval：线程的退出信息
pthread_exit执行完之后不会返回到调用者，而且永远不会失败

3、pthread_join：线程回收
一个进程中的所有线程都可以调用pthread_join函数来回收其他线程(前提是目标线程是可回收的)，即等待其他线程结束，类似与回收进程的wait和waitpid系统调用
#include <pthread.h>
int pthread_join( pthread_t thread, void** retval );
thread：目标线程的标识符
retval：目标线程返回的退出信息
pthread_join将一直阻塞直到被回收的线程结束为止，成功返回0，失败返回错误码：

4、pthread_cancel：取消线程
pthread_cancel异常终止一个线程，即取消线程：
#include <pthread.h>
int pthread_cancel( pthread_t thread );
thread：目标线程的标识符
pthread_cancel成功时返回0，失败时返回错误码
不过，接收到取消请求的目标线程可以决定是否允许被取消以及如何取消，这分别由如下两个函数完成：
#include <pthread.h>
int pthread_setcancelstate( int state, int *oldstate );
int pthread_setcanceltype( int type, int *oldtype );
这两个函数的第一个参数分别用于设置线程的取消状态(是否允许取消)和取消类型(如何取消)
第二个参数分别记录线程原来的取消状态和取消类型
state参数的两个可选值：
* PTHREAD_CANCEL_ENABLE：允许线程被取消，是线程被创建时的默认取消状态
* PTHREAD_CANCEL_DISABLE：禁止线程被取消，这种情况下，如果一个线程收到取消请求，则它会将请求挂起直到该进程允许被取消
type参数的两个可选值：
* PTHREAD_CANCEL_ASYNCHRONOUS：线程随时都可以被取消，接收到取消请求的目标线程将立即采取行动
* PTHREAD_CANCEL_DEFERRED：允许目标线程的取消动作推迟到下个取消点被调用，取消点包括：pthread_join、pthread_testcancel、pthread_cond_wait、pthread_cond_timedwait、sem_wait和sigwait，其他可能阻塞的系统调用，如read、write也可以成为取消点，不过为了安全起见，我们最好在可能会被取消的代码中调用pthread_testcancel函数以设置取消点

pthread_setcancelstate和pthread_setcanceltype成功时返回0，失败时返回错误码

