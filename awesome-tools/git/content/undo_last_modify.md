# Git恢复修改的文件

分三种情况处理：

- 只是修改了文件，没有任何git操作

  ```
  git checkout -- aaa.txt  # aaa.txt 为修改的文件
  ```

- 修改了文件，并提交到暂存区(即已经 git add 但没有 git commit )

  ```
  git log --oneline  # 可以省略
  git reset HEAD     # 回退到当前版本
  git checkout --- aaa.txt  # aaa.txt 为修改的文件
  ```

- 修改了文件，并提交到了仓库区(即不但 git add 而且 git commit )

  ```
  git log --oneline  # 可以省略
  git reset HEAD^    # 回退当上一个版本
  git checkout -- aaa.txt  # aaa.txt 为修改的文件
  ```


## 参考：

- [恢复修改的文件](https://www.cnblogs.com/liuq/p/9203087.html)
