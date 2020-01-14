# sort


<!-- vim-markdown-toc Marked -->

* [一、sort用法：](#一、sort用法：)
  * [1. 容器成员是基本类型](#1.-容器成员是基本类型)
  * [2. 容器成员是自定义类时，根据类中某成员变量排序](#2.-容器成员是自定义类时，根据类中某成员变量排序)
* [二、sort解析：](#二、sort解析：)
* [三、其他排序算法](#三、其他排序算法)
  * [1. stable_sort](#1.-stable_sort)
  * [2. 局部排序partial_sort](#2.-局部排序partial_sort)
  * [3. nth_element](#3.-nth_element)

<!-- vim-markdown-toc -->

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

