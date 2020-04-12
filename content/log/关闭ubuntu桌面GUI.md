# 关闭Ubuntu桌面GUI

在虚拟机中安装了Ubuntu，但是用不到桌面环境，为了避免桌面环境的资源浪费，可以选择安装Server版本，还可以选择关闭桌面环境

永久关闭
```
sudo systemctl set-default multi-user.target
```

永久开启
```
sudo systemctl set-default graphical.target
```

临时开启
```
sudo service lightdm start
```

临时关闭
```
sudo service lightdm stop
```
