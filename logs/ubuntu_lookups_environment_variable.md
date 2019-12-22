# Ubuntu环境变量读取顺序

## 登入系统读取步骤：

当登入系统时获得一个shell进程时，其读取环境设定有三步：

- 首先读入的是全局环境变量设定目录/etc/profile，然后根据其内容读取额外的设定的文档，如/etc/profile.d和/etc/inputrc
- 然后去用户家目录下，读取~/.bash_profile，否则读取~/.bash_login，再否则~/.profile，这三个文档设定基本上一样的，存在读取优先关系
- 最后去用户家目录下，读取~/.bashrc



## /etc/ *和~/. * 区别

- /etc/profile, /etc/bashrc是系统全局环境变量设定
- ~/.profile, ~/.bashrc是用户家目录下的私有环境变量设定

## ~/.profile和~/.bashrc的区别

- 都具有个性化定制功能
- ~/.profile可以设定用户专有的路径，环境变量等，它***只在登入的时候执行一次***
- ~/.bashrc也是用户专有设定文档，可以设定路径，命令别名，***每次shell script的执行都会使用它一次***