# 文件链接

## 一、link

```
#include <unistd.h>
int link(const char *oldpath, const char *newpath);
```

link 创建一个硬链接，当 rm 删除文件时，只是删除了目录下的记录项和把 inode 硬链接计数减 1，当硬链接计数减为 0 时，才会真正的删除文件。

- 硬链接通常要求位于同一文件系统中,POSIX 允许跨文件系统
- 符号链接没有文件系统限制
- 通常不允许创建目录的硬链接，某些 unix 系统下超级用户可以创建目录的硬链接
- 创建目录项以及增加硬链接计数应当是一个原子操作

## 二、symlink

```
int symlink(const char *oldpath, const char *newpath)
```

symlink 创建一个软连接，即符号连接

## 三、readlink

```
ssize_t readlink(const char *path, char *buf, size_t bufsiz)
```

readlink 读符号链接所指向的文件名字，不读文件内容

## 四、unlink

```
int unlink(const char *pathname)
```

1. 如果是符号链接，删除符号链接
2. 如果是硬链接，硬链接数减 1，当减为 0 时，释放数据块和 inode
3. 如果文件硬链接数为 0，但有进程已打开该文件，并持有文件描述符，则等该进程关闭该文件时，kernel 才真正
去删除该文件
4. 利用该特性创建临时文件，先 open 或 creat 创建一个文件，马上 unlink 此文件