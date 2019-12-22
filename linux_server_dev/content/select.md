# select

select API
#include <sys/select.h>
int select( int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, 
        struct tiemval* timeout );
1、nfds：指定被监听的文件描述符的总数。它通常被设置为select监听的所有文件描述符的最大值加1，因为文件描述符是从0开始计数的
2、readfds、writefds和exceptfds：分别为可读、可写和异常事件对应的文件描述符集合。应用程序通过这3个参数传入分别需要监控的文件描述符，select调用返回时，内核将修改它们来通知应用程序哪些文件描述符已经就绪
fd_set结构体仅包含一个整型数组，该数组的每个元素的每一位(bit)标记一个文件描述符.fd_set能容纳的文件描述符数量由FD_SETSIZE指定，这限制了select能同时处理的文件描述符的总量是有限的
通过下列宏来对fd_set结构进行操作:
#include <sys/select.h>
FD_ZERO( fd_set *fdset );   //清除fdset所有位
FD_SET( int fd, fd_set *fdset );    //设置fdset的位fd
FD_CLR( int fd, fd_set *fdset );    //清除fdset的位fd
int FD_ISSET( int fd, fd_set *fdset );  //测试fdset的位fd是否被设置
3、timeout：设置select函数的超时返回时间，为timeval类型的指针，函数返回会修改timeout为程序select的等待时间，不过并不能完全信任timeout返回的时间，如果调用失败timeout的值将是不确定的
timeval结构体定义如下：
struct timeval
{
    long tv_sec;    //秒数
    long tv_usec;   //微秒数
};
如果timeout传入select的值为0，则select将立即返回，如果timeout为NULL，则select将一直阻塞直到某个文件描述符就绪
4、返回值：
select成功时返回就绪的文件描述符个数
如果超时时间内没有任何文件描述符就绪，select返回0
select失败时返回-1并设置errno
如果在select等待期间，程序收到信号，则select立即返回-1并设置errno为EINTR

文件描述符就绪条件
socket可读：
(1)socket内核接收缓冲区中的字节数大于或等于其低水位标记SO_RCVLOWAT
(2)socket通信的对方关闭连接，此时对该socket的读操作将返回0
(3)监听socket上有新连接请求
(4)socket上有未处理的错误。此时可以使用getsockopt来读取和清除该错误(带外数据)
socket可写：
(1)socket内核发送缓冲区中的可用字节数大于等于其低水位标记SO_SNDLOWAT
(2)socket的写操作被关闭，对写操作被关闭的socket执行写操作将触发SIGPIPE信号
(3)socket使用非阻塞connect连接成功或者失败(超时)之后
(4)socket上有未处理的错误，此时可以使用getsockopt来读取和清除该错误
网络程序中，select能处理的异常情况只有一种：socket上接收到带外数据

处理带外数据
socket上接收到普通数据和带外数据都将使select返回，但socket处于不同的就绪状态：前者处于可读状态，后者处于异常状态
接收普通数据的主要逻辑：
if ( FD_ISSET( connfd, &read_fds ) )    //connfd上有可读事件到达
    recv( connfd, buf, sizeof(buf)-1, 0 );  //普通的recv函数读取数据
printf( "get normal data is %s", buf );
接收带外数据的主要逻辑：
if ( FD_ISSET( connfd, &exception_fds ) )   //connfd上有异常事件到达
    recv( connfd, buf, sizeof(buf)-1, MSG_OOB ); //带MSG_OOB标志的recv函数读取带外数据
printf( "get oob data is %s", buf );
