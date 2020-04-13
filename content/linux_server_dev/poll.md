# poll

```
#include <poll.h>
int poll( struct pollfd* fds, nfds_t nfds, int timeout );
```

## 参数

- fds：pollfd结构体数组，指定所有我们监控的文件描述符上发生的可读、可写和异常事件。

    pollfd结构体定义如下：
    ```
    struct pollfd
    {
        int fd;     //文件描述符
        short events;   //注册的事件
        short revents;  //实际发生的事件，又内核填充
    };
    ```
    - fd：指定文件描述符
    - events：指定poll监听fd上的哪些事件，是一系列事件的按位或
    - revents：函数返回时由内核修改，通知fd上实际发生的事件

    poll支持的事件类型如下表：
    | 事件 | 描述 | 是否可作为输入 | 是否可作为输出 |
    | --- | --- | --- | --- |
    | POLLIN | 数据可读(包括普通数据和带外数据) | 是 | 是 |
    | POLLRDNORM | 普通数据可读 | 是 | 是 |
    | POLLPRI | 高优先级数据可读(如TCP带外数据) | 是 | 是 |
    | POLLOUT | 数据可写(包括普通数据和带外数据) | 是 | 是 |
    | POLLWRNORM | 普通数据可写 | 是 | 是 |
    | POLLWRBAND | 优先级数据可写 | 是 | 是 |
    | POLLRDHUP | TCP连接被对方关闭或者对方关闭写操作，由GNU引入，代码开始处需定义_GNU_SOURCE | 是 | 是 |
    | POLLERR | 错误 | 否 | 是 |
    | POLLHUP | 挂起。比如管道的写端被关闭后，读端描述符将收到POLLHUP事件 | 否 | 是 |
    | POLLNVAL | 文件描述符没有打开 | 否 | 是 |

- nfds：指定被监听事件集合fds的大小，定义如下：

    ```
    typedef unsigned long int nfds_t
    ```

- timeout指定poll的超时返回值

    如果timeout为-1，poll永远阻塞直到某个事件发生

    如果timeout为0，poll将立即返回

## 返回值

返回值与select相同
