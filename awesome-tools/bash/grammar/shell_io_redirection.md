# shell输入/输出重定向

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
