# shell数组

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
