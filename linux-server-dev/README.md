# Linux服务器开发

| 基础知识 | [cheatsheet](cheatsheet.md) | [开源项目剖析](project) |

### Linux网络基础API

<details>
<summary>主机字节序和网络字节序</summary>

# 主机字节序和网络字节序

主机字节序 <==> 小端字节序

网络字节序 <==> 大端字节序

以十六进制数0x1234为例：

小端字节序：00000001 00000010 00000011 00000100（高地址存高字节）

大端字节序：00000100 00000011 00000010 00000001（高地址存低字节）

主机字节序和网络字节序转换API：

```
#include <netinet/in.h>

unsigned long htonl( unsigned long hostlong );
unsigned short htons( unsigned short hostshort );
unsigned long ntohl( unsigned long netlong );
unsigned short ntohs( unsigned short netshor
```

</details>

<details>
<summary>sock地址结构体</summary>

# socket地址结构体

## 通用socket地址：

```
#include <bits/socket.h>
struct sockaddr
{
    sa_family_t sa_family;
    char sa_data[14];
};
```

sa_family指明地址类型，地址类型可取值：

- AF_UNIX / PF_UNIX：Unix本地域协议族
- AF_INET / PF_INET：TCP/IPv4协议族
- AF_INET6 / PF_INET6：TCP/IPv6协议族

sa_data用于存放socket地址值，sa_family取不同协议值时，sa_data具有不同的含义和长度，当sa_family=

- AF_UNIX时：sa_data表示文件的路径名，长度可达108字节
- AF_INET：sa_data表示16bit端口号和32bit IPv4地址，共6字节
- AF_INET6：16bit端口号，32bit流标识，128bit IPv6地址，32bit范围ID，共26字节



14字节的sa_data根本无法容纳多数协议族的地址值，因此Linux还定义了下面这个新的通用socket地址结构体

```
struct sockaddr_storage
{
    sa_family_t sa_family;
    unsigned long int __ss_align;
    char __ss_padding[128-sizeof(__ss_align)];
};
```


## 专用socket地址：

UNIX本地域协议族sockaddr_un专用地址结构体：

```
#include <sys/un.h>
struct sockaddr_un
{
    sa_family_t sin_family;    //地址族：AF_UNIX
    char sun_path[108];    //文件路径名
};
```

Linux下IPv4专用socket地址结构体:

```
struct sockaddr_in
{
    sa_family_t sin_family;    //地址族：AF_INET
    u_int16_t sin_port;    //端口号：要用网络字节序表示
    struct in_addr sin_addr;    //IPv4地址结构体，见下
};
struct in_addr
{
    u_int32_t s_addr;    //IPv4地址，要用网络字节序表示
};
```

Linux下IPv6专用socket地址结构体:

```
struct sockaddr_in6
{
    sa_family_t sin6_family;    //地址族：AF_INET6
    u_int16_t sin6_port;    //端口号
    u_int32_t sin6_flowinfo;    //流信息，应设置为0
    struct in6_addr sin6_addr;    //IPv6地址
    u_int32_t sin6_scope_id;    //scope ID，尚在实验
};
struct in6_addr
{
    unsigned char sa_addr[16];  //IPv6地址，要用网络字节序表示
};
```

上述socket地址类型在使用过程中都要转化为sockaddr类型，因为所有的socket编程接口使用的地址参数的类型都是sockaddr

</details>

<details>
<summary>ip地址转换函数</summary>

# IP地址转换函数

```
#include <arpa/inet.h>

in_addr_t inet_addr( const char *strptr );
int inet_aton( const char *cp, struct in_addr *inp );
```

**inet_addr** 函数将用点分十进制字符串表示的IPv4地址转化为用网络字节序整数表示的IPv4地址。失败返回INADDR_NONE

**inet_aton** 和inet_addr函数功能相同，但是将转化结果存储于参数inp指向的地址结构中。成功返回1，失败返回0

```
char *inet_ntoa( struct in_addr in );   //内部使用静态变量存储结果，不可重入
```

**inet_ntoa** 函数将用网络字节序整数表示的IPv4地址转化为用点分十进制字符串表示的IPv4地址，需要注意的是该函数内部使用静态变量存储结果，所以不可重入


**inet_pton** 和 **inet_ntop** 同时适用于IPv4和IPv6地址转化：

```
int inet_pton( int af, const char *src, void *dst );
const char *inet_ntop( int af, const void *src, char *dst, socklen_t cnt );
```

af参数指定地址族：可取`AF_INET`和`AF_INET6`

inet_pton函数将用字符串表示的IP地址src(IPv4或者IPv6)转化为网络字节序整数表示的IP地址。成功返回1，失败返回0并设置errno

inet_ntop函数将网络字节序整数src转化为字符串表示的IP地址，参数cnt指定dst字符串的长度

cnt参数可取的值为：
```
#include <netinet/in.h>
#define INET_ADDRSTRLEN 16
#define INET6_ADDRSTRLEN 46
```

inet_ntop成功时返回目标存储单元的地址，失败返回NULL并设置errno

</details>

<details>
<summary>创建socket</summary>

# 创建socket

```
#include <sys/types.h>
#include <sys/socket.h>
int socket( int domain, int type, int protocol );
```

## 参数

- **domain** 指定协议族，可取值：
  - AF_INET
  - AF_INET6
  - AF_UNIX

- **type** 指定服务类型，可取值：

  - SOCK_STREAM：对TCP/IP协议族而言传输层使用TCP
  - SOCK_UGRAM：对TCP/IP协议族而言传输层使用UDP

  新版本Linux下，type可以接受与下面两个值相与的结果：

  - SOCK_NONBLOCK：设新创建的socket为非阻塞
  - SOCK_CLOEXEC：fork之后子进程中关闭该socket

- **protocol** ：0

## 返回值

socket成功返回socket文件描述符，失败返回-1并设置errno

## 示例


例：创建IPv4和TCP传输时使用的非阻塞socket：

```
#include <sys/types.h>
#include <sys/socket.h>

int sockfd;

if ( ( sockfd = socket(AF_INET, SOCK_STREAM & SOCK_NONBLOCK, 0) ) == -1)
{
    printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
    exit(0);
}
```

