## 语法

TODO: shell中简化的正则表达式 glob

<details>
<summary>变量</summary>

## 1. 定义

- 命令只能使用英文字母，数字和下划线，不能以数字开头，不能使用关键字(bash中输入help查看关键字)
- 定义变量时，变量名和等号之间不能有空格

```
var_name="hello,world"
```

## 2. 使用

- 使用一个定义过的变量，只需要再变量名前面加`$`符号即可，如：

  ```
  var_name="hello,world"
  echo $var_name
  ```

- 为变量名加`{}`可以帮助解释器识别变量边界，这是个可选的操作

  ```
  echo ${var_name}
  ```

- 修改变量值时不需要加`$`符号

  ```
  var_name="hello,Mr liu"
  ```

## 3. 只读变量

使用`readonly`命令可将变量定义为只读变量

```
my_url="www.baidu.com"
readonly my_url
my_url="www.google.com"  # error
```

## 4. 删除变量

使用`unset`命令可以删除变量

```
unset my_url
```

## 5. 变量类型

- **局部变量：**

  局部变量再当前脚本或命令中定义，仅在当前shell实例中有效，其他shell启动的程序不能访问局部变量

- **环境变量：**

  所有程序都可以访问环境变量，许多程序靠环境变量保证其正常运行。必要时shell脚本可以定义环境变量

- **shell变量：**

  shell变量是由shell程序设置的特殊变量。shell变量中有一部分是环境变量，有一部分是局部变量，这些变量保证了shell的正常运行

</details>

<details>
<summary>变量-shell字符串</summary>

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

</details>

<details>
<summary>变量-shell数组</summary>

bash支持一维数组（不支持多维数组），并且没有限定数组大小

数组元素下标从0开始编号，下标可以是整数或算术表达式，其值应大于或等于0

## 1. 定义数组

shell中，用括号表示数组，数组元素用"空格"符号分割开。定义数组的一般形式为：

```
数组名=(值1 值2 ... 值n)
```

例如：

```
array_name=(value0 value1 value2 value3)
```

也可以单独定义数组每个分量：

```
array_name[0]=value0
array_name[1]=value1
array_name[n]=valuen
```

可以不适用连续下标，并且下标的范围没有限制

## 2. 使用数组

使用数组元素值的一般格式是：

```
$数组名[下标]
```

例如：

```
valuen=${array_name[n]}
```

使用`@`符号可以获取数组中的所有元素，例如：

```
echo ${array_name[@]}
```

## 3. 获取数组长度

获取数组长度与获取字符串长度的方法相同，例如：

```
# 取得数组元素的个数
length=${#array_name[@]}
# 或者
length=${#array_name[*]}

# 取得数组单个元素的长度
lengthn=${#array_name[n]}
```

</details>

<details>
<summary>变量-shell传递参数</summary>

## 一、脚本内获取参数

脚本内获取参数的方式是`$n`，n代表一个数字，0为执行的文件名，1为第一个参数，2为第二个参数，以此类推...大于等于10的参数，需要加大括号，如`${10}`

## 二、脚本内与参数相关的其他特殊符号

| 参数处理 | 说明 |
| --- | --- |
| $# | 传递到脚本的参数个数 |
| $* | 以单字符串形式显示所有参数, 同$@ |
| $$ | 脚本运行的当前进程ID号 |
| $! | 后台运行的最后一个进程的ID号 |
| $- | 显示shell使用的当前选项 |
| $? | 显示最后命令的退出状态，0表示没有错误 |

### 1. `$*`和`$@`的区别：

- 相同点：都是引用所有参数
- 不同点：只有再双引号中体现出来。假设再脚本运行时写了三个参数1,2,3，则"*"等价于"1 2 3"(传递了一个参数)，而"@"等价于"1" "2" "3"(传递了三个参数)

执行下面脚本：
```
for i in "$*"; do 
    echo $i
done

for i in "$@"; do
    echo $i
done
```
输出结果如下：
```
1 2 3
1
2
3
```

## 三、实例

