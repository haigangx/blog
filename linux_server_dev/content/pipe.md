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