</details>

<details>
<summary>命名socket</summary>

# 命令socket

`bind`函数用于将socket文件描述符与socket地址绑定，一般用在服务器代码中

```
#include <sys/types.h>
#include <sys/socket.h>
int bind( int sockfd, const struct sockaddr* my_addr, socklen_t addrlen );
```

## 1. 参数

- **sockfd**： socket的文件描述符
- **my_addr**：socket地址
- **addrlen**：socket地址的长度

## 2. 返回值

`bind`成功返回0，失败返回-1并设置errno， 常见的两种errno:
- 1. EACCES：被绑定的地址是受保护的地址，仅超级用户可以访问。比如普通用户将socket绑定到知名服务端口(0~1023)
- 2. EADDRINUSE：被绑定的地址正在使用中。比如将socket绑定到一个处于TIME_WAIT状态的socket地址

## 3. 示例

```
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    struct sockaddr_in bindaddr;
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindaddr.sin_port = htons(3000);
    int listenfd = socket(AF_INET, SOCK_STREAM & SOCK_NONBLOCK, 0);
    if ( bind(listenfd,  (struct sockaddr*)&bindaddr, sizeof(bindaddr) == -1 ) {
        perror("bind failed\n");
        exit(1);
    }
    return 0;
}
```
 
</details>

<details>
<summary>监听socket</summary>

# 监听socket

服务器程序中，socket被bind之后，还需要使用listen创建一个监听队列以存放待处理的客户连接

```
#include <sys/socket.h>
int listen( int sockfd, int backlog );
```

## 1. 参数

- **sockfd**：指定被监听的socket

- **backlog**：内核监听队列的最大长度。 
  表示处于完全连接状态(`ESTABLISHED`)的socket的上限，处于半连接状态(`SYN_RCVD`)的sock上限则由/proc/sys/net/ipv4/tcp_max_syn_backlog内核参数定义。典型值为5（实际监听队列中完整连接的上限通常比backlog值略大）

## 2. 返回值

listen成功时返回0，失败返回-1并设置errno

## 3. 示例

```
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

static bool stop = false;

//SIGTERM信号的处理函数，触发时结束主程序的循环
static void handle_term(int sig)
{
    stop = true;
}

int main( int argc, char* argv[] )
{
    signal(SIGTERM, handle_term);

    if (argc <= 3)
    {
        printf("usage: %s ip_address port_number backlog\n", 
            basename(argv[0]));
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);
    int backlog = atoi(argv[3]);
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    //创建一个IPv4 socket地址
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);
    
    ret = listen(sock, backlog);
    assert(ret != -1);

    //循环等待连接，直到SIGTERM信号将它中断
    while (!stop)
    {
        sleep(1);
    }

    //关闭socket
    close(sock);
    return 0;
}
```

可以在服务器上运行该代码，然后在本地多次执行命令连接服务器程序，使用netstat命令查看服务器的连接状态

```
# 服务器上运行上面程序，监听6677端口，设置监听队列大小为5
# serve_ip可以使用服务器公网IP，也可以使用0.0.0.0
./testlisten 0.0.0.0 6677 5

# 在本地多次执行和服务器建立连接
telnet server_ip 6677

# 本地每执行一次telnet，服务器执行下命令查看连接状态
netstat -nt | grep 6677
```

一般来说，服务器监听队列中，处于`ESTABLISHED`状态的连接只有6个(backlog+1)，其他都处于`SYN_RCVD`状态，改变服务器程序第3个参数并重新运行能发现该规律

</details>

<details>
<summary>接受连接</summary>

# 接受连接accept

服务器程序使用`accept`函数从listen监听队列中接受一个连接

```
#include <sys/types.h>
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

## 1. 参数

- **sockfd**：执行过listen系统调用的监听socket
- **addr**：获取的被接受连接的远端socket地址
- **addrlen**：addr的长度，传入传出参数，传入时指定addr的类型大小，返回获取到的远端地址的实际长度

## 2. 返回值

accept成功时返回一个新连接socket，该socket唯一的标识了被接受的连接，服务器可以通过读写该socket来与被接受连接对应的客户端通信

accept失败时返回-1并设置errno

## 3. 示例

```
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    int connfd = accept(sock, (struct sockaddr*)&client, &client_addrlength);
    if (connfd < 0) {
        printf("errno is : %d\n", errno);
    }
    else {
        char remote[INET_ADDRSTRLEN];
        printf("connected with ip: %s and port: %d\n", 
            inet_ntop(AF_INET, &client.sin_addr, remote, INET_ADDRSTRLEN), 
            ntohs(client.sin_port));
        close(connfd);
    }
    close(sock);
    return 0;
}

```

在远端服务器运行该代码，然后在本地执行telnet命令来连接服务器程序，查看服务器输出

```
# 服务器
./testaccept 0.0.0.0 1234

# 客户端
telnet server_ip 1234
```

accept函数只是从监听队列中取出连接，而不论连接处于何种状态，更不关心任何网络状况的变化
> 如果监听队列中处于ESTABLISHED状态的连接对应的客户端出现网络异常（掉线）或者提前退出，那么服务器对这个连接执行的accept调用还是会成功，也即是accept返回的连接并不总是处于ESTABLISHED状态，accept函数对连接加入监听队列到取出监听队列这一阶段的连接状态改变一无所知

</details>

<details>
<summary>发起连接</summary>

# 发起连接connect

客户端通过`connect`系统调用来主动和服务器建立连接

```
#include <sys/types.h>
#include <sys/socket.h>
int connect(int sockfd, const struct sockaddr* serv_addr, socklen_t addrlen);
```

## 1. 参数

- **sockfd**：客户端socket
- **serv_addr**：服务器socket
- **addrlen**：serv_addr长度

## 2. 返回值

connect成功返回0，成功建立连接后，客户端就可以通过sockfd与服务器通信

connect失败返回-1并设置errno，两种常见的errno：
- ECONNREFUSED：目标端口不存在，连接被拒绝
- ETIMEDOUT：连接超时

## 3. 示例

### 3.1 对阻塞socket进行connect

```
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <assert.h>
#include <netinet/in.h>

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip_address port\n", basename(argv[0]));
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &serv_addr.sin_addr);
    serv_addr.sin_port = htons(port);

    int serv_len = sizeof(serv_addr);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    int ret = connect(sockfd, (struct sockaddr*)&serv_addr, serv_len); 
    if (ret == -1) {
        printf("connect error with errno: %d\n", ret);
        return 1;
    }

    close(sockfd);
    return 0;
}
```

### 3.2 对非阻塞socket进行connect

```
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <assert.h>
#include <netinet/in.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip_address port\n", basename(argv[0]));
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &serv_addr.sin_addr);
    serv_addr.sin_port = htons(port);

    int serv_len = sizeof(serv_addr);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    //设置sockfd为非阻塞
    int flag = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flag | O_NONBLOCK);

    while (true) {
        int ret = connect(sockfd, (struct sockaddr*)&serv_addr, serv_len); 
        if (ret == 0) {
            printf("connect success!\n");
            break;
        } else {
            if (errno != EINPROGRESS) {
                printf("connect error with errno: %d\n", ret);
                break;
            } else {
                //errno为EINPROGRESS时表示正在连接
                printf("connection is being established\n");
                sleep(1);
                continue;
            }
        }
    }

    close(sockfd);
    return 0;
}

