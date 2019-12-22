# 带外标记

内核通知应用程序带外数据到达的两种常见方式：I/O复用产生的异常事件和SIGURG信号

sockatmark判断sockfd是否处于带外标记，即下一个被读取到的数据是否是带外数据，如果是，sockatmakr返回1，此时可以通过带MSG_OOB标志的recv调用来接收带外数据。如果不是，则sockatmark返回0

```
#include <sys/socket.h>
int sockatmark(int sockfd);
```
