# Linux命令

| 命令 | 效果 |
| --- | --- |
| `ssh -D 7001 -fTNnC root@129.226.69.149` | 本地端口7001的数据转发到远程服务器129.226.69.149 |
| `python -m SimpleHTTPServer 8000` | 利用python启动一个简单的本地服务器,root为命令启动目录 |
| **grep** |  |
| `grep -i "the" demo_file` | 文件中查找字符串 |
| `grep -r "ramesh" *` | 在一个文件夹下递归查找包含字符串"ramesh"的文件 |
| `grep -A 3 -i "the" demo_file` | 输出成功匹配的行以及之后的三行 |
| **文件查找** |  |
| `find . -inname *.c` | 查找当前目录下以.c结尾的文件，忽略大小写 |
| `find / -size +500M -print0 | xargs -0 du -m|sort -nr` | 查找500M以上的大文件，按文件大小排序输出 |
| `find -iname "MyProgram.c" -exec md5sum {} \` | 对找到的文件执行某个命令 |
| `find ~ -empty` | 查找家目录下的空文件 |
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
| `objdump -x xxx.so | grep NEEDED` | linux查看依赖的库 |
| `objdump -x 可执行程序名 | grep NEEDED` | 查看可执行程序依赖的库 |
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
