# 最大文件描述符数

系统分配给应用程序的文件描述符数量是有限制的，所以我们必须总是关闭那些已经不再使用的文件描述符，以释放它们占用的资源
例如作为守护进程运行的服务器程序就应该总是关闭标准输入、标准输出和标准错误这3个文件描述符
Linux对应用程序能打开的最大文件描述符数量有两个层次的限制：
用户级限制：目标用户运行的所有进程总共能打开的文件描述符数量
系统级限制：所有用户总共能打开的文件描述符数量

查看用户级文件描述符数限制：
ulimit -n
临时改变用户级文件描述符数限制:
ulimit -SHn max-file-number
永久修改用户级文件描述符数限制：
在/etc/security/limit.conf文件中加入如下两项：
* hard nofile max-file-number
* soft nofile max-file-number

临时修改系统级文件描述符数限制：
sysctl -w fs.file-max=max-file-number
永久修改系统级文件描述符数限制：
在/etc/sysctl.conf文件中添加如下一项：
fs.file-max=max-file-number
然后执行sysctl -p命令使更改生效
