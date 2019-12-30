# 网络编程相关信号

## SIGHUP

当挂起进程的控制终端时，SIGHUP信号将被触发。对于没有控制终端的网络后台程序而言，通常利用SIGHUP信号来强制服务器重新读取配置文件
以xinetd超级服务程序为例：
xinetd程序接收到SIGHUP信号之后将调用hard_reconfig函数，它循环读取/etc/xinetd.d/目录下的每个子配置文件，并检测其变化。如果某个正在运行的子服务的配置文件被修改以停止服务，则xinetd主进程将给该子服务进程发送SIGTERM信号以结束它。如果某个子服务的配置文件被修改以开启服务，则xinetd将创建新socket并将其绑定到该服务对应的端口上。

## SIGPIPE

默认情况下，往一个读端关闭的管道或者socket连接中写数据将引发SIGPIPE信号，我们需要在代码中捕获并处理该信号，或者至少忽略它，因为程序接收到SIGPIPE信号的默认行为是结束进程，而我们很少希望因为错误的写操作而导致进程退出。
引起SIGPIPE信号的写操作将设置errno为EPIPE
我们可以通过设置send函数的MSG_NOSIGNAL标志来禁止写操作触发SIGPIPE信号，这时应该使用send函数设置的errno来判断管道或socket连接的读端是否关闭
还可以利用IO复用系统调用来检测管道和socket连接的读端是否已经关闭。以poll为例，当管道的读端关闭时，写端文件描述符上的POLLHUP事件将被触发；当socket连接被对方关闭时，socket上的POLLRDHUP事件将被触发

## SIGURG

Linux下，内核通知应用程序带外数据到达的两种方法：
1、select等IO复用系统调用在接收到带外数据时返回socket上的异常事件
2、使用SIGURG信号
//为信号设置处理函数
void addsig(int sig, void (*sig_handler)(int))
{
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = sig_handler;
    sa.sa_flags |= SA_RESTART;
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}
//SIGURG信号处理函数
void sig_urg(int sig)
{
    int save_errno = errno;
    char buffer[BUF_SIZE];
    memset(buffer, '\0', BUF_SIZE);
    int ret = recv(connfd, buffer, BUF_SIZE-1, MSG_OOB);    //接收带外数据
    printf("got %d bytes of oob data '%s'\n", ret, buffer);
    errno = save_errno;
}
//为SIGURG信号设置处理函数
addsig(SIGURG, sig_urg);
