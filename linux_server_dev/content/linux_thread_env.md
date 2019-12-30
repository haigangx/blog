# 多线程环境

1、可重入函数
可重入函数：如果一个函数能被多个线程同时调用且不发生竞态条件，则我们称它是线程安全的，或者说它是可重入函数
许多库函数因为内部使用了静态变量导致不可重入，Linux对这些不可重入的函数提供了对应的重入版本，可重入版本的函数是在原函数名尾部加上_r
在多线程程序中调用库函数，一定要调用其可重入版本

2、线程和进程
提出：fork之后，子进程将自动继承父进程中互斥锁(条件变量类似)的状态，也就是说，父进程中已经被加锁的互斥锁在子进程中也是被锁住的，这引起一个死锁问题：
    子进程可能不清楚从父进程继承而来的互斥锁的具体状态(加锁状态或解锁状态)，这个互斥锁可能被加锁了，但并不是由调用fork函数的那个线程锁住的，而是由其他线程锁住的，如果是这种情况，则子进程若再次对该互斥锁执行加锁操作就会导致死锁
代码如下：
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

pthread_mutex_t mutex;
//子线程运行的函数，它首先获得互斥锁mutex，然后暂停5s再释放该互斥锁
void* another(void* arg)
{
    printf("in child thread, lock the mutex\n");
    pthread_mutex_lock( &mutex );
    sleep( 5 );
    pthread_mutex_unlock( &mutex );
}
int main()
{
    pthread_mutex_init( &mutex, NULL );
    pthread_t id;
    pthread_create( &id, NULL, another, NULL );
    //父进程中的主线程暂停1s，以确保在执行fork操作之前，子线程已经开始运行并获得了互斥变量mutex
    sleep(1);
    int pid = fork();
    if ( pid < 0 )
    {
        pthread_join( id, NULL );
        pthread_mutex_destroy( &mutex );
        return 1;
    }
    else if ( pid == 0 )
    {
        printf( "I am in the child, want to get the lock\n" );
        //子进程从父进程继承了互斥锁mutex的状态，该互斥锁处于锁住的状态，这是由父进程中的子进程执行pthread_mutex_lock引起的
        //因此下面这句加锁操作会一直阻塞，尽管从逻辑上来说它是不应该阻塞的
        pthread_mutex_lock( &mutex );
        printf( "I can not run to here, cop...\n" );
        pthread_mutex_lock( &mutex );
        exit(0);
    }
    else 
    {
        wait( NULL );
    }
    pthread_join( id, NULL );
    pthread_mutex_destroy( &mutex );
    return 0;
}
为应对这种情况，pthread提供了一个专门的函数pthread_atfork，以确保fork调用后父进程和子进程都拥有一个清楚的锁状态：
#include <pthread.h>
int pthread_atfork( void (*prepare)(void), void (*parent)(void), void (*child)(void) );
该函数将建立3个fork句柄来帮助我们清理互斥锁的状态：
    * prepare句柄将在fork调用创建出子进程之前被执行，它可以用来锁住所有父进程中的互斥锁
    * parent句柄则是fork调用创建出子进程之后，而fork返回之前，在父进程中被执行，作用是释放所有在prepare句柄中被锁住的互斥锁
    * child句柄是fork返回之前，在子进程中被执行，和parent句柄一样，child句柄也是用于释放所有在prepare句柄中被锁住的互斥锁
该函数成功时返回0，失败时返回错误码
pthread_atfork函数应该在fork调用前执行：
void prepare()
{
    pthread_mutex_lock( &mutex );
}
void infork()
{
    pthread_mutex_unlock( &mutex );
}
pthread_atfork( prepare, infork, infork );
3、线程和信号
每个线程都可以独立设置信号掩码，在多线程环境下应该使用pthread版本的sigprocmask函数来设置线程信号掩码：
#include <pthread.h>
#include <signal.h>
int pthread_sigmask( int how, const sigset_t* newmask, sigset_t* oldmask );
该函数参数的含义和sigprocmask的参数完全相同
pthread_sigmask成功时返回0，失败时返回错误码

进程中线程处理信号的特点：
1、进程中的所有线程共享该进程的信号，所以线程库将根据线程掩码决定把信号发送给哪个具体的线程。因此，如果我们在每个子线程中都单独设置信号掩码，就很容易导致逻辑错误
2、所有线程共享信号处理函数，也就是说：当我们在一个线程中设置了某个信号的信号处理函数后，它将覆盖其他线程为同一个信号设置的信号处理函数
上面两点都说明了我们应该定义一个专门的线程用来处理所有信号，这通过如下两个步骤实现：
(1)在主线程创建出其他子线程之前就调用pthread_sigmask来设置好信号掩码，所有新创建的子线程都将自动继承这个信号掩码，这样做之后，实际上所有线程都不会响应被屏蔽的信号了
(2)在某个线程中调用如下函数来等待信号并处理之：
#include <signal.h>
int sigwait( const sigset_t* set, int* sig );
set：指定需要等待的信号的集合，可以简单的将其指定为在第一步中创建的信号掩码，表示在该线程中等待所有被屏蔽的信号
sig：用于存储该函数返回的信号值
sigwait成功时返回0，失败时返回错误码
sigwait正确返回之后，我们就可以对接收到的信号做处理了，显然，如果我们使用了sigwait，就不应该再为信号设置信号处理函数了，因为当程序接收到信号时，二者中只能有一个起作用
用一个线程处理所有信号的例子：
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define handle_error_en(en, msg) \
    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while(0)

static void *sig_thread( void* arg )
{
    sigset_t *set = (sigset_t *)arg;
    int s, sig;
    for ( ; ; )
    {
        //第二个步骤，调用sigwait等待信号
        s = sigwait( set, &sig );
        if ( s != 0 )
            handle_error_en( s, "sigwait" );
        printf( "Signal handling thread got signal %d\n", sig );
    }
}
int main( int argc, char* argv[] )
{
    pthread_t thread;
    sigset_t set;
    int s;
    
    //第一个步骤，在主线程中设置信号掩码
    sigemptyset( &set );
    sigaddset( &set, SIGQUIT );
    sigaddset( &set, SIGUSR1 );
    s = pthread_sigmask( SIG_BLOCK, &set, NULL );
    if ( s != 0 )
        handle_error_en( s, "pthread_sigmask" );
        
    s = pthread_create( &thread, NULL, &sig_thread, (void *)&set );
    if ( s != 0 )
        handle_error_en( s, "pthread_create" );
        
    pause();
}

pthread还提供了下面的方法，使得可以明确的将一个信号发送给指定的线程
#include <signal.h>
int pthread_kill( pthread_t thread, int sig );
thread：指定目标线程
sig：指定待发送的信号，如果sig为0，则pthread_kill不发送信号，但它仍然会执行错误检查，我们可以使用这种方式来检测目标线程是否存在
pthread_kill成功时返回0，失败时返回错误码
