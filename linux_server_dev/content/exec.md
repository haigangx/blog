# exec系列系统调用

exec系列函数：在子进程中执行其他程序，即替换当前进程映像
#include <unistd.h>
extern char** environ;

int execl( const char* path, const char* arg, ... );
int execlp( const char* file, const char* arg, ... );
int execle( const char* path, const char* arg, ..., char* const envp[] );
int execv( const char* path, char* const argv[] );
int execvp( const char* file, char* const argv[] );
int execve( const char* path, char* const argv[], char* const envp[] );
path：可执行文件的完整路径
file：可执行文件的文件名，具体路径从PATH环境变量中查找
arg：可变长参数
argv：参数数组
envp：新程序的环境变量，如果未设置则采用全局变量environ指定的环境变量

exec函数如果成功执行，exec调用之后的代码将不会执行，因为此时原程序已经被exec的参数指定的程序完全替换(包括代码和数据)
exec函数出错返回-1并设置errno

exec函数不会关闭原程序打开的文件描述符，除非该文件描述符被设置了SOCK_CLOEXEC属性
