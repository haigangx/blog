# expr

expr是一款表达式计算工具，使用它能完成表达式的求值操作

使用expr时要注意，表达式和运算符之间要有空格，例如 `2+2` 是不对的，必须写成 `2 + 2`

expr支持以下操作：

| 运算符 | 说明 | 举例 |
| --- | --- | --- |
| + | 加法 | expr a + b |
| - | 减法 | expr a - b |
| * | 乘法 | expr a * b |
| / | 除法 | expr a / b |
| % | 取余 | expr a % b |
| = | 相等 | expr a = b |
| != | 不相等 | expr a != b |

更多查看`man expr`