```

</details>

<details>
<summary>关闭连接</summary>

# 关闭连接

关闭一个连接实际上就是关闭连接对应的socket，所以可以使用关闭普通文件描述符的系统调用来完成

## 1. close

close系统调用并非总是立即关闭一个连接，而是将fd的引用计数减1。只有当fd的引用计数为0时，才真正关闭连接
> 如果在多进程程序中，一次fork调用默认将使父进程中打开的socket的引用计数加1，因此必须在父进程和子进程都调用close才能将连接真正关闭


```
#include <unistd.h>
int close(int fd);
```

### 1.1. 参数

- **fd**：要关闭的socket

### 1.2. 返回值

成功返回0，失败返回-1并设置errno

## 2. shutdown

shutdown系统调用专为网络编程设计，可以立即终止连接(与close不同)

```
#include <sys/socket.h>
int shutdown(int sockfd, int howto);
```

### 1.1. 参数

- **sockfd**：要关闭的socket
- **howto**：决定了shutdown的行为，可取以下值：

  - SHUT_RD：关闭读端，并且socket接收缓冲区中的数据被丢弃
  - SHUT_WR：关闭写段，关闭之前将socket发送缓冲区内容发送出去
  - SHUT_RDWR：同时关闭读端和写端

### 1.2. 返回值

shutdown成功返回0，失败返回-1并设置errno

</details>

<details>
<summary>数据读写</summary>

# 数据读写

<!-- vim-markdown-toc Marked -->

* [1. TCP数据读写](#1.-tcp数据读写)
  * [1.2. 主要参数和返回值](#1.2.-主要参数和返回值)
  * [1.3. 使用](#1.3.-使用)
* [2. UDP数据读写](#2.-udp数据读写)
* [3. 通用数据读写](#3.-通用数据读写)
  * [3.1 参数和返回值](#3.1-参数和返回值)
  * [3.2 使用](#3.2-使用)

<!-- vim-markdown-toc -->

## 1. TCP数据读写

对文件的读写操作`read`和`write`同样适用于socket，但是socket编程接口中提供了专门用于socket数据读写的系统调用，它们增加了对数据读写的控制，用于TCP流数据读写的系统调用是：

```
#include <sys/types.h>
#include <sys/socket.h>
ssize_t recv(int sockfd, void* buf, size_t len, int flags);
ssize_t send(int sockfd, const void* buf, size_t len, int flags);
```

### 1.2. 主要参数和返回值

- **recv**：
  - len --> buf空间的大小(sizeof)
  - 返回值 --> 读取到的数据的长度

- **send**：
  - len --> 发送数据的长度(strlen) 
  - 返回值 --> 实际发送的数据的长度

- **flags**：只对此次调用有效，只列举部分选项，更多查看man page

  - MSG_OOB：发送或接受紧急数据（both）
  - MSG_PEEK：窥探读缓存中的数据，此次读不会导致这些数据清除（recv）
  - MSG_DONTWAIT：对socket的此次操作是非阻塞的（both）
  - MSG_WAITALL：读操作仅在读取到指定数量的字节才返回（recv）
  - MSG_MORE：防止TCP发送过多小的数据报文（send）
  - MSG_NOSIGNAL：读端关闭不引起SIGPIPE信号（send）

### 1.3. 使用

发送带外数据：

```
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip port\n", basename(argv[0]));
        return 1;
    }

    const char* ip = argv[1];
    short port = atoi(argv[2]);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &serv_addr.sin_addr);
    serv_addr.sin_port = htons(port);

    if ( connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0 ) {
        printf("connect failed\n");
    } else {
        const char* oob_data = "abc";
        const char* normal_data = "123";
        int ret = send(sockfd, normal_data, strlen(normal_data), 0);
        printf("send %d bytes data\n", ret);
        ret = send(sockfd, oob_data, strlen(oob_data), MSG_OOB);
        printf("send %d bytes data\n", ret);
        ret = send(sockfd, normal_data, strlen(normal_data), 0);
        printf("send %d bytes data\n", ret);
    }

    close(sockfd);
    return 0;
}
```

接收带外数据：

```
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define BUF_SIZE 1024

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip port\n", basename(argv[0]));
        return 1;
    }

    const char* ip = argv[1];
    short port = atoi(argv[2]);

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    inet_pton(AF_INET, ip, &serv_addr.sin_addr);
    serv_addr.sin_port = htons(port);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    int ret = bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    assert(ret != -1);

    ret = listen(sockfd, 5);
    assert(ret != -1);

    struct sockaddr_in cli_addr;
    bzero(&cli_addr, sizeof(cli_addr));

    socklen_t cli_addrlen = sizeof(cli_addr);

    int connfd = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_addrlen);
    if (connfd < 0) {
        printf("errno: %d\n", errno);
    } else {
        char buffer[BUF_SIZE];
        memset(buffer, '\0', BUF_SIZE);
        ret = recv(connfd, buffer, BUF_SIZE-1, 0);
        printf("got %d bytes of normal data '%s'\n", ret, buffer);

        memset(buffer, '\0', BUF_SIZE);
        ret = recv(connfd, buffer, BUF_SIZE-1, MSG_OOB);
        printf("got %d bytes of oob data '%s'\n", ret, buffer);

        memset(buffer, '\0', BUF_SIZE);
        ret = recv(connfd, buffer, BUF_SIZE-1, 0);
        printf("got %d bytes of normal data '%s'\n", ret, buffer);

        close(connfd);
    }

    close(sockfd);
    return 0;
}
```

可以使用`tcpdump`来抓取发送数据的过程：
```
sudo tcpdump -ntx -i eth0 port 1234
```

## 2. UDP数据读写

socket编程接口中用于UDP数据报读写的系统调用是：

```
#include <sys/types.h>
#include <sys/socket.h>

