# 设置Git用户名、密码、email

- 全局配置

  ```
  git config --global user.name "xxx"
  git config --global user.email "xxx@xxx.com"
  ```

  查看全局配置文件`~/.gitconfig`

  ```
  cat ~/.gitconfig
  配置方法：git config --global <配置名称> <配置的值>
  ```

- 项目配置

  ```
  git config user.name "xxx"
  git config user.email "xxx@xxx.com"
  ```
  查看项目配置文件`<Git_Project>/.git/config`
