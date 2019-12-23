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
  - [三组IO复用函数对比(缺)](select_poll_epoll.md)
  - [IO复用高级应用一：非阻塞connect(缺)](nonblock_connect.md)
  - [IO复用高级应用二：聊天室程序(缺)](chatting_room.md)
  - [IO复用高级应用三：同时处理TCP和UDP服务(缺)](handle_tcp_and_udp.md)
  - [超级服务xinetd(缺)](xinetd.md)

- 信号

  - [linux信号概述](signal_base.md)
  - [信号函数](signal_functions.md)
  - [信号集](sigset.md)
  - [统一事件源](one_event.md)
  - [网络编程相关信号](signal_server_dev.md)

- 定时器

  - [socket选项so_rcvtimeo和so_sndtimeo](so_rcvtimeo_so_sndtimeo.md)
  - [sigalrm信号](sigalrm.md)
  - [IO复用系统调用的超时参数](timeout_arg.md)
  - [高性能定时器](timer.md)

- 高性能IO框架Libevent

  - [IO框架库概述]()
  - [libevent源码分析]()

- 多进程编程

  - [fork系统调用](fork.md)
  - [exec系列系统调用](exec.md)
  - [处理僵尸进程](zombie_process.md)
  - [管道](more_process_pipe.md)
  - [信号量](sem.md)
  - [共享内存](shm.md)
  - [消息队列](msg.md)
  - [ipc命令](ipc_command.md)
  - [在进程间传递文件描述符](send_fd.md)

- 多线程编程

  - [linux线程概述](linux_thread.md)
  - [创建线程和结束线程](pthread_op.md)
  - [线程属性](pthread_attr.md)
  - [posix信号量](pthread_posix_sem.md)
  - [互斥锁](pthread_mutex.md)
  - [条件变量](pthread_cond.md) 
  - [线程同步机制包装类](locker.md)
  - [多线程环境](linux_thread_env.md)

- 进程池和线程池

  - [进程池和线程池概述](process_pool_thread_pool.md)
  - [半同步/半异步进程池实现](implement_process_pool.md)
  - [用进程池实现的简单cgi服务器](cgi_server_use_process_pool.md)
  - [半同步/半反应堆线程池实现](implement_thread_pool.md)
  - [用线程池实现的简单web服务器](web_server_use_thread_pool.md)

- 服务器调制、调试和测试

  - [最大文件描述符数](max_file_number.md)
  - [调整内核参数](adjust_kernel_arg.md)
  - [压力测试](pressure_test.md)
