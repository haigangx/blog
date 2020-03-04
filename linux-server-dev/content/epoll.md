# epoll

## 1、内核事件表：epoll_create函数

epoll为Linux独有的I/O复用函数，epoll通过内核事件表记录用户关心的文件描述符的事件，内核外通过一个额外的文件描述符来唯一识别内核中的事件表

```
#include <sys/epoll.h>
int epoll_create( int size )   //创建内核事件表，返回内核事件表的文件描述符
```

- size：现在不起作用，只是给内核一个提示，告诉它事件表需要多大

## 2、epoll_ctl函数

```
int epoll_ctl( int epfd, int op, int fd, struct epoll_event *event )    //操作epoll中的内核事件表
```

- epfd：指向内核事件表的文件描述符
- fd：要操作的文件描述符
- op：操作类型

  - EPOLL_CTL_ADD：往事件表中注册fd上的事件
  - EPOLL_CTL_MOD：修改fd上的注册事件
  - EPOLL_CTL_DEL：删除fd上的注册事件
  
- event：指定事件类型，为epoll_event结构，其定义如下：
  
  ```
  struct epoll_event
  {
      //epoll事件，支持的事件类型和poll基本相同，表示epoll事件类型的宏是在poll对应的宏前加上E
      //但是epoll有额外的两个事件类型EPOLLET和EPOLLONESHOT，epoll的高效运作需要这两个宏
      __uint32_t events;  
      
      epoll_data_t data   //用户数据
  };
  data：存储用户数据，epoll_data_t定义如下：
  typedef union epoll_data
  {
      void* ptr;
      int fd;
      uint32_t u32;
      uint64_t u64;
  }epoll_data_t;
  epoll_data_t为联合体，最常使用的为fd，还可以使用ptr指向事件处理器或者用户数据
  ```
  
返回值:

epoll_ctl成功时返回0，失败返回-1并设置errno

## 3、epoll_wait函数

epoll_wait函数如果检测到事件，就将所有就绪的事件从内核事件表(epfd指向)中复制到它的第二个参数events数组中，这个数据只用于输出epoll_wait检测到的就绪事件，而不像select和poll的数组参数那样既用于传入用户注册的事件，又用于输出内核检测到的就绪事件，极大的提到了应用程序索引就绪文件描述符的效率

```
int epoll_wait( int epfd, struct epoll_event* events, int maxevents, 
                int timeout );                        //一段超时事件内等待一组文件描述符上的事件 
```

- maxevents：指定最多监听的事件个数，必须大于0
- timeout：和poll的timeout参数相同

返回值：成功返回就绪的文件描述个数，失败返回-1并设置errno


**poll和epoll在使用的不同：**

- 索引poll返回的就绪文件描述符：

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

- 索引epoll返回的就绪文件描述符：

  ```
  int ret = epoll_wait( epollfd, events, MAX_EVENT_NUMBER, -1 );
  //仅遍历秀徐的ret个文件描述符
  for ( int i = 0; i < ret; i++ )
  {
      int sockfd = event[i].data.fd;
  }
  ```

## 4、epoll的两种工作模式：LT和ET模式

- LT(Level Trigger，电平触发)模式：

  默认的工作模式，相当于一个高效的poll。
  
  当epoll_wait检测到其上有事件发生并将此事件通知应用程序后，应用程序可以不立即处理事件，这样当应用程序下次调用epoll_wait时，epoll_wait还会再次向应用程序通告此事件，知道该事件被处理

- ET(Edge Trigger，边沿触发)模式：

  epoll的更高效工作模式。
  
  当epoll_wait检测到其上有事件发生并将此事件通知应用程序后，应用程序必须立即处理该事件，因为后续的epoll_wait调用将不再向应用程序通知这一事件，ET模式很大程度降低了同一个epoll事件被重复触发的次数，所以效率比LT模式高。
  
  使用ET模式的文件描述符都应该是非阻塞的，如果文件描述符是阻塞的，那么读或写操作将会因为没有后续的事件而一直处于阻塞状态

## 5、EPOLLONESHOT事件

**如果使用ET模式，一个socket上的某个事件还是可能被触发多次**：

在并发程序中，如果一个线程(或进程)在读取完某个socket上的数据后开始处理这些数据，而在数据处理过程中该socket上又有新数据可读(EPOLLIN再次被触发)，此时另一个线程被唤醒来读取这些新数据，于是就出现了两个线程同时操作一个socket的局面。这当然不是我们期望的，我们期望一个socket连接在任一时刻只被一个线程处理，这一点可以使用epoll的EPOLLONESHOT事件实现

注册了EPOLLONESHOT事件的文件描述符，**操作系统最多触发其上注册的一个可读、可写或异常事件，且只触发一次**，除非使用epoll_ctl函数重置该文件描述符注册的EPOLLONESHOT事件，这样当一个线程在处理某个socket时，其他线程是不可能有机会操作该socket的，但是，反过来，注册了EPOLLONESHOT事件的socket一旦被某个线程处理完毕，该线程就应该立即重置这个socket上的EPOLLONESHOT事件，以确保这个socket下次可读时，其EPOLLIN事件能被触发，进而让其他工作线程有机会继续处理这个socket