ssize_t recvfrom( int sockfd, void *buf, size_t len, 
                  int flags, struct sockaddr* src_addr, socklen_t* addrlen );

ssize_t sendto( int sockfd, const void *buf, size_t len, 
                  int flags, const struct sockaddr *dest_addr, socklen_t addrlen );
```

recvfrom/sendto和recv/send的前四个参数意义相同，当recvfrom/sendto的后两个参数为NULL时等价于recv/send。

## 3. 通用数据读写

socket编程接口提供的`recvmsg`和`sendmsg`通用数据读写系统调用，既可以用于TCP流数据，也可以用于UDP数据报

```
#include <sys/socket.h>
ssize_t recvmsg( int sockfd, struct msghdr* msg, int flags );
ssize_t sendmsg( int sockfd, struct msghdr* msg, int flags );
```

### 3.1 参数和返回值

- **sockfd**：被操作的目标socket
- **msg**：msghdr结构体类型的指针

  ```
  struct msghdr
  {
      void* msg_name;    //socket地址
      socklen_t msg_namelen;    //socket地址的长度
      struct iovec* msg_iov;    //分散的内存块
      int msg_iovlen;    //分散内存块的数量
      void* msg_control;    //指向辅助数据的起始位置
      socklen_t msg_controllen;    //辅助数据的大小
      int msg_flags;    //复制函数中的flags参数，并在调用过程中更新
  };
  ```

  - msg_name:指向socket结构体变量，指定通信对方的socket地址，对于面向连接的tcp协议，该值设为NULL
  - msg_iov：iovec结构体类型的指针
  ```
  struct iovec* msg_iov:
  struct iovec
  {
      void *iov_base;    //内存起始位置
      size_t iov_len;    //该内存的长度
  }
  ```
  - msg_iovlen：iovec块的个数

- **flags**：recv/send的flag参数相同

- **返回值**：recvmsg/sendmsg的返回值和recv/send的返回值相同

### 3.2 使用

recvmsg/sendmsg读写数据的形式分别为`分散读`和`集中写`：

- **分散读(scatter read)：**
  recvmsg将数据读取并存放在msg_iovlen块分散的内存中，这些内存的位置和长度由msg_iov指向的数据指定

- **集中写(gather write)：**
  sendmsg将msg_iovlen块分散内存中的数据一并发送

例：
```

```

</details>

<details>
<summary>带外标记</summary>

# 带外标记

内核通知应用程序带外数据到达的两种常见方式：**I/O复用产生的异常事件**和**SIGURG信号**

当内核通知带外数据到达时，可以通过sockatmark判断sockfd是否处于带外标记，即下一个被读取到的数据是否是带外数据，如果是，sockatmakr返回1，此时可以通过带MSG_OOB标志的recv调用来接收带外数据。如果不是，则sockatmark返回0

```
#include <sys/socket.h>
int sockatmark(int sockfd);
```

sockatmark函数的一个常见实现：
```
int sockatmark(int fd) {
    int flag;
    if (ioctl(fd, SIOCATMARK, &flag) < 0)
        return -1;
    return (flag != 0);
}
```

[参考文章](https://blog.csdn.net/ctthuangcheng/article/details/9569011)

</details>

<details>
<summary>地址信息函数</summary>

# 地址信息函数

有时，我们想知道一个连接socket的本端socket地址和远端socket地址，可以使用`getsockname`和`getpeername`

```
#include <sys/socket.h>
int getsockname(int sockfd, struct sockaddr* address, socklen_t* address_len);
int getpeername(int sockfd, struct sockaddr* address, socklen_t* address_len);
```

getsockname获取sockfd对应的本端的socket地址，成功返回0，失败返回-1并设置errno

getpeername获取sockfd对应的远端的socket地址


## 使用：
```
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char* argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip_address port\n", basename(argv[0]));
        return 1;
    }

    const char* ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &serv_addr.sin_addr);
    serv_addr.sin_port = htons(port);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);      
    assert(sockfd >= 0);

    int ret = bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    assert(ret != -1);

    ret = listen(sockfd, 5);
    assert(ret != -1);

    struct sockaddr_in cli_addr;
    bzero(&cli_addr, sizeof(cli_addr));

    while (true) {

        socklen_t cli_addrlen = sizeof(cli_addr);
        int connfd = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_addrlen);

        if (connfd < 0) {
            printf("errno: %d\n", errno);
        } else {
            struct sockaddr_in sock_name;
            bzero(&sock_name, sizeof(sock_name));
            socklen_t sockname_len = sizeof(sock_name);
            int ret = getsockname(sockfd, (struct sockaddr*)&sock_name, &sockname_len);
            char sockname_addr[1024];
            inet_ntop(AF_INET, &sock_name.sin_addr.s_addr, sockname_addr, sizeof(sockname_addr));
            struct sockaddr_in peer_name;
            bzero(&peer_name, sizeof(peer_name));
            socklen_t peername_len = sizeof(peer_name);
            ret = getpeername(sockfd, (struct sockaddr*)&peer_name, &peername_len);
            char peername_addr[1024];
            inet_ntop(AF_INET, &peer_name.sin_addr.s_addr, peername_addr, sizeof(peername_addr));

            printf("sockname : ip: %s, port: %d\n", sockname_addr, ntohs(sock_name.sin_port));
            printf("peername : ip: %s, port: %d\n", peername_addr, ntohs(peer_name.sin_port));

            close(connfd);
        }
    }

    close(sockfd);
    return 0;
}
```

</details>

<details>
<summary>socket选项</summary>

# socket选项

fcntl系统调用是控制文件描述符属性的通用POSIX方法，而getsockopt和setsockopt则是专门用来读取和设置socket文件描述符属性的方法：

```
#include <sys/socket.h>
int getsockopt(int sockfd, int level, int option_name, 
               void *option_value, socklen_t *restrict option_len);
