# coc.nvim

[Github地址](https://github.com/neoclide/coc.nvim) | [参考教程](https://www.jianshu.com/p/55cf1fa7a467)

### 安装

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

### 配置

更多配置信息[查看这里](https://github.com/neoclide/coc.nvim#example-vim-configuration)

### 添加语言支持

#### Python

安装jedi
```
pip install jedi
```
vim中安装coc-python
```
:CocInstall coc-python
```

#### C/C++

未完待续

