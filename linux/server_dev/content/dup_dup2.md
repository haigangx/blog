# dup和dup2

```
#include <unistd.h>
int dup(int file_descriptor);
int dup2(int file_descriptor_one, file_descriptor_two);
```

## 说明

**dup** ：创建一个新的文件描述符，新文件描述符与原有文件描述符file_descriptor指向相同的文件、管道或网络连接，dup总是返回系统当前可用的最小文件描述符

**dup2** ：返回第一个不小于file_descriptor_two的新文件描述符，新文件描述符与文件描述符file_descriptor_one有相同指向

> 通过dup和dup2创建的文件描述符并不继承原文件描述符的文件描述符属性，比如`close-on-exec`和`non-blocking` (note：注意区分文件描述符属性和文件属性)

dup和dup2调用失败时返回-1并设置errno

## 使用

使用dup函数实现一个基本的CGI服务器

```

```
