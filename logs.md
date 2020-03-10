# Log

## 日常问题

<details>
<summary>github+docsify管理个人笔记</summary>

# github+docsify管理博客和笔记

## docsify

进度：移完effective c++

## 参考文档

[docsify-生成文档网站简单教程](https://segmentfault.com/a/1190000017576714)

</details>

<details>
<summary>chrome从本地安装插件</summary>

# 解决新版谷歌浏览器不能安装本地CRX插件文件

参考文档：[How to install Chrome extensions manually](https://www.cnet.com/how-to/how-to-install-chrome-extensions-manually/)

## 步骤：

- 谷歌浏览器中进入 **chrome://extensions** ，然后选中右上方的 **Developer mode** 开启开发者模式。
- 解压CRX插件文件，最简单的办法：将插件文件拓展名改为zip或者rar，然后解压即可，如果这种办法不行可以使用 [CRX Extractor](http://crxextractor.com/) 上传CRX文件得到相应的zip文件并且解压。
- 回到谷歌浏览器 **chrome://extensions** 窗口下，点击 **load unpacked** 然后选择插件解压的目录即可安装该插件。

</details>

<details>
<summary>刚装完新Ubuntu需要做的事</summary>

## when you install a new ubuntu 


[TOC]

### 0.[install sogou](http://blog.csdn.net/iamplane/article/details/70447517)

建议直接安装ibus-pinyin，搜狗装完有乱码问题
```
sudo apt install ibus-pinyin
```
安装完进入设置->Region&Language->Input Sources中，点击+号，选择chinese添加intelligent Pinyin

```
记住安装完成后要在Ubuntu开机启动项中去掉fcitx，否则每次开机后会出现两个输入法
* sudo add-apt-repository ppa:fcitx-team/nightly && sudo apt update 
* sudo apt install fcitx fcitx-config-gtk fcitx-table-all im-switch 
* download and install sogou.deb
ls
```

### 1.Linux交换ctrl和caps

```
setxkbmap -option "ctrl:swapcaps"
```

### 2.源码安装libevent时出现error: 'CLOCK_REALTIME' undeclared

```
在event.c中添加头文件time.h
```

### 3.[Ubuntu双显卡问题](http://blog.csdn.net/liufunan/article/details/52090382)

### 4.[vim bundle插件安装](https://www.baidu.com/link?url=fjgYKY0AYp1bG7LRNdQfArXezKyQ0FtkI_0CTJKopxm3wZR2-mDkUBcJQiiimJrZPtAKk0FQdiGp2R48Sbd2Ka&wd=&eqid=e251922f00009d9c0000000359819670)
  [neocomplete插件](https://github.com/Shougo/neocomplete.vim)

### 5.git连接远程库

```
ssh-keygen -t rsa -C "754657908@qq.com"
ssh git@github.com
git remote add origin git@github.com:lhgaaa/xxxx
git pull origin master
```

### 6.ubuntu下翻墙

提前准备好vps

服务端和客户端都需要安装shadowsocks：

```
shadowsocks安装：sudo apt install shadowsocks
```

服务端配置：

```
1.vim编辑/etc/shadowsocks/config.json,服务端需要配置"server","server_port","password"
  设置server项时注意如果填服务器公网IP报bind(errno99)错误，将server设为0.0.0.0即可
2.启动服务：ssserver -c /etc/shadowsocks/config.json
Note:
进程脱离终端运行：setsid ssserver -c /etc/shadowsocks/config.h
```

客户端配置：

```
1.vim编辑/etc/shadowsocks/config.json,客户端需要配置"server","server_port","local_address","local_port","password"
2.启动服务：sslocal -c /etc/shadowsocks/config.json
```

辅助工具：

1.浏览器代理工具：利用SwitchyOmega插件配合shadowsocks智能翻墙

```
启动shadowsocks： sslocal -c /etc/shadowsocks/config.json
下载SwitchyOmega插件：https://github.com/FelisCatus/SwitchyOmega/releases
SwitchyOmega安装教程：https://github.com/FelisCatus/SwitchyOmega/wiki/GFWList
```

2.proxychains:代理工具

```
安装proxychains:sudo apt install procychains
配置:vim编辑配置文件/etc/proxychains.conf，最后一行改为"sock5 127.0.0.1 1080"
用法：命令行 procychains command
```

3.privoxy:全局代理工具

```
安装:sudo apt install privoxy
配置:sudo vim /etc/privoxy/config

	 添加如下两行：
	 
	listen-address localhost:8118
	forward-socks5t / 127.0.0.1:1080 
	.
	然后执行如下命令：
	
	sudo privoxy --user privoxy /etc/privoxy/config
	
	编辑profile文件并添加配置：
	
	sudo vim /etc/profile
	export http_proxy=http://127.0.0.1:8118
	export https_proxy=http://127.0.0.1:8118
	export ftp_proxy=http://127.0.0.1:8118
	source /etc/profile

	
开关:开启/关闭/状态  sudo systemctl start/stop/status privoxy.service
    
    关闭开机启动：
        sudo systemctl disable privoxy.service

    取消http_proxy和https_proxy环境变量配置：
      本来删除配置行即可，但是因为我忘了当初在哪个文件设置这两个环境变量了，所以不得不采用下面的方法：
        如果是bash: ~/.bashrc中 export http_proxy="" export https_proxy=""
        如果是zsh: ~/.bashrc换成~/.zshrc
```



### 7.安装wps时，libpng12-0依赖问题。

```
下载libpng12并安装即可：https://packages.debian.org/zh-cn/wheezy/amd64/libpng12-0/download
```

### 8.[lftp命令](http://man.linuxde.net/lftp)


### 9.ubuntu16.04安装谷歌浏览器：

```
sudo wget http://www.linuxidc.com/files/repo/google-chrome.list -P /etc/apt/sources.list.d
wget -q -O - https://dl.google.com/linux/linux_signing_key.pub  | sudo apt-key add -
sudo apt-get update 
sudo apt-get install google-chrome-stable
```

### 11.修改Ubuntu下挂载硬盘后的名字/media/user/A

```
打开Ubuntu的Dash，搜索disk打开，在左边栏选中要修改的硬盘，先umount,点击设置按钮，在编辑文件系统中输入新的硬盘名。
```

### 12.Ubuntu完全卸载libreOffice

```
sudo apt-get remove --purge libreoffice*
```

### 13.starDict离线词典安装
参考文章：
[zh_CN简体中文词典](http://download.huzheng.org/zh_CN/)
[ubuntu安装stardict并导入词典](http://blog.163.com/green_pool/blog/static/101915526201231211343824/)

```
将离线词典下载下来解压后得到的.dict.dz, .idx, .info文件放到~/.stardict/dic下
```
### 14.ubuntu安装monaco字体

```
wget https://github.com/fangwentong/dotfiles/raw/master/ubuntu-gui/fonts/Monaco.ttf
sudo mkdir -p /usr/share/fonts/custom
sudo mv Monaco.ttf /usr/share/fonts/custom
sudo chmod 744 /usr/share/fonts/custom/Monaco.ttf

sudo mkfontscale  #生成核心字体信息
sudo mkfontdir
sudo fc-cache -fv
```

### 15.ubuntu18显示状态栏网速

```
sudo add-apt-repository ppa:fossfreedom/indicator-sysmonitor 
sudo apt-get install indicator-sysmonitor
```

### 16.ubuntu18搜狗输入法乱码问题

不能登录个人中心，登录将导致重新乱码

```
cd ~/.config
sudo rm -fr SogouPY* sogou*
```

[可参考文章](http://blog.csdn.net/fuchaosz/article/details/51882935)


### 17.github下载或者访问过慢解决办法

```
1.访问网址：http://tool.chinaz.com/dns/ 分别查询
  github.com
  github.global.ssl.fastly.net
  两个网址的IP地址
2.将IP和域名映射写入/etc/hosts文件末尾中：
  xx.xx.xx.xxx github.com
  xx.xx.xx.xxx github.global.ssl.fastly.net

```

### 18.[ubuntu18.04 网易云音乐安装后无法点击图标打开](https://www.jianshu.com/p/cfa2c46b2e04)

- 修改/etc/sudoers

  ```
  sudo vim /etc/sudoers
  username ALL=NOPASSWD: /usr/bin/netease-cloud-music
  username为你登录的用户名，如lhgaaa
  ```
- 修改桌面程序

  ```
  sudo vim /usr/share/applications/netease-cloud-music.desktop
  修改Exec=netease-cloud-music %U 为 Exec=sudo netease-cloud-music %U
  ```

### 18.ubuntu修复中文字体渲染问题

参考[这篇文章](https://www.synscope.com/1015/ubuntu%E4%BF%AE%E5%A4%8D%E4%B8%AD%E6%96%87%E5%AD%97%E4%BD%93%E6%B8%B2%E6%9F%93%E9%97%AE%E9%A2%98/)

</details>

<details>
<summary>使用apt禁止某些软件更新</summary>

# apt upgrade前，指定某些软件不更新
以wps-office为例：

1、查看wps-office的软件包状态
```
    sudo dpkg --get-selections | grep wps
```
2、锁定wps-office不更新
```
    sudo echo "wps-office hold" | dpkg --set-selections
```
3、查看当前以锁定的软件包
```
    sudo dpkg --get-selections | grep hold
```

此时，可以放心执行apt upgrade更新软件了

</details>

<details>
<summary>cp拷贝.隐藏文件</summary>

# cp命令拷贝隐藏文件

要拷贝test目录下.123文件到test2

```
cp test/. test2
```
拷贝隐藏文件`test/`后要加`.`

</details>

<details>
<summary>黑苹果安装总结</summary>

# 黑苹果

## 安装 & 驱动 & 硬件

### 1、AR9285 驱动？
驱动地址：[下载](https://github.com/lhgaaa/learning_log/blob/master/log/doc/kext/IO80211Family.kext.zip)

用法：直接拖进/System/Library/Extensions文件夹，再运行KEXT UTILITIES重建驱动缓存

### 2、HHKB Pro2 无法使用cmd键？
  
-  1.安装驱动，安装一路确定即可，驱动下载 [Github](https://github.com/lhgaaa/learning_log/blob/master/log/doc/kext/HHKBProMac64_201808.dmg) | [官网](http://www.pfu.fujitsu.com/hhkeyboard/macdownload.html)

- 2.sw2开，其他全关
- 3.需要重启，拔插键盘

### 3. 黑苹果关闭ISP系统完整性保护

查看ISP开关状态：

> 系统偏好设置 -> 关于本机 -> 系统报告 -> 软件

打开Colver Configurator编辑config.list：

> Clover Configurator -> Rt Variables -> CsrActiveConfig

```
csr-active-config 0x0 = SIP Enabled (Default)
csr-active-config 0x3 = SIP Partially Disabled (Loads unsigned kexts)
csr-active-config 0x67 = SIP Disabled completely
```

 CsrActiveConfig改为0x67，重启

## 软件 & 使用

### 1、[安装HomeBrew和更新源](https://www.jianshu.com/p/9592826c254b)

### 2、

</details>

<details>
<summary>书单</summary>

## Vim

- [Vim实用技巧](https://book.douban.com/subject/26967597/)
- [Hacking Vim](https://github.com/wuzhouhui/hacking_vim)
- [笨方法学Vimscript](http://learnvimscriptthehardway.onefloweroneworld.com/)
  
## Go

- [Go语言圣经](https://github.com/golang-china/gopl-zh)

## 算法和数据结构：    

- 《算法导论》
- 《算法》第四版
- 《编程珠玑》


## 计算机系统：  

- 《深入理解计算机系统》  
- 《程序员的自我修养-编译、链接、库》

## 数据库：  

- 《MySQL必知必会》  
- 《高性能MySQL》  
- 《MySQL技术内幕》  
- 《redis设计与实现》  
- 《redis实战》  

## 计算机网络：  

- 《TCP/IP详解》  
- 《计算机网络》  
- 《图解TCP/IP》  
- 《图解HTTP》  
-   [网络基本功系列](https://wizardforcel.gitbooks.io/network-basic/index.html)

## 分布式：  

- 《大规模分布式存储系统》  
- 《分布式系统原理介绍》  

## Linux：  

- 《The Linux Command Line》  

## Git：

- 《progit》

## Linux服务器编程：  

- 《APUE》  
- 《Linux高性能服务器编程》  
- 《Linux多线程服务端编程》  
- 《Lievent源码深度剖析》  
  
## C/C++:  

- 《c++ primer》  
- 《c++ 标准程序库》  
- 《effective c++》   
- 《STL源码剖析》  
- 《Boost库》  
- 《深度探索C++对象模型》
- 《大规模C++程序设计》
- 《泛型程序设计与STL》

## Python：  

- 《Python学习手册》  
- 《Python Cookbook》  

## Go: 

## Lisp：  

- 《计算机程序的构造与解释》  

## 设计模式与软件工程：  

- 《设计模式-可复用面向对象软件的基础》
- 《敏捷软件开发-原则、模式与实践》
- 《重构》
- 《人月神话》

## 编程规范： 

- 《Google编程规范》
 
## 正则表达式：

- 《正则表达式必知必会》

## 安全：  

## 程序员数学：  

- 《计算机程序设计艺术1234》  
- 《具体数学》
 
## other:  

- 《编译原理》
  
## 算法题修炼：  

- 《编程之美》  
- 《LeetCode》  
- 《剑指offer》  
- 《计算机程序设计艺术》

</details>

<details>
<summary>flag</summary>

阶段一：讲Anki中内容整理到Github

- focusing：整理Linux服务器编程内容到linux/server_dev/下

阶段二：完成C++部分主要内容，包括Effective_C++、深度探索C++对象模型、C++11

       持续完成

阶段三：完成算法部分主要内容，包括LeetCode冲刺、基础算法和数据结构、Cy2018

       持续完成，后续每日至少一道leetcode，白天解决，晚上编码总结

阶段四：C++后台开发项目
 - https://github.com/yedf/handy
 - https://github.com/linyacool/WebServer
 - https://github.com/balloonwj/flamingo
 - https://www.shiyanlou.com/courses/565
 - 实验楼


## 思考
- C++、操作系统是摩天大厦的基石，是安身立命的资本，是退无可退的后路
- 数据结构是水泥，加固摩天大厦的基石
- python，go等是基石上的建筑，只有基石够稳，够宽广，建筑才能又高又大
- 现如今，努力加固基石80%，学习如何建筑20%

</details>

<details>
<summary>chrome必备插件</summary>

# chrome必备插件

## 

- [OneTab](https://chrome.google.com/webstore/detail/onetab/chphlpgkkbolifaimnlloiipkdnihall)
  一键保存当前所有tab页，下次一键恢复所有保存的tab页
- [Proxy SwitchyOmega](https://chrome.google.com/webstore/detail/proxy-switchyomega/padekgcemlokbadohgkifijomclgjgif)
  翻墙、代理必备
- [Saladict沙拉查词](https://saladict.crimx.com/)
  特别好用的查词插件
- [Vimium](https://chrome.google.com/webstore/detail/vimium/dbepggeogbaibhgnhhndojpepiihcmeb)
  浏览器中使用vim快捷键

## Github

- [GITHUBER](https://chrome.google.com/webstore/detail/githuber-%E5%BC%80%E5%8F%91%E8%80%85%E7%9A%84%E6%96%B0%E6%A0%87%E7%AD%BE%E9%A1%B5/janmcneaglgklfljjcpihkkomeghljnf)
  新标签页显示Github Trending
- [Octotree](https://chrome.google.com/webstore/detail/octotree/bkhaagjahfmjljalopjnoealnfndnagc/related?hl=en-US)
  侧边栏显示GitHub库中文件目录

</details>

<details>
<summary>vmware网络连接模式——桥接、NAT、仅主机模式</summary>

# vmware网络连接模式——桥接、NAT、仅主机模式

| Mode      | VM->Host | VM<-Host | VM1<->VM2 | VM->Net/LAN | VM<-Net/LAN |
|-----------|----------|----------|-----------|-------------|-------------|
| Host-only | + | + | + | - | - |
| Internal | - | - | + | - | - |
| Bridged | + | + | + | + | + |
| NAT | + | Port forward | - | + | Port forward |
| NATservice | + | Port forward | + | + | Port forward |

[vmware网络连接模式——桥接、NAT、仅主机模式](https://blog.51cto.com/sharemi/1790733)

</details>

<details>
<summary>利用硬链接备份配置文件</summary>

# 使用硬链接备份配置文件

使用Linux做开发时，要配置好一个顺手的环境需要大量的配置文件，如果迁移到一个新的机器上开发，重新建立一个开发环境很不容易，所以我选择 **将这些配置文件备份到github上**。

但是实际开发中，由于配置文件分布比较分散，将这些配置文件统一拷贝到一个文件夹下定时同步更改并上传到github属实麻烦，幸运的是可以利用创建硬链接的办法化繁为简

**为每个配置文档在一个固定的目录下生成一个硬链接，将这个目录备份到github，每次当你对某个配置文档做出更改时，都会实时反映到备份的目录中，不需要手动同步，只需要定时上传即可，非常方便**

关于Linux下硬链接的知识，参考[这篇文章]()

</details>

## Linux

<details>
<summary>Ubuntu安装Albert</summary>

# Ubuntu18.04安装Albert

## 介绍

**Albert** 类似于windows上的 **Everything+wox** ，可以通过快捷键呼出窗口来查找应用程序或者文件。

## 安装

**Albert** [github项目地址](https://github.com/albertlauncher/albert) ，参照项目文件中的安装方法即可安装成功。下面是可参考的简化的安装过程。

- 首先需要导入相关的key文件：

  ```shell
  wget -nv -O Release.key \
    https://build.opensuse.org/projects/home:manuelschneid3r/public_key
  apt-key add - < Release.key
  apt-get update
  ```

- Ubuntu18.04按照下面的方法安装：

  ```shell
  sudo sh -c "echo 'deb http://download.opensuse.org/repositories/home:/manuelschneid3r/xUbuntu_18.04/ /' > /etc/apt/sources.list.d/home:manuelschneid3r.list"
  sudo apt-get update
  sudo apt-get install albert
  ```

</details>

<details>
<summary>Ubuntu环境变量查找顺序</summary>

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

</details>

<details>
<summary>安装tldr终端查看命令用法示例</summary>

# tldr

在终端显示linux命令的用法

[Github地址](https://github.com/raylee/tldr)
  |  [Alfred workflow for tldr](https://github.com/cs1707/tldr-alfred)

## 安装

```
mkdir -p ~/bin
curl -o ~/bin/tldr https://raw.githubusercontent.com/raylee/tldr/master/tldr
chmod +x ~/bin/tldr
```

添加`~/bin`到`$PATH`中，向`~/.bashrc`(OSX)，`~/.bashrc`(Linux)或`~/.zshrc`(zsh)中写入:

```
export PATH="$PATH:~/bin"
```

输入tldr按tab自动补全命令,向上述同一个文件写入：
```
complete -W "$(tldr 2>/dev/null --list)" tldr
```

## 用法

- -h 查看帮助

## 更多配置

添加到上面同一个配置文件中：

```
export TLDR_HEADER='magenta bold underline'
export TLDR_QUOTE='italic'
export TLDR_DESCRIPTION='green'
export TLDR_CODE='red'
export TLDR_PARAM='blue'
```
可用的参数有：black, red, green, yellow, blue, magenta, cyan, white, onblue, ongrey, reset, bold, underline, italic, eitalic, default

</details>

<details>
<summary>Linux历史命令</summary>

# Linux历史命令

history [选项][历史命令保存文件]

- -c 清空历史命令
- -w 将缓存中的历史命令写入~/.bash_history

历史命令默认保存1000条，可以在环境变量配置文件/etc/profile中修改

- !n 返回第n条历史命令
- !! 返回上一条命令
- !xxx 重复执行最后一条以该字符串开头的命令

</details>

<details>
<summary>使用trash代替rm</summary>

</details>


<details>
<summary>关闭Ubuntu桌面GUI</summary>

# 关闭Ubuntu桌面GUI

在虚拟机中安装了Ubuntu，但是用不到桌面环境，为了避免桌面环境的资源浪费，可以选择安装Server版本，还可以选择关闭桌面环境

永久关闭
```
sudo systemctl set-default multi-user.target
```

永久开启
```
sudo systemctl set-default graphical.target
```

临时开启
```
sudo service lightdm start
```

临时关闭
```
sudo service lightdm stop
```

</details>

## Mac

<details>
<summary>Mac os使用心得</summary>

# Mac

## Mac软件：

Mac破解软件社区：[风云社区](https://www.scoee.com/) | [软件sos](https://www.rjsos.com/mac)

### Mac终端：
  - 终端软件安装：Homebrew
  - 终极Shell解决方案：iTerm2 + oh-my-zsh + zsh +powerlevel9k

### 版本控制Git相关软件：[知乎](https://www.zhihu.com/question/351316529/answer/864704092)
  - Git & Tower Git
  - Github客户端：Github For Mac
  - Git分支管理
    - Source Tree
    - Fork
    - smart git
    - sublime merge
  - Github项目交流：Gitter
  
### 开发工具、文档
 - IDE：XCode、JetBrains系列：GoLand、CLion、DataGrip、PyCharm、Rider、WebStorm、PhpStorm、IntelliJ IDEA、AppCode
 - 开发文档合集：Dash
 
### 办公、效率
  - 思维导图：MindNode
  - 快捷键提示：CheatSheet
  - 截图：Xnip
  - WorkFlow效率神奇：Alfred
  - 程序启动，文件查找：LaunchBar [下载](https://sspai.com/post/36732)
  
### 信息获取
 - RSS订阅：reeder | [app store 下载](https://apps.apple.com/cn/app/reeder-3/id880001334?mt=12)
 - 新浪微博客户端：Maipo | [app store 下载](https://apps.apple.com/cn/app/weibox/id789066512?mt=12)
    
### 文件操作：
  - 文件比较：DiffMerge | [下载](http://www.sourcegear.com/diffmerge/downloads.php)
  - PDF阅读：SKim | [下载](https://sourceforge.net/projects/skim-app/)
  - 全盘扫描、查找大文件：DaisyDisk
  
### 系统监控、管理、增强：
  - 菜单栏监控：iStat Menus
  - 强大的清理软件：clean my mac
  - 卸载软件、免费、替代clean my mac： app cleaner| [app store 下载](https://apps.apple.com/cn/app/app-cleaner-find-remove-applications/id1013897218?mt=12)
  - Mac管理安卓手机：Smartfinder | [下载](https://www.smartisan.com/apps/#/handshaker)
  - 免费NTFS工具：Mounty for NTFS | [官网](https://mounty.app)
  - 密码管理：1Password
  - 简化复制粘贴：PopClip
  - 快速切换和打开应用程序：Manico
  - 增强资源管理器：XtraFinder
  - 状态栏图标管理：Bartender
  - finder下快速进入Shell：go2shell
  - 终端下管理app store中没有的非终端软件：Homebrew Cask
  - 窗口管理，实现如Windows一样的窗口拖拽操作：Cinch
  - 免费窗口管理：magent
  - 钟表屏幕保护程序：fliqlo
  

## [Mac快捷键](https://support.apple.com/zh-cn/HT201236)

## Mac技巧

### 将iterm2打造成guake

我想设置一个快捷键假设为F12，在任意场合，我按一下快捷键F12就弹出终端，输入一些命令执行后，再按一下F12终端就自动隐藏，这对经常使用终端的人，例如经常ssh连接服务器的人来说实在太方便了。

设置过程如下：
- 系统已经默认将F12分配给Show Dashboard，需要先取消这个设置。打开System Preferences，选择Keyboard，切换到Shortcuts这个Tab下，点击Mission Control，取消对应F12的快捷键。

- 打开iTerm的Preferences...， 在ProfilesTab里面，点击下面的[+]添加一个新的profile，为什么要新建一个profile？答案是为了定制将来弹出的终端样式和大小等等参数。新的profile假设命名为guake，(注：guake这个名称是为了向Linux下的Guake终端致敬)，你可以自己任意起个名称，下面会用到。

- 再切换到WindowTab下，将Style，Screen和Space这3个值分别设置为Fullscreen、Main Screen、All Spaces。再切换到KeysTab下，将Hotkey设置为F12，profile设置为guake。现在你按下F12，就立即得到一个占满全屏的黑色命令行终端，再按一下F12隐藏终端，非常的方便。

### Hot Corners(触发角)

系统内置的功能：Hot Corners（触发角）。它藏在屏保的设置里：系统设置-桌面与屏幕保护程序-触发角。设置成功后，只要移动鼠标碰一下屏幕的四个角落，就能触发一些已经设置好的功能，比如回到桌面（Desktop）、进入屏保（Start Screen Saver）。

### 删除启动器中已卸载应用的图标

- 打开Finder，前往/private/var/folders目录，在folader目录下搜索:com.apple.dock.launchpad，进入com.apple.dock.launchpad目录
- 当前目录打开终端，输入下面命令，xxx是要删除的程序名，注意要区分大小写
  ```
  cd db
  splite3 db "delete from apps where title='xxx';" && killall Dock
  ```

## 安装brew并替换国内源

替换国内源：
https://www.cnblogs.com/qcwblog/p/11178283.html

## 翻墙

### Ss

- Mac Gui客户端

  [ShadowsockX-NG](https://github.com/shadowsocks/ShadowsocksX-NG/releases/)
  
- 免费账号地址

  [free-ss.site] | [网站](https://free-ss.site/) | [项目地址](https://github.com/free-ss/free-ss.site)

### Shadowsocksr

- Mac Gui客户端

  [ShadowsocksX-NG-R8](https://github.com/qinyuhang/ShadowsocksX-NG-R/releases)
  
  查看log：~/Library/Logs/ss-local.log


### [V2ray](https://www.v2ray.com)

- Mac Gui客户端

  [V2rayX](https://github.com/Cenmrev/V2RayX/releases)

  [V2rayU](https://github.com/yanue/V2rayU/releases)：可以添加订阅

### 免费ssr/v2ray订阅

Telegram群：https://t.me/SSRSUB

</details>

<details>
<summary>Mac os安装使用homebrew</summary>

# Mac安装并使用homebrew

## 介绍homebrew和homebrew cask

- brew
主要用来下载命令行下的工具和第三方开发库

- brew cask
下载已经编译好的带图像界面的软件(.dmg/.pkg)，下载后自动安装，可以在lanuchpad启动

## 安装 & 卸载

### homebrew安装

```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

### homebrew卸载

```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/uninstall)"
```

### homebrew cask安装

```
brew tap phinze/homebrew-cask
brew install brew-cask
```

### homebrew cask卸载

```
brew uninstall brew-cask
```

## 更换为国内镜像源

### 替换homebrew默认源

```
cd "$(brew --repo)"
# 中国科大:
git remote set-url origin https://mirrors.ustc.edu.cn/brew.git
# 清华大学:
git remote set-url origin https://mirrors.tuna.tsinghua.edu.cn/git/homebrew/brew.git
```

### 替换homebrew-core.git:

```
cd "$(brew --repo)/Library/Taps/homebrew/homebrew-core"
# 中国科大:
git remote set-url origin https://mirrors.ustc.edu.cn/homebrew-core.git
# 清华大学:
git remote set-url origin https://mirrors.tuna.tsinghua.edu.cn/git/homebrew/homebrew-core.git
```

### 替换homebrew-cask源:

```
cd "$(brew --repo)/Library/Taps/homebrew/homebrew-cask"
git remote set-url origin git://mirrors.ustc.edu.cn/homebrew-cask.git
```

### 替换homebrew-bottles:

**Note:** zsh将`~/.bash_profile`换为`~/.zshrc`
```
# 中国科大:
echo 'export HOMEBREW_BOTTLE_DOMAIN=https://mirrors.ustc.edu.cn/homebrew-bottles' >> ~/.bash_profile
source ~/.bash_profile
# 清华大学:
echo 'export HOMEBREW_BOTTLE_DOMAIN=https://mirrors.tuna.tsinghua.edu.cn/homebrew-bottles' >> ~/.bash_profile
source ~/.bash_profile
```

### 应用生效:

```
brew update
```

## 恢复到官方源

```
# 重置brew.git:
cd "$(brew --repo)"
git remote set-url origin https://github.com/Homebrew/brew.git

# 重置homebrew-core.git:
cd "$(brew --repo)/Library/Taps/homebrew/homebrew-core"
git remote set-url origin https://github.com/Homebrew/homebrew-core.git
```


## 使用

- brew -h 查看brew命令

- brew cask -h  查看brew cask命令

- cakebrew 可视化homebrew安装工具
```
brew cask install cakebrew
```

</details>

<details>
<summary>Mac上安装gitbook并发布到github</summary>

# Mac使用Gitbook并发布到Github

## 安装Gitbook

- 安装Nodejs：
  
  [官网安装](https://nodejs.org/en/)

  安装完输入`node -v`测试安装是否成功

  npm切换到国内源，切换方法：[🔗](https://www.jianshu.com/p/66f97cadd1eb)

- 安装Gitbook和命令行工具 -g代表全局安装
  ```
  sudo npm install gitbook-cli -g
  sudo npm install gitbook -g
  //测试安装是否成功
  gitbook -V  
  gitbook --version
  ```

- 更新gitbook命令行工具
  ```
  sudo npm update gitbook-cli -g
  ```

- 卸载gitbook命令行工具
  ```
  sudo npm uninstall gitbook-cli -g
  ```

## 使用gitbook

- 创建mygitbook文件夹
  ```
  mkdir mygitbook && cd mygitbook
  ```

- 初始化gitbook工作目录，创建必要的文件
  ```
  gitbook init
  # README.md  - 项目的介绍都写在这个文件
  # SUMMARY.md  - Gitbook的目录结构在这里配置
  ```

- 编辑目录结构

- 目录建好之后在根目录下执行命令，只支持2级目录
  ```
  gitbook init
  ```

- 编写gitbook内容，重新编译
  ```
  gitbook build
  ```

- 在根目录执行命令，启动服务
  ```
  gitbook serve
  ```

- 插件Calibre可生成电子书
  ```
  gitbook mobi ./ ./MyFirstBook.mobi
  ```
  
### 推送到Github

- 建立Git仓库，在仓库内创建gitbook

  ```
  mkdir gitbook_test & cd gitbook_test
  git init
  gitbook init //创建README.md  SUMMARY.md
  # 编写目录结构
  gitbook init //构建层级结构
  # 编写gitbook内容
  gitbook build
  # 创建gh-pages分支
  git checkout --orphan gh-pages
  
  //将_book目录中的内容复制到_book外，只提交_book内容
  git push -u origin gh-pages
  ```

### 参考

[将Gitbook上的书籍发布在GitHubPages上](https://blog.csdn.net/meiko_zhang/article/details/81350924)

</details>

<details>
<summary>网络资源</summary>

- Github

  - [github中文榜](https://github.com/kon9chunkit/GitHub-Chinese-Top-Charts) 
  - [程序员的英语学习指南](https://github.com/yujiangshui/A-Programmers-Guide-to-English)

- [孟岩的博客](https://blog.csdn.net/myan)

  - [技术路线的选择重要但不具有决定性](https://blog.csdn.net/myan/article/details/3247071)

- [张云龙的个人博客](https://github.com/fouber/blog)
  - [一个程序员的成长之路](https://github.com/fouber/blog/issues/41)

- [酷壳-陈皓的博客](https://coolshell.cn/)

  - [打造高效的工作环境-SHELL篇](https://coolshell.cn/articles/19219.html?utm_source=tuicool&utm_medium=referral)
  - [应该知道的Linux技巧](https://coolshell.cn/articles/8883.html)
  - [awk简明教程](https://coolshell.cn/articles/9070.html?utm_source=tuicool&utm_medium=referral)
  - [sed简明教程](https://coolshell.cn/articles/9104.html?utm_source=tuicool&utm_medium=referral)
  - [你可能不知道的shell](https://coolshell.cn/articles/8619.html)
  - [28个UNIX/LINUX的命令行神器](https://coolshell.cn/articles/7829.html)

- [阮一峰的网络日志]()

  - [ssh原理与运用一](https://www.ruanyifeng.com/blog/2011/12/ssh_remote_login.html)
  - [ssh原理与运用二](http://www.ruanyifeng.com/blog/2011/12/ssh_port_forwarding.html)
  - [数字签名是什么？](http://www.ruanyifeng.com/blog/2011/08/what_is_a_digital_signature.html)
  - [容错，高可用和灾备](http://www.ruanyifeng.com/blog/2019/11/fault-tolerance.html)
  - [信息论入门教程](http://www.ruanyifeng.com/blog/2019/08/information-theory.html)

- [守望的个人博客：公众号编程珠玑](https://www.yanbinghu.com/)

- Linux内核

  - Linux内核设计与实现
  - 深入理解Linux内核
  - 鸟哥的Linux私房菜[网页版](http://cn.linux.vbird.org/) | [gitbook第四版](https://wizardforcel.gitbooks.io/vbird-linux-basic-4e/content/index.html)
  - [网络基本功]( )

- C++

  - [怎样才是一个基本水平的c++程序员？ - 一定要瘦啊的回答 - 知乎](https://www.zhihu.com/question/51907924/answer/128509092)

- 算法和数据结构

  - [算法可视化VISUALGO](https://visualgo.net/zh)
  - [Data Structure Visualizations](https://www.cs.usfca.edu/~galles/visualization/Algorithms.html)
  - [Algorithms Visualizer](https://algorithm-visualizer.org/)

- 开发学习经验

  - [C++后台开发学习路线(已签腾讯sp，附学习资料)](https://zhuanlan.zhihu.com/p/61457047)
  - [Linux C/C++学习路线(已拿腾讯，百度offer)](https://www.itcodemonkey.com/article/14737.html)
  - [C++后台开发/云计算方向，offer收割机的学习路线](https://zhuanlan.zhihu.com/p/65432202)
  - [谷歌面试自学手册(中文)](https://github.com/jwasham/coding-interview-university/blob/master/translations/README-cn.md)
  - [后端架构师技术图谱](https://github.com/xingshaocheng/architect-awesome)


</details>

