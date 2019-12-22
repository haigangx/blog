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
