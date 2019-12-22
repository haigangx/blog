# Go+Vim开发环境构建

## Go插件安装

```
1、在%GOPATH%\src\ 目录下，建立golang.org 文件夹，并再新建x文件夹。  目录为 "%GOPATH\src\golang.org\x\"
2、进入%GOPATH\src\golang.org\x\目录
3、完成目录切换后，开始下载插件包：git clone https://github.com/golang/tools.git tools
4、进入“%GOPATH”目录,执行：

go install github.com/ramya-rao-a/go-outline
go install github.com/acroca/go-symbols
go install golang.org/x/tools/cmd/guru
go install golang.org/x/tools/cmd/gorename
go install github.com/josharian/impl
go install github.com/rogpeppe/godef
go install github.com/sqs/goreturns
go install github.com/golang/lint/golint
go install github.com/cweill/gotests/gotests
```

Note:

```
如果执行go install安装过程中提示找不到对应的安装包，可以手动安装，将上面安装包对应的github地址拼成https://github.com/xxx/xxx.git,使用git clone到$GOPATH/github.com/下，然后进入插件目录执行go install即可
```

## 用Vim开发Go

### [插件](https://github.com/lhgaaa/learning_log/blob/master/tools/nvim.md#go)


### [go module加速](https://goproxy.io/)

```
export GOPROXY=https://goproxy.io
```
