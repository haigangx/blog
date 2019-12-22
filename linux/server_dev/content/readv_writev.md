# readv和writev

readv：将数据从文件描述符读到分散的内存块中，即分散读

writev：将数据从多块分散的内存数据一并写入文件描述符中，即集中写

```
#include <sys/uio.h>
ssize_t readv(int fd, const struct iovec* vector, int count);
ssize_t writev(int fd, const struct iovec* vector, int count);

struct iovec
{
    void *iov_base;    //内存起始地址
    size_t iov_len;     //这块内存的长度
};
```
vector：iovec描述一块内存区，count表是vector数组中内存区iovec的数量

readv和writev在成功时返回读入/写入fd的字节数，失败返回-1并设置errno
