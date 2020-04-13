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
