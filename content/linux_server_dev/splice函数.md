# splice函数

splice函数用于在两个文件描述符之间移动数据，也是零拷贝操作(数据完全在内核中操作)

```
#inlcude <fcntl.h>
ssize_t splice(int fd_in, loff_t* off_in, int fd_out, loff_t* off_out, 
            size_t len, unsigned int flags);
```

## 参数

- fd_in：待输入数据的文件描述符

  如果fd_in是管道文件描述符，off_in必须为NULL
  
  如果fd_in不是管道文件描述符，off_in表示读取数据的位置，off_in为NULL表示从当前位置读取
  
- fd_out：含义与fd_in相同，不过用于输出数据
- len：指定移动数据的长度
- flags：控制数据如何移动，可以是以下值的按位或：
  
  | 常用值 | 含义 |
  | --- | --- |
  | SPLICE_F_MOVE | 按整页移动数据(只是给内核的提示) |
  | SPLICE_F_NONBLOCK | 非阻塞splice，实际效果受文件描述符本身阻塞状态的影响 |
  | SPLICE_F_MORE | 后续的splice调用将读取更多数据(给内核提示) |
  | SPLICE_F_GIFT | 对splice无效果 |
  
使用splice函数时，fd_in和fd_out必须至少有一个是管道文件描述符。

## 返回值

splice函数成功返回移动字节个数，返回0表示没有数据移动(从管道读取数据，而管道无数据写入时发生)

失败返回-1并设置errno，常见错误表如下：

| errno | 含义 |
| --- | --- |
| EBADF | 参数所指fd有误 |
| EINVAL | 目标系统不支持splice，或目标文件以追加方式打开，或两个文件描述符都不是管道文件描述符，或某个offset参数被用于不支持随机访问的设备(如字符设备) |
| ENOMEM | 内存不够 |
| ESPIPE | fd_in(off_in)为管道文件描述符，但off_in(off_out)不为NULL |

## 用法

使用splice函数实现一个零拷贝的回射服务器

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
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc <= 2)
    {
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
    if (connfd < 0)
    {
        printf("errno is : %s\n", strerror(errno));
    }
    else
    {
        int pipefd[2];
        assert(ret != -1);
        ret = pipe(pipefd);  //创建管道
        //将connfd上流入的客户数据定向到管道中
        ret = splice(connfd, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
        assert(ret != -1);
        //将管道的输出定向到connfd客户连接文件描述符
        ret = splice(pipefd[0], NULL, connfd, NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
        assert(ret != -1);
        close(connfd);
    }
    close(sock);
    return 0;
}
```

测试：

```
g++ -o test_splice.o test_splice.cpp
./test_splice.o 127.0.0.1 1234

telnet 127.0.0.1 1234
# 输入字符服务器会返回相同字符
```
