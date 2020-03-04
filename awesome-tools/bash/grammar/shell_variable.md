# 变量


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
