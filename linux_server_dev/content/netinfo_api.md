# 网络信息API

## 1. gethostbyname和gethostbyaddr

gethostbyname：根据主机名称获取主机完整信息，会先在/etc/hosts查找主机，找不到再访问DNS服务器查找

gethostbyaddr：根据IP地址获取主机完整信息 

```
#include <netdb.h>
struct hostent* gethostbyname(const char* name);
struct hostent* gethostbyaddr(const void* addr, size_t len, int type);
```

- name：目标主机主机名
- addr：指定目标主机的IP地址
- len：addr所指IP地址的长度
- type：addr所指的IP地址类型，可取AF_INET和AF_INET6

返回值类型：

```
struct hostent
{
    char* h_name;          //主机名
    char** h_aliases;      //主机别名列表
    int h_addrtype;        //地址类型
    int h_length;            //地址长度
    char** h_addr_list;  //按网络字节序列出的主机IP地址列表
};
```

使用：
```
char *host = "www.baidu.com";
struct hostent* hostinfo = gethostbyname(host);
assert(hostinfo);
```

这两个函数都是不可重入函数，对应的可重入函数为原函数名+_r

## 2. getservbyname和getservbyport

getservbyname：根据名称获取某个服务的完整信息

getservbyport：根据端口号获取某个服务的完整信息

```
#include <netdb.h>
struct servent* getservbyname(const char* name, const char* proto);
struct servent* getservbyport(int port, const char* proto);
```

- name：目标服务的名字
- port：目标服务对应端口号
- proto：指定服务类型，"tcp"表示流服务，"udp"表示数据报服务

返回值类型：
```
struct servent
{
    char* s_name;       //服务名称
    char** s_aliases;   //服务别名列表
    int s_port;             //端口号
    char* s_proto;      //服务类型tcp or udp
};
```

使用：
```
struct servent* servinfo = getservbyname("daytime", "tcp");
assert(servinfo);
```

这两个函数都是不可重入函数，对应的重入版本为原函数名+_r

## 3. getaddrinfo

getaddrinfo即能通过主机名获得IP地址(内部使用gethostbyname)，也能通过服务名获得端口号(内部使用getservbyname)，它是否可重入取决于内部调用的gethostbyname和getservbyname是否是可重入版本

```
#include <netdb.h>
int getaddrinfo(const char* hostname, const char* service, 
                      const struct addrinfo* hints, struct addrinfo** result)
```

- hostname：字符串形式的主机名或IP地址
- service：字符串形式服务名或十进制端口号
- result：结果链表
- hints：对getaddrinfo的输出进行精确控制

  ```
  struct addrinfo
  {
      int ai_flags;                      //后文
      int ai_family;                    //地址族
      int ai_socktype;               //SOCKET_STREAM or SOCKET_DGRAM
      int ai_protocol;                //后文
      socklen_t ai_addrlen;      //socket地址ai_addr的长度
      char* ai_canonname;      //主机别名
      struct sockaddr* ai_addr; //指向socket地址
      struct addrinfo* ai_next;  //下一个addrinfo地址
  };
  ```
  - ai_protocol：具体的网络协议，含义与socket系统调用第三个参数相同，通常为0
  - ai_flags(主要选项):
    - AI_CANONONAME：hists参数设置，告诉getaddrinfo函数返回主机别名
    - AI_NUMERICHOST：hists参数设置，hostname必须是用字符串表示的IP地址，避免DNS查询
    - AI_NUMERICSERV：hists参数设置，service强制使用十进制端口号的字符串形式,不能是服务名

使用：
```
struct addrinfo hints;
struct addrinfo* res;

bzero(&hints, sizeof(hints));
hints.ai_socktype = SOCKET_STREAM;
getaddrinfo("ernest-laptop", "daytime", &hints, &res);
```

getaddrinfo中为res指针隐式分配堆内存，所以函数调用完毕后，使用如下配对函数释放这块内存：

```
void freeaddrinfo(struct addrinfo* res);
```

## 4. getnameinfo

getnameinfo函数通过socket地址获得字符串形式的主机名和服务名(内部由gethostbyaddr和getservbyport实现)，它是否可重入由内部调用gethostbyaddr和getservbyport的可重入版本

```
#inlcude <netdb.h>
int getnameinfo(const struct sockaddr* sockaddr, socklen_t addrlen, char* host, 
                socklen_t hostlen, char* serv, socklen_t servlen, int flags);
```

- host：返回的主机名
- serv：返回的服务名
- flags(主要选项)：
  - NI_NAMEREQD：通过socket地址不能得到主机名则返回错误
  - NI_NUMERICHOST：返回字符串表示的IP地址，而非主机名
  - NI_NUMERICSERV：返回字符串表示的十进制端口号，而非服务名
