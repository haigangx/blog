# socket地址结构体

## 通用socket地址：

```
#include <bits/socket.h>
struct sockaddr
{
    sa_family_t sa_family;
    char sa_data[14];
};
```

sa_family指明地址类型，地址类型可取值：

- AF_UNIX / PF_UNIX：Unix本地域协议族
- AF_INET / PF_INET：TCP/IPv4协议族
- AF_INET6 / PF_INET6：TCP/IPv6协议族

sa_data用于存放socket地址值，sa_family取不同协议值时，sa_data具有不同的含义和长度，当sa_family=

- AF_UNIX时：sa_data表示文件的路径名，长度可达108字节
- AF_INET：sa_data表示16bit端口号和32bit IPv4地址，共6字节
- AF_INET6：16bit端口号，32bit流标识，128bit IPv6地址，32bit范围ID，共26字节



14字节的sa_data根本无法容纳多数协议族的地址值，因此Linux还定义了下面这个新的通用socket地址结构体

```
struct sockaddr_storage
{
    sa_family_t sa_family;
    unsigned long int __ss_align;
    char __ss_padding[128-sizeof(__ss_align)];
};
```


## 专用socket地址：

UNIX本地域协议族sockaddr_un专用地址结构体：

```
#include <sys/un.h>
struct sockaddr_un
{
    sa_family_t sin_family;    //地址族：AF_UNIX
    char sun_path[108];    //文件路径名
};
```

Linux下IPv4专用socket地址结构体:

```
struct sockaddr_in
{
    sa_family_t sin_family;    //地址族：AF_INET
    u_int16_t sin_port;    //端口号：要用网络字节序表示
    struct in_addr sin_addr;    //IPv4地址结构体，见下
};
struct in_addr
{
    u_int32_t s_addr;    //IPv4地址，要用网络字节序表示
};
```

Linux下IPv6专用socket地址结构体:

```
struct sockaddr_in6
{
    sa_family_t sin6_family;    //地址族：AF_INET6
    u_int16_t sin6_port;    //端口号
    u_int32_t sin6_flowinfo;    //流信息，应设置为0
    struct in6_addr sin6_addr;    //IPv6地址
    u_int32_t sin6_scope_id;    //scope ID，尚在实验
};
struct in6_addr
{
    unsigned char sa_addr[16];  //IPv6地址，要用网络字节序表示
};
```

上述socket地址类型在使用过程中都要转化为sockaddr类型，因为所有的socket编程接口使用的地址参数的类型都是sockaddr
