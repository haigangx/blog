# STL容器——Map

map将键值对(key/value pair)当作元素管理，它可根据key将元素自动排序，map不允许重复元素，multimaps可允许重复元素，标准STL map底层使用平衡二叉树——红黑树实现

## Map的简单用法

### 操作函数

- 构造map

  | 操作 | 效果 |
  | --- | --- |
  | map<Key, Elem> c | 产生一个空的map，其中不含任何元素，默认使用less<>(operator<)为排序准则 |
  | map<Key, Elem, Op> c | 以op为排序准则，产生一个空的map，也可以用map<Key, Elem> c(op)设置排序准则 |
  | map<Key, Elem> c1(c2) | 产生map c2的副本，所有元素均被复制 |
  | map<Key, Elem> c(beg, end) | 以区间[beg, end)内的元素初始化map，必须保证区间内的元素类型也是pair或者可转化为pair |
  | map<Key, Elem> c(beg, end) | 以op为排序准则，利用[beg, end)内元素初始化map |


- 增加元素

- 删除元素

- 元素查找

  | 操作 | 效果 |
  | --- | --- |
  | count(key) | 返回"键值等于key"的元素个数 |
  | find(key) | 返回"键值等于key"的第一个元素，返回其迭代器，否则返回end() |
  | iower_bound(key) | 返回"键值为key"的元素的第一个可安插位置，也就是"键值>=key"的第一个元素位置
  | upper_bound(key) | 

- 元素比较

  | 操作 | 效果 |
  | --- | --- |
  | c1 == c2/c1 != c2 | c1是否等于c2 |
  | c1 < c2/c1 > c2 | 是否c1大于/小于c2 |
  | c1 <= c2/c1 >= c2 | 是否c1大于等于/小于等于c2 |

  比较基于两个规则：
  
  - 正常下比较只能进行于相同型别(排序规则相同)的容器，不同型别容器间比较需采用equal算法
  - 比较的步骤基于[字典顺序]()

- 其他操作
  
  | 操作 | 效果 |
  | --- | --- |
  | c.size() | 返回容器大小 |
  | c.empty() | 判断容器大小是否为0，可能会比size() == 0更快 |
  | c.max_size() | 返回可容纳的最大元素数量 |



## Map详细解析

- Map的元素——pair
  
  ```
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

无法通过map迭代器修改map元素的key，因为key关系着map元素的正确次序，任意改变key将导致map结构被破坏，但是可以通过迭代器修改元素value值，
要修改元素的key，要先移除该key的元素，然后插入拥有新key/value的元素

对map进行增删操作时，除了被删除的元素迭代器之外，操作之前的其他迭代器在操作之后仍有效

- 