脚本：
```
#!/bin/bash

echo "shell传递参数";
echo "执行的文件名：$0";
echo "第一个参数：$1";
echo "第二个参数：$2";
echo "第三个参数：$3";

echo "参数个数：$#";
echo "*输出所有参数：$*";
echo "@输出所有参数：$@";
echo "脚本运行的当前进程ID号：$$";
echo "后台运行的最后一个进程的ID号：$!";
echo "显示shell使用的当前选项：$-";
echo "显示命令的退出状态：$?";
```

执行脚本，得到以下结果：
```
./test.sh arg1 arg2 arg3 arg4

shell传递参数
执行的文件名：./test.sh
第一个参数：arg1
第二个参数：arg2
第三个参数：arg3
参数个数：4
*输出所有参数：arg1 arg2 arg3 arg4
@输出所有参数：arg1 arg2 arg3 arg4
脚本运行的当前进程ID号：11085
后台运行的最后一个进程的ID号：
显示shell使用的当前选项：hB
显示命令的退出状态：0
```

</details>

<details>
<summary>流程控制-条件语句</summary>

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

</details>

<details>
<summary>流程控制-循环语句</summary>

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


</details>

<details>
<summary>流程控制-多选择语句</summary>

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

</details>

<details>
<summary>函数</summary>

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

</details>

<details>
<summary>输入输出重定向</summary>

| 命令 | 说明 | 举例 |
| --- | --- | --- |
| command > file | 输出重定向到file | who > user |
| command < file | 输入重定向到file | wc -l user |
| command >> file | 输出追加到file末尾 | echo "end of file" > user |
| n > file | 将文件描述符为n的文件重定向到file | command 2 > file |
| n >> file | 将文件描述符为n的文件追加的方式重定向到file | command 2 >> file |
| n >& m | 将输出文件m和n合并 | command > file 2>&1 标准输出和标准错误合并重定向到file |
| n <& m | 将输入文件m和n合并 |  |
| << tag | 将开始标记tag和结束标记tag之间的内容作为输入 |  |

linux下，每个命令运行时都会打开三个文件：
- 标准输入文件(stdin)：stdin文件描述符为0
- 标准输出文件(stdout)：stdout文件描述符为1
- 标准错误文件(stderr)：stderr文件描述符为2

## Here Document

`Here Document`是shell中一种特殊的重定向方式。用来将输入重定向到一个交互式shell脚本或程序，其基本形式如下：
```
command << delimiter
    document
delimiter
```

**Note:**
- 结尾的delimiter一定要顶格写，前面不能有任何字符，后面也不能有任何字符，包括空格和tab

示例：
```
wc -l << EOF
    欢迎学习
    shell
    哈哈哈！
EOF
```

## `/dev/null`文件

`/dev/null`是一个特殊文件，写入到它的内容都会被丢弃；如果尝试从该文件读取内容，那么什么也读不到

```
command > /dev/null  # 将输出重定向到/dev/null
command > /dev/null 2>&1  # 丢弃stdout和stderr
```

</details>

<details>
<summary>文件包含</summary>

shell也可以包含外部脚本，这样可以很方便的封装一些公用代码

两种方式：
```
. filename
或
source filename
```

## 实例

test1.sh:
```
url="www.baidu.com"
```

test2.sh:
```
#!/bin/bash

. ./test1.sh
# 或 source ./test1.sh

echo "url=$url"
```

**Note:**
> 被包含的文件可以没有可执行权限

</details>

<details>
<summary>shell注释</summary>

## 1. 单行注释

以`#`开头的行是注释

开发过程中，如果遇到大段的代码需要临时注释起来，可以讲这段临时代码封装为函数

## 2. 多行注释

```
:<<EOF
注释内容...
注释内容...
注释内容...
EOF
```

EOF还可以使用其他符号：

```
:<<'
注释内容...
注释内容...
注释内容...
'

:<<!
注释内容...
注释内容...
注释内容...
!
```
</details>

## cheatsheet

<details>
<summary>变量操作</summary>

