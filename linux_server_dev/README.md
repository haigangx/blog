# Linux服务器开发

- Linux网络基础API

  - [主机字节序和网络字节序](content/big_endian_and_little_endian.md)
  - [sock地址结构体](content/sockaddr.md)
  - [ip地址转换函数](content/inet_addr.md)
  - [创建socket](content/socket.md)
  - [命名socket](content/bind.md)
  - [监听socket](content/listen.md)
  - [接受连接](content/accept.md)
  - [发起连接](content/connect.md)
  - [关闭连接](content/close.md)
  - [数据读写](content/recv_send.md)
  - [带外标记](content/msg_oob.md)
  - [地址信息函数](content/getsockname_getpeername.md)
  - [socket选项](content/getsockopt_setsockopt.md)
  - [网络信息API](content/netinfo_api.md)

- 高级IO函数

  - [pipe函数](content/pipe.md)
  - [dup和dup2](content/dup_dup2.md)
  - [readv和writev](content/readv_writev.md)
  - [sendfile函数](content/sendfile.md)
  - [mmap和munmap](content/mmap.md)
  - [splice函数](content/splice.md)
  - [tee函数](content/tee.md)
  - [fcntl函数](content/fcntl.md)

- Linux服务器程序规范

  - [日志](content/syslog.md)
  - [用户信息](content/uid_gid.md)
  - [进程间关系](content/pgid_sid_ps.md)
  - [系统资源限制](content/rlimit.md)
  - [改变工作目录和根目录](content/cwd_root.md)
  - [服务器程序后台化](content/daemon.md)

- 高性能服务器程序框架

  - [服务器模型](content/cs_p2p.md)
  - [服务器编程框架](content/server_dev_frame.md)
  - [I/O模型](content/io.md)
  - [两种高效的事件处理模式](content/reactor_proactor.md)
  - [两种高效的并发模式](content/halfsync_halfasync_leader_follower.md)
  - [有限状态机](content/finite_state_machine.md)
  - [提高服务器性能的其他建议](content/pool_datacp_content_switch.md)

- IO复用

  - [selete系统调用](content/select.md)
  - [poll系统调用](content/poll.md)
  - [epoll系统调用](content/epoll.md)
  - [三组IO复用函数对比](content/select_poll_epoll.md)
  - [IO复用高级应用一：非阻塞connect](content/nonblock_connect.md)
  - [IO复用高级应用二：聊天室程序](content/chatting_room.md)
  - [IO复用高级应用三：同时处理TCP和UDP服务](content/handle_tcp_and_udp.md)
  - [超级服务xinetd](content/xinetd.md)

- 信号

  - [linux信号概述]()
  - [信号函数]()
  - [信号集]()
  - [统一事件源]()
  - [网络编程相关信号]()

- 定时器

  - [socket选项so_rcvtimeo和so_sndtimeo](so_rcvtimeo_so_sndtimeo.md)
  - [sigalrm信号](content/sigalrm.md)
  - [IO复用系统调用的超时参数]()
  - [高性能定时器]()
  
- 高性能IO框架Libevent

  - [IO框架库概述]()
  - [libevent源码分析]()

- 多进程编程

  - [fork系统调用](content/fork.md)
  - [exec系列系统调用](content/exec.md)
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
