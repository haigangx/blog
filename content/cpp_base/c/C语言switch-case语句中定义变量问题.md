# C语言switch case语句中定义变量问题

这个问题需要分开讨论，C 语言和 C++ 的标准定义是不同的。

## C++

```
int Caset(int a) {
    switch (a) {
        case 1:
            int b = 1;
            std::cout<<"a==1: "<<b<<std::endl;
            break;
        case 2:
            b = 2;
            std::cout<<"a==2: "<<b<<std::endl;
            break;
    }
}
```
编译报错信息为

```
simple.cc:35:9: error: cannot jump from switch statement to this case label
      case 2:
      ^
simple.cc:32:17: note: jump bypasses variable initialization
          int b = 1;
              ^
```

也就是说，跳到 case2 的这个地方，忽略了对于 b 这个变量的初始化，这个很直观，就是在这里我找不到 b。

那么如果改成

```
int Caset(int a) {
    switch (a) {
        case 1:
            int b;
            b = 1;
            std::cout<<"a==1: "<<b<<std::endl;
            break;
        case 2:
            b = 2;
            std::cout<<"a==2: "<<b<<std::endl;
            break;
    }
}
```

顺利成功，没有报错，如果 a 为 2，那么输出 b 也是 2，说明逻辑没有问题。那么问题来了，b 在前面声明，为什么后面可以用到呢，
因为 switch-case 的逻辑控制就是用 label 来标记跳转的，而不是别的复杂的逻辑控制，所以 b 的作用域是在整个 switch 的花括号内，
关于这个问题见知乎讨论[请教switch内部的变量定义问题](https://www.zhihu.com/question/23051685)

## C语言

上面两种写法统统出错，
```
void Caset(int a) {
    switch (a) {
        case 1:
            /* one style */
            int b;
            b = 1;
            
            /* another style */
            int b = 1;

            printf("1: %d", b);
            break;
        case 2:
            b = 2;
            printf("2: %d", b);
            break;
    }
}
```

两种写法都错，报错信息：

```
	main.c:12:13: error: expected expression
        int b; 
        ^
	main.c:13:13: error: use of undeclared identifier 'b'
        b = 1;
        ^
```

意思是说，此处需要一个表达式（expression），而不是一个变量声明初始化。有一个很黑客的做法，如下：

```
void Caset(int a) {
    switch (a) {
        case 1:
            ; 
            int b = 1;
            // b = 1;

            printf("1: %d \n", b);
            break;
        case 2:
            b = 2;
            printf("2: %d \n", b);
            break;
    }
}
```

这个很不能理解了，其实也就是说保证 case 后面跟着的确实是 expression 即可。考虑一下 C++ 代码出现的问题：跳过变量的声明？C 语言中同样跳过，
但是编译器不认为这个是错误，而且逻辑上面也是没有问题的，在后面的 case 中可以正常给变量赋值，但是如果 case2 中，我不是给 b 赋值，
而是直接访问 b，那返回的数值就是一个随机的错误的数据了，我在我的电脑上使用 gcc 编译，若直接读取数据，得到的是 0，当然编译通过，连警告都没有。

当然我认为这样的代码可读性差，比较好的做法可以是将声明变量的事情放在头上做

```
void Caset(int a) {
    switch (a) {
        int b;
        case 1:
            b = 1;
            // b = 1;
            printf("1: %d \n", b);
            break;
        case 2:
            b = 2;
            printf("2: %d \n", b);
            break;
    }
}
```

但是要留心， switch 和 case 之前那块地方也就只能写写这样的声明，写别的表达式，赋值啊什么的，统统是不会生效的。
