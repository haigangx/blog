# Powerlevel9k

Powerlevel9k是zsh的一个主题

[Github地址](https://github.com/Powerlevel9k/powerlevel9k)

Powerlevel9k使用一段时间之后发现当工作路径较长时，打印需要很长时间，所以现在使用[Powerlevel10k](https://github.com/romkatv/powerlevel10k)，Powerlevel9k的配置在Powerlevel10k下不用修改可以直接使用，相比之下，10k在使用时更加流畅，无卡顿

## 安装

更详细的安装过程[参考这里](https://github.com/Powerlevel9k/powerlevel9k/wiki/Install-Instructions)

本例的前提是安装好oh-my-zsh，然后一句命令搞定安装：

```
git clone https://github.com/bhilburn/powerlevel9k.git ~/.oh-my-zsh/custom/themes/powerlevel9k
```

设置zsh主题，在`~/.zshrc`中写入：

```
ZSH_THEME="powerlevel9k/powerlevel9k"
```

在`~/.zshrc`中配置主题时，主题要把原来的`ZSH_THEME`注释掉

如果提示终端色彩不够256色，则继续在`~/.zshrc`中加入：

```
# 记住此条配置一定要加在~/.zshrc的最顶部所有配置之前
export TERM="xterm-256color" 
```

如果安装完终端有乱码问题，则需要安装powerline字体，安装如下：

```
git clone git@github.com:supermarin/powerline-fonts.git 
```

从github下载字体之后，视具体平台安装字体即可，安装完设置到终端乱码即消失

其他情况下安装参考github地址

## 配置

### 命令行样式自定义

样式自定义详细说明[参考这里](https://github.com/Powerlevel9k/powerlevel9k/wiki/Stylizing-Your-Prompt)

以下配置信息都是要配置到`~/.zshrc`中，主要配置如下：
```
# 命令行显示两行，且右侧元素显示在第二行
POWERLEVEL9K_PROMPT_ON_NEWLINE=true
POWERLEVEL9K_RPROMPT_ON_NEWLINE=true

# 左侧的元素也分两行显示，使用newline分割两行，可自定义划分位置
POWERLEVEL9K_LEFT_PROMPT_ELEMENTS=(dir newline vcs)

# 新命令行之前必输出一个空行
POWERLEVEL9K_PROMPT_ADD_NEWLINE=true

# 关闭右侧元素显示
POWERLEVEL9K_DISABLE_RPROMPT=true

# 设置终端亮色主题下的命令行
POWERLEVEL9K_COLOR_SCHEME='light'

# 缩短目录层级
POWERLEVEL9K_SHORTEN_DIR_LENGTH=1
# 缩短目录策略：隐藏上层目录中间的字
POWERLEVEL9K_SHORTEN_STRATEGY="truncate_middle"
```
还可以配置每个元素的图标和颜色，详细说明看上面github链接

### 自定义命令行元素显示

详细配置[参考这里](https://github.com/Powerlevel9k/powerlevel9k#customizing-prompt-segments)


以下配置信息都是要配置到`~/.zshrc`中，主要配置如下：
```
# 配置左右两部分分别需要显示哪些元素，下面括号中的是默认值
POWERLEVEL9K_LEFT_PROMPT_ELEMENTS=(context dir vcs)
POWERLEVEL9K_RIGHT_PROMPT_ELEMENTS=(status root_indicator background_jobs history time)
```
如果需要新增加显示的元素，只需要添加对应的字段到相应的变量中去，所有可以被添加的元素的完整列表可以去上面链接查看，这里只简单说明一些常用元素：
- context 用户名和主机名
- dir 当前工作目录
- dir_writable 如果对当前目录无写权限，会显示锁标记
- root_indicator 对超级用户做标记
- background_jobs 后台工作的jobs数量
- history 当前命令在历史命令中的序号
- status 上一条命令的执行结果
- time 系统时间
- vcs 当前所处的git仓库

[参考教程](https://www.jianshu.com/p/ae1e0db9f4bb)
