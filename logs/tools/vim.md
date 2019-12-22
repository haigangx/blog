# Neovim

使用Neovim替代vim

## 基本操作

### 1. 安装
#### Ubuntu下安装

普通安装：

```
sudo apt install neovim
```

上面直接安装到的极可能是一个低版本的neovim，可以使用下面命令升级或者直接安装：

- 安装stable版本，版本比较底
```
sudo add-apt-repository ppa:neovim-ppa/stable
sudo apt-get update
sudo apt-get install neovim
```

- 安装unstable版本，版本较高
```
sudo add-apt-repository ppa:neovim-ppa/unstable
sudo apt-get update
sudo apt-get install neovim
```

#### Mac安装

```
brew install neovim
```

#### Ubuntu安装最新版

Ubuntu从ppa库中安装的neovim不是最新版，要安装最新版按照下面的方式安装：

```
curl -l https://github.com/neovim/neovim/releases/download/nightly/nvim.appimage > /tmp/nvim.appimage
sudo mv /tmp/nvim.appimage /usr/local/bin/nvim
chmod +x /usr/local/nvim
```

### 2. 启动

为nvim配置别名，在`~/.bashrc`，`~/.bash_profile`，`~/.zshrc`中加入：
```
alias vim="nvim"
```

### 3. 配置文件

Neovim是能直接使用vim的配置文件的，如果有vim的配置，直接软连接就好：

```
$ ln -s ~/.vim ~/.config/nvim
$ ln -s ~/.vimrc ~/.config/nvim/init.vim
```

如果没有vim的配置文件，但想vim和nvim使用同一个配置，也按上面的方法配置就行。

有时neovim的某些指令在vim中是不能使用的，所有可使用`has('nvim')`来判断当前使用的版本：

```
if has('nvim')
	...
endif
```

如果想nvim单独使用一个配置，那就在`.config`下创建配置文件就行(我目前的方式，不太喜欢混用的方式)：

```
$ mkdir ~/.config/nvim
$ touch ~/.config/nvim/init.vim
```

### 4. 插件管理工具vim-plug

