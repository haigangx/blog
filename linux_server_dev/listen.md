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
