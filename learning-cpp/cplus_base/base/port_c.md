# 移植C/C++

### itoa移植到Linux

```
char *  itoa ( int value, char * str, int base );
```
base代表进制，可取2、6、10等

```
sprintf(str,"%d",value) converts to decimal base.
sprintf(str,"%x",value) converts to hexadecimal base.
sprintf(str,"%o",value) converts to octal base.
```

### __int64

```
#include <inttypes.h>
typedef int64_t __int64;
```

[移植c/c++代码](https://www.ibm.com/developerworks/cn/aix/library/au-porting/index.html)

