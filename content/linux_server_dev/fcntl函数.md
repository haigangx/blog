# fcntl函数

fcntl函数(file control)提供了对文件描述符的各种控制操作

```
#include <fcntl.h>
int fcntl(int fd, int cmd, ...);
```

## 参数

- fd：要操作的文件描述符
- cmd：执行的操作类型，根据不同的操作类型，该函数可能需要第三个可选参数arg

| 操作分类 | 操作 | 含义 | 第三个参数的类型 | 成功时的返回值 |
| --- | --- | --- | --- | --- |
| 复制文件描述符 | F_DUPFD | 创建一个值大于或等于arg的新文件描述符 | long | 新创建的文件描述符 |
| | F_DUPFD_CLOEXEC | 与F_DUPFD类似，不过新的文件描述符被设置了close-on-exec标志 | long | 新创建的文件描述符 |
| 获取和设置文件描述符标志 | F_GETFD | 获取fd的标志(比如close-on-exec) | 无 | fd标志 |
| | F_SETFD | 设置fd的标志 | long | 0 |
| 获取和设置文件描述符的状态标志 | F_GETFL | 状态标志包括:O_APPEND,O_CREAT,O_RDONLY,O_WRONLY,O_RDWR | void | fd的状态标志 |
| | F_SETFL | 设置状态标志，但部分标志不能被修改(如访问模式标志) | long | 0 |
| 管理信号 | F_GETOWN | 获得SIGIO和SIGURG的宿主进程PID或进程组的组ID | 无 | 进程ID或者组ID |
| | F_SETOWN | 设置SIGIO和SIGURG的宿主进程PID或进程组的组ID | long | 0 |
| | F_GETSIG | 获取应用程序被通知fd可读或可写的是哪个信号 | 无 | 信号值，0表示SIGIO |
| | F_SETSIG | 设置通知应用程序fd可读或可写的是哪个信号 | long | 0 |
| 操作管道容量 | F_SETPIPE_SZ | 设置由fd指定的管道的容量。/proc/sys/fs/pipe-size-max内核参数指定了fcntl能设置的管道容量的上限 | long | 0 |
| | F_GETPIPE_SZ | 获取由fd指定的管道的容量 | 无 | 管道容量 |


SIGIO和SIGURG这两个信号必须与某个文件描述符相关联才能使用:

- SIGIO：异步IO，当被关联的文件描述符可读或可写时，系统将触发SIGIO信号
- SIGURG：带外数据到达信号，当被关联的文件描述符(必须为socket)有带外数据到达时，该信号被触发

使用fcntl函数为目标文件描述符指定宿主进程或进程组，被指定的宿主进程或者进程组将捕获这两个信号

## 返回值

fcntl函数成功时返回值如表所示，失败则返回-1并设置errno

## 用法

例：使用fcnt函数将一个文件描述符设置为非阻塞的
```
int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL); //获取文件描述符旧的状态标志
    int new_option = old_option | O_NONBLOCK; //设置非阻塞状态
    fcntl(fd, F_SETFL, new_option);
    return old_option; //返回旧的状态标志，以便日后恢复
}
```
