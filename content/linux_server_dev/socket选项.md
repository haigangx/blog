# socket选项

fcntl系统调用是控制文件描述符属性的通用POSIX方法，而getsockopt和setsockopt则是专门用来读取和设置socket文件描述符属性的方法：

```
#include <sys/socket.h>
int getsockopt(int sockfd, int level, int option_name, 
               void *option_value, socklen_t *restrict option_len);
int setsockopt(int sockfd, int level, int option_name, 
               const void *option_value, socklen_t option_len);
```

## 1. 参数

- **sockfd**：被操作的目标socket
- **level**：指定要操作那个协议的选项，例如IPv4、IPv6、TCP等
- **option_name**：指定选项名字
- **option_vlaue和option_len**：分别指定被操作选项的值和长度

## 2. 返回值

两个函数成功时都返回1，失败时返回-1并设置errno

对服务器而言：
> 有部分socket选项只能在调用listen前针对监听socket设置才有效，因为连接socket只能由accept调用返回，而accept从listen监听队列中接收的连接至少已经完成了tcp三次握手的前两个步骤（监听队列中的连接至少已经进入SYN_RCVD状态），这说明服务器已经往被接收连接上发送除了tcp同步报文段。但有的socket选项却应该在tcp同步报文段中设置，比如tcp最大报文段选项，对这种情况解决方案：对监听socket设置这些socket选项，那么accept返回的连接socket将自动继承这些选项，这些socket选项包括：SO_DEBUG、SO_DONTROUTE、SO_KEEPALIVE、SO_LINGER、SO_OOBINLINE、SO_RCVBUF、SO_RCVLOWAT、SO_SNDBUF、SO_SNDLOWAT、TCP_MAXSEG和TCP_NODELAY

对客户端而言：
> 这些socket选项应该在调用connect函数之前设置，因为connect调用成功返回之后，tcp三次握手已经完成

## 3. socket选项

- **SO_REUSEADDR**

  设置socket选项SO_REUSEADDR来强制使用被处于TIME_WAIT状态的连接的占用的socket地址。

  具体实现方法如下：

  ```
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  assert(sockfd >= 0);

  //设置SO_REUSEADDR
  int reuse = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

  struct sockaddr_in address;
  bzero(&address, sizeof(address));
  address.sin_family = AF_INET;
  inet_pton(AF_INET, ip, &address.sin_addr);
  address.sin_port = htons(port);
  int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
  ```

  此外还可以通过修改内核参数`/proc/sys/net/ipv4/tcp_tw_recycle`来快速回收被关闭的socket，使得tcp连接根本就不会进入TIME_WAIT状态，进而允许应用程序立即重用本地的socket地址

- **SO_RCVBUF和SO_SNDBUF**

  SO_RCVBUF：设置TCP接收缓冲区大小

  SO_SNDBUF：设置TCP发送缓冲区大小

  > 使用setsockopt设置TCP缓冲区大小时，系统一般都会将设置值加倍，并且不得小于某个值，一般TCP接收缓冲区最小值为256字节，而发送缓冲区的最小值是2048字节，这种机制的目的是确保一个TCP连接拥有足够的空闲缓冲区处理拥塞，可以通过修改内核参数`/proc/sys/net/ipv4/tcp_rmem`和`/proc/sys/net/ipv4/tcp_wmem`来强制TCP接收和发送缓冲区的大小没有最小值限制

  ```
  int sendbuf = 4096;
  int sendlen = sizeof(sendbuf);
  setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, sizeof(sendbuf));
  getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, (socklen_t *)&sendlen);

  int recvbuf = 1024;
  int recvlen = sizeof(recvbuf);
  setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, sizeof(recvbuf));
  getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, (socklen_t *)&recvlen);
  ```

- **SO_RCVLOWAT和SO_SNDLOWAT**

  SO_RCVLOWAT：表示TCP接收缓冲区的低水位标记，当TCP接收缓冲区中可读数据的总数大于其低水位标记时，I/O复用系统调用将通知应用程序可以从对应的socket读取数据

  SO_SNDLOWAT：表示TCP发送缓冲区的低水位标记，当TCP发送缓冲区中的空闲空间大于其低水位标记时，I/O复用系统调用将通知应用程序可以往对应的socket上写入数据

  这两个标记一般被I/O复用系统调用用来判断socket是否可读或可写，默认情况这两个低水位标记均为1字节

- **SO_LINGER**

  SO_LINGER：用于控制close系统调用在关闭TCP连接时的行为(默认情况下使用close关闭一个socket时，close将立即返回，TCP模块负责将socket对应的TCP发送缓冲区中残留的数据发送给对方)

  设置SO_LINGER需要给setsockopt和setsockopt系统调用传递一个linger类型结构体

  ```
  #include <sys/socket.h>
  struct linger
  {
      int l_onoff;    //开启(非0)还是关闭(0)该选项
      int l_linger;   //滞留时间
  };
  ```

  - 1. l_onoff=0：

    SO_LINGER设置无效，close()保持默认行为

  - 2. l_onoff!=0：

    l_linger=0：close()立即返回，丢弃被关闭socket发送缓冲区残留的数据，同时向对方发送一个复位报文段

  - 3. l_onoff!=0， l_linger>0：
    如果socket是阻塞的，close将等待l_linger的时间再返回，如果close返回时TCP模块中还没有发送完残留数据并得到对方的确认，close系统调用将返回-1并设置errno为EWOULDBLOCK；如果socket非阻塞，close立即返回，然后根据返回值和errno判断残留数据是否发送完毕

