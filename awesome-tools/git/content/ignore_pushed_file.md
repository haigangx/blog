# 如果想要过滤某个已经push的文件，该怎么办？

- 1.执行下面命令
  ```
  git rm --cached <path>
  如果是文件夹，执行：
  git rm -r --cached <path>
  如果设置后无法生效，可以清理尝试清理全部缓存：
  git rm -r --cached .

  git add .
  git commit -m "update .gitignore"
  ```
- 2.更新".gitignore"文件，添加需要忽略的文件
- 3.commit

# 参考

- [参考教程](https://www.jianshu.com/p/e5b13480479b)
