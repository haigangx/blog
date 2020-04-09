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