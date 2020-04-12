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
