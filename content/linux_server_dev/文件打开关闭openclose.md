# 文件打开和关闭open/close

<!-- TOC -->

- [一、open](#一open)
- [二、umask 掩码](#二umask-掩码)
- [三、最大打开文件个数](#三最大打开文件个数)
- [四、close](#四close)

<!-- /TOC -->

## 一、open

```
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
```

- `pathname` 参数是要打开或创建的文件名，既可以是相对路径也可以是绝对路径
- `flags` 参数有一系列常数值可供选择，可以同时选择多个常数用按位或运算符连接起来，所以这些常数的宏定义都以 O_开头，表示 or

  有三个必选项：以下三个常数中必须指定一个，且仅允许指定一个

  1. `O_RDONLY` 只读打开
  2. `O_WRONLY` 只写打开
  3. `O_RDWR` 可读可写打开

  以下可选项可以同时指定 0 个或多个，和必选项按位或起来作为 flags 参数。可选项有很多，这里只介绍一部分，其它选项可参考 `open(2)` 的 Man Page：

  - `O_APPEND` 表示追加。如果文件已有内容，这次打开文件所写的数据附加到文件的末尾而不覆盖原来的内容
  - `O_CREAT` 若此文件不存在则创建它。使用此选项时需要提供第三个参数 mode，表示该文件的访问权限
  - `O_EXCL` 如果同时指定了 O_CREAT，并且文件已存在，则出错返回
  - `O_TRUNC` 如果文件已存在，并且以只写或可读可写方式打开，则将其长度截断（Truncate）为 0 字节
  - `O_NONBLOCK` 对于设备文件，以 O_NONBLOCK 方式打开可以做非阻塞 I/O（Nonblock I/O），非阻塞 I/O 在下一节详细讲解
  - `O_CLOEXEC` 

- `mode` 参数指定文件权限，可以用八进制数表示，比如 0644 表示 -rw-r-r–，也可以用 S_IRUSR、S_IWUSR 等宏定义按位或起来表示，详见 open(2) 的 Man Page。要注意的是，文件权限由 open 的 mode 参数和当前进程的 umask 掩码共同决定。

- 返回值：成功返回新分配的文件描述符，出错返回 -1 并设置 errno

一个进程默认打开 3 个文件描述符：

1. `STDIN_FILENO 0`
2. `STDOUT_FILENO 1`
3. `STDERR_FILENO 2`

新打开文件总是返回文件描述符表中未使用的最小文件描述符。

## 二、umask 掩码

真正创建出来的文件权限是由设置权限 `&~` umask 掩码得来的

Shell进程的umask掩码可以用umask命令查看：

```
$ umask
0002
```

用 touch 命令创建一个文件时，创建权限是 0666，而 touch 进程继承了 Shell 进程的 umask 掩码，所以最终的文件权限是 0666 &~ 022=0644

```
$ touch file123
$ ls -l file123
-rw-rw-r-- 1 xingwenpeng xingwenpeng 0 9月11 23:48 file123
```

可以把 Shell 进程的 umask 改成 0 来证明 touch 创建文件的权限本来应该是 0666

```
$ rm file123
$ umask 0
$ touch file123
$ ls -l file123
-rw-rw-rw- 1 xingwenpeng xingwenpeng 0 9月11 23:52 file123
```

## 三、最大打开文件个数

查看当前系统允许打开最大文件个数（硬限制）：

```
cat /proc/sys/fs/file-max
```

当前默认设置最大打开文件个数 1024（软限制）：

```
ulimit -a
```

修改默认设置最大打开文件个数为 4096：

```
ulimit -n 4096
```

## 四、close

```
#include <unistd.h>
int close(int fd);
```
- 参数 fd 是要关闭的文件描述符
- 返回值：成功返回 0，出错返回 -1 并设置 errno