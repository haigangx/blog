# Linux服务器开发

## 基础知识

<details>
<summary>cheatsheet</summary>
</details>

### Linux网络基础API

<details>
<summary>主机字节序和网络字节序——htonl、htons、ntohl、ntohs</summary>

</details>

<details>
<summary>sock地址结构体——sockaddr、sockaddr_un、sockaddr_in、sockaddr_in6</summary>
</details>

<details>
<summary>ip地址转换函数——inet_addr、inet_aton、inet_ntoa、inet_pton、inet_ntop</summary>

</details>

<details>
<summary>创建socket——socket</summary>
</details>

<details>
<summary>命名socket——bind</summary>
</details>

<details>
<summary>监听socket——listen</summary>
</details>

<details>
<summary>接受连接——accept</summary>
</details>

<details>
<summary>发起连接——connect</summary>
</details>

<details>
<summary>关闭连接——close、shutdown</summary>
</details>

<details>
<summary>数据读写——recv、send、recvfrom、sendto、recvmsg、sendmsg</summary>
</details>

<details>
<summary>带外标记——sockatmark</summary>
</details>

<details>
<summary>地址信息函数——getsockname、getpeername</summary>
</details>

<details>
<summary>socket选项——getsockopt、setsockopt</summary>
</details>

<details>
<summary>网络信息API——gethostbyname、gethostbyaddr、getservbyname、getservbyport、getaddrinfo、getnameinfo</summary>
</details>

### 高级IO函数

<details>
<summary>pipe函数——pipe、socketpair</summary>
</details>

<details>
<summary>dup和dup2——dup、dup2</summary>
</details>

<details>
<summary>readv和writev——readv、writev</summary>
</details>

<details>
<summary>sendfile函数——sendfile</summary>
</details>

<details>
<summary>mmap和munmap——mmap、munmap</summary>
</details>

<details>
<summary>splice函数——splice</summary>
</details>

<details>
<summary>tee函数——tee</summary>
</details>

<details>
<summary>fcntl函数——fcntl</summary>
</details>

### Linux服务器程序规范

<details>
<summary>日志——syslog、openlog、setlogmask、closelog</summary>
</details>

<details>
<summary>用户信息——getuid、geteuid、getgid、getegid、setuid、seteuid、setgid、setegid</summary>
</details>

<details>
<summary>进程间关系——getpgid、setpgid、setsid、getsid</summary>
</details>

<details>
<summary>系统资源限制——getrlimit、setrlimit</summary>
</details>

<details>
<summary>改变工作目录和根目录——getcwd、chdir、chroot</summary>
</details>

<details>
<summary>服务器程序后台化——daemon</summary>
</details>

### 高性能服务器程序框架

<details>
<summary>服务器模型——CS模型、P2P模型</summary>
</details>

<details>
<summary>服务器编程框架——IO处理单元、逻辑单元、网络存储单元、请求队列</summary>
</details>

<details>
<summary>I/O模型——同步IO、异步IO、阻塞IO、非阻塞IO</summary>
</details>

<details>
<summary>两种高效的事件处理模式——Reactor模式和Proactor模式</summary>


</details>

<details>
<summary>两种高效的并发模式——半同步半异步模式、领导者追随者模式</summary>
</details>

<details>
<summary>有限状态机</summary>
</details>

<details>
<summary>提高服务器性能的其他建议——池、数据复制、上下文切换和锁</summary>
</details>

### IO复用

<details>
<summary>selete系统调用——select</summary>
</details>

<details>
<summary>poll系统调用——poll</summary>
</details>

<details>
<summary>epoll系统调用——epoll_create、epoll_ctl、epoll_wait</summary>
</details>

<details>
<summary>三组IO复用函数对比——select、poll、epoll对比</summary>
</details>

<details>
<summary>IO复用高级应用一：非阻塞connect</summary>
<details>
<summary>IO复用高级应用二：聊天室程序</summary>
</details>

<details>
<summary>IO复用高级应用三：同时处理TCP和UDP服务</summary>
</details>

<details>
<summary>超级服务xinetd(缺)</summary>
TODO：超级服务xinetd

</details>

### 信号

<details>
<summary>linux信号概述——kill、信号处理方式、信号集</summary>
</details>

<details>
<summary>信号函数</summary>
</details>

<details>
<summary>信号集——信号集操作函数、sigprocmask、sigpending</summary>
</details>

<details>
<summary>统一事件源</summary>
</details>

<details>
<summary>网络编程相关信号——SIGHUP、SIGPIPE、SIGURG</summary>
</details>

### 定时器

<details>
<summary>socket选项——so_rcvtimeo、so_sndtimeo</summary>
</details>

<details>
<summary>sigalrm信号</summary>
</details>

<details>
<summary>IO复用系统调用的超时参数</summary>
</details>

<details>
<summary>高性能定时器——时间轮、时间堆</summary>
</details>

### 高性能IO框架Libevent

<details>
<summary>IO框架库概述</summary>

</details>

<details>
<summary>libevent源码分析</summary>
</details>

### 多进程编程

<details>
<summary>fork系统调用——fork</summary>

</details>

<details>
<summary>exec系列系统调用——execl、execlp、execle、execv、execvp、execve</summary>
</details>

<details>
<summary>处理僵尸进程——wait、waitpid</summary>
</details>

<details>
<summary>管道——pipe、socketpair、FIFO命令管道</summary>
</details>

<details>
<summary>信号量——semget、setop、semctl</summary>
</details>

<details>
<summary>共享内存—shmget、shmat、shmdt、shmct、shmopen、shm_unlink</summary>
</details>

<details>
<summary>消息队列—msgget、msgsnd、msgrcv、msgctl</summary>
</details>

<details>
<summary>ipc命令—查看当前系统的共享资源实例</summary>
</details>

<details>
<summary>在进程间传递文件描述符</summary>
</details>

### 多线程编程

<details>
<summary>linux线程概述</summary>
</details>

<details>
<summary>创建线程和结束线程—pthread_create、pthread_exit、pthread_join、pthread_cancel</summary>
</details>

<details>
<summary>线程属性</summary>
</details>

<details>
<summary>posix信号量—sem_init、sem_destroy、sem_wait、sem_trywait、sem_post</summary>
</details>

<details>
<summary>互斥锁—基本API、互斥锁属性、死锁</summary>
</details>

<details>
<summary>条件变量—pthread_cond_init、pthread_cond_destroy、pthread_cond_broadcast、pthread_cond_signal、pthread_cond_wait</summary>
</details>

<details>
<summary>线程同步机制包装类</summary>
</details>

<details>
<summary>多线程环境</summary>
</details>

### 进程池和线程池

<details>
<summary>进程池和线程池概述</summary>
</details>

<details>
<summary>半同步/半异步进程池实现</summary>

</details>

<details>
<summary>用进程池实现的简单cgi服务器</summary>

</details>

<details>
<summary>半同步/半反应堆线程池实现</summary>

</details>

<details>
<summary>用线程池实现的简单web服务器</summary>

</details>

### 服务器调制、调试和测试

<details>
<summary>最大文件描述符数</summary>

</details>

<details>
<summary>调整内核参数</summary>

</details>

<details>
<summary>压力测试</summary>

</details>

## 开源项目剖析

<details>
<summary>handy</summary>
</details>

<details>
<summary>Tinyhttpd</summary>
</details>
