| 命令 | 说明 | 示例 |
| --- | --- | --- |
| git init | 当前文件夹下建立git仓库 |  |
| git clone <address> | 给定地址的git仓库克隆到本地 |  |
| git status | 
| git add <file> | 将修改提交到暂存区 |  |
| git add * | 
| git rm file.txt | 从git仓库删除文件并且将删除信息直接写入暂存区 |
| git commit -m "msg" | 提交到本地代码库 |
| git commit -m "msg" -a | 将工作区还未提交到暂存区的修改一并提交到本地代码库，但不会提交工作区新建的文件 |
| git push my-remote my-branch | 推送提交到远程仓库 |
| git pull my-remote my-branch | 
| git diff | 查看工作区的修改 | 
| git diff --cached | 查看暂存区的修改
| git diff branch1 | 对比当前工作目录与branch1
| git diff branch1 file1 | 对比当前工作目录中file1与branch1分支中的file1 |
| git diff branch1 branch2 | 对比两个分支的差异 |
| git remote | 
| git remote -v |
| git remote add my-remote <address> |
| git remote add myrepo /tmp/myrepo | 为常用远程库起别名 |
| git reset file.txt | 
| git branch | 查看分支列表 |
| git branch my-branch | 创建my-branch分支 | 
| git branch -d my-branch | 删除不再需要的my-branch分支，只能删除已经被当前分支合并的分支 |
| git branch -D my-branch | 强制删除my-branch分支 |
| git checkout my-branch | 切换分支 |
| git merge my-branch -m "this is comment" | 合并分支my-branch到当前分支 |
| git log | 查看提交日志 |
| git log -p master.. |
| git log --stat | 查看log时显示每个提交中那些文件修改了多少行内容 |
| git log --pretty=oneline | 按某种格式格式化日志输出，如oneline、short |
| git log --graph --pretty=oneline | 可视化你的提交图 |
| git log --pretty=format:'%h : %s' [--topo-order] [--reverse] --graph
| git tag | 显示所有tags |
| git tag -a v1.0 -m 'msg' | 
| git show v1.0 |
| git tag --delete v1.0 |
| git push --delete my-remote v1.0 |
| git push my-remote my-branch v1.0 |
| git fetch --tags |
| git stash | 将所有未commit的修改(包括暂存和未暂存的)都保存起来 |
| git stash -u | 
| git stash save "msg" |
| git stash list |
| git stash pop |
| git stash stash@{2} |
| git stash show | 
| git stash apply |
| git stash branch my-branch stash@{1} |
| git stash drop stash@{1} |
| git stash clear |
