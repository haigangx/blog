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


[参考](https://blog.csdn.net/xiaoquantouer/article/details/52015928)
