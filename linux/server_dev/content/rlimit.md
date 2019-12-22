# 系统资源限制

Linux上运行的程序都会受到资源限制的影响，比如物理设备限制(CPU数量、内存数量的)、系统策略限制(CPU时间)以及具体实现的限制(比如文件名的最大长度)

Linux系统资源限制通过getrlimit函数和setrlimit函数来读取和设置：

```
#include <sys/resource.h>
int getrlimit(int resource, struct rlimit* rlim);
int setrlimit(int resource, const struct rlimit* rlim);
struct rlimit
{
    rlim_t rlim_cur;    //资源软限制
    rlim_t rlim_max;    //资源硬限制
};
```

软限制：建议性的、最好不要超越的限制，如果超越的话，系统可能向进程发送信号终止其运行，例：

    当进程CPU时间超过其软限制时，系统将向进程发送SIGXCPU信号；
    
    当文件尺寸超过其软限制时，系统将向进程发送SIGXFSZ信号
    
硬限制：一般为软限制上限，普通程序可以减小硬限制，只有root用户可以增加硬限制

可以使用ulimit命令修改当前shell环境下的资源限制，这种改变只对当前shell启动的后续程序有效

也可以通过修改配置文件来改变资源限制，这种修改是永久的

resource参数指定资源限制类型，下表列举比较重要的资源限制类型：

资源限制类型	含义
- RLIMIT_AS	进程虚拟内存总量限制，超过该限制将导致某些函数(如mmap)产生ENOMEM错误
- RLIMIT_CORE	进程核心转储文件(core dump)的大小限制，值为0表示不产生该文件
- RLIMIT_CPU	进程CPU时间限制(unit:s)
- RLIMIT_DATA	进程数据段(初始化数据data段，未初始化数据bss段和堆)限制(unit:B)
- RLIMIT_FSIZE	文件大小限制(unit:字节),超过该限制将导致某些函数(如write)产生EFBIG错误
- RLIMIT_NOFILE	文件描述符数量限制，超过该限制将导致某些函数(如pipe)产生EMFILE错误
- RLIMIT_NPROC	用户能创建的进程数限制，超过该限制将导致某些函数(如fork)产生EAGAIN错误
- RLIMIT_SIGPENDING	用户能够挂起的信号数量限制
- RLIMIT_STACK	进程栈内存限制，超过该限制将引起SIGSEGV信号

setrlimit和getrlimit成功时返回0，失败时返回-1并设置errno
