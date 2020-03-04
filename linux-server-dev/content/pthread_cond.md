# 条件变量

互斥锁是用于同步线程对共享数据的访问，条件变量则是用于在线程之间同步共享数据的值
条件变量提供了一种线程间的通知机制：当某个共享数据达到某个值的时候，唤醒等待这个共享数据的线程
条件变量的相关函数：
#include <pthread.h>
int pthread_cond_init( pthread_cond_t* cond, const pthread_condaddr_t* cond_attr );
int pthread_cond_destroy( pthread_cond_t* cond );
int pthread_cond_broadcast( pthread_cond_t* cond );
int pthread_cond_signal( pthread_cond_t* cond );
int pthread_cond_wait( pthread_cond_t* cond, pthread_mutex_t* mutex );
cond：指向要操作的目标条件变量，条件变量类型是pthread_cond_t结构体

pthread_cond_init：初始化条件变量
    * cond_attr：指定条件变量的属性。设置为NULL表示使用默认属性，条件变量属性不多并且和互斥锁属性类似
    * 使用pthread_cond_t cond = PTHREAD_COND_INITIALIZER初始化条件变量，将条件变量各个字段初始化为0

pthread_cond_destroy：销毁条件变量，以释放其占用的内核资源。销毁一个正在被等待的条件变量将失败并返回EBUSY

pthread_cond_broadcase：以广播的方式唤醒所有等待目标条件变量的线程

pthread_cond_signal：唤醒一个等待目标条件变量的线程，至于哪个线程将被唤醒则取决于线程的优先级和调度策略
唤醒一个指定线程的方法：定义一个能够唯一表示目标线程的全局变量，在唤醒等待条件变量的线程前先设置该变量为目标线程，然后采用广播方式唤醒所有等待条件变量的线程，这些线程被唤醒后都检查该变量以判断被唤醒的是否是自己，如果是自己就开始执行后续代码，如果不是则返回继续等待

pthread_cond_wait：等待目标条件变量。mutex参数用于保护条件变量的互斥锁，以确保pthread_cond_wait操作的原子性。在调用pthread_cond_wait前，必须确保互斥锁mutex已经加锁，否则将导致不可预期的结果。pthread_cond_wait函数执行时，首先把调用线程放入条件变量的等待队列中，然后将互斥锁mutex解锁，可见，从pthread_cond_wait开始执行到其调用线程被放入条件变量的等待队列之间的这段时间内，pthread_cond_signal和pthread_cond_broadcast等函数不会修改条件变量。换言之，pthread_cond_wait函数不会错过目标条件变量的任何变化。当pthread_cond_wait函数成功返回时，互斥锁mutex将再次被锁上

以上函数成功时返回0，失败时返回错误码

