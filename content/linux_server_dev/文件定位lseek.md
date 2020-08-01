# 文件定位 lseek

## 一、lseek

每个打开的文件都记录着当前读写位置：

- 通常打开文件时读写位置是 0，表示文件开头，通常读写多少个字节就会将读写位置往后移多少个字节。
- 如果以 O_APPEND 方式打开，每次写操作都会在文件末尾追加数据，然后将读写位置移到新的文件末尾

lseek 可以手动移动当前读写位置：

```
#include <sys/types.h>
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence);
```

- `fd` 打开文件的文件描述符
- `offset` off_t 类型的偏移量，off_t 一般为整型类型
- `whence` 可以取以下三个值之一：

   1. `SEEK_SET` 设置文件读写位置为 offset
   2. `SEEK_CUR` 设置文件读写位置为当前位置 +offset
   3. `SEEK_END` 设置文件读写位置为文件大小 +offset

- 返回值：成功返回新的偏移量，失败返回 -1 并设置 errno
  - 如果设备不支持 lseek，errno 将设置为 ESPIPE

## 二、lseek 的更多用处

- 当设置的读写位置超过文件末尾时，lseek 将拓展文件，其中拓展出来的部分都是 0
- 可以通过 lseek 确定一个打开文件的当前偏移量：

  ```c
  off_t currpos;
  currpos = lseek(fd, 0, SEEK_CUR);
  ```