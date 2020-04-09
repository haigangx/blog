# 条款24：若所有参数皆需类型转换，请为此采用non-member函数

假如你有下面的表示分数的类：

```
class Rational
{
public:
    Rational(int numerator = 0,     //构造函数刻意不为explicit，允许int-to-Rational隐式转换
            int denominator = 1);
    int numerator() const;      //分子和分母的访问函数
    int denominator() const;
private:
    ...
};
```

你想为这个表示分数的类增加算术运算，以乘法为例，但是你不确定增加的operator*函数是定义为member函数还是non-member函数：

先研究一下将operator*写成Rational成员函数的写法：

```
class Rational
{
public:
    ...
    const Rational operator* (const Rational& rhs) const;
};
```

这个设计可以满足大多数情况下的乘法：

```
Rational oneEighth(1, 8);
Rational oneHalf(1, 2);
Rational result = oneHalf * oneEighth;  //很好
result = result * oneEighth;            //很好
```

然而当你尝试混合算术时，发现只有一半行得通：

```
result = oneHalf * 2;   //很好
result = 2 * oneHalf;   //错误
```

上面的例子需要我们将2强转类型为Rational才能编译成功，这时我们可以将member函数写为non-member函数：

```
class Rational
{
    ...
};
const Rational operator*(const Rational& lhs, const Rational& rhs);
{
    return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator()*rhs.denominator());
}
```

```
result = oneHalf * 2;   //没问题
result = 2 * oneHalf;   //没问题
```

**Remember：**

如果你需要为某个函数的所有参数(包括被this指针所指的那个隐喻参数)进行类型转换，那么这个函数必须是个non-member.
