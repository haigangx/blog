# IO复用系统调用的超时参数

Linux下的3组IO复用系统调用都带有超时参数，因此它们不仅能统一处理信号和IO事件，也能统一处理定时事件。但是由于IO复用系统调用可能在超时时间到期之前就返回(有IO事件发生)，所以如果要利用它们来定时，就需要不断更新定时参数以反映剩余的事件

例：利用IO复用系统调用定时

```
#define TIMEOUT 5000

int timeout = TIMEOUT
time_t start = time(NULL);
time_t end = time(NULL);
while (1)
{
    printf("the timeout is now %d mil-seconds\n", timeout);
    start = time(NULL);
    int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, timeout);
    if ( (number < 0) && (errno != EINTR) )
    {
        printf("epoll failure\n");
        break;
    }
    //如果epoll_wait成功返回0，说明超时时间到，此时便可处理定时任务，并重置定时时间
    if (number == 0)
    {
        timeout = TIMEOUT;
        continue;
    }
    //如果number大于0，说明epoll_wait此次返回是因为有IO事件到达，则本次epoll_wait调用持续的时间是(end-start)*1000ms
    //将定时时间timeout减去已经等待的时间，以此来获得下次epoll_wait调用的超时参数
    end = time(NULL);
    timeout -= (end - start) * 1000;
    //重新计算之后的timeout有可能等于0，说明本次epoll_wait调用返回时，不仅有文件描述符就绪，而且其超时时间也刚好到达，此时我们要处理定时任务并重置定时时间
    if (timeout <= 0)
        timeout = TIMEOUT;
       
    //....
}
```
