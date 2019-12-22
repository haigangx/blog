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
