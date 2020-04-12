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

