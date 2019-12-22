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