int setsockopt(int sockfd, int level, int option_name, 
               const void *option_value, socklen_t option_len);
```

## 1. 参数

- **sockfd**：被操作的目标socket
- **level**：指定要操作那个协议的选项，例如IPv4、IPv6、TCP等
- **option_name**：指定选项名字
- **option_vlaue和option_len**：分别指定被操作选项的值和长度

## 2. 返回值

两个函数成功时都返回1，失败时返回-1并设置errno

对服务器而言：
> 有部分socket选项只能在调用listen前针对监听socket设置才有效，因为连接socket只能由accept调用返回，而accept从listen监听队列中接收的连接至少已经完成了tcp三次握手的前两个步骤（监听队列中的连接至少已经进入SYN_RCVD状态），这说明服务器已经往被接收连接上发送除了tcp同步报文段。但有的socket选项却应该在tcp同步报文段中设置，比如tcp最大报文段选项，对这种情况解决方案：对监听socket设置这些socket选项，那么accept返回的连接socket将自动继承这些选项，这些socket选项包括：SO_DEBUG、SO_DONTROUTE、SO_KEEPALIVE、SO_LINGER、SO_OOBINLINE、SO_RCVBUF、SO_RCVLOWAT、SO_SNDBUF、SO_SNDLOWAT、TCP_MAXSEG和TCP_NODELAY

对客户端而言：
> 这些socket选项应该在调用connect函数之前设置，因为connect调用成功返回之后，tcp三次握手已经完成

## 3. socket选项

- **SO_REUSEADDR**

  设置socket选项SO_REUSEADDR来强制使用被处于TIME_WAIT状态的连接的占用的socket地址。

  具体实现方法如下：

  ```
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  assert(sockfd >= 0);

  //设置SO_REUSEADDR
  int reuse = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

  struct sockaddr_in address;
  bzero(&address, sizeof(address));
  address.sin_family = AF_INET;
  inet_pton(AF_INET, ip, &address.sin_addr);
  address.sin_port = htons(port);
  int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
  ```

  此外还可以通过修改内核参数`/proc/sys/net/ipv4/tcp_tw_recycle`来快速回收被关闭的socket，使得tcp连接根本就不会进入TIME_WAIT状态，进而允许应用程序立即重用本地的socket地址

- **SO_RCVBUF和SO_SNDBUF**

  SO_RCVBUF：设置TCP接收缓冲区大小

  SO_SNDBUF：设置TCP发送缓冲区大小

  > 使用setsockopt设置TCP缓冲区大小时，系统一般都会将设置值加倍，并且不得小于某个值，一般TCP接收缓冲区最小值为256字节，而发送缓冲区的最小值是2048字节，这种机制的目的是确保一个TCP连接拥有足够的空闲缓冲区处理拥塞，可以通过修改内核参数`/proc/sys/net/ipv4/tcp_rmem`和`/proc/sys/net/ipv4/tcp_wmem`来强制TCP接收和发送缓冲区的大小没有最小值限制

  ```
  int sendbuf = 4096;
  int sendlen = sizeof(sendbuf);
  setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, sizeof(sendbuf));
  getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, (socklen_t *)&sendlen);

  int recvbuf = 1024;
  int recvlen = sizeof(recvbuf);
  setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, sizeof(recvbuf));
  getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, (socklen_t *)&recvlen);
  ```

- **SO_RCVLOWAT和SO_SNDLOWAT**

  SO_RCVLOWAT：表示TCP接收缓冲区的低水位标记，当TCP接收缓冲区中可读数据的总数大于其低水位标记时，I/O复用系统调用将通知应用程序可以从对应的socket读取数据

  SO_SNDLOWAT：表示TCP发送缓冲区的低水位标记，当TCP发送缓冲区中的空闲空间大于其低水位标记时，I/O复用系统调用将通知应用程序可以往对应的socket上写入数据

  这两个标记一般被I/O复用系统调用用来判断socket是否可读或可写，默认情况这两个低水位标记均为1字节

- **SO_LINGER**

  SO_LINGER：用于控制close系统调用在关闭TCP连接时的行为(默认情况下使用close关闭一个socket时，close将立即返回，TCP模块负责将socket对应的TCP发送缓冲区中残留的数据发送给对方)

  设置SO_LINGER需要给setsockopt和setsockopt系统调用传递一个linger类型结构体

  ```
  #include <sys/socket.h>
  struct linger
  {
      int l_onoff;    //开启(非0)还是关闭(0)该选项
      int l_linger;   //滞留时间
  };
  ```

  - 1. l_onoff=0：

    SO_LINGER设置无效，close()保持默认行为

  - 2. l_onoff!=0：

    l_linger=0：close()立即返回，丢弃被关闭socket发送缓冲区残留的数据，同时向对方发送一个复位报文段

  - 3. l_onoff!=0， l_linger>0：
    如果socket是阻塞的，close将等待l_linger的时间再返回，如果close返回时TCP模块中还没有发送完残留数据并得到对方的确认，close系统调用将返回-1并设置errno为EWOULDBLOCK；如果socket非阻塞，close立即返回，然后根据返回值和errno判断残留数据是否发送完毕

</details>

<details>
<summary>网络信息API</summary>

# 网络信息API

## 1. gethostbyname和gethostbyaddr

gethostbyname：根据主机名称获取主机完整信息，会先在/etc/hosts查找主机，找不到再访问DNS服务器查找

gethostbyaddr：根据IP地址获取主机完整信息 

```
#include <netdb.h>
struct hostent* gethostbyname(const char* name);
struct hostent* gethostbyaddr(const void* addr, size_t len, int type);
```

- name：目标主机主机名
- addr：指定目标主机的IP地址
- len：addr所指IP地址的长度
- type：addr所指的IP地址类型，可取AF_INET和AF_INET6

返回值类型：

```
struct hostent
{
    char* h_name;          //主机名
    char** h_aliases;      //主机别名列表
    int h_addrtype;        //地址类型
    int h_length;            //地址长度
    char** h_addr_list;  //按网络字节序列出的主机IP地址列表
};
```

使用：
```
char *host = "www.baidu.com";
struct hostent* hostinfo = gethostbyname(host);
assert(hostinfo);
```

这两个函数都是不可重入函数，对应的可重入函数为原函数名+_r

## 2. getservbyname和getservbyport

getservbyname：根据名称获取某个服务的完整信息

getservbyport：根据端口号获取某个服务的完整信息

```
#include <netdb.h>
struct servent* getservbyname(const char* name, const char* proto);
struct servent* getservbyport(int port, const char* proto);
```

- name：目标服务的名字
- port：目标服务对应端口号
- proto：指定服务类型，"tcp"表示流服务，"udp"表示数据报服务

返回值类型：
```
struct servent
{
    char* s_name;       //服务名称
    char** s_aliases;   //服务别名列表
    int s_port;             //端口号
    char* s_proto;      //服务类型tcp or udp
};
```

使用：
```
struct servent* servinfo = getservbyname("daytime", "tcp");
assert(servinfo);
```

这两个函数都是不可重入函数，对应的重入版本为原函数名+_r

## 3. getaddrinfo

getaddrinfo即能通过主机名获得IP地址(内部使用gethostbyname)，也能通过服务名获得端口号(内部使用getservbyname)，它是否可重入取决于内部调用的gethostbyname和getservbyname是否是可重入版本

```
#include <netdb.h>
int getaddrinfo(const char* hostname, const char* service, 
                      const struct addrinfo* hints, struct addrinfo** result)
