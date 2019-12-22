# Linux服务器开发

- Linux网络基础API

  - [主机字节序和网络字节序](big_endian_and_little_endian.md)
  - [sock地址结构体](sockaddr.md)
  - [ip地址转换函数](inet_addr.md)
  - [创建socket](socket.md)
  - [命名socket](bind.md)
  - [监听socket](listen.md)
  - [接受连接](accept.md)
  - [发起连接](connect.md)
  - [关闭连接](close.md)
  - [数据读写](recv_send.md)
  - [带外标记](msg_oob.md)
  - [地址信息函数](getsockname_getpeername.md)
  - [socket选项](getsockopt_setsockopt.md)
  - [网络信息API](netinfo_api.md)

- 高级IO函数

  - [pipe函数](pipe.md)
  - [dup和dup2](dup_dup2.md)
  - [readv和writev](readv_writev.md)
  - [sendfile函数](sendfile.md)
  - [mmap和munmap](mmap.md)
  - [splice函数](splice.md)
  - [tee函数](tee.md)
  - [fcntl函数](fcntl.md)

- Linux服务器程序规范

  - [日志](syslog.md)
  - [用户信息](uid_gid.md)
  - [进程间关系](pgid_sid_ps.md)
  - [系统资源限制](rlimit.md)
  - [改变工作目录和根目录](cwd_root.md)
  - [服务器程序后台化](daemon.md)

- 高性能服务器程序框架

  - [服务器模型](cs_p2p.md)
  - [服务器编程框架](server_dev_frame.md)
  - [I/O模型](io.md)
  - [两种高效的事件处理模式](reactor_proactor.md)
  - [两种高效的并发模式](halfsync_halfasync_leader_follower.md)
  - [有限状态机](finite_state_machine.md)
  - [提高服务器性能的其他建议](pool_datacp_content_switch.md)

- IO复用

  - [selete系统调用](select.md)
  - [poll系统调用](poll.md)
  - [epoll系统调用](epoll.md)
  - [三组IO复用函数对比](select_poll_epoll.md)
  - [IO复用高级应用一：非阻塞connect](nonblock_connect.md)
  - [IO复用高级应用二：聊天室程序](chatting_room.md)
  - [IO复用高级应用三：同时处理TCP和UDP服务](handle_tcp_and_udp.md)
  - [超级服务xinetd](xinetd.md)

- 信号

  - [linux信号概述]()
  - [信号函数]()
  - [信号集]()
  - [统一事件源]()
  - [网络编程相关信号]()

- 定时器

  - [socket选项so_rcvtimeo和so_sndtimeo](so_rcvtimeo_so_sndtimeo.md)
  - [sigalrm信号](sigalrm.md)
  - [IO复用系统调用的超时参数]()
  - [高性能定时器]()
  
- 高性能IO框架Libevent

  - [IO框架库概述]()
  - [libevent源码分析]()

- 多进程编程

  - [fork系统调用](fork.md)
  - [exec系列系统调用](exec.md)
  - [处理僵尸进程]()
  - [管道]()
  - [信号量]()
  - [共享内存]()
  - [消息队列]()
  - [ipc命令]()
  - [在进程间传递文件描述符]()

- 多线程编程

  - [linux线程概述]()
  - [创建线程和结束线程]()
  - [线程属性]()
  - [posix信号量]()
  - [互斥锁]()
  - [条件变量]()
  - [线程同步机制包装类]()
  - [多线程环境]()

- 进程池和线程池

  - [进程池和线程池概述]()
  - [处理多客户]()
  - [半同步/半异步进程池实现]()
  - [用进程池实现的简单cgi服务器]()
  - [半同步/半反应堆线程池实现]()
  - [用线程池实现的简单web服务器]()

- 服务器调制、调试和测试

  - [最大文件描述符数]()
  - [调整内核参数]()
  - [gdb调试]()
  - [压力测试]()

- 系统检测Linux网络基础API

  - [tcpdump]()
  - [lsof]()
  - [nc]()
  - [strace]()
  - [netstat]()
  - [vmstat]()
  - [ifstat]()
  - [mpstat]()
