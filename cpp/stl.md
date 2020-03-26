## STL技法

<details><summary>迭代器</summary>
</details>

<details><summary>空间配置器</summary>
</details>

<details><summary>仿函数</summary>

# 仿函数


## 预先定义的仿函数

| 函数 | 功能 |
| --- | --- |
| less<typename> | operator<排序准则 |
| greater<typename> | operator>排序准则 |
| negate<typename> | 取相反值运算 |
| multiplies<typename> | 乘法运算 |
| mem_fun_ref(&Person::save) | 用来调用它所作用的元素的某个成员函数 |
</details>

<details><summary>配接器</summary>
</details>

## 序列式容器

<details><summary>vector</summary>

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

- 删除下标为i的元素
  ```
  c.erase( c.begin() + i );
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
</details>

<details><summary>list</summary>
</details>

<details><summary>deque</summary>
</details>

<details><summary>stack</summary>
</details>

<details><summary>queue</summary>
</details>

<details><summary>heap</summary>
</details>

<details><summary>priority_queue</summary>

# 优先队列priority_queue

- 头文件：`#include <queue>`
- 定义：
  ```
  namespace std {
      template <class T,
                class Container = vector<T>,
                class Compare = less<typename Container::value_type> >
      class priority_queue;
  };
  ```
- 迭代器：无
- 特征：大顶堆、小顶堆
  
  

## 一、基本用法

### 1. 核心接口

#### 1.1 构造函数

| 操作 | 说明 |
| --- | --- |
| priority_queue() | 产生一个空的priority_queue() |
| priority_queue(const CompFunc& op, const Container& cont) | 以op为排序准则，并以容器cont的元素为初值 |
| priority_queue(InputIterator beg, InputIterator end) | 以[beg, end)间的元素为初值 |
| priority_queue(InputIterator beg, InputIterator end, const ComFunc& op) | 以[beg, end)为初值，op为排序准则 |
| priority_queue(InputIterator beg, InputIterator end, const ComFunc& op, const Container& cont) | 以[beg, end)和cont为初值，op为排序准则 |

#### 1.2 操作函数

| 操作 | 说明 |
| --- | --- |
| push() | 将一个元素置入priority_queue中 |
| top() | 返回priority_queue中的下一个元素，无元素时调用会导致未定义行为 |
| pop() | 从priority_queue中移除一个元素，无元素调用会导致未定义行为 |
| size() | 返回元素个数 |
| empty() | 返回容器是否为空 |

### 2. 构建大顶堆

priority_queue在无特殊说明时使用比较准则operator<，其构建的就是大顶堆

```
priority_queue<int> max_heap;
```

### 3. 构建小顶堆

构建小顶堆需要改变排序准则为operator>

```
priority_queue<int, std::vector<int>, std::greater<int> > min_heap;
```

### 4. 为自定义类型制定排序规则

当priority_queue的元素为自定义类型时，可以自定义仿函数来排序：
```
struct cmp {
    bool operator()(const Node& n1, const Node& n2) {
        if (n1.x == n2.x)
            return n1.y > n2.y;
        return n1.x > n2.x;
    }
};
priority_queue<Node, std::vector<Node>, cmp> node_heap;
```

### 5. 使用其他底层容器

priority_queue定义中第二个模板参数定义了其使用的底层容器，缺省为vector。由于priority_queue需要用到[STL heap算法]()，所以**其内部容器必须支持随机存取迭代器，并且支持front(), push_back(), pop_back()等操作**，例如可以使用deque来作为其底层容器：

```
priority_queue<int, std::deque<int> > deque_heap;
```
</details>

<details><summary>slist</summary>
</details>

## 关联式容器

<details><summary>RB-Tree</summary>
</details>

<details><summary>hashtable</summary>
</details>

<details><summary>set</summary>
</details>

<details><summary>map</summary>

# STL容器——Map


- 头文件：`#include <map>`
- 定义：
  ```
  namespace std {
      template <class Key, class T,
                class Compare = less<Key>,
                class Allocator = allocator<pair<const Key,T> > >
      class map;
  }
  ```
- 迭代器：双向迭代器
- 底层：红黑树
- 特征：键值对、自动排序、不可重复