```

- hostname：字符串形式的主机名或IP地址
- service：字符串形式服务名或十进制端口号
- result：结果链表
- hints：对getaddrinfo的输出进行精确控制

  ```
  struct addrinfo
  {
      int ai_flags;                      //后文
      int ai_family;                    //地址族
      int ai_socktype;               //SOCKET_STREAM or SOCKET_DGRAM
      int ai_protocol;                //后文
      socklen_t ai_addrlen;      //socket地址ai_addr的长度
      char* ai_canonname;      //主机别名
      struct sockaddr* ai_addr; //指向socket地址
      struct addrinfo* ai_next;  //下一个addrinfo地址
  };
  ```
  - ai_protocol：具体的网络协议，含义与socket系统调用第三个参数相同，通常为0
  - ai_flags(主要选项):
    - AI_CANONONAME：hists参数设置，告诉getaddrinfo函数返回主机别名
    - AI_NUMERICHOST：hists参数设置，hostname必须是用字符串表示的IP地址，避免DNS查询
    - AI_NUMERICSERV：hists参数设置，service强制使用十进制端口号的字符串形式,不能是服务名

使用：
```
struct addrinfo hints;
struct addrinfo* res;

bzero(&hints, sizeof(hints));
hints.ai_socktype = SOCKET_STREAM;
getaddrinfo("ernest-laptop", "daytime", &hints, &res);
```

getaddrinfo中为res指针隐式分配堆内存，所以函数调用完毕后，使用如下配对函数释放这块内存：

```
void freeaddrinfo(struct addrinfo* res);
```

## 4. getnameinfo

getnameinfo函数通过socket地址获得字符串形式的主机名和服务名(内部由gethostbyaddr和getservbyport实现)，它是否可重入由内部调用gethostbyaddr和getservbyport的可重入版本

```
#inlcude <netdb.h>
int getnameinfo(const struct sockaddr* sockaddr, socklen_t addrlen, char* host, 
                socklen_t hostlen, char* serv, socklen_t servlen, int flags);
