# select

```
#include <sys/select.h>
int select( int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, struct tiemval* timeout );
```

## 参数

- nfds：指定被监听的文件描述符的总数。

    它通常被设置为select监听的所有文件描述符的最大值加1，因为文件描述符是从0开始计数的

- readfds、writefds和exceptfds：分别为可读、可写和异常事件对应的文件描述符集合。

    应用程序通过这3个参数传入分别需要监控的文件描述符，select调用返回时，内核将修改它们来通知应用程序哪些文件描述符已经就绪

    fd_set结构体仅包含一个整型数组，该数组的每个元素的每一位(bit)标记一个文件描述符.fd_set能容纳的文件描述符数量由FD_SETSIZE指定，这限制了select能同时处理的文件描述符的总量是有限的

    通过下列宏来对fd_set结构进行操作:

    ```
    #include <sys/select.h>
    FD_ZERO( fd_set *fdset );   //清除fdset所有位
    FD_SET( int fd, fd_set *fdset );    //设置fdset的位fd
    FD_CLR( int fd, fd_set *fdset );    //清除fdset的位fd
    int FD_ISSET( int fd, fd_set *fdset );  //测试fdset的位fd是否被设置
    ```

- timeout：设置select函数的超时返回时间，为timeval类型的指针，函数返回会修改timeout为程序select的等待时间，不过并不能完全信任timeout返回的时间，如果调用失败timeout的值将是不确定的

    timeval结构体定义如下：
    ```
    struct timeval
    {
        long tv_sec;    //秒数
        long tv_usec;   //微秒数
    };
    ```
    如果timeout传入select的值为0，则select将立即返回，如果timeout为NULL，则select将一直阻塞直到某个文件描述符就绪

## 返回值：

select成功时返回就绪的文件描述符个数

如果超时时间内没有任何文件描述符就绪，select返回0

select失败时返回-1并设置errno

如果在select等待期间，程序收到信号，则select立即返回-1并设置errno为EINTR

## 文件描述符就绪条件

socket可读：

- socket内核接收缓冲区中的字节数大于或等于其低水位标记SO_RCVLOWAT
- socket通信的对方关闭连接，此时对该socket的读操作将返回0
- 监听socket上有新连接请求
- socket上有未处理的错误。此时可以使用getsockopt来读取和清除该错误(带外数据)

socket可写：

- socket内核发送缓冲区中的可用字节数大于等于其低水位标记SO_SNDLOWAT
- socket的写操作被关闭，对写操作被关闭的socket执行写操作将触发SIGPIPE信号
- socket使用非阻塞connect连接成功或者失败(超时)之后
- socket上有未处理的错误，此时可以使用getsockopt来读取和清除该错误

网络程序中，select能处理的异常情况只有一种：socket上接收到带外数据

## 处理带外数据

socket上接收到普通数据和带外数据都将使select返回，但socket处于不同的就绪状态：前者处于可读状态，后者处于异常状态

### 实例：同时接收普通数据和带外数据

```
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc <= 2)
    {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);
    ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);
    ret = listen(listenfd, 5);
    assert(ret != -1);

    struct sockaddr_in client_address;
    socklen_t client_addrlength = sizeof(client_address) ;
    int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlength);
    if (connfd < 0)
    {
        printf("errno is: %d\n", errno);
        close(listenfd);
    }

    char buf[1024];
    fd_set read_fds;
    fd_set exception_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&exception_fds);

    while (1)
    {
        memset(buf, '\0', sizeof(buf));
        //每次调用select前都要重新在read_fds和exception_fds中设置文件描述符connfd，
        //因为事件发生之后，文件描述符集合将被内核修改
        FD_SET(connfd, &read_fds);
        FD_SET(connfd, &exception_fds);
        ret = select(connfd+1, &read_fds, NULL, &exception_fds, NULL);
        if (ret < 0)
        {
            printf("selection failure\n");
            break;
        }
        //对于可读时间，采用普通的recv函数读取数据
        if (FD_ISSET(connfd, &read_fds))
        {
            ret = recv(connfd, buf, sizeof(buf)-1, 0);
            if (ret <= 0)
            {
                break;
            }
            printf("get %d bytes of normal data: %s\n", ret, buf);
        }
        //对于异常事件，采用带MSG_OOB标志的recv函数读取带外数据
        else if (FD_ISSET(connfd, &exception_fds))
        {
            ret = recv(connfd, buf, sizeof(buf)-1, MSG_OOB);
            if (ret <= 0)
            {
                break;
            }
            printf("get %d bytes of oob data: %s\n", ret, buf);
        }
    }
    close(connfd);
    close(listenfd);
    return 0;
}
```
