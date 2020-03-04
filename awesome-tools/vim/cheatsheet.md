| 命令 | 说明 | 备注 |
| --- | ---  | --- |
| ZZ | 保存并退出 | |
| gU{motion} | 指定文本转换为大写 | :h gU |
| :vsplit | 竖向分割窗口 | 缩写:vs |
| :split | 横向分隔窗口 | 缩写:sp |
| \<ctrl+c\>ww | 切换窗口 |  |
| |  | |
| |  | |
| 查找 |  |  |
| / | 正向查找 |  |
| ? | 反向查找 |  |
| * | 查找当前光标下的单词 |  |
| /xxx/e | 光标始终处于匹配词的尾部 | 同?xxx?e |
| n/N | 跳至下一处/上一处匹配 |  |
| gn/gN | 进入面向字符的可视模式，并选中下一处/上一处匹配 | 动作命令，例gUgn |
| set hlsearch/nohlsearch | 开启/关闭查找高亮匹配 | 默认开启 :h hlsearch |
| set incsearch | 查找域每输入一个新字符时，即时更新查找内容 | 默认开启 :h incsearch |
| :%s///gn | 统计匹配总数 | 同 :vimgrep //g % |
| 替换substitute命令 |  |  |
| g& | 在整个文件范围内重复上次的substitute命令 | 适用于执行substitute命令时忘记加全文范围 |

