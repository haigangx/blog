## linux基础

<details>
<summary>linux文件系统</summary>

# Linux文件系统详解

Linux的文件系统要从Ext2讲起

操作系统管理文件除了要管理文件内容外，还需要管理文件的属性，如文件的rwx权限和文件属性(拥有者、群组、时间等)。文件系统通常会将这两部分内容保存到不同的区块，权限与属性放到inode中，实际文件内容则放到data block区块中。另外，还有一个超级区块(superblock)会记录整个文件系统的整体信息，包括inode和block的总量、使用量、剩余量等

每个inode与block都有编号，这三者的意义简略说明如下：

- superblock：记录此filesystem的整体信息，包括inode/block的总量、使用量、剩余量，以及文件系统的格式与相关信息
- inode：记录文件的属性，一个文件占用一个inode，同时记录此文件的数据所在的block号码
- block：实际记录文件的内容，若文件太大时，会占用多个block

superblock


[linux文件系统详解](https://blog.csdn.net/yuexiaxiaoxi27172319/article/details/45241923)

[鸟哥linux私房菜-认识Linux文件系统](https://wizardforcel.gitbooks.io/vbird-linux-basic-4e/content/59.html)

</details>

<details>
<summary>软链接和硬链接</summary>

</details>

<details>
<summary>Linux中的零拷贝技术</summary>

</details>

<details>
<summary>linux后台任务的运行、关闭、查看</summary>

# linux的后台任务运行、关闭、查看

## 1. &

  加在命令后，使该命令后台执行，如：
  ```
  # 在后台每10s执行一次test.sh脚本
  watch -n 10 sh test.sh &  
  ```

## 2. nohup

  配合`&`达到后台运行的任务脱离终端的目的
  ```
  nohup watch -n 10 sh test.sh &  
  ```

## 3. ctrl+z

  将一个正在前台运行的命令放到后台，并且处于暂停状态

## 4. jobs

  查看在当前后台运行的任务
  `-l`选项可显示所有任务的PID

## 5. fg

  将后台运行的任务调到前台继续运行，通过`fg %jobnumber`可以将制定任务调出

## 6. bg

  将一个在后台暂停的任务，变成在后台继续运行，如果后台有多个任务暂停，可以使用`bg %jobnumber`将指定任务继续

## 7. kill

  杀死后台任务，有两种方式：
  - 通过`jobs -l`查看后台任务的PID，然后执行`kill pid`
  - 通过`jobs`查看后台任务job号，然后执行`kill %jobnumber`

</details>

<details>
<summary>Linux下调试</summary>

# Linux调试工具

[参考教程](https://blog.csdn.net/paladinzh/article/details/91354900)https://www.jianshu.com/p/55cf1fa7a467

## 输出log

最简单快捷的调试方式，可以快速定位bug，可以利用文本分析工具awk/sed/grep快速在大量日志中找到错误信息

## GDB

GDB调试查看[这篇文章](command/gdb.md)
[GDB调试入门看这篇就够了](https://mp.weixin.qq.com/s/dNZVQGRYLjy6_LcOjXb5xw)

## strace

strace是用来跟踪系统调用的工具。

它最简单的用途是跟踪一个程序整个生命周期里所有的系统调用，并把调用参数和返回值以文本的方式输出。

strace还可以跟踪发给进程的信号。支持attach正在运行的进程strace -p <pid>，当多线程环境下，需要跟踪某个线程的系统调用，可以先ps -efL | grep <process name>查找出该进程，然后调用starace -p <pid>进行分析

strace用法请看[这篇文章](command/strace.md)

## pstack
用来跟踪进程栈，比如我们发现一个服务一直处于work状态（如假死状态，好似死循环），使用这个命令就能轻松定位问题所在；可以在一段时间内，多执行几次pstack，若发现代码栈总是停在同一个位置，那个位置就需要重点关注，很可能就是出问题的地方

pstack用法请看[这篇文章](command/pstack.md)

## core dump文件
在进程收到某些信号而终止运行时，将此时进程地址空间的内容以及有关进程状态的其他信息写到core文件中，例如我们平时的非法访问内存产生segment fault错误，利用gdb可以查看到到底是哪里发生了异常。有时候可以人为的向进程发送信号kill -11 <pid>，查看此时系统运行的状态，例如多线程下程序突然停住了，此时就可能发生了死锁，可以人为的产生信号，再来分析core dump。

## valgrind
包含很多工具：

Memcheck。这是valgrind应用最广泛的工具，一个重量级的内存检查器，能够发现开发中绝大多数内存错误使用情况，比如：使用未初始化的内存，使用已经释放了的内存，内存访问越界等。这也是本文将重点介绍的部分。

Callgrind。它主要用来检查程序中函数调用过程中出现的问题。

Cachegrind。它主要用来检查程序中缓存使用出现的问题。

Helgrind。它主要用来检查多线程程序中出现的竞争问题。

Massif。它主要用来检查程序中堆栈使用中出现的问题。

Extension。可以利用core提供的功能，自己编写特定的内存调试工具。

默认使用的就是memcheck工具，在c++中指针的使用，一不留神就会产生异常，就可以利用memcheck进行检查。个人一般用--track-origins=yes来定位未初始化变量的位置。

valgrind用法请看[这篇文章](command/valgrind.md)

## tcpdump

抓包用的，在开发网络应用的时候很给力,结合awk/sed/grep可以快速查找网络数据包

tcpdump用法请看[这篇文章](command/tcpdump.md)

</details>

<details>
<summary>ubuntu中代理设置总结</summary>

# ubuntu中代理设置总结

## 1. 全局环境变量

```
$ sudo vi /etc/environment
```

加入：

```
http_proxy=http://myproxy.server.com:8080/
https_proxy=http://myproxy.server.com:8080/
ftp_proxy=http://myproxy.server.com:8080/
no_proxy="localhost,127.0.0.1,localaddress,.localdomain.com"
HTTP_PROXY=http://myproxy.server.com:8080/
HTTPS_PROXY=http://myproxy.server.com:8080/
FTP_PROXY=http://myproxy.server.com:8080/
NO_PROXY="localhost,127.0.0.1,localaddress,.localdomain.com"
```

## 2. gtk3 应用代理

```
gsettings set org.gnome.system.proxy mode 'manual'
gsettings set org.gnome.system.proxy.http host 'myproxy.server.com'
gsettings set org.gnome.system.proxy.http port 8080
```

## 3. apt-get 代理

```
$ sudo vi /etc/apt/apt.conf.d/95proxies
```

新增文件内容：
```
Acquire::http::proxy "http://myproxy.server.com:8080/";
Acquire::ftp::proxy "ftp://myproxy.server.com:8080/";
Acquire::https::proxy "https://myproxy.server.com:8080/";
```

## 4. git 代理

4.1 http 及 https
```
git config --global http.proxy http://myproxy.server.com:8080
git config --global https.proxy https://myproxy.server.com:8080
```

4.2 git://协议代理
```
$ sudo apt-get install socat
$ sudo vi /usr/bin/gitproxy
```

```
--------------------------
#!/bin/bash

PROXY=myproxy.server.com
PROXYPORT=8080
PROXYAUTH=username:password
exec socat STDIO PROXY:$PROXY:$1:$2,proxyport=$PROXYPORT,proxyauth=$PROXYAUTH
--------------------------
```
```
$ sudo chmod +x /usr/bin/gitproxy
$ git config --global core.gitproxy gitproxy
```

</details>

<details>
<summary>修改bash命令行前缀</summary>

# 修改bash命令行前缀

## 强制开始bash颜色

ubuntu 中 `~/.bashrc` 中一般都有 `force_color_prompt=yes` 选项，把注释去掉即可

## PS1中的关键字

| 关键字 | 说明 |
| --- | --- |
| `\H` | 完整的主机名称 |
| `\h` | 仅取主机的第一个名字,到“.”结束 |
| `\u` | 当前用户的用户名 |
| `\w` | 完整的工作目录名称。宿主目录(如/hom/peter)会以~代替   |
| `\W` | 利用basename取得工作目录名称，所以只会列出最后一个目录 |
| `\$` | 提示字符，如果是root时，提示符为:#,普通用户则为:$|
| `\#` | 显示命令的编号(如30,31...) |
| `\t` | 显示时间为24小时格式，如：HH:MM:SS |
| `\T` | 显示时间为12小时格式 |
| `\A` | 显示时间为24小时格式:  HH:MM |
| `\d` | 代表日期,格式为weekday month date, 例如："Tue May 26" |
| `\v` | bash的版本信息 |

## 自定义前缀

在`~/.bashrc`末尾添加如下内容：

```
export PS1='[\u@\h \W]\$'
```

或者修改预设PS1值

</details>

## linux命令

<details>
<summary>常用命令</summary>

| 命令 | 效果 |
| --- | --- |
| `ssh -D 7001 -fTNnC root@129.226.69.149` | sock5代理：本地端口7001的数据转发到远程服务器129.226.69.149转发出去 |
| `ssh -CqTnN -L 0.0.0.0:8443:192.168.1.2:443  user@192.168.1.3` | 正向代理：将本地主机的8443端口，通过192.168.1.3转发到192.168.1.2:443 |
| `ssh -CqTnN -R 0.0.0.0:8443:192.168.1.2:443  user@202.115.8.1` | 反向代理：将外网主机（202.115.8.1）端口（8443）转发到内网主机 192.168.1.2:443 |
| `python -m SimpleHTTPServer 8000` | 利用python启动一个简单的本地服务器,root为命令启动目录 |
| <code>history \| awk '{a[$2]++}END{for(i in a){print a[i] " " i}}' \| sort -rn \| head</code> | 列出最常使用的十个命令 |
| <code>netstat -n \| awk '/^tcp/ {++tt[$NF]} END {for (a in tt) print a, tt[a]}'</code> | 列出所有网络状态：ESTABLISHED/TIME_WAIT/FIN_WAIT1/FIN_WAIT2 |
| `sshfs name@server:/path/to/folder /path/to/mount/point` | 使用ssh挂载远程文件目录到本地 |
| <code>ps aux \| sort -nk +4 \| tail</code> | 显示前十个运行的进程并按内存使用量排序 |
| `while sleep 1;do tput sc;tput cup 0 $(($(tput cols)-29));date;tput rc;done&` | 终端右上角显示时钟 |
| <code>wget -qO - "http://www.tarball.com/tarball.gz" \| tar zxvf -</code> | 从网络上的压缩文件中解出一个文件夹，并避免保存中间文件 |
| `python -c "import test.pystone;print(test.pystone.pystones())"` | 性能测试：测量处理器性能 |
| `dd if=/dev/zero of=/dev/null bs=1M count=32768` | 性能测试：测试内存带宽 |
| `mount /path/to/file.iso /mnt/cdrom -oloop` | Linux下挂载一个iso文件 |
| `ssh -t hostA ssh hostB` | 通过主机A直接ssh到主机B |
| `wget -r -l1 --no-parent -nH -nd -P/tmp -A".gif,.jpg" http://example.com/images` | 下载一个网站的所有图片 |
| <code>lsof -P -i -n \| cut -f 1 -d " " \| uniq \| tail -n +2</code> | 显示当前正在使用网络的进程 |
| `:w !sudo tee > /dev/null %` | vim中保存一个没有权限的文件 |
| **grep** |  |
| `grep -i "the" demo_file` | 文件中查找字符串 |
| `grep -r "ramesh" *` | 在一个文件夹下递归查找包含字符串"ramesh"的文件 |
| `grep -A 3 -i "the" demo_file` | 输出成功匹配的行以及之后的三行 |
| **文件查找** |  |
| `find . -iname *.c` | 查找当前目录下以.c结尾的文件，忽略大小写 |
| `find . -type f -newermt "2010-01-01" ! -newermt "2010-06-01"` | 按照日期范围查找文件 |
| <code>find / -size +500M -print0 \| xargs -0 du -m \| sort -nr</code> | 查找500M以上的大文件，按文件大小排序输出 |
| `find -iname "MyProgram.c" -exec md5sum {} \` | 对找到的文件执行某个命令 |
| `find ~ -empty` | 查找家目录下的空文件 |
| **软件管理** |  |
| `apt install xxx` | 安装软件 |
| `apt update && apt upgrade` | 更新系统 |
| `apt remove xxx` | 卸载软件 |
| `dpkg -i xxx.deb` | 安装本地软件 |
| `dpkg --list` | 列出所安装的软件包 |
| `dpkg --status package_name` | 确定是否安装了一个软件包 |
| `apt-cache show package_name` | 显示所安装软件包的信息 |
| `dpkg --search file_name` | 查找安装了某个文件的软件包 |
| **解压缩打包** |  |
| `tar cvf archive_name.tar dirname/` | 创建一个新的tar文件 |
| `tar xvf archive_name.tar` | 解压tar文件 |
| `tar tvf archive_name.tar` | 查看tar文件 |
| `tar -xvJf archine_name.tar.xz` | 解压tar.xz文件 |
| `xz -z test.tar` | 将tar包压缩为xz文件 |
| `gzip test.txt` | 创建一个*.gz的压缩文件 |
| `gzip -d test.txt.gz` | 解压*.gz文件 |
| `gzip -l test.txt.gz` | 显示压缩比率 |
| `tar zxvf test.tar.gz -C dir/` | 解压*.tar.gz文件到指定文件夹 |
| `bzip2 test.txt` | 创建*.bz2压缩文件 |
| `bzip2 -d test.txt.gz` | 解压*.bz2文件 |
| <code>objdump -x xxx.so \| grep NEEDED</code> | linux查看依赖的库 |
| <code>objdump -x 可执行程序名 \| grep NEEDED</code> | 查看可执行程序依赖的库 |
| `ldd xxx.so` | 查看缺少的库 |

</details>

<details>
<summary>快捷键</summary>

| 快捷键 | 说明 |
| --- | --- |
| `CTRL+A` | 移动到行首，同 `<Home>` |
| `CTRL+B` | 向后移动，同 `<Left>` |
| `CTRL+C` | 结束当前命令 |
| `CTRL+D` | 删除光标前的字符，同 `<Delete>` ，或者没有内容时，退出会话 |
| `CTRL+E` | 移动到行末，同 `<End>` |
| `CTRL+F` | 向前移动，同 `<Right>` |
| `CTRL+G` | 退出当前编辑（比如正在 `CTRL+R` 搜索历史时） |
| `CTRL+H` | 删除光标左边的字符，同 `<Backspace>` |
| `CTRL+K` | 删除光标位置到行末的内容 |
| `CTRL+L` | 清屏并重新显示 |
| `CTRL+N` | 移动到命令历史的下一行，同 `<Down>` |
| `CTRL+O` | 类似回车，但是会显示下一行历史 |
| `CTRL+P` | 移动到命令历史的上一行，同 `<Up>` |
| `CTRL+R` | 历史命令反向搜索，使用 `CTRL+G` 退出搜索 |
| `CTRL+S` | 历史命令正向搜索，使用 `CTRL+G` 退出搜索 |
| `CTRL+T` | 交换前后两个字符 |
| `CTRL+U` | 删除字符到行首 |
| `CTRL+V` | 输入字符字面量，先按 `CTRL+V` 再按任意键 |
| `CTRL+W` | 删除光标左边的一个单词 |
| `CTRL+X` | 列出可能的补全 |
| `CTRL+Y` | 粘贴前面 `CTRL+u/k/w` 删除过的内容 |
| `CTRL+Z` | 暂停前台进程返回 bash，需要时可用 `fg` 将其切换回前台 |
| `CTRL+_` | 撤销（undo），有的终端将 `CTRL+_` 映射为 `CTRL+/` 或 `CTRL+7` |
| `ALT+b ` | 向后（左边）移动一个单词 |
| `ALT+d ` | 删除光标后（右边）一个单词 |
| `ALT+f ` | 向前（右边）移动一个单词 |
| `ALT+t ` | 交换字符 |
| `ALT+BACKSPACE` | 删除光标前面一个单词，类似 `CTRL+W`，但不影响剪贴板 |
| `CTRL+X CTRL+X` | 连续按两次 `CTRL+X`，光标在当前位置和行首来回跳转 |
| `CTRL+X CTRL+E` | 用你指定的编辑器，编辑当前命令 |

</details>

<details>
<summary>Bash基本操作</summary>

| 命令 | 说明 |
| --- | --- |
| exit                | 退出当前登陆 |
| env                 | 显示环境变量 |
| echo $SHELL         | 显示你在使用什么 SHELL |
| bash                | 使用 bash，用 exit 返回 |
| which bash          | 搜索 $PATH，查找哪个程序对应命令 bash |
| whereis bash        | 搜索可执行，头文件和帮助信息的位置，使用系统内建数据库 |
| whatis bash         | 查看某个命令的解释，一句话告诉你这是干什么的 |
| clear               | 清初屏幕内容 |
| reset               | 重置终端（当你不小心 cat 了一个二进制，终端状态乱掉时使用） |

</details>


<details>
<summary>目录操作</summary>

| 命令 | 说明 |
| --- | --- |
| cd                  | 返回自己 $HOME 目录 |
| cd {dirname}        | 进入目录 |
| pwd                 | 显示当前所在目录 |
| mkdir {dirname}     | 创建目录 |
| mkdir -p {dirname}  | 递归创建目录 |
| pushd {dirname}     | 目录压栈并进入新目录 |
| popd                | 弹出并进入栈顶的目录 |
| dirs -v             | 列出当前目录栈 |
| cd -                | 回到之前的目录 |
| cd -{N}             | 切换到目录栈中的第 N个目录，比如 cd -2 将切换到第二个 |

</details>

<details>
<summary>文件操作</summary>

| 命令 | 说明 |
| --- | --- |
| ls                  | 显示当前目录内容，后面可接目录名：ls {dir} 显示指定目录 |
| ls -l               | 列表方式显示目录内容，包括文件日期，大小，权限等信息 |
| ls -1               | 列表方式显示目录内容，只显示文件名称，减号后面是数字 1 |
| ls -a               | 显示所有文件和目录，包括隐藏文件（.开头的文件/目录名） |
| ln -s {fn} {link}   | 给指定文件创建一个软链接 |
| cp {src} {dest}     | 拷贝文件，cp -r dir1 dir2 可以递归拷贝（目录） |
| rm {fn}             | 删除文件，rm -r 递归删除目录，rm -f 强制删除 |
| mv {src} {dest}     | 移动文件，如果 dest 是目录，则移动，是文件名则覆盖 |
| touch {fn}          | 创建或者更新一下制定文件 |
| cat {fn}            | 输出文件原始内容 |
| any_cmd > {fn}      | 执行任意命令并将标准输出重定向到指定文件 |
| more {fn}           | 逐屏显示某文件内容，空格翻页，q 退出 |
| less {fn}           | 更高级点的 more，更多操作，q 退出 |
| head {fn}           | 显示文件头部数行，可用 head -3 abc.txt 显示头三行 |
| tail {fn}           | 显示文件尾部数行，可用 tail -3 abc.txt 显示尾部三行 |
| tail -f {fn}        | 持续显示文件尾部数据，可用于监控日志 |
| nano {fn}           | 使用 nano 编辑器编辑文件 |
| vim {fn}            | 使用 vim 编辑文件 |
| diff {f1} {f2}      | 比较两个文件的内容 |
| wc {fn}             | 统计文件有多少行，多少个单词 |
| chmod 644 {fn}      | 修改文件权限为 644，可以接 -R 对目录循环改权限 |
| chgrp group {fn}    | 修改文件所属的用户组 |
| chown user1 {fn}    | 修改文件所有人为 user1, chown user1:group1 fn 可以修改组 |
| file {fn}           | 检测文件的类型和编码 |
| basename {fn}       | 查看文件的名字（不包括路径） |
| dirname {fn}        | 查看文件的路径（不包括名字） |
| grep {pat} {fn}     | 在文件中查找出现过 pat 的内容 |
| grep -r {pat} .     | 在当前目录下递归查找所有出现过 pat 的文件内容 |
| stat {fn}           | 显示文件的详细信息 |

</details>


<details>
<summary>用户管理</summary>

| 命令 | 说明 |
| --- | --- |
| whoami              | 显示我的用户名 |
| who                 | 显示已登陆用户信息，w / who / users 内容略有不同 |
| w                   | 显示已登陆用户信息，w / who / users 内容略有不同 |
| users               | 显示已登陆用户信息，w / who / users 内容略有不同 |
| passwd              | 修改密码，passwd {user} 可以用于 root 修改别人密码 |
| finger {user}       | 显示某用户信息，包括 id, 名字, 登陆状态等 |
| adduser {user}      | 添加用户 |
| deluser {user}      | 删除用户 |
| su                  | 切换到 root 用户 |
| su -                | 切换到 root 用户并登陆（执行登陆脚本） |
| su {user}           | 切换到某用户 |
| su -{user}          | 切换到某用户并登陆（执行登陆脚本） |
| id {user}           | 查看用户的 uid，gid 以及所属其他用户组 |
| id -u {user}        | 打印用户 uid |
| id -g {user}        | 打印用户 gid |
| write {user}        | 向某用户发送一句消息 |
| last                | 显示最近用户登陆列表 |
| last {user}         | 显示登陆记录 |
| lastb               | 显示失败登陆记录 |
| lastlog             | 显示所有用户的最近登陆记录 |
| sudo {command}      | 以 root 权限执行某命令 |

</details>

<details>
<summary>进程管理</summary>

| 命令 | 说明 |
| --- | --- |
| ps                        | 查看当前会话进程 |
| ps ax                     | 查看所有进程，类似 ps -e |
| ps aux                    | 查看所有进程详细信息，类似 ps -ef |
| ps auxww                  | 查看所有进程，并且显示进程的完整启动命令 |
| ps -u {user}              | 查看某用户进程 |
| ps axjf                   | 列出进程树 |
| ps xjf -u {user}          | 列出某用户的进程树 |
| ps -eo pid,user,command   | 按用户指定的格式查看进程 |
| ps aux | grep httpd       | 查看名为 httpd 的所有进程 |
| ps --ppid {pid}           | 查看父进程为 pid 的所有进程 |
| pstree                    | 树形列出所有进程，pstree 默认一般不带，需安装 |
| pstree {user}             | 进程树列出某用户的进程 |
| pstree -u                 | 树形列出所有进程以及所属用户 |
| pgrep {procname}          | 搜索名字匹配的进程的 pid，比如 pgrep apache2 |
| kill {pid}                | 结束进程 |
| kill -9 {pid}             | 强制结束进程，9/SIGKILL 是强制不可捕获结束信号 |
| kill -KILL {pid}          | 强制执行进程，kill -9 的另外一种写法 |
| kill -l                   | 查看所有信号 |
| kill -l TERM              | 查看 TERM 信号的编号 |
| killall {procname}        | 按名称结束所有进程 |
| pkill {procname}          | 按名称结束进程，除名称外还可以有其他参数 |
| top                       | 查看最活跃的进程 |
| top -u {user}             | 查看某用户最活跃的进程 |
| any_command &             | 在后台运行某命令，也可用 CTRL+Z 将当前进程挂到后台 |
| jobs                      | 查看所有后台进程（jobs） |
| bg                        | 查看后台进程，并切换过去 |
| fg                        | 切换后台进程到前台 |
| fg {job}                  | 切换特定后台进程到前台 |
| trap cmd sig1 sig2        | 在脚本中设置信号处理命令 |
| trap "" sig1 sig2         | 在脚本中屏蔽某信号 |
| trap - sig1 sig2          | 恢复默认信号处理行为 |
| nohup {command}           | 长期运行某程序，在你退出登陆都保持它运行 |
| nohup {command} &         | 在后台长期运行某程序 |
| disown {PID|JID}          | 将进程从后台任务列表（jobs）移除 |
| wait                      | 等待所有后台进程任务结束 |

</details>

<details>
<summary>常用命令：SSH / 系统信息 / 网络</summary>

| 命令 | 说明 |
| --- | --- |
| ssh user@host             | 以用户 user 登陆到远程主机 host |
| ssh -p {port} user@host   | 指定端口登陆主机 |
| ssh-copy-id user@host     | 拷贝你的 ssh key 到远程主机，避免重复输入密码 |
| scp {fn} user@host:path   | 拷贝文件到远程主机 |
| scp user@host:path dest   | 从远程主机拷贝文件回来 |
| scp -P {port} ...         | 指定端口远程拷贝文件 |
| uname -a                  | 查看内核版本等信息 |
| man {help}                | 查看帮助 |
| man -k {keyword}          | 查看哪些帮助文档里包含了该关键字 |
| info {help}               | 查看 info pages，比 man 更强的帮助系统 |
| uptime                    | 查看系统启动时间 |
| date                      | 显示日期 |
| cal                       | 显示日历 |
| vmstat                    | 显示内存和 CPU 使用情况 |
| vmstat 10                 | 每 10 秒打印一行内存和 CPU情况，CTRL+C 退出 |
| free                      | 显示内存和交换区使用情况 |
| df                        | 显示磁盘使用情况 |
| du                        | 显示当前目录占用，du . --max-depth=2 可以指定深度 |
| uname                     | 显示系统版本号 |
| hostname                  | 显示主机名称 |
| showkey -a                | 查看终端发送的按键编码 |
| ping {host}               | ping 远程主机并显示结果，CTRL+C 退出 |
| ping -c N {host}          | ping 远程主机 N 次 |
| traceroute {host}         | 侦测路由连通情况 |
| mtr {host}                | 高级版本 traceroute |
| host {domain}             | DNS 查询，{domain} 前面可加 -a 查看详细信息 |
| whois {domain}            | 取得域名 whois 信息 |
| dig {domain}              | 取得域名 dns 信息 |
| route -n                  | 查看路由表 |
| netstat -a                | 列出所有端口 |
| netstat -an               | 查看所有连接信息，不解析域名 |
| netstat -anp              | 查看所有连接信息，包含进程信息（需要 sudo） |
| netstat -l                | 查看所有监听的端口 |
| netstat -t                | 查看所有 TCP 链接 |
| netstat -lntu             | 显示所有正在监听的 TCP 和 UDP 信息 |
| netstat -lntup            | 显示所有正在监听的 socket 及进程信息 |
| netstat -i                | 显示网卡信息 |
| netstat -rn               | 显示当前系统路由表，同 route -n |
| ss -an                    | 比 netstat -an 更快速更详细 |
| ss -s                     | 统计 TCP 的 established, wait 等 |
| wget {url}                | 下载文件，可加 --no-check-certificate 忽略 ssl 验证 |
| wget -qO- {url}           | 下载文件并输出到标准输出（不保存） |
| curl -sL {url}            | 同 wget -qO- {url} 没有 wget 的时候使用 |
| sz {file}                 | 发送文件到终端，zmodem 协议 |
| rz                        | 接收终端发送过来的文件 |

</details>

<details>
<summary>curl</summary>

# curl

## 设置代理

`curl -v`可以确定代理是否设置成功

- 1. 传参代理

每次访问都需要写代理参数：

```
curl -x socks5://127.0.0.1:7001 http://www.google.com
```

- 2. 设置配置文件

每次下载都会自动使用代理：

```
vim ~/.curlrc

socks5 = "127.0.0.1:7001"
```

如果临时不需要代理使用以下参数：

```
curl --noproxy "*" http://www.google.com
```

</details>

<details>
<summary>find</summary>

# find、locate、whereis、which、grep等查找命令

## find

find命令用来在指定目录下查找文件。任何位于参数之前的字符串都将被视为欲查找的目录名。
如果使用该命令时，不设置任何参数，则find命令将在当前目录下查找子目录与文件。并且将查找到的子目录和文件全部进行显示。

https://blog.csdn.net/wzzfeitian/article/details/40985549
https://www.runoob.com/linux/linux-comm-find.html
https://man.linuxde.net/find

## locate

## whereis

## which

## grep

https://www.runoob.com/linux/linux-comm-grep.html
https://man.linuxde.net/grep

</details>

<details>
<summary>gdb</summary>

# GDB调试工具

## 1. 命令行GDB调试

使用gdb调试，编译时要用-g选项，并使用-O级优化

### 1.1 常用命令

| 命令 | 简写 | 命令说明 |
| :--- | :--- | :------- |
| list | l | 显示多行源代码 |
| break n | b n | 在第n行设置断点 |
| break if | b if | 当满足某个条件时停止 |
| delete n | d n | 删除断点 |
| disable |  | 禁用断点 |
| enable |  | 启用断点 |
| info | i | 描述程序状态，比如：i break显示有哪些断点 |
| run | r | 开始运行程序 |
| display | disp | 跟踪查看某个变量，每次停下来都显示其值 |
| print | p | 打印内部变量值 |
| watch |  | 监视变量新旧值变化 |
| step | s | 下一步 |
| next | n | 下一条语句 |
| continue | c | 继续运行程序，直到遇到下一个断点 |
| finish |  | 跳出当前函数 |
| set var name = v |  | 设置变量的值 |
| backtrace | bt | 查看堆栈 |
| start |  | 开始执行程序，在main函数的第一条语句前停下 |
| frame | f | 查看栈帧 |
| quit | q | 离开gdb |
| edit |  | 在gdb中进行编辑 |
| whatis |  | 查看变量的类型 |
| search |  | 搜索源文件中的文本 |
| file |  | 装入需要调试的程序 |
| kill |  | 终止正在调试的程序 |


### 1.2 gdb调试多进程

1. 先运行服务器，然后找到目标子进程的PID，再将其附加(attach)到gdb调试器
  ```
  attach <pid>
  ```

2. 调试器选项`follow-work-mode`
  `follow-fork-mode`选项允许我们选择程序在执行fork系统调用之后是继续调试父进程还是调试子进程，在启动gdb之后通过下面的命令设置：
  ```
  set follow-fork-mode child  //调试子进程
  set follow-fork-mode parent //调试父进程
  ```
3. 调试器选项`detach-on-fork`
  `detach-on-fork`选项指示gdb在fork后调试某个进程时，是断开(detach)另一个进程的调试还是交给gdb控制
  ```
  set detach-on-fork [on|off]
  ```
  - on：表示断开另一个进程
  - off：gdb将控制父进程和子进程。当follow-frok-mode指定的进程被调试时，另一个进程处于暂停(suspended)状态

### 1.3. gdb调试多线程

gdb有一组命令可辅助多线程程序的调试：

- info threads：显式当前可调试的所有线程。gdb会为每个线程分配一个ID，我们可以使用这个ID来操作对应的线程，ID前有*号的线程是当前被调试的线程

- thread ID：调试目标ID指定的线程

- set scheduler-locking [off|on|step]：调试多线程程序时，默认除了被调试的线程在执行外，其他线程也在继续执行。通过这个命令可以只让被调试的线程运行：

  该命令设置scheduler-locking的值：
  - off代表不锁定任何线程，即所有线程都可以继续执行
  - on表示只有当前调试线程会继续执行
  - step表示在单步执行时，除了next过一个函数的情况(这其实是一个设置断点然后continue的行为)以外，只有当前线程执行

调试进程池和线程池程序时：可以先将池中的进程个数或线程个数减少至1，以观察程序逻辑是否正确，然后逐步增加进程和线程的数量，以调试进程或线程的同步是否正确

### 1.4. 调试core dump

core dump又叫核心转储, 当程序运行过程中发生异常, 程序异常退出时, 由操作系统把程序当前的内存状况存储在一个core文件中, 叫core dump. (linux中如果内存越界会收到SIGSEGV信号，然后就会core dump)

#### 1.4.1 造成segment fault，产生core dump的可能原因

- 内存访问越界

  - 由于使用错误的下标，导致数组访问越界

  - 搜索字符串时，依靠字符串结束符来判断字符串是否结束，但是字符串没有正常的使用结束符

  - 使用strcpy, strcat, sprintf, strcmp, strcasecmp等字符串操作函数，将目标字符串读/写爆。应该使用strncpy, strlcpy, strncat, strlcat, snprintf, strncmp, strncasecmp等函数防止读写越界。

- 多线程程序使用了线程不安全的函数

- 多线程读写的数据未加锁保护。对于会被多个线程同时访问的全局数据，应该注意加锁保护，否则很容易造成core dump

- 非法指针

  - 使用空指针

  - 随意使用指针转换。一个指向一段内存的指针，除非确定这段内存原先就分配为某种结构或类型，或者这种结构或类型的数组，否则不要将它转换为这种结构或类型的指针，而应该将这段内存拷贝到一个这种结构或类型中，再访问这个结构或类型。这是因为如果这段内存的开始地址不是按照这种结构或类型对齐的，那么访问它时就很容易因为bus error而core dump.

- 堆栈溢出.不要使用大的局部变量（因为局部变量都分配在栈上），这样容易造成堆栈溢出，破坏系统的栈和堆结构，导致出现莫名其妙的错误。

#### 1.4.2 配置操作系统使其产生core文件

首先通过ulimit命令查看一下系统是否配置支持了dump core的功能。通过ulimit -c或ulimit -a，可以查看core file大小的配置情况，如果为0，则表示系统关闭了dump core。可以通过ulimit -c unlimited来打开。 **若发生了段错误，但没有core dump，可能是由于系统禁止core文件的生成。**

解决方法:
```
$ulimit -c unlimited　　（只对当前shell进程有效）
```
或在~/.bashr*　的最后加入： ulimit -c unlimited （一劳永逸）

查看系统是否禁止core文件生成：

```
\# ulimit -c

0

$ ulimit -a

core file size          (blocks, -c) 0

data seg size           (kbytes, -d) unlimited

file size               (blocks, -f) unlimited
```

#### 1.4.3 用gdb查看core文件

发生core dump之后, 用gdb进行查看core文件的内容, 以定位文件中引发core dump的行.

```
gdb [exec file]  \[ core file]
```

如: 

```
gdb ./test test.core
```

#### 1.4.4 使用core文件定位core dump位置

先使用命令 gdb [exec file]  \[ core file]查看core文件，然后输入where命令，gdb就会输出coredump的位置。


### 1.5. 调试宏

调试宏需要gcc在编译时加上`-ggdb3`参数，然后可以使用下面的gdb宏调试命令来查看宏：

- info macro：查看这个宏在哪些文件被引用，以及宏定义是什么样的
- macro：查看宏展开的样子

### 1.6. 源文件

有时候使用gdb调试提示找不到源文件，这时候需要注意两点：

- 编译时是否加-g参数以及保护debug信息
- 源码路径是否设置正确，可以使用gdb的`directory`命令来设置源文件的目录

### 1.7. 条件断点

```
break [where] if [condition]
```

### 1.8. 命令行参数

如果调试的程序运行时需要命令行参数，有两种方法设置：

- gdb命令行的`-args`参数
- gdb环境中`set args`命令

### 1.9. x命令

无需变量名查看内存

### 1.10. command命令

command命令可以将一组gdb命令打包，当断点到达时，自动执行command打包的gdb命令

### 1.11. 调试脚本

优点：

- 自己定义一些方便的命令，比如打印STL容器中的内容
- 不用每次打开gdb都要重新打一次断点

使用方法：

一般有三种方法：https://blog.csdn.net/cnsword/article/details/16337031

好用的调试脚本推荐：

- 查看STL容器：http://www.yolinux.com/TUTORIALS/src/dbinit_stl_views-1.03.txt
- gdb init：https://github.com/gdbinit/Gdbinit/blob/master/gdbinit

参考：

[gdb中应该知道的几个调试方法](https://coolshell.cn/articles/3643.html)

[使用gdb调试多进程程序](https://www.ibm.com/developerworks/cn/linux/l-cn-gdbmp/index.html)

## 2. 图像界面调试

### 2.1 gdb自带的tui

```
gdb --tui a.out
```

更具体的使用方法参考[该博客](https://blog.csdn.net/xu415/article/details/19021759)

### 2.2 在浏览器显示调试界面---gdbgui

[Github项目地址](https://github.com/cs01/gdbgui)

#### 2.2.1 安装：

```
curl https://raw.githubusercontent.com/cs01/pipx/master/get-pipx.py | python3

pipx install gdbgui
```

#### 2.2.2 使用：

```
gdbgui -p 10001 -r "a.out"
```
-p 制定端口号 -r 表示远程remote调试

运行之后就可以在本地浏览器调试服务器程序

[参考教程](https://blog.csdn.net/songchuwang1868/article/details/86132281)
</details>

<details>
<summary>ifstat</summary>

# ifstat

ifstat(interface statistics)：简单的网络流量监测工具
常用选项如下：
-a 监测系统上的所有网卡接口
-i 指定要监测的网卡接口
-t 在每行输出信息前加上时间戳
-b 以Kbit/s为单位显示数据，而不是默认的KB/s
delay 采样间隔(单位为s)，即每隔delay的时间输出一次统计信息
count 采样次数，即共输出count次统计信息

</details>

<details>
<summary>mpstat</summary>

# mpstat

mpstat(multi-processor statistics)：实时监测多个处理器系统上每个CPU的使用情况
mpstat的典型用法是：
mpstat [-P {|ALL}] [interval [count]]
P 指定要监控的CPU号(0~CPU个数-1)，ALL表示监听所有CPU
interval：采样间隔(单位是s)，即每隔interval的时间输出一次统计情况
count：采样次数，即共输出count次统计信息

</details>

<details>
<summary>nc</summary>

# nc

nc(netcat)用来快速构建网络连接：
* 可以让它以服务器方式运行，监听某个端口并接收客户连接，因此它可以用来调试客户端程序
* 也可以使之以客户端方式运行，向服务器发起连接并收发数据，因此它可以用来调试服务器程序，此时的行为类似于telnet

nc命令常用选项：
-i 设置数据包传送的时间间隔
-l 以服务器方式运行，监听指定端口 nc命令默认以客户端方式运行
-k 重复接受并处理某个端口上的所有连接，必须与-l选项一起使用
-n 使用IP地址表示主机，而不是主机名；使用数字表示端口号，而不是服务名称
-p 当nc命令以客户端方式运行时，强制其使用指定的端口号
-s 设置本地主机发送出的数据包的IP地址
-C 将CR和LF两个字符作为行结束符
-u 使用UDP协议，nc命令默认使用的传输层协议是TCP协议
-w 如果nc客户端在指定时间内没有检测到任何输入，则退出
-X 当nc客户端和代理服务器通信时，该选项指定它们之间使用的通信协议。目前nc支持的代理协议包括4:(socks4) 5:(socks5) connect(HTTPS proxy)，nc默认使用socks5
-x 指定目标代理服务器的IP地址和端口号
   例如：从Kongming20连接到ernest-laptop上的squid代理服务器，并通过它访问www.baidu.com的Web服务：
   $ nc -x ernest-laptop:1080 -X connect www.baidu.com 80
-z 扫描目标机器上的某个或某些服务是否开启(端口扫描)
   例如：扫描机器ernest-laptop上端口号20~50之间的服务：
   $ nc -z ernest-laptop 20-50

</details>

<details>
<summary>netstat</summary>

# netstat

netstat是一个功能很强大的网络信息统计工具，它可以打印本地网卡接口上的全部连接、路由表信息、网卡接口信息等。
netstat主要使用它来显示TCP连接及状态信息，要获得路由表信息和网卡接口信息，可以使用输出内容更丰富的route和ifconfig命令
netstat命令常用的选项：
-n 使用IP地址表示主机，而不是主机名；使用数字表示端口号，而不是服务名称
-a 显示结果中也包含监听socket
-t 仅显示TCP连接
-r 显示路由信息
-i 显示网卡接口的数据流量
-c 每隔1s输出一次
-o 显示socket定时器(比如保活定时器)的信息
-p 显示socket所属的进程的PID和名字

</details>

<details>
<summary>vmstat</summary>

# vmstat

vmstat(virtual memory statistics)：实时输出系统的各种资源的使用情况，比如进程信息、内存使用、CPU使用率以及IO使用情况
vmstat选项和参数：
-f 显示系统自启动以来执行的fork次数
-s 显示内存相关的统级信息以及多种系统活动的数量(CPU上下文切换次数)
-d 显示磁盘相关的统计信息
-p 显示指定磁盘分区的统计信息
-S 使用指定单位显示 参数k、K、m、M分别代表1000、1024、1000000和1048576字节
delay 采样间隔(单位为s)，即每隔delay的时间输出以此统计信息
count 采样次数，即共输出count统计信息

</details>

<details>
<summary>top/htop</summary>

</details>

<details>
<summary>strace</summary>

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

</details>

<details>
<summary>ltrace</summary>

</details>

<details>
<summary>pstack</summary>

# pstack

pstack是一个shell脚本，用于打印正在运行的进程的栈跟踪信息，pstack命令必须由相应进程的属主或root进行，可以使用pstack来确定进程挂起的位置。此命令允许使用的唯一选项是要检查的进程的PID

如果我们发现一个服务一直处于work状态(如假死状态，就像死循环)，使用这个命令就能轻松定位问题所在。可以在一段时间内，多执行几次pstack，若发现代码栈总是停在同一个位置，那个位置就需要重点关注，很可能就是出问题的地方

## 示例：查看bash程序进程栈

```
# 查看bash进程的pid
ps -fe | grep bash

# 假设pid为7013
pstack 7013
```

</details>

<details>
<summary>valgrind</summary>

</details>

<details>
<summary>tcpdump</summary>

# tcpdump

tcpdump是一款经典的网络抓包工具，它的常见选项如下：
-n 使用IP地址表示主机，而不是主机名；使用数字表示端口号，而不是服务名称
-i 指定要监听的网卡接口。"-i any"表示抓取所有网卡接口上的数据包
-v 输出比较详细的信息，比如，显示IP数据包中的TTL和TOS信息
-t 不打印时间戳
-e 显示以太网帧头部信息
-c 仅抓取指定数量的数据包
-x 以十六进制数显示数据包的内容，但不显示包中以太网帧的头部信息
-X 与-x选项类似，不过还打印每个十六进制字节对应的ASCII字符
-XX 与-X相同，不过还打印以太网帧的头部信息
-s 设置抓包时的抓取长度。当数据包的长度超过抓取长度时，tcpdump抓取到的将是被截断的数据包。在4.0以及以前的版本中，默认的抓包长度是68字节。这对于IP、TCP和UDP等协议已经足够了，但对于像DNS、NFS这样的协议，68字节通常不能通纳一个完整的数据包。不过4.0之后的版本，默认的抓包长度被修改为65535字节，因此基本不用担心抓包长度的问题
-S 以绝对值显示TCP报文段的序号，而不是相对值
-w 将tcpdump的输出以特殊的格式定向到某个文件
-r 从文件读取数据包信息并显示之

tcpdump还支持用表达式进一步过滤数据包。tcpdump表达式的操作数分为3种：类型(type)、方向(dir)和协议(proto)，下面依次介绍：
* 类型，解释其后面紧跟着的参数的含义。tcpdump支持的类型包括host、net、port和portrange。它们分别指定主机名(或IP地址)，用CIDR方法表示的网络地址，端口号以及端口范围
  例如：要抓取1.2.3.0/255.255.255.0网络上的数据包，可以使用如下命令：
  $ tcpdump net 1.2.3.0/24
* 方向，src指定数据包的发送端，dst指定数据包的目的端
  比如：要抓取进入端口13579的数据包：
  $ tcpdump dst port 13579
* 协议，指定目标协议
  比如：要抓取所有ICMP数据包：
  $ tcpdump icmp
  
还可以使用逻辑操作符来组织上述操作数以创建更复杂的表达式。
tcpdump支持的逻辑操作符包括and(或&&)、or(或||)、not(或!)
例如：抓取主机ernest-laptop和所有非Kongming20的主机之间交换的IP数据包：
  $ tcpdump ip host ernest-laptop and not Kongming20

如果表达式比较复杂，可以使用括号将他们分组，不过在使用括号时，要么使用反斜杠"\"对它转义，要么用单引号"'"，以避免它被shell所解释
例如：要抓取来自主机10.0.2.4，目标端口是3389或22的数据包：
  $ tcpdump 'src 10.0.2.4 and (dst port 3389 or 22)'

tcpdump还允许直接使用数据包中的部分协议字段的内容来过滤数据包
例如：仅抓取TCP同步报文段：
  $ tcpdump 'tcp[13] & 2 != 0'
  这是因为TCP头部的第14个字节的第2个位正是同步标志，该命令还可以表示为：
  $ tcpdump 'tcp[tcpflags] & tcp-syn != 0'

更多用法参考tcpdump的man手册

</details>

<details>
<summary>grep</summary>

</details>

<details>
<summary>tar</summary>

</details>

<details>
<summary>lsof</summary>

# lsof

lsof(list open file)：列出当前系统打开的文件描述符，通过这个命令我们可以了解某个进程打开了哪些文件描述符，或者我们感兴趣的文件描述符被哪些进程打开了

lsof常用选项：
-i 显示socket文件描述符。使用方法如下：
   $ lsof -i [46] [protocol][@hostname|ipaddr][:service|port]
     4表示IPv4协议，6表示IPv6协议
     protocol：指定传输层协议，可以是TCP或者UDP
     hostname：指定主机名
     ipaddr：指定主机IP地址
     service：服务名
     port：端口号
     例如：要显示所有连接到主机192.168.1.108的ssh服务的socket文件描述符：
     $ lsof -i@192.168.1.108:22
   如果-i选项后不指定任何参数，则lsof命令将显示所有socket文件描述符
-u 显示指定用户启动的所有进程打开的所有文件描述符
-c 显示指定的命令打开的所有的文件描述符
   例如：查看websrv程序打开了哪些文件描述符：
   $ lsof -c websrv
-p 显示指定进程打开的文件描述符
-t 仅显示打开了目标文件描述符的进程的PID

例：查看websrv服务器打开的文件描述符
$ ps -ef | grep websrv      #先获取websrv程序的进程号
$ sudo lsof -p 6346         #用-p选项指定进程号
COMMAND PID     USER    FD  TYPE    DEVICE  SIZE/OFF    NODE    NAME
websrv  6246    shuang  cwd DIR     8,3     4096        1199520 /home/shuang/codes/pool_thread
...
lsof输出的表格各个字段的意义如下：
* COMMAND：执行程序所执行的终端命令(默认仅显示前9个字符)
* PID：文件描述符所属进程的PID
* USER：拥有该文件描述符的用户的用户名
* FD：文件描述符的描述：
    cwd：进程的工作目录
    rtd：用户的根目录
    txt：进程运行的程序代码
    mem：直接映射到内存中的文件
    数字+访问权限组合：数字是文件描述符的具体值，访问权限r、w、u分别为可读、可写、可读可写
* TYPE：文件描述符类型：
    DIR：目录
    REG：普通文件
    CHR：字符设备文件
    IPv4：IPv4类型的socket文件描述符
    0000：未知类型
* DEVICE：文件所属设备：
    对于字符设备和块设备，表示方法为"主设备号，次设备号"，例"8,3"：8表示这是一个SCSI硬盘，3表示这是该硬盘上的第3个分区，即sda3
    假设程序的标准输入、标准输出和标准错误输出为"136,3"，则136表示这是一个伪终端，3表示它是第3个伪终端，即/dev/pts/3
    对于FIFO类型的文件，比如管道和socket，该字段将显示一个内核引用目标文件的地址，或者是其i节点号
* SIZE/OFF：文件大小或偏移值
    对字符设备或FIFO类型的文件定义文件大小没有意义，所以该字段将显示一个偏移值
    如果该字段显示为"0t*"或"0x*"，则表示是一个偏移值，否则表示文件大小
* NODE：文件的i节点号
        对于socket，则显示为协议类型，如TCP
* NAME：文件名

</details>

<details>
<summary>sed</summary>

# sed 

https://coolshell.cn/articles/9104.html?utm_source=tuicool&utm_medium=referral

</details>

<details>
<summary>awk</summary>

# awk

https://coolshell.cn/articles/9070.html?utm_source=tuicool&utm_medium=referral

</details>

<details>
<summary>scp</summary>

# scp

scp(secure copy)是用于在Linux下进行远程文件拷贝的命令，scp的传输是加密的，所以可能会稍微影响速度

## scp命令参数：

- -1 强制scp使用协议ssh1
- -2 强制scp使用协议ssh2
- -4 强制scp只使用IPv4寻址
- -6 强制scp只使用IPv6寻址
- -r 递归复制整个目录
- -C 允许压缩(将-C标志传递给ssh，从而打开压缩功能)
- -p 保留原文件的修改时间，访问时间和访问权限
- -q 安静模式，不显示传输进度条、警告及诊断信息
- -B 使用批处理模式(传输过程中不询问传输口令或短语)
- -v 详细方式显示输出。scp和ssh会显示出整个过程的调试信息
- -P port 指定数据传输用到的端口号
- -l 限制最大传输速度，单位为kbit/s
- -F ssh_config 指定一个ssh配置文件，此参数直接传递给ssh
- -i identity_file 从指定文件中读取传输时使用的秘钥文件，此参数直接传递给ssh
- -c cipher 以cipher将数据传输进行加密，这个选项将直接传递给ssh
- -S program 指定加密传输时所使用的程序，此程序必须能够理解ssh的选项
- -o ssh_option 通过命令行为ssh设置某个特殊属性

## scp使用方式：

- 远端文件/目录下载到本地：
  ```
  scp user@host:/val/file.tar.gz /val/file.tar.gz
  scp -r user@host:/val/dir/ /val/dir/
  # 将远端多个文件下载到本地
  scp user@host:/path/dir/\{foot.txt,bar.txt\} .
  ```

- 本地文件/目录上传到远端：
  ```
  scp /val/file.tar.gz user@host:/val/file.tar.gz
  scp -r /val/dir/ user@host:/val/dir/
  # 将多个文件上传到远端目录
  scp foo.txt bar.txt user@host:/path/dir/
  ```

- 将文件从一个远程主机复制到另一个远程主机
  ```
  scp user1@host1:/path/foo.txt user2@host2:/path/dir/
  ```

</details>

<details>
<summary>ssh</summary>

# ssh

## ssh介绍

ssh是一种网络协议，用于计算机之间的加密登录，ssh采用公钥加密，所以保证了两个计算机之间交流的信息安全

ssh只是一种协议，存在多种实现，本文针对的实现是openssh，它是自由软件，应用非常广泛

### ssh风险--中间人攻击

ssh连接的整个过程是这样的：

- 1.远程主机收到用户的登录请求，把自己的公钥发送给用户
- 2.用户使用这个公钥，将登录密码加密后，发送到远程主机
- 3.远程主机用自己的私钥，解密登录密码，如果密码正确，就同意用户登录

这个过程本身是安全的，但是实施的过程中存在一个风险：如果有人截获了登录请求，然后冒充远程主机，将伪造的公钥发送给用户，那么用户很难辨别真伪。

所以，如果攻击者插在用户与远程主机之间(比如公共的wifi区域)，用伪造的公钥，获取用户的登录密码。再用这个密码登录远程主机，那么ssh的安全机制就荡然无存了，这种风险就是著名的`中间人攻击(Man-in-the-middle-attack)`

## ssh安装与启动

ssh分客户端openssh-client和服务端openssh-server

如果你只是想登陆别的机器的ssh，只需要安装openssh-client，如果要使本机开放ssh服务需要安装openssh-server

### 1. 查看电脑上是否已安装了客户端和服务端
```
dpkg -l | grep ssh
```

### 2. 安装
```
apt install openssh-client
apt install openssh-server
```

### 3. 确认ssh-server是否已经启动
```
ps -e | grep ssh
```
出现`ssh-agent`表示ssh-client启动，`sshd`表示ssh-server启动

ssh服务启动、停止、重启：
```
sudo /etc/init.d/ssh start
sudo /etc/init.d/ssh stop
sudo /etc/init.d/ssh restart
```

## ssh的两种登录方式

ssh提供两种方式的验证方式：

- 基于口令的安全验证。只要你知道账号和口令，就可以登录到远程主机。所有传输的数据都会被加密，但是不能保证你正在连接的服务器就是你想连接的服务器。可能会有别的服务器正在冒充真正的服务器，也就是会受到"中间人攻击"
- 基于密钥的安全验证。你需要为自己创建一对密钥，并把公钥放到需要访问的服务器。如果你要连接到ssh服务器，ssh客户端就会向服务器发出请求，请求用你的密钥进行安全验证。服务器收到请求之后，先在该服务器上你的主目录下寻找你的公钥，然后把它和你发送过来的公钥进行比较，如果两个密钥一致，服务器就用公钥加密"质询"并把它发送给客户端软件。客户端软件收到"质询"之后就可以用你的私钥在本地解密再把它发送给服务器完成登录

与第一种级别相比，密钥登录不仅加密所有传输的数据，也不需要再网络上传送口令，因此安全性更高，可以有效防止"中间人攻击"

### 1. 口令登录

ssh 用户名@服务器ip地址：
```
ssh user@192.168.0.1
```

如果需要调用图形界面可以使用`-X`选项
```
ssh -X user@192.168.0.1
```

如果客户机和服务器用户名相同，登录时可以省略用户名

ssh服务的默认端口是22，如果服务器设置了其他的端口，通过`-p`选项修改登录端口：
```
ssh -p 1234 192.168.0.1
```

### 2. 公钥登录

- 1.在本机生成密钥对

  公钥登录之前需要先使用`ssh-keygen`在本地生成密钥对：
  ```
  ssh-keygen -t rsa   # -t表示加密类型，这里使用rsa加密算法
  ```

  然后根据提示一步步按enter即可，执行结束之后会在 **当前用户家目录** 下生成一个 **.ssh文件夹** ，其中包含 **私钥id_rsa** 和 **公钥id_rsa.pub** 

- 2.将公钥复制到远程主机

  使用`ssh-copy-id`命令将公钥复制到远程主机。公钥会被写到远程主机的`~/.ssh/authorized_keys`文件中
  ```
  ssh-copy-id user@192.168.0.1
  ```

经过以上两个步骤，以后登录这个远程主机就不再需要输入密码，也更加安全了

## 其他问题

### 1. ssh登录后使程序脱离终端运行

如果在ssh登录后直接在终端跑一些程序，关闭本地终端窗口后，不管后台程序还是前台程序都会随终端关闭而结束

可以使用`nohup`命令让程序脱离终端，在终端关闭时还能继续运行

```
nohup python3 a.py &
```

### 2. 保持ssh一直连接

如果使用iTerm2，要让ssh不断线：preferences -> profiles -> sessions -> when idel, send ASCII code

其他命令行客户端，可以通过配置`ServerAliveInterval`来实现，在`~/.ssh/config`中写入：
```
Host *
  ServerAliveInterval 60
```
表示ssh客户端每隔60秒给远程主机发送一个no-op包，no-op是无任何操作的意思，这样远程主机就不会关闭这个ssh会话

`Host *`表示连接到所有的远程主机时都保持一直连接，也可以针对某个机器，需要配置为该机器的hostname

### 3. ssh远程操作

ssh不仅可以用于远程主机登录，还可以直接在远程主机上执行操作，例：
```
ssh user@host 'mkdir -p .ssh && cat >> .ssh/authorized_keys' < ~/.ssh/id_rsa.pub
```
单引号中的部分，表示在远程主机上执行的操作；后面的输入重定向，表示数据通过ssh传向远程主机

这就是说，ssh可以在用户和远程主机之间，建立命令和数据的传输通道，因此很多事情都可以通过ssh来完成

下面看几个例子：

- 1. 将`$HOME/src/`目录下的所有文件复制到远程主机的`$HOME/src/`目录
  ```
  cd && tar czv src | ssh user@host 'tar xz'
  ```

- 2. 将远程主机`$HOME/src/`目录下的所有文件，复制到用户的当前目录
  ```
  ssh user@host 'tar cz src' | tar zxv
  ```
- 3. 查看远程主机是否运行进程httpd
  ```
  ssh user@host 'ps ax | grep httpd'
  ```
跨机远程拷贝推荐使用`scp`

### 4. scp跨机远程拷贝

scp命令用法查看[这篇文章](command/scp.md)

### 5. ssh端口操作

- **1. 绑定本地端口**

  既然ssh可以传送数据，那么我们可以让那些不加密的网络连接，全部改走ssh连接，从而提高安全性

  例如，我们要让8080端口的数据，都通过ssh传向远程主机，命令就这样写：
  ```
  ssh -D 8080 user@host
  ```
  ssh就会建立一个socket，去监听本地的8080端口。一旦有数据传到该端口，就自动把它转移都ssh连接上面，发往远程主机，可以想象，如果8080端口原来是一个不加密端口，现在将变成一个加密端口
  
  可以利用`-D`实现科学上网，具体参考 [该教程](https://www.huiyingwu.com/353/) | [科学上网的原理](https://segmentfault.com/a/1190000011485579)

  **注：** windows下可以使用bitvise ssh client工具达到翻墙的效果，具体参考[该教程](https://www.cnblogs.com/plokmju/p/SSH_Chrome_SwitchySharp_BitviseTunnelier.html)

- **2. 本地端口转发**

  假如host1是本地主机，host2是远程主机。由于种种原因，这两台主机之间无法连通。但是还有另外一台host3，可以同时连通前面两台主机，利用ssh本地端口转发可以借助host3连通host1和host2，可以通过在host1运行下面的命令实现：
  ```
  ssh -L 2121:host2:21 host3
  ```

  L参数接收三个值，分别是"本地端口:目标主机:目标主机端口"，它们之间用冒号隔开。这条命令的意思，就是讲本地端口2121的数据通过host3转发到目标主机host2的21端口上

  这样，我们只要连接host1的2121端口，就可以连接host2的ftp服务(假定host2开启ftp服务，且运行于默认端口21上)
  ```
  ftp localhost:2121
  ```

  "本地端口转发"使得host1和host2之间形成了一个数据传输的秘密隧道，因此被称为"ssh隧道"

  举两个有趣的例子：

  - 本地端口和远程端口绑定

    ```
    ssh -L 5900:localhost:5900 host3
    ```

    这表示将本机的5900端口和host3的5900端口绑定(这里的localhost指host3，因为目标主机是相对于host3而言的)

  - host1利用ssh登录host2

    ```
    ssh -L 9001:host2:22 host3
    ```

    这样，只要ssh登录本机的9001端口，就相当于登录host2了

    ```
    ssh -p 9001 localhost
    ```


- **3.  远程端口转发**

  接着看上面那个例子，host1与host2之间无法连通，必须借助host3转发。但是，特殊情况出现了，host3是一台内网机器，它可以连接外网的host1，但是反过来就不行，外网的host1连不上内网的host3，这时，"本地端口转发"就不能用了，怎么办？

  解决办法是，既然host3可以连host1，那么就从host3上建立与host1的ssh连接，然后在host1上使用这条连接就可以了

  在host3上执行下面的命令：
  ```
  ssh -R 2121:host2:21 host1
  ```

  R参数也接收三个值，分别是"远程主机端口:目标主机:目标主机端口"。这条命令的意思，就是让host1监听自己的2121端口，然后将所有数据经由host3，转发到host2的21端口。由于对于host3来说，host1是远程主机，所以这种情况就被称为"远程端口绑定"

  绑定之后，我们就可以在host1中连接host2了：
  ```
  ftp localhost:2121
  ```
  
### 6. ssh其他参数

ssh一般在做隧道与端口转发时，一般还有其它参数配合。

- -f ssh在后台运行，即认证之后，ssh退居后台
- -T 不要分配tty终端
- -N 不要在服务器执行命令
- -C 压缩数据包
- -i 指定认证密钥文件
- -n 将 stdio 重定向到 /dev/null，与-f配合使用
- -p 指定连接端口
- -X Enables X11 forwarding.
- -q 安静模式

一般做隧道和端口转发时，使用`-f`、`-T`、`-N`、`-n`、`-C`选项：
```
ssh -fTNnC -D user@host
```


[参考教程](https://blog.csdn.net/pipisorry/article/details/52269785)

[ssh转发代理：ssh-agent用法详解](https://www.cnblogs.com/f-ck-need-u/p/10484531.html)

O‘RELLY的《SSH: The Secure Shell - The Definitive Guide》

</details>

<details>
<summary>telnet</summary>

</details>

<details>
<summary>gcc</summary>

# GCC

## gcc编译关闭警告

- -w 关闭编译时的任何警告
- -W 只显示编译器认为会出现错误的警告
- -Wall 显示所有警告

</details>

<details>
<summary>wc</summary>

</details>

<details>
<summary>expr</summary>

# expr

expr是一款表达式计算工具，使用它能完成表达式的求值操作

使用expr时要注意，表达式和运算符之间要有空格，例如 `2+2` 是不对的，必须写成 `2 + 2`

expr支持以下操作：

| 运算符 | 说明 | 举例 |
| --- | --- | --- |
| + | 加法 | expr a + b |
| - | 减法 | expr a - b |
| * | 乘法 | expr a * b |
| / | 除法 | expr a / b |
| % | 取余 | expr a % b |
| = | 相等 | expr a = b |
| != | 不相等 | expr a != b |

更多查看`man expr`

</details>

## 操作系统知识

<details>
<summary>进程和线程的区别</summary>

# 进程和线程区别

**核心：进程是资源分配的最小单位，线程是CPU调度的最小单位**

- 进程：
  
  - 进程是资源竞争的基本单位，比如竞争CPU的调度，以及申请内存（物理地址空间）
  - 进程之间相互独立安全性高，如果两个进程之间需要进行（事件通知，数据传输，资源共享，进程控制）那么就需要通过进程间通信（管道，消息队列，共享内存，信号量等）的方式来达成。
  - 进程有自己的内存，通过分页将虚拟地址空间映射到物理地址空间来存储数据 

- 线程：
  
  - 线程是程序运行的最小单位，线程是进程的一个分流（一个进程至少有一个线程）
  - 一个进程内部的多个线程之间共享进程的数据，如果多个线程同时访问临界资源就会存在线程冲突（通过互斥锁来放置线程访问共享资源冲突的问题，有的时候互斥锁会带“死锁”和“饥饿现象”的问题），当然大多数线程内部的数据是单独享有的存储在线程栈上面。
  - 线程共享进程的虚拟地址空间（共享段、数据段）、用户ID和组ID、文件描述符表、当前工作目录、但是线程也私有自己的一部分数据例如一组寄存器（用于线程切换时保存独立硬件上下）、用户栈（保存私有数据）、线程优先级等。

**理解：**
- 资源管理角度：

  资源即计算机里的中央处理器、内存、文件、网络等
  
  进程可以理解为在一定环境下，把静态的程序代码运行起来，通过使用不同的资源来完成一定的任务
  
  进程的环境包括：环境变量、进程掌握的资源：中央处理器、内存、打开的文件、映射的网络端口等


  线程作为进程的一部分，扮演的角色是怎么利用中央处理器去运行代码，线程关注的是中央处理器的运行，而不是其他内存等资源的管理
  
  当只有一个中央处理器时，进程中只需要一个线程，随着多处理器的发展，一个进程可以有多个线程来并行的完成任务
  
  进程和线程不是同一层面的概念，线程是进程的一部分，线程主抓中央处理器执行代码的过程，其余的资源保护和管理由整个进程完成

- CPU任务切换角度：

  CPU轮流执行任务的过程：先加载程序A的上下文，然后开始执行A，保存程序A的上下文，调入下一个要执行的程序B的程序上下文，然后执行B，保存程序B的上下文
  
  所以： 进程就是包括上下文切换的程序执行时间总和 = CPU加载上下文 + CPU执行 + CPU保存上下文
  
  进程的颗粒度太大，每次都要有上下文的调入、保存、调出
  
  如果将进程分为a,b,c三个线程组合而成，执行流程将变为：
  
  程序A得到CPU -> CPU加载上下文 -> 执行程序A的a -> 执行b -> 执行c ->保存A的上下文
  
  也即，线程共享进程的上下文，使得线程切换导致的上下文切换代价更小，是更为细小的CPU时间段
  
  总结：进程和线程都是一个时间段的描述，是CPU工作时间段的描述，不过是颗粒大小不同

- 计算机发展史角度：

  早期计算机只有进程，进程是最基本的运行单位，包含静态的资源和动态的计算，随着计算机性能的提升和系统设计的改进，为了避免进程间调度带来的资源开销，同时提升系统的并发性能，于是在进程中引入了线程的概念，专门来负责程序的动态部分
  
  总之：
  
  - 进程是一个资源的容器，为进程里所有线程提供共享资源，是对程序的一种静态描述
  
  - 线程是计算机最小的调度和运行单位，是对程序的一种动态描述

- 从程序角度：

  - 定义方面：进程是程序在某个数据集合上的一次运行活动；线程是进程中的一个执行路径
  - 角色方面：在支持线程机制的系统中，进程是系统资源分配的单位，线程是系统调度的单位
  - 资源共享方面：进程之间不能共享资源，而线程共享所在进程的地址空间和其它资源。同时线程还有自己的栈和栈指针，程序计数器等寄存器
  - 独立性方面：进程有自己独立的地址空间，而线程没有，线程必须依赖于进程而存在

</details>
