# 获取文件信息 stat

<!-- TOC -->

- [一、stat](#一stat)
- [二、access](#二access)

<!-- /TOC -->

## 一、stat

```
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int stat(const char *path, struct stat *buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *path, struct stat *buf);

struct stat {
    dev_t st_dev; /* ID of device containing file */
    ino_t st_ino; /* inode number */
    mode_t st_mode; /* protection */
    nlink_t st_nlink; /* number of hard links */
    uid_t st_uid; /* user ID of owner */
    gid_t st_gid; /* group ID of owner */
    dev_t st_rdev; /* device ID (if special file) */
    off_t st_size; /* total size, in bytes */
    blksize_t st_blksize; /* blocksize for file system I/O */
    blkcnt_t st_blocks; /* number of 512B blocks allocated */
    time_t st_atime; /* time of last access */
    time_t st_mtime; /* time of last modification */
    time_t st_ctime; /* time of last status change */
};
```

stat既有命令也有同名函数，用来获取文件Inode里主要信息

stat 跟踪符号链接，lstat不跟踪符号链接

stat里面时间辨析：

- atime(最近访问时间)： 
- mtime(最近更改时间):指最近修改文件内容的时间
- ctime(最近改动时间)：指最近改动Inode的时间

## 二、access

```
#include <unistd.h>
int access(const char *pathname, int mode);
```

access 按实际用户ID和实际组ID测试,跟踪符号链接

参数mode：
- `R_OK` 是否有读权限
- `W_OK` 是否有写权限
- `X_OK` 是否有执行权限
- `F_OK` 测试一个文件是否存在

sudo 执行时，有效用户 ID 是root，实际用户 ID 是 xingwenpeng