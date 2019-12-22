# Mac使用Gitbook并发布到Github

## 安装Gitbook

- 安装Nodejs：
  
  [官网安装](https://nodejs.org/en/)

  安装完输入`node -v`测试安装是否成功

  npm切换到国内源，切换方法：[🔗](https://www.jianshu.com/p/66f97cadd1eb)

- 安装Gitbook和命令行工具 -g代表全局安装
  ```
  sudo npm install gitbook-cli -g
  sudo npm install gitbook -g
  //测试安装是否成功
  gitbook -V  
  gitbook --version
  ```

- 更新gitbook命令行工具
  ```
  sudo npm update gitbook-cli -g
  ```

- 卸载gitbook命令行工具
  ```
  sudo npm uninstall gitbook-cli -g
  ```

## 使用gitbook

- 创建mygitbook文件夹
  ```
  mkdir mygitbook && cd mygitbook
  ```

- 初始化gitbook工作目录，创建必要的文件
  ```
  gitbook init
  # README.md  - 项目的介绍都写在这个文件
  # SUMMARY.md  - Gitbook的目录结构在这里配置
  ```

- 编辑目录结构

- 目录建好之后在根目录下执行命令，只支持2级目录
  ```
  gitbook init
  ```

- 编写gitbook内容，重新编译
  ```
  gitbook build
  ```

- 在根目录执行命令，启动服务
  ```
  gitbook serve
  ```

- 插件Calibre可生成电子书
  ```
  gitbook mobi ./ ./MyFirstBook.mobi
  ```
  
### 推送到Github

- 建立Git仓库，在仓库内创建gitbook

  ```
  mkdir gitbook_test & cd gitbook_test
  git init
  gitbook init //创建README.md  SUMMARY.md
  # 编写目录结构
  gitbook init //构建层级结构
  # 编写gitbook内容
  gitbook build
  # 创建gh-pages分支
  git checkout --orphan gh-pages
  
  //将_book目录中的内容复制到_book外，只提交_book内容
  git push -u origin gh-pages
  ```

### 参考

[将Gitbook上的书籍发布在GitHubPages上](https://blog.csdn.net/meiko_zhang/article/details/81350924)