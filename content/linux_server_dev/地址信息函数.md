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
