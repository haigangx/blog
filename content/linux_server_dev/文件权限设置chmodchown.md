# 文件权限设置

<!-- TOC -->

- [一、chmod](#一chmod)
- [二、chown](#二chown)

<!-- /TOC -->

## 一、chmod

```c
#include <sys/stat.h>
int chmod(const char *path, mode_t mode);
int fchmod(int fd, mode_t mode);
```


## 二、chown

```c
#include <unistd.h>
int chown(const char *path, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int lchown(const char *path, uid_t owner, gid_t group); //跟踪符号链接
```

chown 使用时必须拥有 root 权限