# IP地址转换函数

```
#include <arpa/inet.h>

in_addr_t inet_addr( const char *strptr );
int inet_aton( const char *cp, struct in_addr *inp );
```

**inet_addr** 函数将用点分十进制字符串表示的IPv4地址转化为用网络字节序整数表示的IPv4地址。失败返回INADDR_NONE

**inet_aton** 和inet_addr函数功能相同，但是将转化结果存储于参数inp指向的地址结构中。成功返回1，失败返回0

```
char *inet_ntoa( struct in_addr in );   //内部使用静态变量存储结果，不可重入
```

**inet_ntoa** 函数将用网络字节序整数表示的IPv4地址转化为用点分十进制字符串表示的IPv4地址，需要注意的是该函数内部使用静态变量存储结果，所以不可重入


**inet_pton** 和 **inet_ntop** 同时适用于IPv4和IPv6地址转化：

```
int inet_pton( int af, const char *src, void *dst );
const char *inet_ntop( int af, const void *src, char *dst, socklen_t cnt );
```

af参数指定地址族：可取`AF_INET`和`AF_INET6`

inet_pton函数将用字符串表示的IP地址src(IPv4或者IPv6)转化为网络字节序整数表示的IP地址。成功返回1，失败返回0并设置errno

inet_ntop函数将网络字节序整数src转化为字符串表示的IP地址，参数cnt指定dst字符串的长度

cnt参数可取的值为：
```
#include <netinet/in.h>
#define INET_ADDRSTRLEN 16
#define INET6_ADDRSTRLEN 46
```

inet_ntop成功时返回目标存储单元的地址，失败返回NULL并设置errno


