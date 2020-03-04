# strace

strace只能统计发生的内核态的程序异常，如果故障发生在用户态，则要使用[ltrace](command/ltrace.md)

## strace是什么？

strace是一个可用于诊断、调试的Linux用户空间跟踪器，可以用它来监控用户空间进程和内核的交互，比如系统调用、信号传递、进程状态变更等

> strace的底层使用内核的ptrace特性来实现其功能

我们都知道，在Linux中，进程并不能直接访问硬件设备，所以进程在读取磁盘文件、接收网络数据等操作时，需要将用户态模式切换到内核态，然后调用系统调用来进行这行操作。而strace则可以通过监控一个进程产生的系统调用，包括其参数，返回值，执行消耗的时间、调用次数、成功和失败的次数等来了解一个进程

**一个简单的例子来说明：**

假如有个叫some_serve的软件包，启动时报错，查看日志和输出时只能看出来似乎是初始化日志失败，但具体什么原因导致的呢？

启动命令：

```
./some_server ./conf/some_server.conf
```

输出：

```
FATAL: InitLogFile failed
```

这时候我们可以使用strace看看：
```
strace -tt -f ./some_server ./conf/some_server.conf
```
查看输出的时候，我们可以看到在输出错误前有个open系统调用调用失败:

```
open("/usr/local/apps/some_server/log//server_agent.log", O_RDWR|O_CREAT|O_APPEND|O_LARGEFILE, 0666) = -1 ENOENT (No such file or directory)
```
open返回错误码-1，系统错误号为ENOENT，我们通过查看open系统调用的man手册，找到ENOENT对应的错误发生原因即可解决该问题


## strace怎么用？

### strace两种运行模式

- 一种是通过它启动要跟踪的进程，这时在原本的命令前加上strace即可。比如我们要跟踪 "ls -lh /var/log/messages" 这个命令的执行，可以这样：

  ```
  strace ls -lh /var/log/messages
  ```

- 另外一种是跟踪已经在运行的进程，在不中断进程执行的情况下，理解它在干嘛。 这时给strace传递个-p pid 选项即可。

  ```
  //先得到程序的进程id
  pidof some_server
  //然后跟踪该进程
  strace -p <pid>
  ```
### strace常用选项

- -tt 每行输出前，显示毫秒级别的时间
- -T 显示每次系统调用花费的时间
- -v 对某些系统调用，打印完整的环境变量、文件stat结构
- -f 追踪目标进程及其所有子进程
- -e 控制要跟踪的事件和跟踪行为，比如指定要跟踪的系统调用名称
- -o 把strace的输出单独写到指定文件
- -s 当系统调用的某个参数是字符串时，最多输出指定长度的内容，默认32字节
- -p 指定要跟踪的进程pid，要跟踪多个pid，重复多次-p选项即可

例如：跟踪nginx，看启动时都访问了哪些文件：
```
strace -tt -T -f -e trace=file -o /data/log/strace.log -s 1024 ./nginx
```
其中`-e trace=file`指定只显示和文件访问相关的系统调用，像这样可用的选项都有：

- -e trace=file 跟踪和文件访问相关的调用(参数中有文件名)
- -e trace=process 和进程管理相关的调用，如fork/exec/exit_group
- -e trace=network 和网络通信相关的调用，如socket/sendto/connect
- -e trace=signal 信号发送和处理相关调用，如kill/sigaction
- -e trace=desc 和文件描述符相关调用，如write/read/select/epoll
- -e trace=ipc 和进程间通信相关调用，如shmget

绝大多数情况下，我们使用上面的组合名字就够了，如果实在需要跟踪具体的系统调用时，要注意c库和底层系统调用的区别：

> 比如，我们知道创建进程使用的fork函数，但在glibc中，fork调用实际上映射到了更底层的clone系统调用。所以使用strace时，得指定-e trace=clone，而不是-e trace=fork

## strace问题定位案例

### 定位进程异常退出

问题：

> 机器上有个叫做run.sh的常驻脚本，运行一分钟后会死掉，需要查出死因

定位：

进程还在运行时，通过ps命令获取其pid，假设得到其pid为24298
```
strace -o strace.log -tt -p 24298
```
查看strace.log，我们在最后2行看到如下内容：
```
22:47:42.803937 wait4(-1,  <unfinished ...>
22:47:43.228422 +++ killed by SIGKILL +++
```
可以看到，进程是被其他进程用KILL信号杀死的。通过分析发现，是机器上的一个监控脚本在监控一个叫做run.sh的进程，当发现run.sh的进程数大于2时，就会把它杀死重启，结果导致该run.sh脚本被误杀

进程被杀退出时，strace会输出kill by SIGX(SIGX表示发送给进程的信号)，那么，进程自己退出时会输出什么呢？

以下面的程序test_exit为例，使用strace分析其退出时的情况：
```
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
       exit(1);
}
```

使用strace跟踪该程序：
```
strace -tt -e trace=process -f ./test_exit
```

输出：
```
23:07:24.672849 execve("./test_exit", ["./test_exit"], [/* 35 vars */]) = 0
23:07:24.674665 arch_prctl(ARCH_SET_FS, 0x7f1c0eca7740) = 0
23:07:24.675108 exit_group(1)           = ?
23:07:24.675259 +++ exited with 1 +++
```

可以看出，进程自己退出时(调用exit函数，或从main函数返回)，最终调用的exit_group系统调用，并且strace会输出exited with x(x为退出码)

> exit_group是exit函数底层真正调用的系统调用

### 定位共享内存异常

有个服务启动报错：
```
shmget 267264 30097568: Invalid argument
Can not get shm...exit!
```

错误日志大概告诉我们获取共享内存时出错，通过strace查看：
```
strace -tt -f -e trace=ipc ./a_mon_svr ../conf/a_mon_svr.conf
```

输出：
```
22:46:36.351798 shmget(0x5feb, 12000, 0666) = 0
22:46:36.351939 shmat(0, 0, 0)          = ?
Process 21406 attached
22:46:36.355439 shmget(0x41400, 30097568, 0666) = -1 EINVAL (Invalid argument)
shmget 267264 30097568: Invalid argument
Can not get shm...exit!
```

通过strace的输出，我们知道是shmget系统调用出错了，errno是EINVAL，然后我们就可以通过查看shmget的man手册去查询错误原因了

### 性能分析

加入有两个shell脚本完成同样的功能，我们需要对比两个脚本的系统调用情况和所花的时间情况

可以使用strace的`-c`和`-f`选项分别统计时间和同时统计每个进程的子进程情况

[参考文章](https://www.linuxidc.com/Linux/2018-01/150654.htm)