```

- host：返回的主机名
- serv：返回的服务名
- flags(主要选项)：
  - NI_NAMEREQD：通过socket地址不能得到主机名则返回错误
  - NI_NUMERICHOST：返回字符串表示的IP地址，而非主机名
  - NI_NUMERICSERV：返回字符串表示的十进制端口号，而非服务名

</details>

### 高级IO函数

<details>
<summary>pipe函数</summary>

# pipe函数

## 1. pipe

```
#include <unistd.h>
int pipe(int fd[2]);
```

巧记fd读写端：
- fd[1]：写端(1形似笔杆，代表写)
- fd[0]：读端(0形似张开的嘴，代表读)

一个管道只能单向通信，要实现双向数据传输需要使用两个管道

fd[0],fd[1]默认阻塞,阻塞行为：

- 如果有指向管道写端的文件描述符没关闭(管道写端的引用计数等于0)，而管道写端也没有数据被写入，这时有进程从管道读端读取数据，那么管道中的剩余数据被读取完后，再次read会阻塞，直到管道中有数据可读了才读取数据返回

- 如果有指向管道读端的文件描述符没关闭(管道读端的引用计数等于0)，而持有管道读端的进程也没有从管道中读数据，这时有进程向管道写端写数据，那么在管道被写满时再次write会阻塞，直到管道中有空闲空间才写入数据并返回

fd[0],fd[1]非阻塞时的行为：

- 如果所有指向管道写端的文件描述符都关闭了(管道写端的引用计数等于0)，而仍然有进程从管道的读端读数据，那么管道中剩余的数据都被读取后，再次read会返回0，表示读到了文件结束标记(EOF)

- 如果所有指向管道读端的文件描述符都关闭了(管道读端的引用计数等于0)，这时如果有进程向管道的写端write，那么进程将会收到SIGPIPE信号，SIGPIPE信号的行为默认会导致进程异常终止

管道本身有容量限制，默认65535字节，可以使用fcntl函数修改管道容量和设置非阻塞(O_NONBLOCK)

## 2. socketpair

pipe只能创建单向管道，socketpair可以创建双向管道，创建的fd中的两个文件描述既可读又可写

```
#include <sys/types.h>
#include <sys/socket.h>
int socketpair(int domain, int type, int protocol, int fd[2]);
```

- domain，type，protocol参数和socket系统调用前三个参数相同
- domain：只能使用UNIX本地域AF_UNIX
- fd[2]：和pipe第二个参数相同

socketpair成功时返回0，失败返回-1并设置errno

管道pipe和socketpair的区别示意图：

管道：

![管道示意图](doc/pipe_fd.png)

socketpair：

![sockpair示意图](doc/sockpair_fd.png)

</details>

<details>
<summary>dup和dup2</summary>

# dup和dup2

```
#include <unistd.h>
int dup(int file_descriptor);
int dup2(int file_descriptor_one, file_descriptor_two);
```

## 说明

**dup** ：创建一个新的文件描述符，新文件描述符与原有文件描述符file_descriptor指向相同的文件、管道或网络连接，dup总是返回系统当前可用的最小文件描述符

**dup2** ：返回第一个不小于file_descriptor_two的新文件描述符，新文件描述符与文件描述符file_descriptor_one有相同指向

> 通过dup和dup2创建的文件描述符并不继承原文件描述符的文件描述符属性，比如`close-on-exec`和`non-blocking` (note：注意区分文件描述符属性和文件属性)

dup和dup2调用失败时返回-1并设置errno

## 使用

使用dup函数实现一个基本的CGI服务器

```
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip port\n", basename(argv[0]));
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr.s_addr);
    address.sin_port = htons(port);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    int ret = bind(sockfd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sockfd, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addrlen = sizeof(client);
    int connfd = accept(sockfd, (struct sockaddr*)&client, &client_addrlen);
    if (connfd < 0) {
        printf("errno is: %d\n", errno);
    } else {
        close(STDOUT_FILENO);
        dup(connfd);
        printf("abcd\n");
        close(connfd);
    }
    close(sockfd);
    return 0;
}
```

</details>

<details>
<summary>readv和writev</summary>

# readv和writev

readv：将数据从文件描述符读到分散的内存块中，即分散读

writev：将数据从多块分散的内存数据一并写入文件描述符中，即集中写

```
#include <sys/uio.h>
ssize_t readv(int fd, const struct iovec* vector, int count);
ssize_t writev(int fd, const struct iovec* vector, int count);

struct iovec
{
    void *iov_base;    //内存起始地址
    size_t iov_len;     //这块内存的长度
};
```

vector：iovec描述一块内存区，count表示vector数组中内存区iovec的数量

readv和writev在成功时返回读入/写入fd的字节数，失败返回-1并设置errno


## 使用：

在Web服务器上集中写：

```
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

static const char* status_line[2] = {"200 OK", "500 Internal server error"};

