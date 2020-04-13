# socket选项的SO_RCVTIMEO和SO_SNDTIMEO

socket选项SO_RCVTIMEO和SO_SNDTIMEO分别用来设置socket接收数据超时时间和发送数据超时时间

这两个选项仅对数据接收和发送相关的socket专用系统调用有效，如send, sendmsg, recv, recvmsg, accpet和connect等API

这两个选项对上述系统调用的影响总结如下表：

| 系统调用 | 有效选项 | 系统调用超时后的行为 |
| --- | --- | --- |
| send | SO_SNDTIMEO | 返回-1，设置errno为EAGAIN或EWOULDBLOCK |
| sendmsg | SO_SNDTIMEO | 返回-1，设置errno为EAGAIN或EWOULDBLOCK |
| recv | SO_RCVTIMEO | 返回-1，设置errno为EAGAIN或EWOULDBLOCK |
| recvmsg | SO_RCVTIMEO | 返回-1，设置errno为EAGAIN或EWOULDBLOCK |
| accept | SO_RCVTIMEO | 返回-1，设置errno为EAGAIN或EWOULDBLOCK |
| connect | SO_SNDTIMEO | 返回-1，设置errno为EINPROGRESS |

我们可以通过系统调用的返回值及errno来判断超时时间是否已到，进而决定是否开始处理定时任务

```
int sockfd = socket(PF_INET, SOCK_STREAM, 0);
struct timeval timeout;
timeout.tv_sec = time;
timeout.tv_usec = 0;
socklen_t len = sizeof(timeout);
ret = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, len);
assert(ret != -1);
ret = connect(sockfd, (struct sockaddr *)&address, sizeof(address));
```

