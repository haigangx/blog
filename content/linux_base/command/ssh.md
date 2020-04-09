# ssh

TODO：ssh协议原理和完整连接过程

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
