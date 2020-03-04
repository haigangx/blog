# Git基本操作

### 生成SSH秘钥

```
ssh-keygen -t rsa -C "754657908@qq.com"
cat ~/.ssh/id_rsa.pub 配置到 Github
ssh git@github.com
```
### 基本操作

```
git init  //初始化Git仓库
git clone //克隆远程库到本地
git status  //查看当前git仓库状态

```
### 工作区修改提交到缓存区

```
git add file1 file2
  -all 添加所有修改
git rm file  //从Git仓库删除文件并且将删除信息直接写入缓存区
```

### 缓存区修改提交到本地库

```
git commit -m "xxx"   //提交到本地代码库 -m 注释(必需)
  -a 将工作区未提交的修改一并提交到本地代码库，但-a不会提交工作区新建的文件
```
### 查看修改

```
git diff 查看工作区的修改
git diff --cached 查看缓存区的修改
git diff branch1  查看当前工作目录与另一个分支的区别
git diff branch1 file1  比较当前工作目录file1与branch1分支中的file1
git diff branch1 branch2  查看两个分支的差异
```

### 更新代码

```
git pull origin master  //远程库同步到本地库
```

### 上传代码 

```
git push -u origin master  //本地库同步到远程库
```

### 添加远程库并下载代码

```
git remote add origin git@github.com:lhgaaa/xxxx
git pull origin master
```
### 常用远程库起别名
```
git remote add myrepo /tmp/myrepo
```

### 分支

```
git branch xxx  //创建名为xxx的分支
git branch  //查看当前所处分支
git checkout xxx  //切换到xxx分支
git merge -m "there is comment" xxx  //将xxx分支的修改合并到当前分支 
git branch -d xxx  //删除不再需要的分支xxx，只能删除已经被当前分支合并的分支
git branch -D xxx  //强制删除xxx分支
git reset --hard HEAD^  //回复到合并前当前分支的内容
```

### 分布式开发

### 日志

```
git log  //查看提交记录日志
git log -p master..
git log --stat  //查看log时显示每个提交中那些文件修改了多少行内容
git log --pretty=oneline  //按某种格式格式化日志输出，如oneline、short
git log --graph --pretty=oneline  //可视化你的提交图
git help log  //git log帮助
git log --pretty=format:'%h : %s' [--topo-order] [--reverse] --graph
```
