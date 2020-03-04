# mmap和munmap

mmap函数用于申请一段内存空间。可以将这段内存作为进程间通信的共享内存，也可以讲文件直接映射到其中

munmap函数用于释放mmap创建的内存空间

```
#include <sys/mman.h>
void *mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void *start, size_t length);
```

- start：用户指定某个特定地址作为这段内存的起始地址，如果为NULL，系统自动分配一个地址
- length：内存段的长度
- prot：内存段的访问权限：PROT_READ(可读),PROT_WRITE(可写),PROT_EXEC(可执行),PROT_NONE(不能被访问)
- flags：控制内存段内容被修改后程序的行为

  常用值	含义
  - MAP_SHARED	内存段的修改同步到文件
  - MAP_PRIVATE	内存段为进程私有，修改不会同步到文件
  - MAP_ANONYMOUS	内存段并非文件映射而来，内容初始化为0，mmap函数后两个参数被忽略
  - MAP_FIXED	内存段必须位于start参数指定的地址处，start必须是内存页面大小(4096字节)的整数倍
  - MAP_HUGETLB	“大内存页面”分配内存空间，“大内存页面”大小通过/proc/meminfo查看
- fd：要映射的文件
- offset：从文件的偏移量offset开始映射

mmap函数成功返回指向目标内存区域的指针，失败返回MAP_FAILED((void*)-1)并设置errno

munmap函数成功返回0，失败返回-1并设置errno
