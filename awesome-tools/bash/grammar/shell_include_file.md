# shell文件包含

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
