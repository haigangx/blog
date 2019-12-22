# sendfile函数

sendfile函数在两个文件描述符之间直接传递数据(完全在内核中操作),从而避免了内核缓冲区和用户缓冲区之间的数据拷贝，效率很高，被称为零拷贝。

```
#include <sys/sendfile.h>
ssize_t sendfile(int out_fd, int in_fd, off_t* offset, size_t count);
```

- out_fd：等待写入内容的fd，可理解为发送给网络上的socket
- in_fd：待读出内容的fd，可理解为本地需要发送的文件
- offset：指定读入文件的读取偏移量，如果为空，则从默认读取位置读取
- count：指定传输字节数

函数成功返回传输的字节数，失败返回-1并设置errno

in_fd必须为支持mmap函数的文件描述符，必须指向真实的文件，不能是socket或者管道

out_fd则必须为socket

由此可见，sendfile是专门为在网络上传输文件设计的