| 命令 | 说明 |
| --- | --- |
| `varname=value           `| 定义变量 |
| varname=value command     | 定义子进程变量并执行子进程 |
| echo $varname             | 查看变量内容 |
| echo $$                   | 查看当前 shell 的进程号 |
| echo $!                   | 查看最近调用的后台任务进程号 |
| echo $?                   | 查看最近一条命令的返回码 |
| export VARNAME=value      | 设置环境变量（将会影响到子进程） |
| <code>array[0]=valA <br /> array[1]=valB <br /> array[2]=valC</code> | 定义数组 |
| array=([0]=valA [1]=valB [2]=valC)   | 另一种方式 |
| array=(valA valB valC)               | 另一种方式 |
| ${array[i]}               | 取得数组中的元素 |
| ${#array[@]}              | 取得数组的长度 |
| ${#array[i]}              | 取得数组中某个变量的长度 |
| declare -a                | 查看所有数组 |
| declare -f                | 查看所有函数 |
| declare -F                | 查看所有函数，仅显示函数名 |
| declare -i                | 查看所有整数 |
| declare -r                | 查看所有只读变量 |
| declare -x                | 查看所有被导出成环境变量的东西 |
| declare -p varname        | 输出变量是怎么定义的（类型+值） |
| ${varname:-word}          | 如果变量不为空则返回变量，否则返回 word |
| ${varname:=word}          | 如果变量不为空则返回变量，否则赋值成 word 并返回 |
| ${varname:?message}       | 如果变量不为空则返回变量，否则打印错误信息并退出 |
| ${varname:+word}          | 如果变量不为空则返回 word，否则返回 null |
| ${varname:offset:len}     | 取得字符串的子字符串 |
| ${variable#pattern}       | 如果变量头部匹配 pattern，则删除最小匹配部分返回剩下的 |
| ${variable##pattern}      | 如果变量头部匹配 pattern，则删除最大匹配部分返回剩下的 |
| ${variable%pattern}       | 如果变量尾部匹配 pattern，则删除最小匹配部分返回剩下的 |
| ${variable%%pattern}      | 如果变量尾部匹配 pattern，则删除最大匹配部分返回剩下的 |
| ${variable/pattern/str}   | 将变量中第一个匹配 pattern 的替换成 str，并返回 |
| ${variable//pattern/str}  | 将变量中所有匹配 pattern 的地方替换成 str 并返回 |
| ${#varname}               | 返回字符串长度 |
| *(patternlist)            | 零次或者多次匹配 |
| +(patternlist)            | 一次或者多次匹配 |
| ?(patternlist)            | 零次或者一次匹配 |
| @(patternlist)            | 单词匹配 |
| !(patternlist)            | 不匹配 |
| array=($text)             | 按空格分隔 text 成数组，并赋值给变量 |
| IFS="/" array=($text)     | 按斜杆分隔字符串 text 成数组，并赋值给变量 |
| text="${array[*]}"        | 用空格链接数组并赋值给变量 |
| text=$(IFS=/; echo "${array[*]}")  | 用斜杠链接数组并赋值给变量 |
| A=( foo bar "a  b c" 42 ) | 数组定义 |
| B=("${A[@]:1:2}")         | 数组切片：B=( bar "a  b c" ) |
| C=("${A[@]:1}")           | 数组切片：C=( bar "a  b c" 42 ) |
| echo "${B[@]}"            | bar a  b c |
| echo "${B[1]}"            | a  b c |
| echo "${C[@]}"            | bar a  b c 42 |
| echo "${C[@]: -2:2}"      | a  b c 42  减号前的空格是必须的 |
| $(UNIX command)           | 运行命令，并将标准输出内容捕获并返回 |
| varname=$(id -u user)     | 将用户名为 user 的 uid 赋值给 varname 变量 |
| num=$(expr 1 + 2)         | 兼容 posix sh 的计算，使用 expr 命令计算结果 |
| num=$(expr $num + 1)      | 数字自增 |
| expr 2 \* \( 2 + 3 \)     | 兼容 posix sh 的复杂计算，输出 10 |
| num=$((1 + 2))            | 计算 1+2 赋值给 num，使用 bash 独有的 $((..)) 计算 |
| num=$(($num + 1))         | 变量递增 |
| num=$((num + 1))          | 变量递增，双括号内的 $ 可以省略 |
| num=$((1 + (2 + 3) * 2))  | 复杂计算 |

</details>


<details>
<summary>事件指示符</summary>

| 命令 | 说明 |
| --- | --- |
| !!                  | 上一条命令 |
| !^                  | 上一条命令的第一个单词 |
| !:n                 | 上一条命令的第n个单词 |
| !:n-$               | 上一条命令的第n个单词到最后一个单词 |
| !$                  | 上一条命令的最后一个单词 |
| !-n:$               | 上n条命令的最后一个单词 |
| !string             | 最近一条包含string的命令 |
| !^string1^string2   | 最近一条包含string1的命令, 快速替换string1为string2 |
| !#                  | 本条命令之前所有的输入内容 |
| !#:n                | 本条命令之前的第n个单词, 快速备份cp /etc/passwd !#:1.bak |

</details>

<details>
<summary>条件判断（兼容 posix sh 的条件判断）：man test</summary>

| 命令 | 说明 |
| --- | --- |
| statement1 && statement2  | and 操作符 |
| <code>statement1 \|\| statement2</code>  | or 操作符 |
| exp1 -a exp2              | exp1 和 exp2 同时为真时返回真（POSIX XSI扩展） |
| exp1 -o exp2              | exp1 和 exp2 有一个为真就返回真（POSIX XSI扩展） |
| ( expression )            | 如果 expression 为真时返回真，输入注意括号前反斜杆 |
| ! expression              | 如果 expression 为假那返回真 |
| str1 = str2               | 判断字符串相等，如 [ "$x" = "$y" ] && echo yes |
| str1 != str2              | 判断字符串不等，如 [ "$x" != "$y" ] && echo yes |
| str1 < str2               | 字符串小于，如 [ "$x" \< "$y" ] && echo yes |
| str2 > str2               | 字符串大于，注意 < 或 > 是字面量，输入时要加反斜杆 |
| -n str1                   | 判断字符串不为空（长度大于零） |
| -z str1                   | 判断字符串为空（长度等于零） |
| -a file                   | 判断文件存在，如 [ -a /tmp/abc ] && echo "exists" |
| -d file                   | 判断文件存在，且该文件是一个目录 |
| -e file                   | 判断文件存在，和 -a 等价 |
| -f file                   | 判断文件存在，且该文件是一个普通文件（非目录等） |
| -r file                   | 判断文件存在，且可读 |
| -s file                   | 判断文件存在，且尺寸大于0 |
| -w file                   | 判断文件存在，且可写 |
| -x file                   | 判断文件存在，且执行 |
| -N file                   | 文件上次修改过后还没有读取过 |
| -O file                   | 文件存在且属于当前用户 |
| -G file                   | 文件存在且匹配你的用户组 |
| file1 -nt file2           | 文件1 比 文件2 新 |
| file1 -ot file2           | 文件1 比 文件2 旧 |
| num1 -eq num2             | 数字判断：num1 == num2 |
| num1 -ne num2             | 数字判断：num1 != num2 |
| num1 -lt num2             | 数字判断：num1 < num2 |
| num1 -le num2             | 数字判断：num1 <= num2 |
| num1 -gt num2             | 数字判断：num1 > num2 |
| num1 -ge num2             | 数字判断：num1 >= num2 |

</details>

<details>
<summary>其他操作</summary>

| 命令 | 说明 | 备注 |
| --- | --- | --- |
| **环境变量** |  |  |
| **算术运算符** |  |  |
| `+` | 加法 | \`expr a + b\` |
| `-` | 减法 | \`expr a - b\` |
| `*` | 乘法 | \`expr a * b\` |
| `%` | 取余 | \`expr a % b\` |
| `=` | 赋值 | a=$b 将变量b的值赋给a |
| `==` | 相等 | [ $a == $b ] 比较a和b两个的值 |
| `!=` | 不相等 | [ $a != $b ] 比较a和b两个的值 |
| **关系运算符** | | |
| `-eq` | 检测两个数是否相等 | [ $a -eq $b ] |
| `-ne` | 检测两个数是否不相等 | [ $a -ne $b ] |
| `-gt` | 检测左边的数是否大于右边的 | [ $a -gt $b ] |
| `-lt` | 检测左边的数是否小于右边的 | [ $a -lt $b ] |
| `-ge` | 检测左边的数是否大于等于右边的 | [ $a -ge $b ] |
| `-le` | 检测左边的数是否小于等于右边的 | [ $a -le $b ] |
| **布尔运算符** |  |  |
| `!` | 非运算 | [ ! false ] 返回true |
| `-o` | 或运算 | [ $a -lt 20 -o $b -gt 100 ] |
| `-a` | 与运算 | [ $a -lt 20 -a $b -gt 100 ] |
| **逻辑运算符** |  |  |
| `&&` | AND | [ $a -lt 100 && $b -gt 100 ] |
| <code>\|\|</code> | OR | [ $a -lt 100 \|\| $b -gt 100 ] |
| **字符串运算符** |  |  |
| `=` | 检测两个字符串是否相等 | [ $a = $b $a == $b可以表达同样的效果 ] |
| `!=` | 检测两个字符串是否不相等 | [ $a != $b ] |
| `str1 > str2` | str1排列在str2之后 | "<"号需要用引号引起来或者用反斜杠转义，否则会被解释为重定向操作符 |
| `str1 < str2` | str1排列在str2之前 | ">"号需要用引号引起来或者用反斜杠转义，否则会被解释为重定向操作符 |
| `-z` | 检测字符串长度是否为0 | [ -z $a ] | 
| `-n` | 检测字符串长度大于零 | [ -n $a ] |
| `$` | 检测字符串是否为空，不为空返回true | [ $a ]返回true |
| **测试文件表达式** |  |  |
| `file1 -ef file2` | file1和file2拥有相同的索引号(硬链接链接的两个文件) |  |
| `file1 -nt file2` | file1新于file2 |  |
| `file1 -ot file2` | file1早于file2 |  |
| `-b file` | file存在并且是一个块设备文件 |  |
| `-c file` | file存在并且是一个字符设备文件 |  |
| `-d file` | file存在并且是一个目录 |  |
| `-e file` | file存在|  |
| `-f file` | file存在并且是一个普通文件 |  |
| `-g file` | file存在并且设置了组ID |  |
| `-G file` | file存在并且由有效组ID拥有 |  |
| `-k file` | file存在并且设置了"sticky bit" |  |
| `-L file` | file存在并且是一个符号链接 |  |
| `-O file` | file存在并且由有效用户ID拥有 |  |
| `-p file` | file存在并且是一个命令管道 |  |
| `-r file` | file存在并且并且可读 |  |
| `-s file` | file存在且其长度大于零 |  |
| `-S file` | file存在并且是一个网络socket |  |
| `-t fd` | fd是一个定向到终端/从终端定向的文件描述符 | 可以被用来决定是否重定向了标准输入/输出错误 |
| `-u file` | file存在并且设置了setuid位 |  |
| `-w file` | file存在并且可写（有效用户拥有可写权限）|  |
| `-x file` | file存在并且可执行（有效用户有执行/搜索权限）|  |

</details>


<details>
<summary>函数</summary>

# 定义一个新函数
```
function myfunc() {
    # $1 代表第一个参数，$N 代表第 N 个参数
    # $# 代表参数个数
    # $0 代表被调用者自身的名字
    # $@ 代表所有参数，类型是个数组，想传递所有参数给其他命令用 cmd "$@" 
    # $* 空格链接起来的所有参数，类型是字符串
    {shell commands ...}
}
```

myfunc                    # 调用函数 myfunc 
myfunc arg1 arg2 arg3     # 带参数的函数调用
myfunc "$@"               # 将所有参数传递给函数
myfunc "${array[@]}"      # 将一个数组当作多个参数传递给函数
shift                     # 参数左移

unset -f myfunc           # 删除函数
declare -f                # 列出函数定义
</details>

<details>
<summary>批量创建文件和重命名</summary>

[批量创建文件并重新命名](https://blog.csdn.net/taiyang1987912/article/details/39934055)

</details>