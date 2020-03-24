# vscode

<details><summary>插件推荐</summary>

- Chinese : 提供vscode的汉化
- Python: 提供python代码分析、高亮、规范化等基本功能
- filesize: 左下角显示文件大小
- vim: vscode下的vim模式
- Bracket Pair Colorizer: 成对的彩色括号
- Settings Sync: 备份vscode配置到Github
- Indent-Rainbow: 带颜色的缩进
- TODO Highlight: 高亮TODO，搭配TODO Tree使用
- TODO Tree: 显示TODO List
- Polacode: 代码生成图片
- Guides：比vscode自带的更好的参考线
- Regex Previewer：正则结果预览
- Document this：能够一键给代码中的类、函数加上注释，支持函数声明、函数表达式、箭头函数
- Code Spell Checker：能实时的识别单词拼写是否有误，并给出提示，不少 bug 都是因为拼写错误导致的
- Code Runner：支持数十种语言，在不离开代码编辑器的前提下通过命令面板可直接执行代码，并查看输出


</details>


<details><summary>使用vscode远程开发</summary>

# 使用vscode远程开发

# TODO: 总结使用vscode远程开发遇到的问题

[我最终还是选择了vscode](https://zhuanlan.zhihu.com/p/93239107)

</details>

<details><summary>win下用vscode远程开发时自动补全Linux头文件</summary>

目前发现，只要在远程开发时为远程机安装`C/C++`插件，在默认配置下即可自动补全

</details>

<details><summary>vscode下快捷键设置以及解决与vim插件按键冲突</summary>

查看vscode中vim插件官方文档来查看完整自定义按键信息[官方文档](https://github.com/VSCodeVim/Vim)

直接在`setting.json`文件中为vim添加配置：
```
{
    "vim.easymotion": true,
    "vim.incsearch": true,
    "vim.hlsearch": true,
    "vim.useCtrlKeys": true,
    //插入模式下自定义按键功能
    "vim.insertModeKeyBindingsNonRecursive": [
        {
            "before": ["<C-e>"],
            "after": ["<Esc>", "A"]
        }
    ],
    "vim.normalModeKeyBindingsNonRecursive": [
    ],
    "vim.handleKeys": {
        "<C-d>": true,
        "<C-f>": true,
    }
}

```


</details>


<details><summary>关闭vscode编辑区域左边预览栏</summary>

关闭预览功能方法：
> 点击—文件----首选项----设置-----用户设置-----文本编辑器----小地图----取消对勾

</details>

