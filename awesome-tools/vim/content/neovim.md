## 使用Neovim替代vim

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
