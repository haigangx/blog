# Linux命令

| 命令 | 效果 |
| --- | --- |
| `ssh -D 7001 -fTNnC root@129.226.69.149` | sock5代理：本地端口7001的数据转发到远程服务器129.226.69.149转发出去 |
| `ssh -CqTnN -L 0.0.0.0:8443:192.168.1.2:443  user@192.168.1.3` | 正向代理：将本地主机的8443端口，通过192.168.1.3转发到192.168.1.2:443 |
| `ssh -CqTnN -R 0.0.0.0:8443:192.168.1.2:443  user@202.115.8.1` | 反向代理：将外网主机（202.115.8.1）端口（8443）转发到内网主机 192.168.1.2:443 |
| `python -m SimpleHTTPServer 8000` | 利用python启动一个简单的本地服务器,root为命令启动目录 |
| <code>history \| awk '{a[$2]++}END{for(i in a){print a[i] " " i}}' \| sort -rn \| head</code> | 列出最常使用的十个命令 |
| `netstat -n | awk '/^tcp/ {++tt[$NF]} END {for (a in tt) print a, tt[a]}'` | 列出所有网络状态：ESTABLISHED/TIME_WAIT/FIN_WAIT1/FIN_WAIT2 |
| `sshfs name@server:/path/to/folder /path/to/mount/point` | 使用ssh挂载远程文件目录到本地 |
| <code>ps aux \| sort -nk +4 \| tail</code> | 显示前十个运行的进程并按内存使用量排序 |
| `while sleep 1;do tput sc;tput cup 0 $(($(tput cols)-29));date;tput rc;done&` | 终端右上角显示时钟 |
| `wget -qO - "http://www.tarball.com/tarball.gz" | tar zxvf -` | 从网络上的压缩文件中解出一个文件夹，并避免保存中间文件 |
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