[vim-plug项目地址](https://github.com/junegunn/vim-plug)

#### Neovim下安装：

```
$ curl -fLo ~/.config/nvim/autoload/plug.vim --create-dirs \
    https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
```

#### 用法：

```
1.添加call plug#begin()和call plug#end()到Neovim的配置文件中
2.将需要安装的插件放置到两者之间
```

#### 命令：
- PlugInstall [name ...] 安装插件
- PlugUpdate [name ...] 安装或更新插件
- PlugClean 清除未列出的插件
- PlugUpgrade 更新vim-plug
- PlugStatus 查看vim-plug的状态
- PlugDiff 查看上次更新的变化
- PlugSnapshot[!] [output path] 生成一个脚本来备份当前安装的插件

更多用法参考上面vim-plug项目地址


## 插件

### 1. 状态栏airline

[Github项目地址](https://github.com/vim-airline/vim-airline)

```
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
```

### 2. 补全插件coc.nvim

[Github地址](https://github.com/neoclide/coc.nvim) | [参考教程](https://www.jianshu.com/p/55cf1fa7a467)

#### 安装

需要先安装nodejs和yarn，先判断本机有没有装nodejs和yarn：
```
node -v
yarn -v
```

如果还没有安装，分别用下面命令安装：
```
curl -sL install-node.now.sh | sh
curl --compressed -o- -L https://yarnpkg.com/install.sh | sh
```

注：国内下载可能要使用代理，curl如何设置代理查看[这篇文章]()

Ubuntu下预先安装以下软件：
```
# gem
sudo apt install ruby-dev

# pynvim
sudo apt install python3-pip
pip3 install pynvim
```





`./config/nvim/init.vim`中写入：
```
Plug 'neoclide/coc.nvim', {'branch': 'release'}
```
然后运行：
```
:PlugInstall
```
完成之后需要检查，打开vim，执行：
```
:checkhealth
```
如果出现错误，按照上面的提示做就可以解决错误，这里记录一下我遇到的几个问题：

- `:pyx` does not work

  解决方法：
  ```
  1.确保已经按按照python2或者3，并且确保在终端输入python2或python3可以进入对应版本的python

  //pyxversion变量是默认启动python的版本
  2.在neovim配置文件init.vim中写入：set pyxversion=3 或者 set pyxversion=2
  ```

- python2 provider error

  确保已经按照了python2和pip2
  vim中输入`:help provider-python`，按照说明执行下面命令：
  ```
  python3 -m pip install --user --upgrade pynvim
  ```

- python3 provider error

  确保已经按照了python3和pip3
  vim中输入`:help provider-python`，按照说明执行下面命令：
  ```
  python2 -m pip install --user --upgrade pynvim
  ```

- ruby provider error

  ```
  sudo gem install neovim
  gem environment
  ```
  重新开启一个终端测试是否解决问题

- nodejs provider error

  ```
  npm install -g neovim
  yarn global add neovim
  ```

至此，coc.vim插件安装成功

#### 配置

更多配置信息[查看这里](https://github.com/neoclide/coc.nvim#example-vim-configuration)

#### 添加语言支持

##### Python

安装jedi
```
pip install jedi
```
vim中安装coc-python
```
:CocInstall coc-python
```

##### C/C++

未完待续

### 3. Markdown插件

#### vim-markdown

[项目地址](https://github.com/plasticboy/vim-markdown)

提供了针对Markdown的语法高亮，段落折叠，查看目录，段间跳转等功能

安装与命令
```
"安装插件
Plug 'godlygeek/tabular' "必要插件，安装在vim-markdown前面
Plug 'plasticboy/vim-markdown'

" 关闭打开Markdown文件默认折叠
let g:vim_markdown_folding_disabled = 1

"查看所有配置建议
:help vim-markdwon
[[ "跳转上一个标题
]] "跳转下一个标题
]c "跳转到当前标题
]u "跳转到副标题
zr "打开下一级折叠
zR "打开所有折叠
zm "折叠当前段落
zM "折叠所有段落
:Toc "显示目录
```

#### vim-markdown-toc

[项目地址](https://github.com/mzlogin/vim-markdown-toc)

自动在当前光标生成目录

安装与命令
```
"安装插件
Plug 'mzlogin/vim-markdown-toc'
"在当前光标后生成目录
:GenTocMarked
"更新目录
:UpdateToc
"取消储存时自动更新目录
let g:vmt_auto_update_on_save = 0
```

#### markdown-preview.nvim

[项目地址](https://github.com/iamcco/markdown-preview.nvim)

通过浏览器实时预览markdown文件

安装与命令

需要先安装nodejs和yarn，先判断本机有没有装nodejs和yarn：
```
node -v
yarn -v
```
如果还没有安装，分别用下面命令安装：
```
curl -sL install-node.now.sh | sh
curl --compressed -o- -L https://yarnpkg.com/install.sh | sh
```

```
" 安装插件(已经安装好nodejs和yarn)
Plug 'iamcco/markdown-preview.nvim', { 'do': 'cd app & yarn install'  }

" 打开/关闭预览
:MarkdownPreview
:MarkdownPreviewStop
```

其他配置选项参考项目github地址


## 开发环境

### 1. Go

#### vim-go
[项目地址](https://github.com/fatih/vim-go)

提供Go快速编译、执行，Go语言语法高亮等等.....

### 2. C/C++


## 问题

### 1. vim访问系统粘贴板？


[原文](https://www.zhihu.com/question/19863631/answer/89354508)

vim中复制、删除的内容都会被存放到默认(未命名)寄存器中，之后可以通过粘贴操作读取默认寄存器中的内容。寄存器是完成这一过程的中转站，vim支持的寄存器非常多，其中常用的有`a-zA-Z0-9"`。其中：

- 0-9：数字寄存器，是vim用来保存最近复制、删除等操作的内容，其中0号寄存器保存的是最近一次的操作内容
- a-zA-Z：用户寄存器，vim一般不会读写这部分寄存器
- "：未命名寄存器，是vim的默认寄存器，删除、复制等操作的内容都会被保存到这里
- +：剪贴板寄存器，关联系统剪贴板，保存在这个寄存器中的内容可以被系统其它程序访问，也可以通过这个寄存器访问其它程序保存到剪贴板中的内容

如果想了解更多寄存器的内容，可在vim中输入`:help registers`查看文档，或者查看[网页版](http://vimdoc.sourceforge.net/htmldoc/change.html#registers)

通过下面的命令可以查看所有寄存器中的内容，也可以只查看指定寄存器的内容(将寄存器名称作为参数)：
```
:reg [register_name]
```

要在vim中对系统剪贴板操作，只需要将内容复制到剪贴板寄存器`+`中即可：
```
"+yy  //复制当前行到系统剪贴板
"+p   //将剪贴板内容复制到vim
"ayy  //复制当前行到寄存器a
"ap   //将寄存器a中的内容粘贴到vim
```

【参考文章】：

[安装使用配置 Neovim——配置](https://www.jianshu.com/p/c382222e5151)
