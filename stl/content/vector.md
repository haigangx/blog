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

## 一、Vector基本用法

### 1. 构造vector

| 操作 | 效果 |
| --- | --- |
| vector<Elem> c | 构造一个空vector |
| vector<Elem> c1(c2) | 构造同型vectorc2的一个副本 |
| vector<Elem> c(n) | 利用元素默认构造函数构造大小为n的vector |
| vector<Elem> c(n, elem) | 构造大小为n的vector，每个元素都为elem |
| vector<Elem> c(beg, end) | 利用区间[beg;end]之间的元素构造vector |

### 2. 赋值操作

下面的赋值操作会将旧值全部移除

| 操作 | 效果 |
| --- | --- |
| c1 = c2 | 将c2的全部元素赋值给c1 |
| c.assign(n, elem) | 给c赋值为n个elem |
| c.assign(beg, end) | 将区间[beg;end]内的元素赋值给c |
| c1.swap(c2) | 将c1和c2元素互换，同swap(c1, c2) |

### 3. 增加元素

| 操作 | 效果 |
| --- | --- |
| c.insert(pos, elem) | 在pos位置插入新元素elem，并返回新元素位置 |
| c.insert(pos, n, elem) | 在pos位置插入n个elem, 无返回值 |
| c.insert(pos, beg, end) | 在pos位置插入区间[beg;end]内的所有元素，无返回值 |
| c.push_back(elem) | 尾部插入elem |

### 4. 删除元素

| 操作 | 效果 |
| --- | --- |
| c.erase(pos) | 移除pos位置上的元素，返回下一元素位置 |
| c.erase(beg, end) | 移除[beg;end]区间内的所有元素，返回下一元素位置 |
| c.resize(num) | 元素数量resize为num个，size变大时，新元素以默认构造函数完成 |
| c.resize(num, elem) | 元素数量resize为num个，size变大时，新元素为elem副本 |
| c.clear() | 移除所有元素 |

- 直接删除"与某值相等"的所有元素：
  ```
  c.erase( remove(c.begin(), c.end(), val),
           c.end );
  ```

- 删除"与某值相等"的第一个元素：
  ```
  vector<Elem>::iterator pos;
  pos = find( c.begin(), c.end(), val );
  if (pos != c.end()) {
      c.erase(pos);
  }
  ```

### 5. 元素存取

| 操作 | 效果 |
| --- | --- |
| c.at(idx) | 返回索引idx处的元素，如果idx越界，抛出out_of_range |
| c[idx] | 返回索引idx处的元素，不进行范围检查 |
| c.front() | 返回第一个元素。要确保vector非空 |
| c.back() | 返回最后一个元素。要确保vector非空 |

### 6. 元素比较

以下判断对vector内含元素进行判断

| 操作 | 效果 |
| --- | --- |
| c1 ==/!= c2 | c1和c2的相等判断 |
| c1 >/>= c2 | c1 大于/大于等于 c2 |
| c1 </<= c2 | c1 小于/小于等于 c2 |


### 7. 迭代器

| 操作 | 效果 |
| --- | --- |
| c.begin() | 返回随机存取迭代器，指向第一元素 |
| c.end() | 返回随机存取迭代器，指向最后元素的下一个位置 |
| c.rbegin() | 返回逆向迭代器，指向逆向迭代的第一元素 |
| c.rend() | 返回逆向迭代器，指向逆向迭代器的最后元素的下一个位置 |

#### 7.1 迭代器失效问题：

迭代器泛指：reference、pointers、iterator等

迭代器失效问题的两种理解：

- 1. 迭代器不可用，因为指向不可用的内存空间

  一般来说，vector因容量变化导致重新分配内存空间时，可能会导致迭代器这种失效：

  - 添加元素：因为添加元素可能会导致，vector因为容量不够而重新分配内存空间，这样原来的迭代器所指的内存空间就完全失效了
  - swap操作：因为swap函数作用于vector时，不仅会交换两者的元素，还会交换容量，这样会引起vector会重新分配内存空间来适应容量变化

- 2. 迭代器可用，但是指向的数据或元素与使用者意愿不符

  在较小索引位置上(非尾部)插入或删除元素，但不引起容量变化时会导致操作点之后的迭代器失效

### 8. 其他操作

| 操作 | 效果 |
| --- | --- |
| c.size() | 当前元素数量 |
| c.empty() | 当前大小是否为空，可能比size()==0快 |
| c.max_size() | 可容纳的元素最大数量 |
| c.capacity() | 重新分配空间前可容纳的最大元素个数 |
| c.reserve(n) | vector的空间扩大到可容纳n个元素的空间，不支持缩减容量，若n小于当前容量，不引发任何反应 |

#### 8.1 使用reserve()

如果创建vector的时候就确定了元素的个数，可以使用reserve()避免后期重新分配空间

```
vector<string> sentence;
sentence.reserve(10);

sentence.push_back("hello, ");
```


#### 8.2 使用copy函数输出vector

```
//使用空格分隔各元素
copy(sentence.begin(), sentence.end(), ostream_iterator<string>(cout, " "));
cout << endl;
```

#### 8.3 尽量在末尾增删元素

尽量在末尾删除和添加元素，避免在前端或中端添加或删除，因为会导致操作点后的所有元素进行移位操作

#### 8.4 使用swap()缩减容量

一般来说，不为vector提供缩小容量的操作，但是可以使用swap间接缩减vector容量

swap()函数交换时也会将vector的容量交换

```
std::vector<T>(v).swap(v);
```

注意：交换后会引起迭代器失效问题


## 二、Vector详细解析

SGI STL将vector实现于更底层的`<stl_vector.h>`

### 1. vector的迭代器

### 2. vector的构造和内存管理：constructor, push_back

### 3. vector的元素操作：pop_back, erase, clear, insert

## 三、性能分析

## 四、Vector特殊版本

### 1. class vector\<bool>

vector<bool>可以当作动态大小的位域(bitfileld)，可以添加或移除bits，也提供了更方便地操作bit的接口，如果你需要静态大小的bitfield，应当使用[bitset]()
  
| 操作 | 效果 |
| --- | --- |
| c.flip() | 将所有bool元素值取反值 |
| c[idx].flip() | 将索引idx上的bit元素取反值 |
| c[idx] = val | 令索引idx的bit元素值为val |
| c[idx1] = c[idx2] | 令索引idx1的bit元素值为idx2处的元素值 |
