# 调整内核参数

几乎所有的内核模块，包括内核核心模块和驱动程序，都在/proc/sys文件系统下提供了某些配置文件以供用户调整模块的属性和行为。通常一个配置文件对应一个内核参数，文件名就是参数的名字，文件的内容使参数的值，可以通过sysctl -a查看所有这些内核参数

/proc/sys/fs目录下的部分文件：
/proc/sys/fs目录下的内核参数都与文件系统相关，对于服务器程序来说，最重要的是如下两个参数：
/proc/sys/fs/file-max：系统级文件描述符限制。直接修改这个参数可以临时修改系统级文件描述符限制，一般修改完/proc/sys/fs/file-max后，应用程序需要把/proc/sys/fs/inode-max设置为新/proc/sys/fs/file-max的3~4倍，否则可能导致i节点不够用
/proc/sys/fs/epoll/max_user_watches：用户能够往epoll内核事件表中注册的时间的总量。它是指该用户打开的所有epoll实例总共能监听的事件数目，而不是单个epoll实例能监听的事件数目。往epoll内核事件表中注册一个事件，在32位系统上大概消耗90字节内核空间，在64位系统上则消耗160字节的内核空间，所以这个内核参数限制了epoll使用的内核内存总量

/proc/sys/net目录下的部分文件：
内核中网络模块的相关参数都位于/proc/sys/net目录下，与服务器性能相关的参数有：
/proc/sys/net/core/somaxconn：指定listen监听队列里，能够建立完整连接从而进入ESTABLISHED状态的socket的最大数目
/proc/sys/net/ipv4/tcp_max_syn_backlog：指定listen监听队列里，能够转移至ESTABLISHED或者SYN_RCVD状态的socket的最大数目
/proc/sys/net/ipv4/tcp_wmen：包含3个值，分别指定socket的TCP写缓冲区的最小值、默认值和最大值
/proc/sys/net/ipv4/tcp_rmen：包含3个值，分别指定socket的TCP读缓冲区的最小值、默认值和最大值，通过这个参数来改变接收通告窗口大小
/proc/sys/net/ipv4/tcp_syncookies：指定是否打开TCP同步标签。同步标签通过启动cookie来防止一个监听socket因不停地重复接收来自同一个地址的连接请求(同步报文段)，而导致listen监听队列溢出(SYN风暴)

除了直接修改文件来修改这些系统参数，还可以使用sysctl命令来修改它们，这两种修改方式都是临时的
永久的修改方法是在/etc/sysctl.conf文件中加入相应网络参数及数值，并执行sysctl -p使之生效
