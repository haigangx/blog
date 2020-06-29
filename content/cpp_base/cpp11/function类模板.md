# function类模板

function 是一个模板，其定义在 `functional` 头文件中，和其他模板一样，为其传入可调用对象必须的额外信息，其可以表示一种类型的可调用对象

```c++
function<int(int, int)>
```

上面我们声明了一个 function 类型，它可以表示接受两个 int，返回一个 int 的可调用对象

我们可以用这个新声明的类型表示一种计算器用到的类型：

```c++
function<int(int, int)> f1 = add;               //函数指针
function<int(int, int)> f2 = divide();          //函数对象类的对象
function<int(int, int)> f3 = [](int i, int j)   //lambda
                             { return i * j; };

cout << f1(4, 2) << endl;   //打印6
cout << f2(4, 2) << endl;   //打印2
cout << f3(4, 2) << endl;   //打印8
```