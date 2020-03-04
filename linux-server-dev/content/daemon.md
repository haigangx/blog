# 服务程序后台化

让进程以守护进程的方式运行步骤如下：

```
bool daemonize()
{
    //创建子进程，关闭父进程，这样可以使程序在后台运行
    pid_t pid = fork();
    if ( pid < 0 )
        return false;
    else if ( pid > 0 )
        exit( 0 );
        
    //设置文件权限掩码，当进程创建新文件，文件的权限将是mode & 0777
    umask( 0 );
    
    //创建新会话，设置本进程为进程组的首领
    pid_t sid = setsid();
    if ( sid < 0 )
        return false;
    
    //切换工作目录
    if ( ( chdir("/") ) < 0 )
        return false;
        
    //关闭标准输入设备、标准输出设备和标准错误输出设备
    close( STDIN_FILENO );
    close( STDOUT_FILENO );
    close( STDERR_FILENO );
    
    //关闭其他已经打开的文件描述符
    //...
    
    //将标准输入、标准输出和标准错误输出都重定向到/dev/null文件
    open( "/dev/null", O_RDONLY );
    open( "/dev/null", O_RDWR );
    open( "/dev/null", O_RDWR );
        
    return true;
}
```

Linux提供了daemon函数来完成同样的功能：

```
#include <unistd.h>
int daemon(int nochdir, int noclose);
```

- nochdir:用于指定是否改变工作目录，如果传递0，则工作目录将设置为"/"(根目录)，否则继续使用当前工作目录
- noclose：为0时，标准输入、标准输出和标准错误输出都被重定向到/dev/null文件，否则依然使用原来的设备

daemon成功返回0，失败返回-1并设置errno
