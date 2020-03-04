# 消息队列

消息队列是两个进程之间传递二进制块数据的一种简单有效的方式。每个数据块都有一个特定的类型，接收方可以根据类型来有选择的接收数据，而不一定像管道和命名管道那样必须以先进先出的方式接收数据
Linux消息队列的API都定义在sys/msg.h头文件中，包括4个系统调用：msgget、msgsnd、msgrcv、msgctl

## msgget系统调用

msgget创建一个消息队列，或者获取一个已有的消息队列
#include <sys/msg.h>
int msgget( key_t key, int msgflg );
key：是一个键值，用来标识一个全局唯一的消息队列，和semget一样
msgflg：使用和含义与semget函数的sem_flags参数相同

msgget成功时返回一个正整数值，它是消息队列的标识符。msgget失败时返回-1并设置errno

如果msgget用于创建消息队列，则与之关联的内核数据结构msqid_ds将被创建并初始化，msqid_ds结构体定义如下：
struct msqid_ds
{
    struct ipc_perm msg_perm;       //消息队列的操作权限
    time_t msg_stime;               //最后一次调用msgsnd的时间
    time_t msg_rtime;               //最后一次调用msgrcv的时间
    time_t msg_ctime;               //最后一次被修改的时间
    unsigned long __msg_cbytes;     //消息队列中已有的字节数
    msgqnum_t msg_qnum;             //消息队列中已有的消息数
    msglen_t msg_qbytes;            //消息队列允许的最大字节数
    pid_t msg_lspid;                //最后执行msgsnd的进程的PID
    pid_t msg_lrpid;                //最后执行msgrcv的进程的PID
};

## msgsnd系统调用

msgsnd把一条消息添加到消息队列中，定义如下：
#include <sys/msg.h>
int msgsnd( int msqid, const void* msg_ptr, size_t msg_sz, int msgflg );
msqid：由msgget调用返回的消息队列标识符
msg_ptr：指向一个准备发送的消息，消息必须被定义为如下类型：
struct msgbuf
{
    long mtype;         //消息类型
    char mtext[512];    //消息数据
};
mtype：指定消息类型，必须为一个正整数
mtext：消息数据
msg_sz：消息的数据部分长度，长度可以为0，表示没有消息数据
msgflg：控制msgsnd的行为，通常仅支持IPC_NOWAIT标志，表示以非阻塞方式发送消息。默认情况下，发送消息时如果消息队列满了则msgsnd将阻塞，若IPC_NOWAIT标志被指定，则msgsnd将立即返回并设置errno为EAGAIN
处于阻塞状态的msgsnd调用可能被如下两种异常情况所中断：
* 消息队列被移除：此时msgsnd调用将立即返回并设置errno为EIDRM
* 程序接收到信号：此时msgsnd将立即返回并设置errno为EINTR

msgsnd成功时返回0，失败返回-1并设置errno
msgsnd成功时将修改内核数据结构msqid_ds的部分字段，修改如下：
* 将msg_qnum加1
* 将msg_lspid设置为调用进程的PID
* 将msg_stime设置为当前时间


## msgrcv系统调用

msgrcv从消息队列中获取消息，定义如下：
#include <sys/msg.h>
int msgrcv( int msqid, void* msg_ptr, size_t msg_sz, long int msgtype, int msgflg );
msqid：由msgget调用返回的消息队列标识符
msg_ptr：用于存储接收的消息
msg_sz：消息数据部分的长度
msgtype：指定接收何种类型的消息，取值有以下几种情况：
* msgtype等于0：读取消息队列中的第一个消息
* msgtype大于0：读取消息队列中的第一个类型为msgtype的消息(除非指定标志MSG_EXCEPT)
* msgtype小于0：读取消息队列中第一个类型值比msgtype的绝对值小的消息
msgflg：控制msgrcv函数的一些行为，可以是以下标志的按位或：
* IPC_NOWAIT：如果消息队列中没有消息，则msgrcv调用立即返回并设置errno为ENOMSG
* MSG_EXCEPT：如果msgtype大于0，则接收消息队列中第一个非msgtype类型的消息
* MSG_NOERROR：如果消息数据部分的长度超过了msg_sz，就将它截断

处于阻塞状态的msgrcv调用可能会被如下两种异常情况中断：
* 消息队列被移除：此时msgrcv调用将立即返回并设置errno为EIDRM
* 程序接收到信号：此时msgrcv调用将立即返回并设置errno为EINTR

msgrcv成功时返回0，失败则返回-1并设置errno
msgrcv成功时将修改内核数据结构msqid_ds的部分字段，如下：
* 将msg_qnum减1
* 将msg_lrpid设置为调用进程的PID
* 将msg_rtime设置为当前的时间


## msgctl系统调用

msgctl：控制消息队列的某些属性，定义如下：
#include <sys/msg.h>
int msgctl( int msqid, int command, struct msqid_ds* buf );
msqid：由msgget调用返回的消息队列标识符
command：指定要执行的命令，msgctl支持的所有命令如下表：
命令	含义	msgctl成功时的返回值
IPC_STAT	将消息队列关联的内核数据结构复制到buf中	0
IPC_SET	将buf中的部分成员复制到消息队列关联的内核数据结构中，同时内核数据中的msqid_ds.msg_ctime被更新	0
IPC_RMID	立即移除消息队列，唤醒所有等待读消息和写消息的进程(这些调用立即返回并设置errno为EIDRM)	0
IPC_INFO	获取系统消息队列资源配置信息，将结果存储在buf中。应用程序需要将buf转换成msginfo结构体类型来读取这些系统信息，msginfo结构体与seminfo类似	内核消息队列信息数组中已经被使用的项的最大索引值
MSG_INFO	与IPC_INFO类似，不过返回的是已经分配的消息队列占用的资源信息	同IPC_INFO
MSG_STAT	与IPC_STAT类似，不过此时msqid参数不是用来表示消息队列标识符，而是内核消息队列信息数组的索引(每个消息队列的信息都是该数组的一项)	内核消息队列信息数组中索引值为msqid的消息队列的标识符
msgctl成功时返回值取决于command参数，如上表所示。msgctl失败时返回-1并设置errno

