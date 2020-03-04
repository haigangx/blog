## markdown-preview.nvim

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
