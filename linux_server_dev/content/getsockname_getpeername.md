# 地址信息函数

有时，我们想知道一个连接socket的本端socket地址和远端socket地址，可以使用`getsockname`和`getpeername`

```
#include <sys/socket.h>
int getsockname(int sockfd, struct sockaddr* address, socklen_t* address_len);
int getpeername(int sockfd, struct sockaddr* address, socklen_t* address_len);
```

getsockname获取sockfd对应的本端的socket地址，成功返回0，失败返回-1并设置errno

getpeername获取sockfd对应的远端的socket地址