map将键值对(key/value pair)当作元素管理，它可根据key将元素自动排序，map不允许重复元素，[multimaps](https://github.com/haigangx/learning/blob/master/stl/stl_map.md#multimap)可允许重复元素，标准STL map底层使用平衡二叉树——红黑树实现



## 一、Map的简单用法

### 1. 构造map

| 操作 | 效果 |
| --- | --- |
| map<Key, Elem> c | 产生一个空的map，其中不含任何元素，默认使用less<>(operator<)为排序准则 |
| map<Key, Elem, Op> c | 以op为排序准则型别，产生一个空的map，也可以用map<Key, Elem> c(op)设置排序准则 |
| map<Key, Elem> c1(c2) | 产生map c2的副本，所有元素均被复制 |
| map<Key, Elem> c(beg, end) | 以区间[beg, end]内的元素初始化map，必须保证区间内的元素类型也是pair或者可转化为pair |
| map<Key, Elem> c(beg, end) | 以op为排序准则，利用[beg, end]内元素初始化map |

- 更改排序准则

```
std::map<std::string, float, std::greater<std::string> > stringfloatmap;
```

- 使用仿函数自定义排序准则型别，并在运行期指定排序准则

```
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

//为map定义排序准则型别
class RuntimeStringCmp {
public:
    enum cmp_mode {normal, nocase};

private:
    const cmp_mode mode;

    static bool nocase_compare(char c1, char c2) {
        return toupper(c1) < toupper(c2);
    }

public:
    RuntimeStringCmp(cmp_mode m=normal) : mode(m) {}

    bool operator()(const string& s1, const string& s2) const {
        if (mode == normal) {
            return s1 < s2;
        } else {
            return lexicographical_compare(s1.begin(), s1.end(), 
                                           s2.begin(), s2.end(), 
                                           nocase_compare);
        }
    }
};

typedef map<string, string, RuntimeStringCmp> StringStringMap;

//为map填充内容并打印其值
void fillAndPrint(StringStringMap& coll);

int main() {
    StringStringMap coll;
    fillAndPrint(coll);

    //定义忽略大小的比较器
    RuntimeStringCmp ignorecase(RuntimeStringCmp::nocase);

    StringStringMap coll2(ignorecase);
    fillAndPrint(coll2);
}
```
coll和coll2的比较准则不同，coll使用RuntimeStringCmp的缺省仿函数，coll2使用型别为RuntimeStringCmp的仿函数，但为其指定nocase为初始值，使其排序时忽略大小写，两者在填充同样的值时输出顺序不同


### 2. 赋值操作

| 操作 | 效果 |
| --- | --- |
| c1 = c2 | 将c2中所有元素赋值给c1 |
| c1.swap(c2) | 将c1和c2的元素互换，也可以使用全局函数swap(c1, c2) |

赋值操作两端的容器必须具备相同型别，尽管"比较准则"本身可能不同，但其型别必须相同
  

### 3. 增加元素

| 操作 | 效果 |
| --- | --- |
| c.insert(elem) | 插入elem到map，返回新元素的位置 |
| c.insert(pos, elem) | 插入elem到map，返回新元素位置，pos用于提示插入操作的搜寻起点，提示恰当有助于加速插入 |
| c.insert(beg, end) | 将[beg, end]内所有元素副本插入到c(无返回值) |

插入元素到map时，要保证插入的是正确的key/value pair，key被视为常数，下面有三种方法来插入元素：

- **运用value_type**

  ```
  std::map<std::string, float> coll;
  ...
  coll.insert(std::map<std::string, float>::value_type("otto", 22.3))
  ```

- **运用pair<>**

  ```
  coll.insert(std::pair<const std::string, float>("otto", 22.3));
  ```

- **运用make_pair()**

  ```
  coll.insert(std:make_pair("otto", 22.3));
  ```

- **C11：使用大括号{}**

  ```
  coll.insert({"otto", 22.3});
  ```

### 4. 删除元素

| 操作 | 效果 |
| --- | --- |
| c.erase(elem) | 移除"value与elem"相等的所有元素，返回被移除的元素个数，map上非0即1 |
| c.erase(pos) | 移除迭代器pos所指位置上的元素，无返回值 |
| c.erase(beg, end) | 移除区间[beg, end]内的所有元素，无返回值 |
| c.clear() | 清空map，移除全部元素 |

对map进行删除操作时，除了被删除的元素迭代器之外，操作之前的其他迭代器在操作之后仍有效

在删除过程中，要注意被删除元素迭代器的失效问题：
```
typedef std::map<std::string, float> StringFloatMap;
StringFloatMap coll;
StringFloatMap::iterator pos;
...
for (pos = coll.begin(); pos != coll.end(); ++pos) {
    if (pos->second == value) {
        //千万不要写成coll.erase(pos)，因为删除完pos已经无效了，再执行pos++会导致未定义行为
        coll.erase(pos++);  
    }
    else {
        ++pos;
    }
}
```

### 5. 元素查找

| 操作 | 效果 |
| --- | --- |
| c.count(key) | 返回"键值等于key"的元素个数 |
| c.find(key) | 返回"键值等于key"的第一个元素，返回其迭代器，否则返回end()，查找拥有某特定value的元素，采用其他方法，如find_if()等 |
| c.lower_bound(key) | 返回"键值为key"的元素的第一个可安插位置，也就是"键值>=key"的第一个元素位置 |
| c.upper_bound(key) | 返回"键值为key"的元素的最后一个可安插位置，也就是"键值>key"的第一个元素位置 |
| c.equal_range(key) | 返回"键值为key"的元素的第一个和最后一个可插入位置区间，即"键值==key"的元素区间 |
  

### 6. 元素比较

| 操作 | 效果 |
| --- | --- |
| c1 == c2/c1 != c2 | c1是否等于c2 |
| c1 < c2/c1 > c2 | 是否c1大于/小于c2 |
| c1 <= c2/c1 >= c2 | 是否c1大于等于/小于等于c2 |

比较基于两个规则：

- 正常下比较只能进行于相同型别(排序规则相同)的容器，不同型别容器间比较需采用equal算法
- 比较的步骤基于[字典顺序]()

### 7. 迭代器

| 操作 | 效果 |
| --- | --- |
| c.begin() | 返回一个双向迭代器，指向第一元素 |
| c.end() | 返回一个双向迭代器，指向最后一个元素的下一个位置 |
| c.rbegin() | 返回一个逆向迭代器，指向逆向遍历时的第一个元素 |
| c.rend() | 返回一个逆向迭代器，指向逆向遍历时的最后元素的下一个位置 |

```
std::map<std::string, float> coll;
...
std::map<std::string, float>::iterator pos;
for (pos = coll.begin(); pos != coll.end(); ++pos) {
    std::cout << "key: " << pos->first << "\t" 
              << "value: " << pos->second << std::endl;
}
```

要注意的点是：

无法通过map迭代器修改map元素的key，因为key关系着map元素的正确次序，任意改变key将导致map结构被破坏，但是可以通过迭代器修改元素value值，要修改元素的key，要先移除该key的元素，然后插入一个"value相同"的新元素
  
### 8. 使用下标存取map

| 操作 | 效果 |
| --- | --- |
| c[key] | 返回一个reference，指向键值为key的元素，如果该元素尚未存在，就安插该元素 |

- coll["otto"]

  在coll中查看key为"otto"的元素并返回其reference，如果coll中没有该元素，则插入该新元素，其key为"otto"，value由默认构造函数初始化

- coll["otto"] = 2.33

  将coll中查找key并设其value为2.33，如果没有该元素，则插入新元素

  注意：这种元素插入方法相比一般的插入方法慢，因为这种方法下，新元素必须先使用默认构造函数将value初始化，然后再被赋值的真正value值覆盖

### 9. 其他操作
  
| 操作 | 效果 |
| --- | --- |
| c.size() | 返回容器大小 |
| c.empty() | 判断容器大小是否为0，可能会比size() == 0更快 |
| c.max_size() | 返回可容纳的最大元素数量 |


## 二、Map详细解析

### 1. Map的元素——[pair](pair.md)

  
## 三、性能分析

## 四、其他Map

### 1. multimap

头文件：`#include <map>`

`multimap`的特性及用法与map完全相同，底层也使用红黑树实现，唯一的差别在于它允许键值重复，因为它的插入操作采用红黑树的`insert_equal()`而非`insert_unique()`

### 2. unordered_map

头文件：`#include <unordered_map>`

`unordered_map`是map的无序版本，底层使用哈希表实现，

### 3. unordered_multimap

头文件：`#include <unordered_map>`

`unordered_multimap`是multimap的无序版本，底层使用哈希表实现，

### 4. hash_map

头文件：`#include <hash_map>`

hash_map本质上与unordered_map相同，C++标准中并未纳入hash_map，而是加入了unordered_map，hash_map是标准的不同实现者提供的非标准散列表，hash_map和unordered_map底层实现和使用完全相同，由于hash_map未纳入标准，效率和功能可能会有微妙的差异

### 5. hash_multimap

头文件：`#include <hash_map>`

hash_multimap和unordered_multimap的关系同hash_map与unordered_map的关系相同

</details>

## 算法

<details><summary>sort</summary>

# sort

- 头文件：`#include <algorithms>`

- 定义

  sort接受两个`RandomAccessIterators（随机存取迭代器）`，将迭代器区间内的所有元素以指定顺序重新排列
  ```
  void sort(RandomAccessIterator beg, RandomAccessIterator end);  //默认以递增方式由小到大排列operator<
  void sort(RandomAccessIterator beg, RandomAccessIterator end, BinaryPredicate op);  //指定排序准则op
  ```
- 使用范围：

  - STL中所有关系型容器(set、map、multiset、multimap等)底层都采用RB-tree，都拥有自动排序功能，不需要用到sort算法
  - stack、queue和priority-queue等容器都有特定的出入口，不允许用户排序，也用不到sort算法
  - list的迭代器属于BidirectionalIterators，slist的迭代器是forwarditerators，都不能使用sort算法，要对这两个容器排序，需要使用它们自己提供的sort成员函数
  - **vector、deque非常适合使用sort算法**

## 一、sort用法：

### 1. 容器成员是基本类型

  ```
  deque<int> coll;
  ...  //为coll乱序插入元素1-9
  
  sort(coll.begin(), coll.end());  //1, 2, 3, ..., 9
  
  sort(coll.begin(), coll.end(), greater<int>()); //9, 8, ..., 1
  ```
  
### 2. 容器成员是自定义类时，根据类中某成员变量排序

  ```
  //容器成员是Person
  class Person {
  public:
      string firstname() const;
      string lastname() const;
  };
  
  //自定义比较函数
  bool personSortCriterion(const Person& p1, const Person& p2) {
      return p1.lastname() < p2.lastname() ||
      (!(p2.lastname() < p1.lastname()) && p1.firstname() < p2.firstname());
  }
  
  int main() {
      deque<Person> coll;
      ...
      sort(coll.begin(), coll.end(),  //排序范围
           personSortCriterion);      //使用自定义排序函数
      ...
  }
  ```

## 二、sort解析：

sort算法，数据量大时采用quick sort，分段递归排序，一旦分段后的数据量小于某个门槛，为避免quick sort的递归调用带来过大的额外负担，就改用insert sort，
如果递归层次过深，还会改用heap sort

具体查看《STL源码剖析》

## 三、其他排序算法

### 1. stable_sort

stable_sort和sort的区别在于，stable_sort保证相等元素的原本相对次序在排序后保持不变

```
void stable_sort(RandomAccessIterator beg, RandomAccessIterator end);
void stable_sort(RandomAccessIterator beg, RandomAccessIterator end, BinaryPredicate op);
```

### 2. 局部排序partial_sort

### 3. nth_element

</details>

## 辅助工具

<details><summary>pair</summary>

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

</details>

## 总结

<details><summary>STL容器迭代器失效总结</summary>

# STL容器迭代器失效问题总结

## vector

[参考](https://github.com/haigangx/learning/blob/master/stl/vector.md#%E8%BF%AD%E4%BB%A3%E5%99%A8%E5%A4%B1%E6%95%88%E9%97%AE%E9%A2%98)

</details>
