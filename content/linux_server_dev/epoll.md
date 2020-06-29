# epoll

<!-- TOC -->

- [一、内核事件表：epoll_create 函数](#一内核事件表epoll_create-函数)
- [二、epoll_ctl函数](#二epoll_ctl函数)
    - [1. 参数](#1-参数)
    - [2. 返回值](#2-返回值)
- [三、epoll_wait函数](#三epoll_wait函数)
    - [1. 参数](#1-参数-1)
    - [2. poll 和 epoll 在使用的不同](#2-poll-和-epoll-在使用的不同)
- [四、epoll 的两种工作模式：LT 和 ET 模式](#四epoll-的两种工作模式lt-和-et-模式)
    - [1. LT和ET工作方式差异](#1-lt和et工作方式差异)
    - [2. 测试](#2-测试)
- [五、89EPOLLONESHOT事件](#五89epolloneshot事件)

<!-- /TOC -->

## 一、内核事件表：epoll_create 函数

epoll 为 Linux 独有的 I/O 复用函数，epoll 通过内核事件表记录用户关心的文件描述符的事件，内核外通过一个额外的文件描述符来唯一识别内核中的事件表

```
#include <sys/epoll.h>
int epoll_create( int size )   //创建内核事件表，返回内核事件表的文件描述符
```

- size：现在不起作用，只是给内核一个提示，告诉它事件表需要多大

## 二、epoll_ctl函数

epoll_ctl 函数用来操作 epoll 中的内核事件表

```
int epoll_ctl( int epfd, int op, int fd, struct epoll_event *event );
```

### 1. 参数

- epfd：指向内核事件表的文件描述符
- fd：要操作的文件描述符
- op：操作类型

  - EPOLL_CTL_ADD：往事件表中注册fd上的事件
  - EPOLL_CTL_MOD：修改fd上的注册事件
  - EPOLL_CTL_DEL：删除fd上的注册事件
  
- event：指定事件类型，为 epoll_event 结构，其定义如下：
  
  ```
  struct epoll_event
  {
      __uint32_t events;  
      
      epoll_data_t data   //用户数据
  };
  ```

  - events：

      epoll 事件，支持的事件类型和 poll 基本相同，表示 epoll 事件类型的宏是在 poll 对应的宏前加上 E_

      但是 epoll 有额外的两个事件类型 EPOLLET 和 EPOLLONESHOT，epoll 的高效运作需要这两个宏

  - data：存储用户数据，epoll_data_t 定义如下：

    ```
    typedef union epoll_data
    {
        void* ptr;
        int fd;
        uint32_t u32;
        uint64_t u64;
    }epoll_data_t;
    ```

    epoll_data_t 为联合体，最常使用的为 fd，还可以使用 ptr 指向事件处理器或者用户数据
  
### 2. 返回值

epoll_ctl 成功时返回 0，失败返回 -1 并设置 rrno

## 三、epoll_wait函数

epoll_wait 函数如果检测到事件，就将所有就绪的事件从内核事件表( epfd 指向)中复制到它的第二个参数 events 数组中，这个数据只用于输出 epoll_wait 检测到的就绪事件，而不像 select 和 poll 的数组参数那样既用于传入用户注册的事件，又用于输出内核检测到的就绪事件，极大的提到了应用程序索引就绪文件描述符的效率

```
int epoll_wait( int epfd, struct epoll_event* events, int maxevents, int timeout ); 
```

### 1. 参数

- maxevents：指定最多监听的事件个数，必须大于 0
- timeout：和 poll 的 timeout 参数相同

返回值：成功返回就绪的文件描述个数，失败返回 -1 并设置 errno


### 2. poll 和 epoll 在使用的不同

- 寻找 poll 返回的就绪文件描述符：

  ```
  int ret = poll( fds, MAX_EVENT_NUMBER, -1 );
  //必须遍历所有已注册文件描述符并找到其中的就绪者
  for ( int i = 0; i < MAX_EVENT_NUMBER; ++i )
  {
      if ( fds[i].revents & POLLIN )
      {
          int sockfd = fds[i].fd;
      }
  }
  ```

- 寻找 epoll 返回的就绪文件描述符：

  ```
  int ret = epoll_wait( epollfd, events, MAX_EVENT_NUMBER, -1 );
  //仅遍历就绪的 ret 个文件描述符
  for ( int i = 0; i < ret; i++ )
  {
      int sockfd = event[i].data.fd;
  }
  ```

## 四、epoll 的两种工作模式：LT 和 ET 模式

- LT(Level Trigger，电平触发)模式：默认的工作模式，相当于一个高效的poll。
  
  当 epoll_wait 检测到其上有事件发生并将此事件通知应用程序后，应用程序可以不立即处理事件，这样当应用程序下次调用 epoll_wait 时，epoll_wait 还会再次向应用程序通告此事件，知道该事件被处理

- ET(Edge Trigger，边沿触发)模式：epoll 的更高效工作模式。
  
  当 epoll_wait 检测到其上有事件发生并将此事件通知应用程序后，应用程序必须立即处理该事件，因为后续的 epoll_wait 调用将不再向应用程序通知这一事件，ET 模式很大程度降低了同一个 epoll 事件被重复触发的次数，所以效率比 LT 模式高。
  
  使用 ET 模式的文件描述符都应该是非阻塞的，如果文件描述符是阻塞的，那么读或写操作将会因为没有后续的事件而一直处于阻塞状态

### 1. LT和ET工作方式差异

```
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 10

//将文件描述符设置成非阻塞的
int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

//将文件描述符fd上的EPOLLIN注册到epollfd指示的epoll内核事件表中，参数enable_et指定是否对fd启用ET模式
void addfd(int epollfd, int fd, bool enable_et)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if (enable_et)
    {
        event.events |= EPOLLET;
    }
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

//LT模式的工作流程
void lt(epoll_event* events, int number, int epollfd, int listenfd)
{
    char buf[BUFFER_SIZE];
    for (int i = 0; i < number; i++)
    {
        int sockfd = events[i].data.fd;
        if (sockfd == listenfd)
        {
            struct sockaddr_in client_address;
            socklen_t client_addrlength = sizeof(client_address);
            int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlength);
            addfd(epollfd, connfd, false);  //对connfd禁用ET模式
        }
        else if (events[i].events & EPOLLIN)
        {
            //只要socket读缓存中还有未读出的数据，这段代码就被触发
            printf("event trigger once\n");
            memset(buf, '\0', BUFFER_SIZE);
            int ret = recv(sockfd, buf, BUFFER_SIZE-1, 0);
            if (ret <= 0)
            {
                close(sockfd);
                continue;
            }
            printf("get %d bytes of content: %s\n", ret, buf);
        }
        else 
        {
            printf("something else happened \n");
        }
    }
}

//ET模式的工作流程
void et(epoll_event* events, int number, int epollfd, int listenfd)
{
    char buf[BUFFER_SIZE];
    for (int i = 0; i < number; i++)
    {
        int sockfd = events[i].data.fd;
        if (sockfd == listenfd)
        {
            struct sockaddr_in client_address;
            socklen_t client_addrlength = sizeof(client_address);
            int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlength);
            addfd(epollfd, connfd, true);
        }
        else if (events[i].events & EPOLLIN)
        {
            //这段代码不会被重复触发，所以我们循环读取数据，以确保把socket读缓存中的所有数据读出
            printf("event trigger once\n");
            while (1)
            {
                memset(buf, '\0', BUFFER_SIZE);
                int ret = recv(sockfd, buf, BUFFER_SIZE-1, 0);
                if (ret < 0)
                {
                    //对于非阻塞IO，下面的条件成立表示数据已经全部读取完毕
                    //此后，epoll就能再次触发sockfd上的EPOLLIN事件，以驱动下一次读操作
                    if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
                    {
                        printf("read later\n");
                        break;
                    }
                    close(sockfd);
                    break;
                }
                else if (ret == 0)
                {
                    close(sockfd);
                }
                else
                {
                    printf("get %d bytes of content: %s\n", ret, buf);
                }
            }
        }
        else
        {
            printf("something else happened \n");
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc <= 2)
    {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    assert(epollfd != -1);
    addfd(epollfd, listenfd, true);

    while (1)
    {
        int ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if (ret < 0)
        {
            printf("epoll failure\n");
            break;
        }
        lt(events, ret, epollfd, listenfd); //使用LT模式
        // et(events, ret, epollfd, listenfd);  //使用ET模式
    }
    close(listenfd);
    return 0;
}
```

### 2. 测试

可以使用telnet连接到这个服务器程序上并一次传输超过10字节(BUFFER_SIZE大小)的数据，然后比较LT模式和ET模式的异同


> **Note！** 每个使用ET模式的文件描述符都应该是非阻塞的。如果文件描述符是阻塞的，那么读或写操作将会因为没有后续的事件而一直处于阻塞状态(饥渴状态)

## 五、89EPOLLONESHOT事件

**如果使用ET模式，一个socket上的某个事件还是可能被触发多次**：

在并发程序中，如果一个线程(或进程)在读取完某个socket上的数据后开始处理这些数据，而在数据处理过程中该socket上又有新数据可读(EPOLLIN再次被触发)，此时另一个线程被唤醒来读取这些新数据，于是就出现了两个线程同时操作一个socket的局面。这当然不是我们期望的，我们期望一个socket连接在任一时刻只被一个线程处理，这一点可以使用epoll的EPOLLONESHOT事件实现

注册了EPOLLONESHOT事件的文件描述符，**操作系统最多触发其上注册的一个可读、可写或异常事件，且只触发一次**，除非使用epoll_ctl函数重置该文件描述符注册的EPOLLONESHOT事件，这样当一个线程在处理某个socket时，其他线程是不可能有机会操作该socket的，但是，反过来，注册了EPOLLONESHOT事件的socket一旦被某个线程处理完毕，该线程就应该立即重置这个socket上的EPOLLONESHOT事件，以确保这个socket下次可读时，其EPOLLIN事件能被触发，进而让其他工作线程有机会继续处理这个socket

下面代码展示了EPOLLONESHOT事件的使用：

```
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 1024

struct fds
{
    int epollfd;
    int sockfd;
};

int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

//将fd上的EPOLLIN和EPOLLET事件注册到epollfd指示的epoll内核事件表中
//参数oneshot指定是否注册fd上的EPOLLONESHOT事件
void addfd(int epollfd, int fd, bool oneshot)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    if (oneshot)
    {
        event.events |= EPOLLONESHOT;
    }
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

//重置fd上的事件，这样操作之后，尽管fd上的EPOLLONESHOT事件被注册，
//但是操作系统仍然会触发fd上的EPOLLIN事件，且只触发一次
void reset_oneshot(int epollfd, int fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}

//工作线程
void* worker(void* arg)
{
    int sockfd = ((fds*)arg)->sockfd;
    int epollfd = ((fds*)arg)->epollfd;
    printf("start new thread to receive data on fd: %d\n", sockfd);
    char buf[BUFFER_SIZE];
    memset(buf, '\0', BUFFER_SIZE);
    //循环读取sockfd上的数据，直到遇见EAGAIN错误
    while (1)
    {
        int ret = recv(sockfd, buf, BUFFER_SIZE-1, 0);
        if (ret == 0)
        {
            close(sockfd);
            printf("foreiner closed the connection\n");
            break;
        }
        else if (ret < 0)
        {
            if (errno == EAGAIN)
            {
                reset_oneshot(epollfd, sockfd);
                printf("read later\n");
                break;
            }
        }
        else
        {
            printf("get content: %s\n", buf);
            //休眠5s，模拟数据处理过程
            sleep(5);
        }
    }
    printf("end thread receiving data on fd: %d\n", sockfd);
}

int main(int argc, char* argv[])
{
    if (argc <= 2)
    {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(listenfd, 5);
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    assert(epollfd != -1);
    //注意，监听socket listenfd上是不能注册EPOLLONESHOT事件的，否则应用程序只能处理一个客户连接！
    //因为后续的客户连接请求将不再触发listenfd上的EPOLLIN事件
    addfd(epollfd, listenfd, false);

    while (1)
    {
        int ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if (ret < 0)
        {
            printf("epoll failure\n");
            break;
        }
        for (int i = 0; i < ret; i++)
        {
            int sockfd = events[i].data.fd;
            if (sockfd == listenfd)
            {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof(client_address);
                int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlength);
                //对每个非监听文件描述符都注册EPOLLONESHOT事件
                addfd(epollfd, connfd, true);
            }
            else if (events[i].events & EPOLLIN)
            {
                pthread_t thread;
                fds fds_for_new_worker;
                fds_for_new_worker.epollfd = epollfd;
                fds_for_new_worker.sockfd = sockfd;
                //新启动一个工作线程为sockfd服务
                pthread_create(&thread, NULL, worker, (void*)&fds_for_new_worker);
            }
            else
            {
                printf("something else happened \n");
            }
        }
    }
    close(listenfd);
    return 0;
}
```
