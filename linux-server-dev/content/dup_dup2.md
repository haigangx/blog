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
