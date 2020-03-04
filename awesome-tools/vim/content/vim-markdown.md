## vim-markdown

[项目地址](https://github.com/plasticboy/vim-markdown)

提供了针对Markdown的语法高亮，段落折叠，查看目录，段间跳转等功能

安装与命令
```
"安装插件
Plug 'godlygeek/tabular' "必要插件，安装在vim-markdown前面
Plug 'plasticboy/vim-markdown'

" 关闭打开Markdown文件默认折叠
let g:vim_markdown_folding_disabled = 1

"查看所有配置建议
:help vim-markdwon
[[ "跳转上一个标题
]] "跳转下一个标题
]c "跳转到当前标题
]u "跳转到副标题
zr "打开下一级折叠
zR "打开所有折叠
zm "折叠当前段落
zM "折叠所有段落
:Toc "显示目录
```

