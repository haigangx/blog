# Vector

- 头文件：`#include <vector>`
- 定义：
  ```
  namespace std {
      template<class T,
               class Allocator = allocator<T> >
      class vector;
  }
  ```
- 迭代器：随机存取迭代器(Random Access Iterators)
- 特征：动态数组

## Vector基本用法

### 构造vector

| 操作 | 效果 |
| --- | --- |
| vector<Elem> c | 构造一个空vector |
| vector<Elem> c1(c2) | 构造同型vectorc2的一个副本 |
| vector<Elem> c(n) | 利用元素默认构造函数构造大小为n的vector |
| vector<Elem> c(n, elem) | 构造大小为n的vector，每个元素都为elem |
| vector<Elem> c(beg, end) | 利用区间[beg;end]之间的元素构造vector |

### 赋值操作

下面的赋值操作会将旧值全部移除

| 操作 | 效果 |
| --- | --- |
| c1 = c2 | 将c2的全部元素赋值给c1 |
| c.assign(n, elem) | 给c赋值为n个elem |
| c.assign(beg, end) | 将区间[beg;end]内的元素赋值给c |
| c1.swap(c2) | 将c1和c2元素互换，同swap(c1, c2) |

### 增加元素

| 操作 | 效果 |
| --- | --- |
| c.insert(pos, elem) | 在pos位置插入新元素elem，并返回新元素位置 |
| c.insert(pos, n, elem) | 在pos位置插入n个elem, 无返回值 |
| c.insert(pos, beg, end) | 在pos位置插入区间[beg;end]内的所有元素，无返回值 |
| c.push_back(elem) | 尾部插入elem |

### 删除元素

| 操作 | 效果 |
| --- | --- |
| c.erase(pos) | 移除pos位置上的元素，返回下一元素位置 |
| c.erase(beg, end) | 移除[beg;end]区间内的所有元素，返回下一元素位置 |
| c.resize(num) | 元素数量resize为num个，size变大时，新元素以默认构造函数完成 |
| c.resize(num, elem) | 元素数量resize为num个，size变大时，新元素为elem副本 |
| c.clear() | 移除所有元素 |

### 查找元素

| 操作 | 效果 |
| --- | --- |

### 元素比较

以下判断对vector内含元素进行判断

| 操作 | 效果 |
| --- | --- |
| c1 ==/!= c2 | c1和c2的相等判断 |
| c1 >/>= c2 | c1 大于/大于等于 c2 |
| c1 </<= c2 | c1 小于/小于等于 c2 |


### 迭代器

| 操作 | 效果 |
| --- | --- |
| c.begin() | 返回随机存取迭代器，指向第一元素 |
| c.end() | 返回随机存取迭代器，指向最后元素的下一个位置 |
| c.rbegin() | 返回逆向迭代器，指向逆向迭代的第一元素 |
| c.rend() | 返回逆向迭代器，指向逆向迭代器的最后元素的下一个位置 |

### 其他操作

| 操作 | 效果 |
| --- | --- |
| c.size() | 当前元素数量 |
| c.empty() | 当前大小是否为空，可能比size()==0快 |
| c.max_size() | 可容纳的元素最大数量 |

## Vector详细解析

SGI STL将vector实现于更底层的`<stl_vector.h>`

### vector的迭代器

### vector的构造和内存管理：constructor, push_back

### vector的元素操作：pop_back, erase, clear, insert
