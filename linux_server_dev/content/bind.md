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
 
