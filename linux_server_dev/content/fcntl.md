# fcntl函数

fcntl函数(file control)提供了对文件描述符的各种控制操作

```
#include <fcntl.h>
int fcntl(int fd, int cmd, ...);
```

- fd：要操作的文件描述符
- cmd：执行的操作类型，根据不同的操作类型，该函数可能需要第三个可选参数arg

表格，需要重新写

| 操作分类 | 操作 | 含义 | 第三个参数的类型 | 成功时的返回值 |
| :--- | :--- | :--- | :--- | :--- |
复制文件描述符	
F_DUPFD
F_DUPFD_CLOEXEC
创建一个值大于或等于arg的新文件描述符
与F_DUPFD类似，不过新的文件描述符被设置了close-on-exec标志
long
long
新创建的文件描述符
新创建的文件描述符
获取和设置文件描述符标志	
F_GETFD
F_SETFD
获取fd的标志(比如close-on-exec)
设置fd的标志
无
long
fd标志
0
获取和设置文件描述符的状态标志	
F_GETFL
F_SETFL
状态标志包括:O_APPEND,O_CREAT,O_RDONLY,O_WRONLY,O_RDWR
设置状态标志，但部分标志不能被修改(如访问模式标志)
void
long
fd的状态标志
0
管理信号	
F_GETOWN
F_SETOWN
F_GETSIG
F_SETSIG
获得SIGIO和SIGURG的宿主进程PID或进程组的组ID
设置SIGIO和SIGURG的宿主进程PID或进程组的组ID
获取应用程序被通知fd可读或可写的是哪个信号
设置通知应用程序fd可读或可写的是哪个信号
无
long
无
long
进程ID或者组ID
0
信号值，0表示SIGIO
0
操作管道容量	
F_SETPIPE_SZ
F_GETPIPE_SZ
设置由fd指定的管道的容量。/proc/sys/fs/pipe-size-max内核参数指定了fcntl能设置的管道容量的上限
获取由fd指定的管道的容量
long
无
0
管道容量
fcntl函数成功时返回值如表所示，失败则返回-1并设置errno
例：使用fcnt函数将一个文件描述符设置为非阻塞的
int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}
SIGIO和SIGURG这两个信号必须与某个文件描述符相关联才能使用:
SIGIO：异步IO，当被关联的文件描述符可读或可写时，系统将触发SIGIO信号
SIGURG：带外数据到达信号，当被关联的文件描述符(必须为socket)有带外数据到达时，该信号被触发
使用fcntl函数为目标文件描述符指定宿主进程或进程组，被指定的宿主进程或者进程组将捕获这两个信号
