# posix信号量

POSIX信号量函数的名字都以sem_开头，并不像大多数线程函数那样以pthread_开头

常用的POSIX信号量函数：

```
#include <semaphore.h>
int sem_init( sem_t* sem, int pshared, unsigned int value );
int sem_destroy( sem_t* sem );
int sem_wait( sem_t* sem );
int sem_trywait( sem_t* sem );
int sem_post( sem_t* sem );
```

第一个参数sem指向被操作的信号量

sem_init函数用于初始化一个未命名的信号量：
- pshared：指定信号量的类型，如果其值为0，就表示这个信号量是当前进程的局部信号量，否则该信号量就可以在多个进程之间共享
- value：指定信号量的初始值

初始化一个已经被初始化的信号量将导致不可预期的结果

sem_destroy：用于销毁信号量，以释放其占用的内核资源，如果销毁一个正被其他线程等待的信号量，将导致不可预期的结果

sem_wait：以原子操作的方式将信号量的值减1.如果信号量的值为0，则sem_wait将被阻塞，直到这个信号量具有非0值

sem_trywait：与sem_wait函数相似，不过它始终立即返回，而不论被操作的信号量是否具有非0值，相当于sem_wait的非阻塞版本。
- 当信号量的值非0时，sem_trywait对信号量执行减1操作
- 当信号量的值为0时，它将返回-1并设置errno为EAGAIN

sem_post：以原子操作的方式将信号量的值加1，当信号量的值大于0时，其他正在调用sem_wait等待信号量的线程将被唤醒

上面这些函数成功时返回0，失败时返回-1并设置errno