int main(int argc, char* argv[]) {
    if (argc <= 3) {
        printf("usage: %s ip_address port_number filename\n", basename(argv[0]));
        return 1;
    }

    const char* ip = argv[1];
    int port = atoi(argv[2]);
    const char* file_name = argv[3];

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    int ret = bind(sockfd, (struct sockaddr*)&address, sizeof(address));
    assert(sockfd != -1);

    ret = listen(sockfd, 5);
    assert(ret != -1);
    
    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    
    int connfd = accept(sockfd, (struct sockaddr*)&client, &client_addrlength);
    if (connfd < 0) {
        printf("errno is : %d\n", errno);
    } else {
        char header_buf[BUFFER_SIZE];
        memset(header_buf, '\0', BUFFER_SIZE);
        char* file_buf;
        struct stat file_stat;
        bool valid = true;
        int len = 0;
        if (stat(file_name, &file_stat) < 0) {
            valid = false;
        } else {
            if (S_ISDIR(file_stat.st_mode)) {
                valid = false;
            } 
            else if (file_stat.st_mode & S_IROTH) {
                int fd = open(file_name, O_RDONLY);
                file_buf = new char[file_stat.st_size+1];
                memset(file_buf, '\0', file_stat.st_size+1);
                if (read(fd, file_buf, file_stat.st_size) < 0) {
                    valid = false;
                }
            }
            else {
                valid = false;
            }
        }

        if (valid) {
            ret = snprintf(header_buf, BUFFER_SIZE-1, "%s %s\r\n", "HTTP/1.1", status_line[0]);
            len += ret;
            ret = snprintf(header_buf+len, BUFFER_SIZE-1-len, "Content-Length: %d\r\n", file_stat.st.size);
            len += ret;
            struct iovec iv[2];
            iv[0].iov_base = header_buf;
            iv[0].iov_len = strlen(header_buf);
            iv[0].iov_base = file_buf;
            iv[0].iov_len = file_stat.st_size;
            ret = writev(connfd, iv, 2);
        }
        else {
            ret = snprintf(header_buf, BUFFER_SIZE-1, "%s %s\r\n", "HTTP/1.1", status_line[1]);
            len += ret;
            ret = snprintf(header_buf+len, BUFFER_SIZE-1-len, "%s", "\r\n");
            send(connfd, header_buf, strlen(header_buf), 0);
        }
        close(connfd);
        delete [] file_buf;
    }
    close(sock);
    return 0;
}
```

</details>

<details>
<summary>sendfile函数</summary>

# sendfile函数

sendfile函数在两个文件描述符之间直接传递数据(完全在内核中操作),从而避免了内核缓冲区和用户缓冲区之间的数据拷贝，效率很高，被称为零拷贝。

```
#include <sys/sendfile.h>
ssize_t sendfile(int out_fd, int in_fd, off_t* offset, size_t count);
```

- out_fd：等待写入内容的fd，可理解为发送给网络上的socket
- in_fd：待读出内容的fd，可理解为本地需要发送的文件
- offset：指定读入文件的读取偏移量，如果为空，则从默认读取位置读取
- count：指定传输字节数

函数成功返回传输的字节数，失败返回-1并设置errno

in_fd必须为支持mmap函数的文件描述符，必须指向真实的文件，不能是socket或者管道

out_fd则必须为socket

由此可见，sendfile是专门为在网络上传输文件设计的

</details>
- [](content/sendfile.md)
<details>
<summary>mmap和munmap</summary>
</details>
- [](content/mmap.md)
<details>
<summary>splice函数</summary>
</details>
- [](content/splice.md)
<details>
<summary>tee函数</summary>
</details>
- [](content/tee.md)
<details>
<summary>fcntl函数</summary>
</details>
- [](content/fcntl.md)

### Linux服务器程序规范

<details>
<summary>日志</summary>
</details>
- [](content/syslog.md)
<details>
<summary>用户信息</summary>
</details>
- [](content/uid_gid.md)
<details>
<summary>进程间关系</summary>
</details>
- [](content/pgid_sid_ps.md)
<details>
<summary>系统资源限制</summary>
</details>
- [](content/rlimit.md)
<details>
<summary>改变工作目录和根目录</summary>
</details>
- [](content/cwd_root.md)
<details>
<summary>服务器程序后台化</summary>
</details>
- [](content/daemon.md)

### 高性能服务器程序框架

<details>
<summary>服务器模型</summary>
</details>
- [](content/cs_p2p.md)
<details>
<summary>服务器编程框架</summary>
</details>
- [](content/server_dev_frame.md)
<details>
<summary>I/O模型</summary>
</details>
- [](content/io.md)
<details>
<summary>两种高效的事件处理模式</summary>
</details>
- [](content/reactor_proactor.md)
<details>
<summary>两种高效的并发模式</summary>
</details>
- [](content/halfsync_halfasync_leader_follower.md)
<details>
<summary>有限状态机</summary>
</details>
- [](content/finite_state_machine.md)
<details>
<summary>提高服务器性能的其他建议</summary>
</details>
- [](content/pool_datacp_content_switch.md)

### IO复用

<details>
<summary>selete系统调用</summary>
</details>
- [](content/select.md)
<details>
<summary>poll系统调用</summary>
</details>
- [](content/poll.md)
<details>
<summary>epoll系统调用</summary>
</details>
- [](content/epoll.md)
<details>
<summary>三组IO复用函数对比(缺)</summary>
</details>
- [](content/select_poll_epoll.md)
<details>
<summary>IO复用高级应用一：非阻塞connect(缺)</summary>
</details>
- [](content/nonblock_connect.md)
<details>
<summary>IO复用高级应用二：聊天室程序(缺)</summary>
</details>
- [](content/chatting_room.md)
<details>
<summary>IO复用高级应用三：同时处理TCP和UDP服务(缺)</summary>
</details>
- [](content/handle_tcp_and_udp.md)
<details>
<summary>超级服务xinetd(缺)</summary>
</details>
- [](content/xinetd.md)

### 信号

<details>
<summary>linux信号概述</summary>
</details>
- [](content/signal_base.md)
<details>
<summary>信号函数</summary>
</details>
- [](content/signal_functions.md)
<details>
<summary>信号集</summary>
</details>
- [](content/sigset.md)
<details>
<summary>统一事件源</summary>
</details>
- [](content/one_event.md)
<details>
<summary>网络编程相关信号</summary>
</details>
- [](content/signal_server_dev.md)

### 定时器

<details>
<summary>socket选项so_rcvtimeo和so_sndtimeo</summary>
</details>
- [](content/so_rcvtimeo_so_sndtimeo.md)
<details>
<summary>sigalrm信号</summary>
</details>
- [](content/sigalrm.md)
<details>
<summary>IO复用系统调用的超时参数</summary>
</details>
- [](content/timeout_arg.md)
<details>
<summary>高性能定时器</summary>
</details>
- [](content/timer.md)

### 高性能IO框架Libevent

<details>
<summary>IO框架库概述</summary>
</details>
- []()
<details>
<summary>libevent源码分析</summary>
</details>
- []()

### 多进程编程

<details>
<summary>fork系统调用</summary>
</details>
- [](content/fork.md)
<details>
<summary>exec系列系统调用</summary>
</details>
- [](content/exec.md)
<details>
<summary>处理僵尸进程</summary>
</details>
- [](content/zombie_process.md)
<details>
<summary>管道</summary>
</details>
- [](content/more_process_pipe.md)
<details>
<summary>信号量</summary>
</details>
- [](content/sem.md)
<details>
<summary>共享内存</summary>
</details>
- [](content/shm.md)
<details>
<summary>消息队列</summary>
</details>
- [](content/msg.md)
<details>
<summary>ipc命令</summary>
</details>
- [](content/ipc_command.md)
<details>
<summary>在进程间传递文件描述符</summary>
</details>
- [](content/send_fd.md)

### 多线程编程

<details>
<summary>linux线程概述</summary>
</details>
- [](content/linux_thread.md)
<details>
<summary>创建线程和结束线程</summary>
</details>
- [](content/pthread_op.md)
<details>
<summary>线程属性</summary>
</details>
- [](content/pthread_attr.md)
<details>
<summary>posix信号量</summary>
</details>
- [](content/pthread_posix_sem.md)
<details>
<summary>互斥锁</summary>
</details>
- [](content/pthread_mutex.md)
<details>
<summary>条件变量</summary>
</details>
- [](content/pthread_cond.md) 
<details>
<summary>线程同步机制包装类</summary>
</details>
- [](content/locker.md)
<details>
<summary>多线程环境</summary>
</details>
- [](content/linux_thread_env.md)

### 进程池和线程池

<details>
<summary>进程池和线程池概述</summary>
</details>
- [](content/process_pool_thread_pool.md)
<details>
<summary>半同步/半异步进程池实现</summary>
</details>
- [](content/implement_process_pool.md)
<details>
<summary>用进程池实现的简单cgi服务器</summary>
</details>
- [](content/cgi_server_use_process_pool.md)
<details>
<summary>半同步/半反应堆线程池实现</summary>
</details>
- [](content/implement_thread_pool.md)
<details>
<summary>用线程池实现的简单web服务器</summary>
</details>
- [](content/web_server_use_thread_pool.md)

### 服务器调制、调试和测试

<details>
<summary>最大文件描述符数</summary>
</details>
- [](content/max_file_number.md)
<details>
<summary>调整内核参数</summary>
</details>
- [](content/adjust_kernel_arg.md)
<details>
<summary>压力测试</summary>
</details>
- [](content/pressure_test.md)
