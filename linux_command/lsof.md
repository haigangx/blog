# lsof

lsof(list open files)是一个列出当前系统打开文件的工具

- -i 显示符合条件的进程

例：查找占用了8070端口的程序
```
lsof -i:8070
```
