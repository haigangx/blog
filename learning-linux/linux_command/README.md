# Linux命令

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
| `find . -inname *.c` | 查找当前目录下以.c结尾的文件，忽略大小写 |
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
| w                   | 查看谁在线 |
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



- [find](content/find.md)
- [gdb](content/gdb.md)
- [strace](content/strace.md)
- [ltrace](content/ltramd)
- [pstack](content/pstack.md)
- [valgrind](content/valgrind.md)
- [tcpdump](content/tcpdump.md)
- [grep](content/grep.md)
- [tar](content/tar.md)
- [lsof](content/lsof.md)
- [sed](content/sed.md)
- [awk](content/awk.md)
- [scp](content/scp.md)
- [ssh](content/ssh.md)
- [telnet](content/telnet.md)
- [gcc](content/gcc.md)
- [wc](content/wc.md)
- [expr](content/expr.md)
