# zsh

## 1. 基本操作

### 1.1. 安装

```
sudo apt install zsh
```


### 1.2 zsh为默认shell

```
chsh -s /bin/zsh
```

## 2. 插件

### 2.1 oh-my-zsh

[Github地址](https://github.com/ohmyzsh/ohmyzsh)

安装：

```
sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
```

### 2.2 zsh-autosuggestions

[Github地址](https://github.com/zsh-users/zsh-autosuggestions)

安装到oh-my-zsh：

1. clone库到oh-my-zsh插件目录`$ZSH_CUSTOM/plugins`(默认~/.oh-my-zsh/custom/plugins)
```
git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
```
2. 添加zsh-autosuggestions到oh-my-zsh配置文档`~/.zshrc`，多个插件用空格隔开

```
plugins=(zsh-autosuggestions)
```

配置：
```
# 配置文件是$ZSH_CUSTOM/plugins/zsh-autosuggestions/zsh-autosuggestions.zsh
# 修改首先从历史命令匹配，然后按照系统补全匹配
ZSH_AUTOSUGGEST_STRATEGY=(history completion)
```

