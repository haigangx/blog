# shell字符串

字符串和数组是shell编程中最常用的两种的数据类型。

## 1. 单引号和双引号

字符串可以用单引号，也可以用双引号。但单引号和双引号的使用有些许不同

### 1.1 单引号

```
str='this is string'
```

单引号的限制：

- 单引号里的任何字符都会原样输出，单引号字符串中的变量是无效的
- 单引号字符串中不能出现单独一个单引号（即使对单引号使用转义符也不行）。但可嵌套成对出现，可以作为拼接字符串使用

```
your_name="runoob"
greeting_2='hello, '$your_name'!'
greeting_3='hello, ${your_name}!'
echo $greeting_2 $greeting_3
```

输出结果：

```
hello, runoob! hello, ${your_name}!
```

### 1.2 双引号

双引号的优点：

- 双引号中的变量自动解析
- 双引号中转义字符自动解析

```
str="hello, i know you are \"$your_name\"!\n"
echo -e $str

str2="hello, "$your_name"!"
str3="hello, $your_name!"
echo $str2 $str3
```

输出结果：

```
hello, i know you are "runoob"!
hello, runoob! hello, runoob!
```

## 2. 获取字符串长度

```
str="abcd"
echo ${#str}  #输出 4
```

## 3. 截取子字符串

```
str="runoob is a great site"
echo ${str:1:4} #从字符串第2个字符开始截取4个字符
```

输出结果：

```
unoo
```

截取子字符串的方法：

- 1. `#` 和 `##` 截取

  `#`、`##` 表示从左边开始删除。一个 `#` 表示从左边开始删除到第一个指定的字符；两个 `##` 表示从左边开始删除到最后一个指定的字符

- 2. `%` 和 `%%` 截取

  `%`、`%%` 表示从左边开始删除。一个 `%` 表示从左边开始删除到第一个指定的字符；两个 `%%` 表示从左边开始删除到最后一个指定的字符

- 3. 指定范围截取

  - `echo $(var:0:5)` 表示从左边第一个字符开始，5表示截取的字符总个数
  - `echo $(var:7)` 表示从左边第8个字符开始，一直到结束
  - `echo $(var:0-7:3)` 表示从右边算起第7个字符开始，3表示截取的字符总个数
  - `echo $(var:0-7)` 表示从右边第7个字符开始，一直到结束

## 4. 查找子字符串


```
str="runoob is a great site"
echo `expr index "$string" io` #输出 4
```

注：反引号包起来的字串被视为命令在终端执行
