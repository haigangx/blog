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
