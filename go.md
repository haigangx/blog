## Learn Go

<details>
<summary>学习方法</summary>

### HOW

* [官方文档，墙裂推荐，超级强大！！](https://go-zh.org/doc/)
    * 学习
        * Go语言规范：[旧译版](https://go-zh.org/ref/spec.old) 、[新未译版](https://go-zh.org/ref/spec)
        * [Go语言之旅](https://tour.go-zh.org/welcome/1)
        * [如何使用Go：代码组织、测试、远程包](https://go-zh.org/doc/code.html)
        * [实效Go编程：编写清晰而地道的Go代码](https://go-zh.org/doc/effective_go.html)
        * [Go内存模型](https://go-zh.org/ref/mem)
        * [Go博客](https://blog.golang.org/)
        * [Go Wiki](https://github.com/golang/go/wiki)
    * 文档
        * [命令文档](https://go-zh.org/doc/cmd)
            * [Go命令](https://go-zh.org/cmd/go/)
        * [标准库包文档](https://go-zh.org/pkg/)
    * 项目
        * 外部Go项目列表：[Go_Wiki_Project](https://github.com/golang/go/wiki/Projects)、[Go_Doc](https://godoc.org/)
    * 其他
        * 一些文章和视频教程[more...](https://go-zh.org/doc/)

* 其他外部学习资料
    * [菜鸟教程](https://www.runoob.com/go/go-tutorial.html)
    - [Github-Go语言基础](https://github.com/unknwon/go-fundamental-programming)
    - [Github-2019 Go开发者学习路线](https://github.com/Quorafind/golang-developer-roadmap-cn)

* 书
    * Go语言圣经
 


### LOG

* Go语言为什么要使用变量名后置的方式做声明？[中文版](https://studygolang.com/articles/3855) [英文版](https://blog.go-zh.org/gos-declaration-syntax)
* [Defer, Panic, and Recover](https://blog.go-zh.org/defer-panic-and-recover)

    1. defer函数可以用来处理一些清理工作，保证有异常发生时，清理工作也可以正常完成
        * 1. A deferred function's arguments are evaluated when the defer statement is evaluated.
        * 2. Deferred function calls are executed in Last In First Out order after the surrounding function returns.
        * 3. Deferred functions may read and assign to the returning function's named return values.
    2.
 
* [Go 切片：用法和本质](https://blog.go-zh.org/go-slices-usage-and-internals)

* [Go开发环境构建](content/go_dev_enviroment.md)

* [Go包管理工具Module](content/go_modules.md)

进度：
    基础：--------菜鸟教程------GO语言之旅----《Go语言圣经》


### 踩坑

* [Go开发环境构建]()

* [cannot assign to struct field in a map](https://stackoverflow.com/questions/32751537/why-do-i-get-a-cannot-assign-error-when-setting-value-to-a-struct-as-a-value-i)

### Go Passage

* [今日头条用Go建千亿级微服务 分析详细,适合新手理解概念](https://studygolang.com/topics/6178#commentForm)

### 项目

</details>

## 总结

<details>
<summary>Go+Vim开发环境搭建</summary>

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

</details>

<details>
<summary>Go包管理</summary>

# Go包管理

## GOPATH


## Go Module

## 参考文章
[GO包管理的前世今生](https://strconv.com/posts/go-modules/?utm_source=tuicool&utm_medium=referral)
[十分钟学会go module](https://blog.csdn.net/e421083458/article/details/89762113)
[]()

</details>
