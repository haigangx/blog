# Ubuntu18.04安装Albert

## 介绍

**Albert** 类似于windows上的 **Everything+wox** ，可以通过快捷键呼出窗口来查找应用程序或者文件。

## 安装

**Albert** [github项目地址](https://github.com/albertlauncher/albert) ，参照项目文件中的安装方法即可安装成功。下面是可参考的简化的安装过程。

- 首先需要导入相关的key文件：

  ```shell
  wget -nv -O Release.key \
    https://build.opensuse.org/projects/home:manuelschneid3r/public_key
  apt-key add - < Release.key
  apt-get update
  ```

- Ubuntu18.04按照下面的方法安装：

  ```shell
  sudo sh -c "echo 'deb http://download.opensuse.org/repositories/home:/manuelschneid3r/xUbuntu_18.04/ /' > /etc/apt/sources.list.d/home:manuelschneid3r.list"
  sudo apt-get update
  sudo apt-get install albert
  ```
