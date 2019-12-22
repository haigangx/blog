# tee函数

tee函数用于在两个管道文件描述符之间复制数据，也是零拷贝操作。它不消耗数据，因此源文件描述符上的数据仍然可以用于后续的读操作

```
#include <fcntl.h>
ssize_t tee(int fd_in, int fd_out, size_t len, unsigned int flags);
```

fd_in和fd_out必须都是管道文件描述符

len,flags参数含义和splice函数相同

tee函数成功返回两个文件描述符之间复制的字节数，0表示没有复制任何数据

失败返回-1并设置errno
