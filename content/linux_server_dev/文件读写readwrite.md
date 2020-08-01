# 文件读写

<!-- TOC -->

- [一、read](#一read)
- [二、write](#二write)
- [三、阻塞和非阻塞](#三阻塞和非阻塞)
    - [1. 阻塞](#1-阻塞)
        - [1.1 阻塞读终端](#11-阻塞读终端)
    - [2. 非阻塞](#2-非阻塞)
        - [2.1 非阻塞读终端](#21-非阻塞读终端)

<!-- /TOC -->

## 一、read

```c
#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count);
```

- `fd` 是要读的文件或设备
- `count` 是请求读取的字节数，读上来的数据保存在缓冲区 `buf` 中，同时文件的当前读写位置向后移
- 返回值：成功返回读取的字节数，出错返回 -1 并设置 errno，如果在调 read 之前已到达文件末尾，则这次 read 返回 0

## 二、write

```c
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
```

- 返回值：成功返回写入的字节数，出错返回 -1 并设置 errno

## 三、阻塞和非阻塞

### 1. 阻塞

阻塞（Block）即当进程调用一个阻塞的系统函数时，该进程被置于睡眠（Sleep）状态，这时内核调度其它进程运行，直到该进程等待的事件发生了（比如网络上接收到数据包，或者调用sleep指定的睡眠时间到了）它才有可能继续运行。

读/写常规文件是不会阻塞的，不管读多少字节，read 一定会在有限的时间内返回。而从终端设备或网络读则不一定，如果从终端输入的数据没有换行符，调用 read 读终端设备就会阻塞，如果网络上没有接收到数据包，调用 read 从网络读就会阻塞，至于会阻塞多长时间也是不确定的，如果一直没有数据到达就一直阻塞在那里。

#### 1.1 阻塞读终端

```c
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    char buf[10];
    int n;
    n = read(STDIN_FILENO, buf, 10);
    if (n < 0) {
        perror("read STDIN_FILENO");
        exit(1);
    }

    write(STDOUT_FILENO, buf, n);
    return 0;
}
```

执行结果：

```
$ ./a.out
hello（回车）
hello

$ ./a.out
hello world（回车）
hello worl$ d
bash: d: command not found
```

第一次执行 a.out 的结果很正常，而第二次执行的过程有点特殊，现在分析一下： 

a.out 调用 read 时睡眠等待，直到终端设备输入了换行符才从 read 返回，read 只读走 10 个字符，剩下的字符仍然保存在内核的终端设备输入缓冲区中。a.out 进程打印并退出，这时 Shell 进程恢复运行，Shell 继续从终端读取用户输入的命令，于是读走了终端设备输入缓冲区中剩下的字符 d 和换行符，把它当成一条命令解释执行，结果发现执行不了，没有 d 这个命令。

### 2. 非阻塞


如果在open一个设备时指定了O_NONBLOCK标志，read/write就不会阻塞。

以read为例，如果设备暂时没有数据可读就返回-1，同时置errno为EWOULDBLOCK（或者EAGAIN，这两个宏定义的值相同），表示本来应该阻塞在这里（would block，虚拟语气），事实上并没有阻塞而是直接返回错误，调用者应该试着再读一次（again）。这种行为方式称为轮询（Poll），调用者只是查询一下，而不是阻塞在这里死等，这样可以同时监视多个设备：

```
while(1) {
    非阻塞read(设备1);
    if(设备1有数据到达)
        处理数据;
    非阻塞read(设备2);
    if(设备2有数据到达)
        处理数据;
    ...
}
```

后面可以通过 IO 服用函数来管理非阻塞 IO

#### 2.1 非阻塞读终端

```c
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define MSG_TRY "try again\n"

int main(void)
{
    char buf[10];
    int fd, n;
    fd = open("/dev/tty", O_RDONLY|O_NONBLOCK);
    if(fd<0) {
        perror("open /dev/tty");
        exit(1);
    }
    tryagain:
    n = read(fd, buf, 10);
    if (n < 0) {
        if (errno == EAGAIN) {
            sleep(1);
            write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
            goto tryagain;
        }
        perror("read /dev/tty");
        exit(1);
    }
    write(STDOUT_FILENO, buf, n);
    close(fd);
    return 0;
}
```