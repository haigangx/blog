# STL容器——Map

头文件：`#include <map>`

迭代器：双向迭代器

map将键值对(key/value pair)当作元素管理，它可根据key将元素自动排序，map不允许重复元素，[multimaps](https://github.com/haigangx/learning/blob/master/stl/stl_map.md#multimap)可允许重复元素，标准STL map底层使用平衡二叉树——红黑树实现



## Map的简单用法

### 操作函数

- 构造map

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

- 赋值操作

  | 操作 | 效果 |
  | --- | --- |
  | c1 = c2 | 将c2中所有元素赋值给c1 |
  | c1.swap(c2) | 将c1和c2的元素互换，也可以使用全局函数swap(c1, c2) |
  
  赋值操作两端的容器必须具备相同型别，尽管"比较准则"本身可能不同，但其型别必须相同
  

- 增加元素

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

- 删除元素

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

- 元素查找

  | 操作 | 效果 |
  | --- | --- |
  | c.count(key) | 返回"键值等于key"的元素个数 |
  | c.find(key) | 返回"键值等于key"的第一个元素，返回其迭代器，否则返回end()，查找拥有某特定value的元素，采用其他方法，如find_if()等 |
  | c.lower_bound(key) | 返回"键值为key"的元素的第一个可安插位置，也就是"键值>=key"的第一个元素位置 |
  | c.upper_bound(key) | 返回"键值为key"的元素的最后一个可安插位置，也就是"键值>key"的第一个元素位置 |
  | c.equal_range(key) | 返回"键值为key"的元素的第一个和最后一个可插入位置区间，即"键值==key"的元素区间 |
  

- 元素比较

  | 操作 | 效果 |
  | --- | --- |
  | c1 == c2/c1 != c2 | c1是否等于c2 |
  | c1 < c2/c1 > c2 | 是否c1大于/小于c2 |
  | c1 <= c2/c1 >= c2 | 是否c1大于等于/小于等于c2 |

  比较基于两个规则：
  
  - 正常下比较只能进行于相同型别(排序规则相同)的容器，不同型别容器间比较需采用equal算法
  - 比较的步骤基于[字典顺序]()

- 迭代器

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
  
- 使用下标存取map

  | 操作 | 效果 |
  | --- | --- |
  | c[key] | 返回一个reference，指向键值为key的元素，如果该元素尚未存在，就安插该元素 |
  
  - coll["otto"]
  
    在coll中查看key为"otto"的元素并返回其reference，如果coll中没有该元素，则插入该新元素，其key为"otto"，value由默认构造函数初始化
  
  - coll["otto"] = 2.33
  
    将coll中查找key并设其value为2.33，如果没有该元素，则插入新元素
    
    注意：这种元素插入方法相比一般的插入方法慢，因为这种方法下，新元素必须先使用默认构造函数将value初始化，然后再被赋值的真正value值覆盖

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
  
## 性能分析

## 其他Map

### multimap

头文件：`#include <map>`

`multimap`的特性及用法与map完全相同，底层也使用红黑树实现，唯一的差别在于它允许键值重复，因为它的插入操作采用红黑树的`insert_equal()`而非`insert_unique()`

### unordered_map

头文件：`#include <unordered_map>`

`unordered_map`是map的无序版本，底层使用哈希表实现，

### unordered_multimap

头文件：`#include <unordered_map>`

`unordered_multimap`是multimap的无序版本，底层使用哈希表实现，

