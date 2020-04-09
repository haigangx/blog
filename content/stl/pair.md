# pair

[cplusplus](http://www.cplusplus.com/reference/utility/pair/)

pair就是将2个数据组合成一个数据，当需要这样的需求时就可以使用pair

## 定义：
  
```
#include <utility>
template<class T1, class T2>
struct pair {
    typedef T1 first_type;
    typedef T2 second_type;
    T1 first;
    T2 second;
    pair() : first(T1()), second(T2()) {}
    pair(const T1& a, const T2& b) : first(a), second(b) {}
};
```

```
template pair make_pair(T1 a, T2 b) {return pair(a, b);}
```

## 使用

```
std::pair<int, float> p0();         //默认构造函数
std::pair<int, float> p1(1, 1.1);   //给定值初始化
std::pair<int, float> p2(p1);       //拷贝构造函数
pair<int, float> p3 = make_pair(1, 1.1);  //利用make_pair函数

//使用值
p3.first = 2;
p3.second = 2.2;
```

## 使用场景：

### 1. vector中

  ```
  vector<std::pair<int, int> >& points; 
  ```

