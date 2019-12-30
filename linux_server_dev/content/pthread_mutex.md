# 互斥锁

互斥锁(互斥量)可以用于保护关键代码段，以确保其独占式的访问，这有点像一个二进制信号量：
    * 当进入关键代码段时，我们需要获得互斥锁并将其加锁，这等价于二进制信号量的P操作；
    * 当离开关键代码段时，我们需要对互斥锁解锁，以唤醒其它等待该互斥锁的线程，这等价于二进制信号量的V操作
1、互斥锁基础API
POSIX互斥锁相关函数：
#include <pthread.h>
int pthread_mutex_init( pthread_mutex_t* mutex, const pthread_mutexattr_t* mutexattr );
int pthread_mutex_destroy( pthread_mutex_t* mutex );
int pthread_mutex_lock( pthread_mutext_t* mutex );
int pthread_mutex_trylock( pthread_mutex_t* mutex );
int pthread_mutex_unlock( pthread_mutex_t* mutex );
mutex参数指向要操作的目标互斥锁，互斥锁的类型是pthread_mutex_t结构体

pthread_mutex_init：初始化互斥锁
    * mutexattr：指定互斥锁的属性，如果设置为NULL则表示使用默认属性，使用pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER将互斥锁的各个字段都初始化为0

pthread_mutex_lock：以原子操作的方式给一个互斥锁加锁，如果目标互斥锁已经被锁，则pthread_mutex_lock调用将阻塞，直到该互斥锁的占有者将其解锁

pthread_mutex_trylock：与pthread_mutex_lock类似，不过它始终立即返回，而不论被操作的互斥锁是否已经被加锁，相当于pthread_mutex_lock的非阻塞版本
    * 当目标互斥锁未被加锁时，pthread_mutex_trylock对互斥锁执行加锁操作
    * 当互斥锁已经被加锁时，pthread_mutex_trylock将返回错误码EBUSY
    上面的行为是针对普通锁而言，对于其他类型的锁而言，这两个加锁函数会有不同的行为

pthread_mutex_unlock：以原子操作的方式给一个互斥锁解锁。如果此时有其他进程正在等待这个互斥锁，则这些线程中的某一个将获得它

上面这些函数成功时返回0，失败则返回错误码

2、线程同步——互斥锁属性
pthread_mutexattr_t结构体定义了一套完整的互斥锁属性。线程库提供了一系列函数来操作pthread_mutexattr_t类型的变量来获取和设置互斥锁属性：
#include <pthread.h>
//初始化互斥锁属性对象
int pthread_mutexattr_init( pthread_mutexattr_t* attr );
//销毁互斥锁属性对象
int pthread_mutexattr_destroy( pthread_mutexattr_t* attr );
//获取和设置互斥锁的pshared属性
int pthread_mutexattr_getpshared( const pthread_mutexattr_t* attr, int* pshared );
int pthread_mutexattr_setpshared( pthread_mutexattr_t* attr, int pshared );
//获取和设置互斥锁的type属性
int pthread_mutexattr_gettypes( const pthread_mutexattr_t* attr, int* type );
int pthread_mutexattr_settype( pthread_mutexattr_t* attr, int type );
互斥锁的两种常用属性：pshared和type：
互斥锁属性pshared指定是否允许跨进程共享互斥锁，可选值有两个：
    * PTHREAD_PROCESS_SHARED：互斥锁可以被跨进程共享
    * PTHREAD_PROCESS_PRIVATE：互斥锁只能被和锁的初始化进程隶属于同一个进程的线程共享
互斥锁属性type指定互斥锁的类型，Linux支持如下4中类型：
    * PTHREAD_MUTEX_NORMAL：普通锁
        互斥锁的默认类型，当一个线程对一个普通锁加锁后，其余请求该锁的线程将形成一个等待队列，并在该锁解锁后按优先级获得它
        这种锁类型保证了资源分配的公平性，但这种锁也容易引发问题：
            * 一个线程如果对一个已经加锁的普通锁再次加锁，将引发死锁；
            * 对一个已经被其他线程加锁的普通锁解锁，或者对一个已经解锁的普通锁再次解锁，将导致不可预期的后果
    * PTHREAD_MUTEX_ERRORCHECK：检错锁
        * 一个线程如果对一个已经加锁的检错锁再次加锁，则加锁操作返回EDEADLK
        * 对一个已经被其他线程加锁的检错锁解锁，或者对一个已经解锁的检错锁再次解锁，则解锁操作返回EPERM
    * PTHREAD_MUTEX_RECURSIVE：嵌套锁
        这种锁允许一个线程在释放锁之前多次对它加锁而不发生死锁，不过其他线程如果要获得这个锁，则当前锁的拥有者必须执行相应次数的解锁操作
        对一个已经被其他线程加锁的嵌套锁解锁，或者对一个已经解锁的嵌套锁再次解锁，则解锁操作返回EPERM
    * PTHREAD_MUTEX_DEFAUTL：默认锁
        一个线程如果对一个已经加锁的默认锁再次加锁，或者对一个已经被其他线程加锁的默认锁解锁，或者对一个已经解锁的默认锁再次解锁，将导致不可预期的后果，这种锁在实现上可能被映射为上面三种锁之一

3、死锁
使用互斥锁容易引发死锁问题：死锁使得一个或多个线程被挂起而无法继续执行，而且这种情况不容易被发现
在一个线程中对一个已经加锁的普通锁再次加锁将导致死锁
另外，如果两个线程按照不同的顺序申请同时拥有两个互斥锁也容易产生死锁
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

int a = 0;
int b = 0;
pthread_mutex_t mutex_a;
pthread_mutex_t mutex_b;

void *another( void* arg )
{
    pthread_mutex_lock( &mutex_b );
    printf( "in child thread, got mutex b, waiting for mutex a\n" );
    sleep( 5 );
    ++b;
    pthread_mutex_lock( &mutex_a );
    b += a++;
    pthread_mutex_unlock( &mutex_a );
    pthread_mutex_unlock( &mutex_b );
    pthread_exit( NULL );
}

int main(  )
{
    pthread_t id;

    pthread_mutex_init( &mutex_a, NULL );
    pthread_mutex_init( &mutex_b, NULL );
    pthread_create( &id, NULL, another, NULL );

    pthread_mutex_lock( &mutex_a );
    printf( "in parent thread, got mutex a, waiting for mutex b\n" );
    sleep( 5 );     //两个线程都必须有sleep函数，保证两个线程都能拿到一个锁
    ++a;
    pthread_mutex_lock( &mutex_b );
    a += b++;
    pthread_mutex_unlock( &mutex_b );
    pthread_mutex_unlock( &mutex_a );

    pthread_join( id, NULL );
    pthread_mutex_destroy( &mutex_a );
    pthread_mutex_destroy( &mutex_b );

    return 0;
}
