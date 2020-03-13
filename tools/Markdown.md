# Markdown

[Markdown语法](http://naotu.baidu.com/file/dbb270c5616139e091f0d8b5c383a7ce?token=fa1cde6c866337c4)


<details open>
<summary>实现内容折叠</summary>

```
<details>
<summary>展开查看</summary>

Markdown内容

</details>
```

默认展开：
```
<details>
<summary>展开查看</summary>

Markdown内容

</details>
```

实际效果如下：

<details>
<summary>展开查看</summary>

> Markdown内容

</details>

默认展开的效果：

<details open>
<summary>展开查看</summary>

> Markdown内容

</details>

</details>

<details>
<summary>在表格单元格里换行</summary>

表格单元格中换行通过HTML中的 `<br />` 标签实现

例：

```
| Header1 | Header2 |
| --- | --- |
| item1 | 1. one <br /> 2.two <br /> 3. three <br /> |
| item2 | hello, world |
```

| Header1 | Header2 |
| --- | --- |
| item1 | 1. one <br /> 2.two <br /> 3. three <br /> |
| item2 | hello, world |

</details>

<details>
<summary>设置表格对其方式</summary>


```
| 左对齐 | 右对齐 | 居中 |
| :--- | ---: | :---: |
| item1左对齐 | item2右对齐 | item3居中 |
|  item4 | item5 | item6 |
```

| 左对齐 | 右对齐 | 居中 |
| :--- | ---: | :---: |
| item1左对齐 | item2右对齐 | item3居中 |
|  item4 | item5 | item6 |

</details>

<details>
<summary>Github Markdow 设置锚点</summary>

```
# 标题1

[锚点](#标题1)
```

设置锚点的技巧：
- 英文全小写，空格转为`-`
- 中文标点符号全省略
- 可以通过查看github效果页面设置锚点信息

</details>

<details>
<summary></summary>

</details>