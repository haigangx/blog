# shell流程控制语句

## 一、条件语句

### 1. if

```
if condition
then 
    command
    command
fi
```

写成一行：

```
if [ condition ]; then command; command; fi;
```

### 2. if-else

```
if condition
then 
    command
    command
else
    command
fi
```

### 3. if-elif-else

```
if condition
then 
    command
    command
elif condition
then
    command
    command
else
    command
fi
```

## 二、循环语句

### 1. for

```
for var in item1 item2 ... itemN
do 
    command
    command
done
```

写成一行：

```
for var in item1 item2 ... itemN; do command; command; done;
```

### 2. while

```
while condition
do 
    command
    command
done
```

### 3. until

util循环执行一系列命令直到条件为true时停止

```
until condition
do 
    command
    command
done
```

### 4. break和continue

break命令跳出所有循环

continue命令仅仅跳出当前循环

## 三、多选择语句

### 1. case

```
case 值 in
模式1)
    command
    command
    ;;
模式2)
    command
    command
    ;;
esac
```

例：下面脚本提示输入1到4，与每一种模式进行匹配：

```
echo '输入1到4之间的数字：'
echo '你输入的数字为：'
read aNum
case $aNum in
    1) echo '你选择了 1'
    ;;
    2) echo '你选择了 2'
    ;;
    3) echo '你选择了 3'
    ;;
    4) echo '你选择了 4'
    ;;
    *) echo '你没有输入1到4之间的数字'
    ;;
esac
```



