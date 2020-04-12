# 代理环境下使用ADD-APT-REPOSITORY添加PPA软件源

- 1. 使用 sudo 参数 -E 使得 root 用户可以使用普通用户下的环境变量，包括代理设置。

  ```
  jonathan@n:~$ sudo -E add-apt-repository ppa:mitya57/ppa
  ```

- 2. 直接在 root 用户下设置代理。

  ```
  jonathan@n:~$ sudo bash
  root@n:~# export http_proxy=http://192.168.1.8:80
  root@n:~# export https_proxy=http://192.168.1.8:80
  root@n:~# add-apt-repository ppa:mitya57/ppa
  ```
