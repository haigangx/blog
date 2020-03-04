# 插件管理工具vim-plug

[vim-plug项目地址](https://github.com/junegunn/vim-plug)

### Neovim下安装：

```
$ curl -fLo ~/.config/nvim/autoload/plug.vim --create-dirs \
    https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
```

### 用法：

```
1.添加call plug#begin()和call plug#end()到Neovim的配置文件中
2.将需要安装的插件放置到两者之间
```

### 命令：
- PlugInstall [name ...] 安装插件
- PlugUpdate [name ...] 安装或更新插件
- PlugClean 清除未列出的插件
- PlugUpgrade 更新vim-plug
- PlugStatus 查看vim-plug的状态
- PlugDiff 查看上次更新的变化
- PlugSnapshot[!] [output path] 生成一个脚本来备份当前安装的插件

更多用法参考上面vim-plug项目地址
