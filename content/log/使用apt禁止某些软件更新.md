# apt upgrade前，指定某些软件不更新

以wps-office为例：

1、查看wps-office的软件包状态
```
    sudo dpkg --get-selections | grep wps
```
2、锁定wps-office不更新
```
    sudo echo "wps-office hold" | dpkg --set-selections
```
3、查看当前以锁定的软件包
```
    sudo dpkg --get-selections | grep hold
```

此时，可以放心执行apt upgrade更新软件了
