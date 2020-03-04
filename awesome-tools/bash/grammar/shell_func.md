# shell函数

## 一、定义

shell中函数定义格式如下：
```
[ function ] funname [()]
{
    action;

    [return int;]
}
```

说明：
- 可以使用关键词`function fun()`定义，也可以直接`fun()`定义，不带任何参数
- 参数返回：可以显式加`return`返回；如果不加，将以最后一条命令运行结果作为返回值。`return`后跟数值n(0~255)
- 所有函数在使用前必须定义。必须将函数放在脚本开始部分，直至shell解释器首次发现它时，才可以使用

## 二、参数

函数参数的使用和shell脚本参数的使用相同，见[shell传递参数](shell_passing_arg.md)

## 三、实例

```
funWithReturn(){
    echo "hello, world"
    return 0
}

funWithParam(){
    echo "第一个参数为 $1 "
    echo "第二个参数为 $2 "
    echo "第十个参数为 ${10} "
    echo "第十一个参数为 ${11} "
    echo "参数共有 $# 个"
    echo "作为一个字符串输出所有参数 $* "
}

funWithReturn 
echo "funWithReturn命令的结果为 $? "

funWithParam 1 2 3 4 5 6 7 8 9 34 73
```

输出：

```
hello, world
funWithReturn命令的结果为 0
第一个参数为 1
第二个参数为 2
第十个参数为 34
第十一个参数为 73
参数共有 11 个
作为一个字符串输出所有参数 1 2 3 4 5 6 7 8 9 34 73
```
