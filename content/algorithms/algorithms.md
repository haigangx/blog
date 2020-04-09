## 数据结构

### 字符串

#### 字符串排序

<details><summary>键索引计数法</summary>

### 键索引计数法

对键长度较小的字符串排序中，一般使用 *键索引计数法* ，其过程类似于计数排序，在上述两种字符串排序方法的过程中，可以在按位排序时使用这种方法辅助排序

键索引计数法使用计数排序的思想对键索引进行排序来完成键值对的排序

![键索引计数法排序](img/key_count_sort.png)

#### 过程

排序的步骤：

- 使用int数组conut[]计算每个键出现的频率。如果键为r，则将count[r+1]加1(这样的话，count[r+1]中保存r键的出现频率，count[r+1]之前所有元素的和是r键在排序结果中的位置)
- 将count[]转化为每个键在排序结果中的起始索引位置。对于键值r来说，其排序后的起始索引位置为所有键值小于r的键的频率之和，
- 将所有键值对排序到辅助数据aux[]中，每排序好一个键值对，需要将count[]中对应元素的值加1，以保证count[r]总是下一个键为r的元素在aux[]中的索引位置

键索引计数法是一种对于小整数键排序非常有用却常常被忽略的排序方法


#### 代码：

```
#include <utility>
#include <string>
#include <vector>

using namespace std;

const int COUNT_SIZE = 11;

void key_count_sort(vector<pair<int, string> >& std_table)
{
    int count[COUNT_SIZE] = {0};
    //第一步
    for (auto v : std_table)
    {
        count[v.first+1]++;
    }
    //第二步
    for (int i = 1; i < COUNT_SIZE; i++)
    {
        count[i] = count[i] + count[i-1];
    }
    //第三步
    vector<pair<int, string> > std_sort_table(std_table.size());
    for (auto v : std_table)
    {
        std_sort_table[count[v.first]] = v;
        count[v.first]++;
    }
    //回写
    for (int i = 0; i < std_table.size(); ++i)
    {
        std_table[i] = std_sort_table[i];
    }
}

```

</details>

<details><summary>低位优先的字符串排序</summary>

### 低位优先的字符串排序

低位优先的字符串排序： 从右向左检查字符串中的字符，分别按每一位上的字符对字符串排序，类似于基数排序，这种方法一般称为 *低位优先(LSD)* 的字符串排序，低位优先的字符串排序适合于键长度都相同的字符串排序

以案例说明：

> 假设我们需要对一堆车牌号进行排序，车牌号由数字和字母组成，一般情况下，它们的长度都相同（类似的定长字符串还有电话号码、银行账户、IP地址等）

低位优先字符串排序很适合上述排序：

低位优先字符串排序的意义在于，它是一种适用于一般应用的*线性时间排序算法*：无论要排序的字符串数量N多大，它都只需要遍历W(每个字符串长度)次数据

![低位优先的字符串排序](img/lsd_sort.png)

将上图中的字符串从右到左的顺序依次按位进行排序，每次排序可以使用键索引计数法，键索引计数法是一种稳定的排序方法


```
//将每个元素长度均为w的字符串数组排序按低位优先排序
void LSD_sort(vector<string> str_vec, int w)
{
    int len = str_vec.size();
    int R = 256;
    vector<string> sort_str_vec(len);

    for (int i = w-1; i >= 0; i--)
    {
        int count[R+1] = {0};
        for (int j = 0; j < len; j++)
        {
            count[str_vec[j].at(i)]++;
        }
        for (int j = 1; j < R+1; j++)
        {
            count[j] = count[j] + count[j-1];
        }
        for (int j = 0; j < len; j++)
        {
            sort_str_vec[count[str_vec[j].at(i)]++] = str_vec[i];
        }
        for (int j = 0; j <len; j++)
        {
            str_vec[j] = sort_str_vec[j];
        }
    }
}
```

</details>

<details><summary>高位优先的字符串排序</summary>

### 高位优先的字符串排序

从左到右检查字符串中的字符，这种方法一般称为 *高位优先(MSD)* 的字符串排序，高位优先的字符串排序的优先在于：它不一定需要检查所有的输入就能够完成排序


要实现一个通用的字符串排序算法（字符串的长度不一定相同），应该考虑从左向右遍历所有字符，即高位优先的字符串排序，最终实现字符串的字典序排序。

实现这种思想可以采用递归算法：首先用键索引计数法将所有字符串按照首字母排序，然后（递归地）再将每个首字母所对应的子数组排序（忽略首字母，因为每一类中的所有字符串的首字母都是相同的），还可以再子数组较小时使用插入排序进行优化

高位优先字符串排序的最坏情况是所有的字符串键都相同，这时将递归对所有字符串每个字符进行比较

![高位优先字符串排序过程](img/string_msd_sort1.png)

思想讲起来总是很简单，不过当中的一些细节却是我们需要注意的。一个显而易见的问题就是怎么处理结尾字符的问题，因为MSD运行字符的长度不通，那么总会有字符串先结束，这时我们就需要对这些字符串进行处理。如果我们每个字符都去判断显然会很麻烦，因此我们选择一种巧妙的方式使用一个CharAt(string, int)函数来返回字``符串对应下标的字符，当对应下标不存在的时候我们返回-1

```
/* 转换函数：返回字符串中对应索引的字符
 * 参数：s：想要进行转换的字符串 i：字符索引
 * 返回值：对应索引的字符，若超出字符串长度返回-1
 */
char CharAt(string s, int i)
{
    if (i < s.length())
        return s[i];
    else
        return -1;
}
```

这样我们就可以把字符串结尾的情况同其余情况一起处理，同时保证了已结尾的字符串会在未结尾的字符串之前

```
void MSD(string *a, string*Aux, int *Count, int lo, int hi, int d)
{
    int const M = 3, R = 256;

    //小的子数组进行插入排序，与快速排序相同
    if (hi <= lo+M)
    {
        InsertionSort(a, lo, hi, d);
        return ;
    }

    //初始化索引数组
    for (int i = 0; i < R+2; i++)
    {
        Count[i] = 0;
    }

    //统计频数
    //特别说明：Count[0]:无用，Count[1]:长度为d的字符串个数
    for (int i = lo; i <= hi; i++)
    {
        Count[CharAt(a[i], d)+2]++;
    }

    //转换频数为索引
    for (int i = 0; i < R+1; i++)
    {
        Count[i+1] += Count[i];
    }

    //数组分类
    for (int i = lo; i < hi; i++)
    {
        Aux[Count[CharAt(a[i], d)+1]++] = a[i];
    }

    //回写
    for (int i = lo; i <= hi; i++)
    {
        a[i] = Aux[i-lo];
    }

    //递归排序
    //特别说明：Count[0]:长度为d的字符串索引的终止坐标
    for (int i = 0; i < R; i++)
    {
        MSG(a, Aux, Count, lo+Count[i], lo+Count[i+1]-1, d+1);
    }
}

/* 高位优先排序：将目标字符串进行高位优先排序
 * 参数：a:想要进行高位优先排序的数组 N:数组中元素的个数
 * 返回值：无
 */
void MSG(string *a, int N)
{
    int R = 256;
    int *Count = new int[R+2];
    string *Aux = new string[N];

    MSG(a, Aux, Count, 0, N-1, 0);

    Aux = NULL;
    delete Aux;
    Aux = NULL;
    delete Count;
    Count = NULL;
}
```

### 优化

#### 元素较少时使用插入排序

上面的两种字符串排序方法，不管是低位优先还是高位优先，都采用键索引计数法排序，这种排序方法每次排序时都需要开辟固定大小的空间，以空间换取时间。所以在要排序的字符串数量较多的情况下表现很好，但是在排序的字符串较少时，会出现浪费大量空间的情况，所以在子数组中字符串较少的情况下代用插入排序提高效率

#### 最坏情况

高位优先字符串排序在处理含有大量等值键的子数组时会比较慢，如果相同的子字符串出现的过多，切换排序方法条件将不会出现，那么递归方法就会检查所有相同键中的每一个字符。另外，键索引计数法无法有效判断字符串中的字符是否全部相同：它不仅需要检查每个字符和移动每个字符串，还需要初始化所有的频率统计并将它们转换为索引等。

因此，高位优先的字符串排序的最坏情况就是所有的键均相同。大量含有相同前缀的键也会产生同样的问题

</details>

<details><summary>三向字符串快速排序</summary>

### 三向字符串快速排序

高位优先排序对包含大量重复键的字符串进行排序时，效率十分低下。三向字符串快速排序可以很好的解决这个问题

#### 核心思想

利用分治的思想，通过中间字符串每次将字符串数组划分为三个小组

再递归地对小组进行同样的处理，直到走到字符串末尾，最后形成的字符串数组自然有序

#### 具体做法

- 1. 用一个字符作为中间字符(本片文章中默认字符串的第一个字符)，比它大的移到字符串数组末尾，比它小的移到它前面，这样遍历完一遍后会形成三个小组，里面的字符串开头字母分别为：小于中间字符、等于中间字符、大于中间字符
- 2. 对分类的三个字符串数组逐一进行步骤1直到字符串中的字符全部便利。最后形成的字符串自然有序

#### 实例演示

![三向字符串快速排序](img/quick_three_sort_string.png)

#### 与LSD、MSD的对比

- LSD中没有分组的概念，单纯从右到左对每个字符排序
- MSD加入了分组的概念，但对于每个分组也是从头到尾，由于每次排序都要创建辅助数组，在数组较长时将会用到很大的空间
- 三向字符串快速排序与两者不同的是不用额外申请空间，且对于存在大量相同前缀的字符串数组，它也能很好的处理

#### 完整代码

```
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
 
using namespace std;
 
void swap(vector<string>& a, int m, int n)
{
    string temp = a[m];
    a[m] = a[n];
    a[n] = temp;
}
 
int charAt(const string& str, int d)
{
    if ( d < str.size() )
        return str[d];
    else 
        return -1;
}
 
void quick_3_string(vector<string>& sVec, int lo, int hi, int d)
{
    if (hi<=lo)
        return;
    int lt = lo, gt = hi;
    int v = charAt(sVec[lo], d);
    int i = lo + 1;
    while (i<=gt)
    {
        int t =  charAt(sVec[i], d);
        if (t < v) swap(sVec, lt++, i++);
        else if ( t > v) swap(sVec, i, gt--);
        else i++;
    }
 
    quick_3_string(sVec, lo, lt-1, d);
    if (v >=0 )
        quick_3_string(sVec, lt, gt, d+1);
    quick_3_string(sVec, gt+1, hi, d);
}
```

</details>

<details><summary>字符串排序算法的比较</summary>

### 字符串排序算法比较

| 算法 | 是否稳定 | 原地排序 | 运行时间 | 额外空间 | 优势领域 |
| --- | --- | --- | --- | --- | --- |
| 字符串的插入排序 | 是 | 是 | N~N<sup>2</sup> | 1 | 小数组或是已经有序的数组 |
| 快速排序 | 否 | 是 | Nlog<sup>2</sup>N | logN | 通用排序算法，特别适合用于空间不足的情况 |
| 归并排序 | 是 | 否 | Nlog<sup>2</sup>N | N | 稳定的通用排序算法 |
| 三向快速排序 | 否 | 是 | N~NlogN | logN | 大量重复键 |
| 低位优先的字符串排序 | 是 | 否 | NW | N | 较短的定长字符串 |
| 高位优先的字符串排序 | 是 | 否 | N~Nw | N+WR | 随机字符串 |
| 三向字符串快速排序 | 否 | 是 | N~Nw | W+logN | 通用排序算法，特别适合用于含有较长公共前缀的字符串 |

</details>


#### 字符串查找

<details><summary>单词查找树(字典树)</summary>

### 单词查找树

单词查找树即字典树(Trie树)，是一种哈希树的变种。典型应用是用于统计、排序和保存大量的字符串(但不仅限于字符串)，所以经常被搜索引擎系统用于文本词频统计。它的优点是：利用字符串的公共前缀来减少查询时间，最大限度地减少无谓的字符串比较，查询效率比哈希树高

#### 基本思想

下图是由单词at, bee, ben, bt, q组成的Trie树

![单词查找树实例](img/trie_tree_example1.jpg)

可以看出，trie树中每个字母的父节点就是它的前一个字母

Trie树的三个性质：

- 1. 根节点不包含字符，除根节点外的每一个节点都只包含一个字符
- 2. 从根节点到某一节点，路径上经过的字符连接起来，为该节点对应的字符串
- 3. 每个节点的所有子节点包含的字符都不相同

这样，对于长为l的单词来说，无论插入还是查询都是O(l)的事件复杂度

Trie树的特点：

- 空间换时间
    - 每个节点都有至少26个子节点(英文字母)
    - 插入、查询时间复杂度为O(len)
    - 排序按照Trie树先序遍历
- 节约空间
    - 保存大量单词的时候，相同前缀的空间公用。大部分字符串具有相同的前缀，即公共前缀
    - 每个节点，对应一项前缀，叶子节点对应最长前缀，即单词本身

#### Trie树实现

```
struct Trie     //定义Trie树节点结构体
{
    int value;  //节点的值，表示该单词出现的次数
    Trie *child[26];    //指向的子节点的指针
    Trie()
    {
        value = 0;
        memset(child, NULL, sizeof(child));
    }
}*root;     //根节点指针

/* 插入过程：
 * 1.从根节点开始，按照字母对应节点不断向下
 * 2.直到单词结束，在该节点上记录单词信息
 */
void Insert(char str[])     //插入字符串str
{
    Trie *x = root;     //从根节点开始
    for (int i = 0; str[i]; i++)    //逐个插入
    {
        int d = str[i] - 'a';
        //若子节点不存在，则new出对应节点
        if (x->child[d] == NULL)
            x->child[d] = new Trie;
        x = x->child[d];    //转成对应子树
    }
    x->value++;     //表示该单词出现次数
}

/* 查找过程
 * 1.从根节点开始搜索
 * 2.得到第一个字母节点后，转到对应子树
 * 3.在相应子树继续搜索下一个字母
 * 4.重复上述操作，直到到此结束，读取节点信息
 */
int Search(char str[])      //查找字符串str
{
    Trie *x = root;     //从根节点开始
    for (int i = 0; str[i]; i++)
    {
        int d = str[i] - 'a';
        if (x->child[d] == NULL)    //查找失败，直接退出
            return 0;
        x = x->child[d];    //转成对应子树
    }
    return x->value;    //查找成功，返回节点的值
}


void Deal(Trie *x)  //释放x为根的子树
{
    if (x == NULL)
        return;
    for (int i = 0; i < 26; i++)    //释放x的所有子节点
    {
        if (x->child[i] != NULL)
            Deal(x->child[i]);
    }
    delete x;   //释放x节点空间
}
```

</details>

<details><summary>三向单词查找树</summary>

在 R 向单词查找树中，每生成一个新结点，就会为该结点生成 R 个子节点，然后很多结点都是空的，因此，为了避免 R 向单词查找树的过度空间消耗，可以使用另一种数据结构的表示方法——三向单词查找树

三向单词查找树中：

- 每个结点包含一个字符，一个值，三个子节点
- 三个子节点分别对应着当前结点中，结点字母小于，等于，或大于当前结点的所有键
- 字符显式地保存在结点中

下图是R向单词查找树和三向单词查找树的区别：上面是R向单词查找树，下面是三向单词查找树

![三向单词查找树和R向单词查找树区别](img/R_Trie_3_Trie.png)

##### 代码实现

- 查找：在三向单词查找树的查找操作中，我们先对比根节点，如果键的首字母较小，则在左侧子树中查找；如果键首字母较大，则在右子树中查找。递归进行该算法，直到遇到空节点或键结束
- 插入：进行插入操作时，在查找的基础上，每当遇到一个空连接，则新建一个结点并保存字符

```
#pragma once
#include <memory>
#include <string>

class TST
{
private:
    class Node
    {
    private:
        std::unique_ptr<int> c;
        bool end;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> mid;
        std::unique_ptr<Node> right;
    private:
        void put(const std::string& s, const int& pos)
        {
            if (pos == s.length())
                return;
            if (c == nullptr)
            {
                c = std::move(std::unique_ptr<int>(new int(s[pos])));
                if (pos == s.length() - 1)
                {
                    end = true;
                    return;
                }
                if (mid == nullptr)
                    mid = std::move(std::unique_ptr<Node>(new Node));
                mid->put(s, pos + 1);
                return;
            }
            int temp = *c;
            if (s[pos] < temp)
            {
                if (left == nullptr)
                    left = std::move(std::unique_ptr<Node>(new Node));
                left->put(s, pos);
            }
            else if (s[pos] > temp)
            {
                if (right == nullptr)
                    right = std::move(std::unique_ptr<Node>(new Node));
                right->put(s, pos);
            }
            else
            {
                if (mid == nullptr)
                    mid = std::move(std::unique_ptr<Node>(new Node));
                mid->put(s, pos);
            }
        }
        bool find(const std::string& s, const int& pos)
        {
            if (pos >= s.length())
                return false;
            if (c == nullptr)
                return false;
            if (end == true && pos == s.length() - 1 && *c == s[pos])
                return true;
            else if (end != true && pos == s.length() - 1 && *c == s[pos] && mid != nullptr)
                return mid->find(s, pos);
            else
            {
                int temp = *c;
                if (s[pos] < temp && left != nullptr)
                    return left->find(s, pos);
                else if (s[pos] > temp && right != nullptr)
                    return right->find(s, pos);
                else if (s[pos] == temp && mid != nullptr)
                    return mid->find(s, pos + 1);
            }
            return false;
        }
    public:
        Node()
            :c(nullptr),left(nullptr),mid(nullptr),right(nullptr),end(false)
        {

        }
        void put(const std::string& s)
        {
            put(s, 0);
        }
        bool find(const std::string& s)
        {
            return find(s, 0);
        }
    };
private:
    std::unique_ptr<Node> root;
public:
    TST():root(new Node)
    {

    }
public:
    void put(const std::string& s)
    {
        root->put(s);
    }
    bool find(const std::string& s)
    {
        return root->find(s);
    }
};
```



</details>

#### 子字符串查找


<details><summary>暴力子字符串查找算法</summary>



</details>

<details><summary>KMP算法</summary>

### KMP算法

</details>

<details><summary>Boyer-Moore字符串查找算法</summary>


</details>

<details><summary>Rabin-Karp指纹字符串查找算法</summary>


</details>

<details><summary>子字符串查找算法比较</summary>


</details>

#### 正则表达式

#### 数据压缩

### 数组

<details><summary>数组</summary>


</details>

### 链表

<details><summary>链表</summary>


</details>

### 栈

<details><summary>栈</summary>


</details>

### 队列

<details><summary>队列</summary>


</details>

### 堆

<details><summary>堆</summary>


</details>

### 树

### 二叉树

<details><summary>二叉树</summary>


</details>

<details><summary>2-3查找树</summary>


</details>
<details><summary>字典树</summary>

TODO：字典树

[字典树](https://blog.csdn.net/forever_dreams/article/details/81009580)

</details>

<details><summary>AVL树</summary>


</details>

<details><summary>红黑树</summary>


</details>

<details><summary>散列表</summary>


</details>
<details><summary>哈希表</summary>


</details>
<details><summary>跳跃表</summary>

TODO：跳跃表

</details>
<details><summary>哈希树</summary>

TODO：哈希树

[哈希树](https://blog.csdn.net/yang_yulei/article/details/46337405)

</details>

<details><summary>图</summary>


</details>


## 算法

### 基本概念

<details><summary>时间复杂度</summary>

- 时间复杂度：

</details>

<details><summary>空间复杂度</summary>

- 空间复杂度：

</details>

<details><summary>原地排序算法</summary>

- [原地算法](https://en.wikipedia.org/wiki/In-place_algorithm)：原地算法指算法不借助辅助内存空间，但可以使用少量临时变量，在算法运行过程中，算法输入中的数据逐渐被输出替换，与原地算法相对于的叫做非原地算法

</details>

<details><summary>排序算法稳定性</summary>

- 排序算法稳定性：

</details>


### [排序算法](https://en.wikipedia.org/wiki/Sorting_algorithm)

<details><summary>排序算法对比</summary>

| 算法 | 最好 | 平均 | 最坏 | 额外空间 | 排序方式 | 稳定性 | 备注 |
| --- | :---: | :---: | :---: | :---: |:---: | :---: | :---: |
| [冒泡排序](content/bubble_sort.md) | n | n<sup>2</sup> | n<sup>2</sup> | 1 | 交换、原地 | 稳定 | 简单、代码量小 |
| [选择排序](content/selection_sort.md) | n<sup>2</sup> | n<sup>2</sup> | n<sup>2</sup> | 1 | 选择、原地 | 不稳定 | 元素交换时产生不稳定，使用O(n)额外空间或底层链表可达稳定 |
| [插入排序](content/insertion_sort.md) | n | n<sup>2</sup> | n<sup>2</sup> | 1 | 插入、原地 | 稳定 |  |
| [快速排序](content/quick_sort.md) | nlogn | nlogn | n<sup>2</sup> | 平均logn，最坏n | 原地 | 不稳定 | 存在稳定版本，原地排序通常需要O(logn)空间 |
| [堆排序](content/heap_sort.md) | n | nlogn | nlogn | 1 | 原地 | 不稳定 |  |
| [归并排序](content/merge_sort.md) | nlogn | nlogn | nlogn | n | 合并、原地 | 稳定 | 有非原地版本 |
| [希尔排序](content/shell_sort.md) | nlogn |  |  | 1 | 插入、原地 | 不稳定 |  |
| [计数排序](content/counting_sort.md) |  | n+r | n+r | n+r | 原地 | 稳定 |  |
| [桶排序](content/bucket_sort.md) |  | n+r| n+r | n+r | 原地 | 稳定 |  |
| [基数排序](content/radix_sort.md) | O(N) | O() |  | 稳定性 |

</details>

<details><summary>冒泡排序</summary>

# 冒泡排序

冒泡排序是最基本的排序方式，是在每次遍历时，通过交换相邻元素将未排序元素中最大元素（最小元素）沉下去（浮上来）的过程。

## 一、经典的冒泡排序：

```
void bubble(vector<int>& nums)
{
    int size = nums.size();
    //外层循环：每次循环排序好一个元素
    for (int i = 0; i < size - 1; i++)
    {
        has_sorted = true;
        for (int j = 1; j < size - i; j++)
        {
            if (nums[j] < nums[j - 1])
            {
                swap(nums, j, j - 1);
            }
        }
    }
}
```

<div align="center"><img src="img/bubble_sort.gif"/></div>

## 二、优化

### 1. 阻止数组排好序之后无意义的循环

上面经典冒泡排序法在数组的数据已经排好的情况下，仍会继续进行下一轮循环遍历，进行无意义的循环，通过增加标记位来处理这种情况

```
void bubble(vector<int>& nums)
{
    int size = nums.size();
    bool has_sorted = false;    //记录nums是否已经是排序数组的标记
    for (int i = 0; i < size - 1 && !has_sorted; i++)
    {
        has_sorted = true;
        for (int j = 1; j < size - i; j++)
        {
            if (nums[j] < nums[j - 1])
            {
                has_sorted = false;
                swap(nums, j, j - 1);
            }
        }
    }
}
```

### 2. 优化内层循环

每次记住每趟第一次交换的位置和最后一次交换的位置，第一次交换位置之前的元素都已经排好序了，同理，最后一次交换的位置之后的元素都已经排好序了
```
void bubble_sort( vector<int>& nums )
{
    int size = nums.size();
    int last_swap_end = size - 1, last_swap_start = 0;
    int q = size -1;
    int p = last_swap_start;
    int first_flag = 1;     //记录是否为第一次交换
    for ( int i = 0; i < size-1; i++ )
    {
        for ( int j = p; j < q; j++ )
        {
            if ( nums[j] > nums[j+1] )
            {
                swap(nums[j], nums[j+1]);
                last_swap_end = j;
                if ( first_flag )
                {
                    last_swap_start = j == 0 ? 0 : j -1;
                    first_flag = 0;
                }
            }
        }
        q = last_swap_end;
        first_flag = 1;
        p = last_swap_start;
    }
}
```

### 3. 双向冒泡排序法（鸡尾酒排序法）

鸡尾酒排序是冒泡排序的一种改进和变型 ，又称“双向冒泡排序”，鸡尾酒排序是从低到高然后从高到低来回排序（选出最大和最小项），比冒泡排序的效率稍微好一点，原因是冒泡排序只从一个方向进行比对(由低到高)，每次循环只移动一个项目

```
// 鸡尾酒排序(C++)
void CockTailSort(vector<int> &vi)
{
    int isSorted=false;
    //双向同时进行
    for(int i = 0; i < vi.size()/2 && !isSorted; i++)
    {
        isSorted = true;
        //升序排列
        for(int j = i;j < vi.size()-i-1; j++)
        {
            if(vi[j] > vi[j+1])
            {
                swap(vi[j], vi[j + 1]);
                isSorted = false;
            }
        }

        //降序排列
        for(int j = vi.size()-i-1; j>i; j--)
        {
            if(vi[j] < vi[j-1])
            {
                swap(vi[j], vi[j - 1]);
                isSorted = false;
            }
        }
    }
}
```

<div align="center">
    <img src="https://img-blog.csdn.net/20170312144555263?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvRlg2Nzc1ODg=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast"></img>
</div><br>

## 三、性能分析

- 平均时间复杂度：O(N<sup>2</sup>)
- 最坏时间复杂度：O(N<sup>2</sup>)，出现在当前数组被逆序排序
- 最好时间复杂度：O(N)，出现在优化1的版本中，输入的数组已经被排好序时
- 稳定性：稳定，相等元素在排序前后保持相对位置不变

</details>

<details><summary>选择排序</summary>

# 选择排序

## 一、简单选择排序

选择排序每次遍历数组时，从数组中未排序部分中选择出最大（最小）元素，并将该元素与未排序部分的最后一个（第一个）元素交换，最后得到有序数组

```
void selection(vector<int>& nums)
{
    int min_i = 0;
    int size = nums.size();
    for (int i = 0; i < size - 1; i++)
    {
        min_i = i;
        //选出最小值
        for (int j = i + 1; j < size; j++)
        {
            if (nums[j] < nums[min_i])
                min_i = j;
        }
        //将未排序部分的第一个元素与最小元素交换
        swap(nums, i, min_i);
    }
}
```

<div align="center"><img src="img/selection_sort.gif"></img></div>

## 二、优化

### 1. 一次遍历，双向选择

```
//二元选择排序
void select_sort( vector<int>& nums )
{
    int mini; 
    int maxi;
    for ( int i = 0; i < size/2; i++ )
    {
        mini = i;
        maxi = i;
        for ( int j = i+1; j < size-i; j++ )
        {
            if ( nums[j] < nums[mini] )
                mini = j;
            else if ( nums[j] > nums[maxi] )
                maxi = j;
        }
        if ( mini != i )
            swap( nums[i], nums[mini] );
        if ( maxi != i && maxi != j )
            swap( nums[j-1], nums[maxi] );
    }
}
```

## 三、性能分析

- 时间复杂度：O(N<sup>2</sup>)
- 空间复杂度：O(1)
- 稳定性：不稳定
- 排序方式：原地排序

</details>

<details><summary>插入排序</summary>

# 插入排序

## 一、简单插入排序

插入排序将数组分为排序区和乱序区，排序过程中每次从乱序区中选择一个元素放入排序区，直到乱序区没有元素

```
void insertion(vector<int>& nums)
{
    int size = nums.size();
    for (int i = 1; i < size; i++)
    {
        for (int j = i; j > 0 && （nums[j] < nums[j-1]）; j--)
        {
            swap(nums, j, j - 1);
        }
    }
}
```

## 二、优化

### 1. 融合二分查找

使用二分查找快速查找新元素在排序区的位置

```
//哨兵和二分查找相结合的插入排序
void insert_sort( vector<int>& nums )
{
    int target;
    int k;
    for ( int i = 1; i < size; ++i )
    {
        target = nums[i];
        //找到target应该插入的位置
        k = bin_search( nums, 0, i, target );
        for ( int j = i-1; j >= k; --j )
        {
            nums[j+1] = nums[j];
        }
        nums[k] = target;
    }
}
```

### 2. 加入哨兵位

在将新元素插入排序区使用哨兵位避免频繁交换元素的开销

```
//带哨兵的插入排序
void insert_sort( vector<int>& nums )
{
    int size = nums.size();
    int sentry;
    for ( int i = 1; i < size; ++i )
    {
        sentry = nums[i];
        for ( int j = i-1; j >= 0; j-- )
        {
            if ( sentry < array[j] )
                nums[j+1] = nums[j];
            else break;
        }
        if ( j+1 != i )
            nums[j+1] = sentry;
    }
}
```

<div align="center"><img src="img/insert_sort3.gif"></img></div>

## 三、性能分析

- 时间复杂度：O(N<sup>2</sup>)
- 空间复杂度：O(1)
- 排序方式：原地
- 稳定性：稳定

</details>

<details><summary>快速排序</summary>

# 快速排序

最好情况：每次正好将数组分半，O(NlogN)

最坏情况：输入的输入已经排好序，O(N^2)

为了防止出现最坏情况，需要在进行快速排序前随机打乱数组以避免数组已经排好序

## 一、经典快速排序

### 1. 主要过程

  ```
  void quick_sort_core(vector<int>& nums, int l, int h)
  {
      if (h <= l)
          return;
      int m = partition(nums, l, h);
      quick_sort_core(nums, l, m - 1);
      quick_sort_core(nums, m + 1, h);
  }
  void quick_sort(vector<int>& nums)
  {
      quick_sort_core(nums, 0, nums.size() - 1);
  }
  ```

### 2. partition函数

  ```
  int partition(vector<int>& nums, int l, int h)
  {
      int i = l, j = h + 1;
      int v = nums[l];
      while (true)
      {
          while (nums[++i] < v && i != h);
          while (v < nums[--j] && j != l);
          if (i >= j)
              break;
          swap(nums, i, j);
      }
      swap(nums, l, j);
      return j;
  }
  ```
  partition函数的另一种写法，参考[Leetcode](https://github.com/haigangx/leetcode/blob/master/algorithms/215_kth_largest_element_in_an_array.md)

<div align="center"><img src="img/quick_sort.gif" /></div>

## 二、改进

### 1.随机快排

<div align="center"><img src="img/random_quick_sort.gif" /></div>

### 2. 切换到插入排序

因为快速排序在小数组中也会递归调用自己，对于小数组，插入排序比快速排序的性能更好，因此在小数组中可以切换到插入排序
 
### 3. 三数取中

三取样切分跟随机快排一样，也是从寻找最优的切分点这个方向上来优化快排。

三取样切分即是使用数组中的小部分元素的中位数来切分数组，这样做的切分更好，但是会带来计算中位数的负担，人们发现将取样大小设为3并用大小居中的元素切分效果最好。
 
### 4. 三向切分

熵最优的排序（三向切分）主要是为了处理数组中有大量重复元素的情况，如果数组中有大量重复的元素，如果不考虑对重复元素做特殊处理，就会少了一个优化的好机会，比如，一个元素全部重复的数组就不需要在进行排序了。

一个简单的想法就是将数组的元素分成三部分，大于哨兵的，小于哨兵的和等于哨兵的。这个问题有一个解法，就是**Dijkstra解法**，[荷兰国旗问题](https://leetcode-cn.com/problems/sort-colors/)可以通过此法解决，三向切分快速排序对于只有若干不同主键的随机数组可以在线性时间内完成排序

> **Dijkstra解法**的主要思路是：从左到右遍历数组一次，维护一个指针lt，使得data[lo…lt-1]的所有元素都小于哨兵，一个指针gt，使得data[gt+1…hi]之间的元素都大于哨兵，维护一个指针i，使得data[lt…i-1]之间的元素都等于哨兵，data[i…gt]之间的元素还未处理。

具体的处理过程如下，一开始i等于lo，哨兵值等于v：
- 如果data[i]小于v，则交换data[i]和data[lt]，lt++, i++;
- 如果data[i]大于v，则交换data[i]和data[gt]，gt–;
- 如果data[i]等于v，i++;

```
void three_way_quick_sort(vector<int>& nums, int l, int h)
{
    if (h <= l)
        return;
    int lt = l, i = l + 1, gt = h;
    int v = nums[l];
    while (i < gt)
    {
        int cmp = nums[i] - v;
        if (cmp < 0)
            swap(nums, lt++, i++);
        else if (cmp > 0)
            swap(nums, i, gt--);
        else
            i++;
    }
    three_way_quick_sort(nums, l, lt-1);
    three_way_quick_sort(nums, gt+1, h);
}
```

### 5. 基于切分的快速选择算法

快速排序的partition方法，会返回一个整数j使得a[l..j-1]小于等于a[j],且a[j+1..h]大于等于a[j]，此时a[j]就是数组的第j大元素

可以利用这个特性找出数组的第k个元素

该算法是线性级别的，假设每次能将数组二分，那么比较的总次数为(N+N/2+N/4+...)，直到找到第k个元素，这个和显然小于2N

```
void selectK(vector<int>& nums, int k)
{
    int l = 0, h = nums.size()-1;
    while (h > l)
    {
        int j = partition(nums, l, h);
        if (j == k)
            return nums[k];
        else if (j > k)
            h = j - 1;
        else
            l = j + 1;
    }
    return nums[k];
}
```

</details>

<details><summary>堆排序</summary>

# 堆排序

## 一、堆结构

### 1. 堆的定义

堆中某个节点的值总是大于等于其子节点的值，并且堆是一颗完全二叉树。

堆可以用数组来表示，这是因为堆是完全二叉树，而完全二叉树很容易就存储在数组中。位置 k 的节点的父节点位置为 k/2，
而它的两个子节点的位置分别为 2k 和 2k+1。

这里不使用数组索引为 0 的位置，是为了更清晰地描述节点的位置关系。

```
int heap[maxN+1];
int N = 0;
bool isEmpty {return N==0;}
int size() {return N;}
```

### 2. 上浮和下沉操作

在堆中，当一个节点比父节点大，那么需要交换这个两个节点。交换后还可能比它新的父节点大，因此需要不断地进行比较和交换操作，把这种操作称为上浮。

```
void swim(int k)
{
    while (k > 1 && heap[k/2]<heap[k])
    {
        swap(k/2, k);
        k = k/2;
    }
}
```

类似地，当一个节点比子节点来得小，也需要不断地向下进行比较和交换操作，把这种操作称为下沉。一个节点如果有两个子节点，
应当与两个子节点中最大那个节点进行交换。

```
void sink(int k)
{
    while (2 * k <= N)
    {
        int j = 2 * k;
        if (j < N && heap[j]<heap[j+1])  //如果节点k有两个子节点，选出最大子节点
            j++;
        if (heap[k]>heap[j])    //如果最大子节点不大于节点k，下沉完成
            beak;
        swap(k, j); //如果最大子节点大于节点k，交换最大子节点和节点k，继续下沉
        k = j;
    }
}
```

### 3. 插入元素

将新元素放到数组末尾，然后上浮到合适位置

```
void insert(int v)
{
    heap[++N] = v;
    swim(N);
}
```

### 4. 删除堆顶元素

从数组顶端删除最大元素，并将数组的最后一个元素放到顶端，并让这个元素下沉到合适的位置

```
int delMax
{
    int max = heap[1];
    swap(1, N--);
    heap[N+1] = null;
    sink(1);
    return max;
}
```

## 二、堆排序

给定一个数组，将其使用堆排序进行排序。需要先使用sink函数将这个数组构造成最大堆，接下来每次讲堆顶的最大元素取下来与数组的最后一个元素交换，这时候最大堆的结构已经被破坏，将数组元素个数减一并且对新的堆顶元素调用sink函数使数组恢复最大堆，重复执行这个过程，直到所有元素都已排序。

### 1. 构建堆

无序数组建立堆最直接的方法就是从左到右遍历数组进行上浮操作。

一个更高效的方法是从右至左进行下沉操作，如果一个节点的两个节点都已经是堆有序，那么进行下沉操作可以使得这个节点为
根节点的堆有序。叶子节点不需要进行下沉操作，可以忽略叶子节点的元素，因此只需要便利一半的元素即可。

### 2. 交换堆顶元素与最后一个元素

交换之后需要进行下沉操作维持堆的有序状态

### 3. 完整代码

```
void heap_sort(vector<int>& nums)
{
    int size = num.size()-1;
    for (int k = size/2; k >= 1; k--)
        sink(nums, k, N);
    while (N > 1)
    {
        swap(nums, 1, N--);
        sink(nums, 1, N);
    }
}
void sink(vector<int>& nums, int k, int N)
{
    while (2 * k <= N)
    {
        int j = 2 * k;
        if (j < N && heap[j]<heap[j+1])
            j++;
        if (heap[k]>heap[j])
            beak;
        swap(k, j);
        k = j;
    }
}
```

## 三、性能分析

堆高度为logN，因此在堆中插入元素和删除最大元素的复杂度都为logN

堆排序：要对N个节点进行下沉操作，所以时间复杂度为NlogN

堆排序为原地排序，不需要额外空间

</details>

<details><summary>归并排序</summary>

# 归并排序

## 一、经典归并排序

归并排序就是将要排序的数组分成两部分，每一部分都排好序，再将这两部分归并为一个数组，每一部分的排序又采用归并排序。

归并排序按照空间的使用上来分主要分为两种：普通归并和原地归并。按照归并的方向可以分为自顶向下归并和自底向上归并。

### 1. merge函数

归并排序最主要的一个函数就是merge，函数接口如下：

```
void merge(int data[], int start, int mid, int end);
```

这个函数负责将data数组中start-mid子数组和mid-end子数组进行原地归并，这个函数的前提条件是两个子数组都已经排好序。下面是这个函数的具体实现代码：

```
//归并两个排好序的数组
void merge(vector<int>& nums, int l, int m, int h)
{
    int i = l, j = m + 1;
    vector<int> aux(nums.begin(), nums.end());
    for (int k = l; k <= h; k++)
    {
        //i>=mid说明前半部分先被合并完，直接将后半部分剩余的元素接到data后面
        if (i > m)
            nums[k] = aux[j++];
        //i>=mid说明后半部分先被合并完，直接将前半部分剩余的元素接到data后面
        else if (j > h)
            nums[k] = aux[i++];
        //两者中选择较小的放到data中
        else if (aux[i] < aux[j])
            nums[k] = aux[i++];
        else
            nums[k] = aux[j++];

    }
}
```

归并排序最主要的函数就是merge函数，所以保证将merge函数写正确是非常重要的，写归并排序的时候可以先写一个merge函数，然后模拟几个环境测试一下，测试没有问题之后再进行下一步，否则如果一次性将整个归并算法全部写出，出现问题之后，因为递归层数比较多，找起来很麻烦。写好了merge函数，不管是自顶向下还是自底向上归并都只是对merge函数不同方式的调用而已。

<div align="center"><img src="img/merge_sort.gif" /></div>

### 2. 归并排序的两种方向：

为了直观的理解自顶而下和自底向上，我放了一张图。

<div align="center"><img src="img/merge_sort1.png"></img></div>

#### 2.1 自顶而下归并

自顶而下顾名思义：就是从最上面到最下面了，从这幅图来看，最上面就是a[0...15]，就是整个数组了。而最下面就是每一个元素了。所以自顶而下归并就是先从数组的整体出发，将数组全部元素看做一个整体，将这个整体分成两部分，并且假设每一部分都已经排好序了，所以只需要将这两部分直接归并，但是为了保证这两个部分都已经排好序，我们又需要为每一部分使用归并排序排序，在对图中第二层的每个子数组调用归并排序时，又会将图中第二层的数组分解为第三层，然后分别调用归并排序，经过这样几轮递归后，直到每个子数组都只剩下一个元素递归才开始回溯。回溯完成，排序也就完成了。这就是自顶而下。

##### 自顶向下代码实现：

因为自顶向下归并要使用递归，传递参数时要向下一层递归传递一些信息，为了保证接口的统一性，所以特别增加了内部函数merge_sort1_core来完成排序的主要工作。

```
void merge_sort1(vector<int>& nums)
{
    merge_sort1_core(nums, 0, nums.size() - 1);
}
void merge_sort1_core(vector<int>& nums, int l, int h)
{
    if (h <= l)
        return;
    int m = (l + h) / 2;
    merge_sort1_core(nums, l, m);
    merge_sort1_core(nums, m + 1, h);
    merge(nums, l, m, h);
}
```

<div align="center"><img src="img/merge_sort2.png"></img></div>

#### 2.2 自底向上归并


自底向上：与自顶向下刚好相反，先从子数组依赖树的最低端出发，保证在为一个数组排序时，它的两个部分都已经被排好序，（自顶而下是假设已经排好序，两个不一样）

##### 自底向上代码实现

```
void merge_sort2(vector<int>& nums)
{
    int size = nums.size();

    for (int sz = 1; sz < size; sz += sz)
    {
        for (int lo = 0; lo < size - sz; lo += sz + sz)
        {
            int end = lo + sz + sz - 1 < size - 1 ? lo + sz + sz - 1 : size - 1;
            merge(nums, lo, lo + sz - 1, end);
        }
    }
}
```

<div align="center"><img src="img/merge_sort3.png"></img></div>

## 二、性能分析

- 时间复杂度：NlogN 
- 空间复杂度：N
- 稳定性：稳定

</details>

<details><summary>希尔排序</summary>

# 希尔排序

```
void shell(vector<int>& nums)
{
    int size = nums.size();
    int h = 1;

    while (h < (size / 3))
    {
        h = 3 * h + 1;
    }

    while (h >= 1)
    {
        for (int i = h; i < size; i++)
        {
            for (int j = i; j >= h && nums[j] < nums[j - h]; j -= h)
            {
                swap(nums, j, j - h);
            }
            for (int k = 0; k < nums.size(); k++)
                cout << nums[k] << " ";
            cout << endl;
        }
        h /= 3;
    }
}
```

</details>

<details><summary>计数排序</summary>

# 计数排序

计数排序是一种稳定的线性时间排序算法，计数排序不是比较排序，排序的速度快于任何比较排序算法，计数排序可以配合基数排序，能够更有效排序数据范围很大的数组

### 1. 计数排序步骤：

- 1.找出待排序的数组中最大和最小的元素
- 2.统计数组中每个值为i的元素出现的次数，存入数组C的第i项
- 3.对所有的计数累加（从C中的第一个元素开始，每一项和前一项相加）
- 4.反向填充目标数组：将每个元素i放在新数组的第C(i)项，每放一个元素就将C(i)减去1

### 2. 计数排序实现

```
#include "utili.h"

//假设要排序的数字都是小于100的
void count_sort( int data[], int size )
{
    int count_arr[100];
    int temp[size];
    int i, j, k;
    for ( k = 0; k < 100; k++ )
        count_arr[k] = 0;
    for ( i = 0; i < size; i++ )
        count_arr[data[i]]++;
    for ( i = 1; i < 100; i++ )
        count_arr[i] = count_arr[i-1] + count_arr[i];
    for ( j = size; j > 0; j-- )
    {
        temp[--count_arr[data[j-1]]] = data[j-1];
    }
    for ( i = 0; i < size; ++i )
        data[i] = temp[i];
}
```

<div align="center"><img src="img/counting_sort1.gif"><></div>

### 3. 性能分析

- 时间复杂度：O(N+k)
- 空间复杂度：O(N+k)
- 稳定性：稳定

</details>

<details><summary>桶排序</summary>

| [桶排序](content/bucket_sort.md) |  | n+r| n+r | n+r | 原地 | 稳定 |  |

</details>

<details><summary>基数排序</summary>

# 基数排序

基数排序是将所有待比较数值（正整数）统一为同样的数位长度，数位较短的数前面补零。然后，从最低位开始，一次进行一次排序。这样从最低位排序一直到最高位排序完成之后，数列就变成一个有序序列

**NOTE:** 基数排序只能排序非负整数

### 1. 效率

基数排序的时间复杂度为 O(k\*n)其中n是排序元素个数，k是数字位数。需要注意的是这个时间复杂度不一定优于 O(n\*log_n)

### 2. 实现

基数排序的过程图示如下：

<div align="center"><img src="img/radix_sort1.jpg"></img></div>

```
int maxbit( int data[], int size )      //辅助函数，求数据的最大位数
{
    int i;
    //先求出最大数，再求最大数的位数.
    int maxData = data[0];
    for ( i = 1; i < size; ++i )
    {
        if ( data[i] > maxData )
            maxData = data[i];
    }
    i = 1;
    while ( maxData >= 10 )
    {
        maxData /= 10;
        ++i;
    }
    return i;
}

void radix_sort( int data[], int size )
{
    int d = maxbit( data, size );
    //int *temp = (int *)malloc( sizeof(int)*size );
    int temp[size];
    int count[10];                  //计数器
    int i, j, k;
    int radix = 1;
    for ( i = 1; i <= d; i++ )
    {
        for ( j = 0; j < 10; j++ )
            count[j] = 0;               //每次分配前清空计数器

        //(1)
        //将data中第i位为j的个数保存在count[j]中
        for ( j = 0; j < size; j++ )
        {
            k = ( data[j] / radix ) % 10;   //k为data中每个数第i位的数字
            count[k]++;
        }
        //count[j]中保存第i位小于j的数字的个数
        for ( j = 1; j < 10; j++ )
        {
            count[j] = count[j-1] + count[j];
        }
        for ( j = size-1; j >= 0; j-- )
        {
            k = ( data[j] / radix ) % 10;
            //printf( "k = %d, data[%d] = %d\n", k, j, data[j] );
            temp[count[k]-1] = data[j];
            count[k]--;
        }
        //(2)
        for ( j = 0; j < size; j++ )
        {
            //printf( "%d ", temp[j] );
            data[j] = temp[j];
        }
        radix = radix * 10;
    }
}
```

<div align="center"><img src="img/radix_sort.gif"></div>

</details>


### 排列

<details><summary>全排列</summary>

# 全排列生成算法

[全排列生成算法](https://zh.wikipedia.org/wiki/%E5%85%A8%E6%8E%92%E5%88%97%E7%94%9F%E6%88%90%E7%AE%97%E6%B3%95)
即将给定序列中所有可能的全排列无重复无遗漏地枚举出来，此处全排列地定义是：从n个元素中取出m个元素进行排列，当n=m时这个排列被称为全排列，
生成全排列地方法有：回溯法、字典序法、邻位对换法、循环移位法、递增进位制法、递减进位制法等

用C++写一个函数, 如 Foo(const char \*str), 打印出 str 的全排列,
如 abc 的全排列: abc, acb, bca, dac, cab, cba


## 一、回溯法

### 1. 全排列的递归实现

为方便起见，用123来示例下。123的全排列有123、132、213、231、312、321这六种。首先考虑213和321这二个数是如何得出的。显然这二个都是123中的1与后面两数交换得到的。然后可以将123的第二个数和每三个数交换得到132。同理可以根据213和321来得231和312。因此可以知道——全排列就是从第一个数字起每个数分别与它后面的数字交换。找到这个规律后，递归的代码就很容易写出来了：

***【注】：将上面描述的过程画成图就可以清晰的看出来递归的过程。***

![这里写图片描述](https://imgconvert.csdnimg.cn/aHR0cDovL2ltZy5ibG9nLmNzZG4ubmV0LzIwMTcwODA3MTAyODQ0NDU5?x-oss-process=image/format,png)

```
#include<iostream>  
using namespace std;  
#include<assert.h>  
    
void Permutation(char* pStr, char* pBegin)  
{  
    assert(pStr && pBegin);  
    
    if(*pBegin == ‘\0’)  
        printf(”%s\n”,pStr);  
    else  
    {  
        for(char* pCh = pBegin; *pCh != ‘\0’; pCh++)  
        {  
            swap(*pBegin,*pCh);  
            Permutation(pStr, pBegin+1);  
            swap(*pBegin,*pCh);  
        }  
    }  
}  
```

#### 另外一种写法：

```
//k表示当前选取到第几个数，m表示共有多少个数  
void Permutation(char* pStr,int k,int m)  
{  
    assert(pStr);  
    
    if(k == m)  
    {  
        static int num = 1;  //局部静态变量，用来统计全排列的个数  
        printf(”第%d个排列\t%s\n”,num++,pStr);  
    }  
    else  
    {  
        for(int i = k; i <= m; i++)  
        {  
            swap(*(pStr+k),*(pStr+i));  
            Permutation(pStr, k + 1 , m);  
            swap(*(pStr+k),*(pStr+i));  
        }  
    }  
}   
```
如果字符串中有重复字符的话，上面的那个方法肯定不会符合要求的，因此现在要想办法来去掉重复的数列。

### 2. 去掉重复的全排列的递归实现

由于全排列就是从第一个数字起每个数分别与它后面的数字交换。我们先尝试加个这样的判断——如果一个数与后面的数字相同那么这二个数就不交换了。如122，第一个数与后面交换得212、221。然后122中第二数就不用与第三个数交换了，但对212，它第二个数与第三个数是不相同的，交换之后得到221。与由122中第一个数与第三个数交换所得的221重复了。所以这个方法不行。

换种思维，对122，第一个数1与第二个数2交换得到212，然后考虑第一个数1与第三个数2交换，此时由于第三个数等于第二个数，所以第一个数不再与第三个数交换。再考虑212，它的第二个数与第三个数交换可以得到解决221。此时全排列生成完毕。

***【注】：将上面描述的过程画成图就可以清晰的看出来递归的过程。***

![这里写图片描述](https://imgconvert.csdnimg.cn/aHR0cDovL2ltZy5ibG9nLmNzZG4ubmV0LzIwMTcwODA3MTAyOTA5NzAw?x-oss-process=image/format,png)

这样我们也得到了在全排列中去掉重复的规则——去重的全排列就是从第一个数字起每个数分别与它后面非重复出现的数字交换。下面给出完整代码：

```
#include<iostream>  
using namespace std;  
#include<assert.h>  
    
//在[nBegin,nEnd)区间中是否有字符与下标为pEnd的字符相等  
bool IsSwap(char* pBegin , char* pEnd)  
{  
    char *p;  
    for(p = pBegin ; p < pEnd ; p++)  
    {  
        if(*p == *pEnd)  
            return false;  
    }  
    return true;  
}  
void Permutation(char* pStr , char *pBegin)  
{  
    assert(pStr);  
    
    if(*pBegin == ‘\0’)  
    {  
        static int num = 1;  //局部静态变量，用来统计全排列的个数  
        printf(”第%d个排列\t%s\n”,num++,pStr);  
    }  
    else  
    {  
        for(char *pCh = pBegin; *pCh != ‘\0’; pCh++)   //第pBegin个数分别与它后面的数字交换就能得到新的排列     
        {  
            if(IsSwap(pBegin , pCh))  
            {  
                swap(*pBegin , *pCh);  
                Permutation(pStr , pBegin + 1);  
                swap(*pBegin , *pCh);  
            }  
        }  
    }  
} 
```

OK，到现在我们已经能熟练写出递归的方法了，并且考虑了字符串中的重复数据可能引发的重复数列问题。那么如何使用非递归的方法来得到全排列了？

### 3. 全排列的非递归实现

***【注】：这种方法的前提是输入的字符串是预先由小到大排好序的***

要考虑全排列的非递归实现，先来考虑如何计算字符串的下一个排列。如”1234”的下一个排列就是”1243”。只要对字符串反复求出下一个排列，全排列的也就迎刃而解了。

如何计算字符串的下一个排列了？来考虑”926520”这个字符串，我们从后向前找第一双相邻的递增数字，”20”、”52”都是非递增的，”26 “即满足要求，称前一个数字2为替换数，替换数的下标称为替换点，再从后面找一个比替换数大的最小数（这个数必然存在），(【这块没太读懂，按我自己的理解应该是，再从后往前找到第一个比替换数大的数】)，0、2都不行，5可以，将5和2交换得到”956220”，然后再将替换点后的字符串”6220”颠倒即得到”950226”。

对于像“4321”这种已经是最“大”的排列，采用STL中的处理方法，将字符串整个颠倒得到最“小”的排列”1234”并返回false。

***【注】：将上面描述的过程画成图就可以清晰的看出来递归的过程。***

[外链图片转存失败,源站可能有防盗链机制,建议将图片保存下来直接上传(img-RlCtDeRx-1574778815228)(http://img.blog.csdn.net/20170807102926688?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvZ2l0aHViXzM2MTg2NDg4/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)]

这样，只要一个循环再加上计算字符串下一个排列的函数就可以轻松的实现非递归的全排列算法。按上面思路并参考STL中的实现源码，不难写成一份质量较高的代码。值得注意的是在循环前要对字符串排序下，可以自己写快速排序的代码（请参阅《白话经典算法之六 快速排序 快速搞定》），也可以直接使用VC库中的快速排序函数（请参阅《使用VC库函数中的快速排序函数》）。下面列出完整代码：

```
#include<iostream>  
#include<algorithm>  
#include<cstring>  
using namespace std;  
#include<assert.h>  
    
//反转区间  
void Reverse(char* pBegin , char* pEnd)  
{  
    while(pBegin < pEnd)  
        swap(*pBegin++ , *pEnd–);  
}  
//下一个排列  
bool Next_permutation(char a[])  
{  
    assert(a);  
    char *p , *q , *pFind;  
    char *pEnd = a + strlen(a) - 1;  
    if(a == pEnd)  
        return false;  
    p = pEnd;  
    while(p != a)  
    {  
        q = p;  
        p–;  
        if(*p < *q)  //找降序的相邻2数,前一个数即替换数    
        {  
                //从后向前找比替换点大的第一个数  
            pFind = pEnd;  
            while(*pFind < *p)  
                –pFind;  
            swap(*p , *pFind);  
            //替换点后的数全部反转  
            Reverse(q , pEnd);  
            return true;  
        }  
    }  
    Reverse(a , pEnd);   //如果没有下一个排列,全部反转后返回false     
    return false;  
}  
    
int cmp(const void *a,const void *b)  
{  
    return int(*(char *)a - *(char *)b);  
}
```

至此我们已经运用了递归与非递归的方法解决了全排列问题，总结一下就是：

- 1、全排列就是从第一个数字起每个数分别与它后面的数字交换。

- 2、去重的全排列就是从第一个数字起每个数分别与它后面非重复出现的数字交换。

- 3、全排列的非递归就是由后向前找替换数和替换点，然后由后向前找第一个比替换数大的数与替换数交换，最后颠倒替换点后的所有数据。

## 二、字典序法

### 1. 介绍

字典序法的核心思想即 **从字典序最小的排列出发，每次找到当前排列的下一个较大的字典序排列，直到找到最大的字典序排列，至此要求的全排列已经找到**

> 字典序即是对各排列按照字典的顺序进行排列，如对于串 "123456" ，按照字典串生成的序列是 "123456"->"123465"->...->"654312"->"654321"，
按照字典序法的要求，我们要从 "123456" 出发，依次找到下一个字典序的排列，直到找到最后一个字典序排列 "654321"

所以，该算法的关键是 **给定一个当前排列，如何找到下一个字典序的排列？**

### 2. 算法核心

遵循以下步骤，即可找到当前排列的下一个字典序排列(以 "158476531" 为例，其下一个字典序排列为 "158513467" )：

- 1. 从当前排列 "158476531" 的右端开始，找到第一个比其右边数字小的数字 "4"（找最后一个正序）
- 2. 在 "4" 的右边数字中，找出所有比 "4" 大的数字中最小的数字 "5"
- 3. 交换 "4" 和 "5" 的位置，此时生成的排列为 "158576431"
- 4. 再将现在序列中 "5" 的位置之后的数字 "76431" 进行倒转，生成下一个字典序列 "158513467"

<div align="center"><img src="img/dicseq.gif"></img></div>

### 3. 例子：

`nextPermutation` 用于求给定排列的下一个字典序排列，如果给定的已经是最大字典序列，则返回最小字典序列

```
//前提：vector中的元素必须已经排好序
void nextPermutation(vector<int>& arr) {
    //1.求最后一个正序
    int i = arr.size() - 2;
    while (i >= 0 && arr[i] >= arr[i+1]) {
        i--;
    }
    if (i >= 0) {
        //2.找到比pos大的数字中最小的数字
        int j = arr.size() - 1;
        while (j >= 0&&  arr[j] <= arr[i]) {
            j--;
        }
        swap(arr[i], arr[j]);
    }
    reverse(arr, i+1);
}
void reverse(vector<int>& arr, int beg) {
    int left = beg;
    int right = arr.size()-1;
    while (left < right) {
        swap(arr[left], arr[right]);
        left++;
        right--;
    }
}
```

其实，STL 中已经有[std::permutation](https://www.geeksforgeeks.org/stdnext_permutation-prev_permutation-c/)库函数，平时可以直接用

### 4. 相关题目：

- [LeetCode：下一个排列](https://leetcode-cn.com/problems/next-permutation/)

## 三、插入法

## 四、邻位对换法

## 五、递增进位制法

## 六、递减进位制法

</details>

<details><summary>子集（幂集）</summary>

# 字符串组合算法

题目：输入一个字符串，输出该字符串中字符的所有组合。举个例子，如果输入abc，它的组合有a、b、c、ab、ac、bc、abc。

上面我们详细讨论了如何用递归的思路求字符串的排列。同样，本题也可以用递归的思路来求字符串的组合。

### 方法一:递归求解

假设我们想在长度为n的字符串中求m个字符的组合。我们先从头扫描字符串的第一个字符。针对第一个字符，我们有两种选择：第一是把这个字符放到组合中去，接下来我们需要在剩下的n-1个字符中选取m-1个字符；第二是不把这个字符放到组合中去，接下来我们需要在剩下的n-1个字符中选择m个字符。这两种选择都很容易用递归实现。下面是这种思路的参考代码：

```
#include<iostream>  
#include<vector>  
#include<cstring>  
using namespace std;  
#include<assert.h>  
    
void Combination(char *string ,int number,vector<char> &result);  
    
void Combination(char *string)  
{  
    assert(string != NULL);  
    vector<char> result;  
    int i , length = strlen(string);  
    for(i = 1 ; i <= length ; ++i)  
        Combination(string , i ,result);  
}  
    
void Combination(char *string ,int number , vector<char> &result)  
{  
    assert(string != NULL);  
    if(number == 0)  
    {  
        static int num = 1;  
        printf(”第%d个组合\t”,num++);  
    
        vector<char>::iterator iter = result.begin();  
        for( ; iter != result.end() ; ++iter)  
            printf(”%c”,*iter);  
        printf(”\n”);  
        return ;  
    }  
    if(*string == ‘\0’)  
        return ;  
    result.push_back(*string);  
    Combination(string + 1 , number - 1 , result);  
    result.pop_back();  
    Combination(string + 1 , number , result);  
}  
    
int main(void)  
{  
    char str[] = “abc”;  
    Combination(str);  
    return 0;  
}  
```

由于组合可以是1个字符的组合，2个字符的字符……一直到n个字符的组合，因此在函数void Combination(char* string)，我们需要一个for循环。另外，我们用一个vector来存放选择放进组合里的字符。

## 方法二：用位运算来实现求组合

```
#include<iostream>  
using namespace std;  
    
int a[] = {1,3,5,4,6};  
char str[] = “abcde”;  
    
void print_subset(int n , int s)  
{  
    printf(”{“);  
    for(int i = 0 ; i < n ; ++i)  
    {  
        if( s&(1<<i) )         // 判断s的二进制中哪些位为1，即代表取某一位  
            printf(”%c ”,str[i]);   //或者a[i]  
    }  
    printf(”}\n”);  
}  
    
void subset(int n)  
{  
    for(int i= 0 ; i < (1<<n) ; ++i)  
    {  
        print_subset(n,i);  
    }  
}  
    
    
    
int main(void)  
{  
    subset(5);  
    return 0;  
}  
```

## 字符串全排列扩展—-八皇后问题

    题目：在8×8的国际象棋上摆放八个皇后，使其不能相互攻击，即任意两个皇后不得处在同一行、同一列或者同一对角斜线上。下图中的每个黑色格子表示一个皇后，这就是一种符合条件的摆放方法。请求出总共有多少种摆法。


 这就是有名的八皇后问题。解决这个问题通常需要用递归，而递归对编程能力的要求比较高。因此有不少面试官青睐这个题目，用来考察应聘者的分析复杂问题的能力以及编程的能力。

由于八个皇后的任意两个不能处在同一行，那么这肯定是每一个皇后占据一行。于是我们可以定义一个数组ColumnIndex[8]，数组中第i个数字表示位于第i行的皇后的列号。先把ColumnIndex的八个数字分别用0-7初始化，接下来我们要做的事情就是对数组ColumnIndex做全排列。由于我们是用不同的数字初始化数组中的数字，因此任意两个皇后肯定不同列。我们只需要判断得到的每一个排列对应的八个皇后是不是在同一对角斜线上，也就是数组的两个下标i和j，是不是i-j==ColumnIndex[i]-Column[j]或者j-i==ColumnIndex[i]-ColumnIndex[j]。

关于排列的详细讨论，详见上面的讲解。

接下来就是写代码了。思路想清楚之后，编码并不是很难的事情。下面是一段参考代码：

```
#include<iostream>  
using namespace std;  
    
int g_number = 0;  
void Permutation(int * , int  , int );  
void Print(int * , int );  
    
void EightQueen( )  
{  
    const int queens = 8;  
    int ColumnIndex[queens];  
    for(int i = 0 ; i < queens ; ++i)  
        ColumnIndex[i] = i;    //初始化  
    Permutation(ColumnIndex , queens , 0);  
}  
    
bool Check(int ColumnIndex[] , int length)  
{  
    int i,j;  
    for(i = 0 ; i < length; ++i)  
    {  
        for(j = i + 1 ; j < length; ++j)  
        {  
            if( i - j == ColumnIndex[i] - ColumnIndex[j] || j - i == ColumnIndex[i] - ColumnIndex[j])   //在正、副对角线上  
                return false;  
        }  
    }  
    return true;  
}  
void Permutation(int ColumnIndex[] , int length , int index)  
{  
    if(index == length)  
    {  
        if( Check(ColumnIndex , length) )   //检测棋盘当前的状态是否合法  
        {  
            ++g_number;  
            Print(ColumnIndex , length);  
        }  
    }  
    else  
    {  
        for(int i = index ; i < length; ++i)   //全排列  
        {  
            swap(ColumnIndex[index] , ColumnIndex[i]);  
            Permutation(ColumnIndex , length , index + 1);  
            swap(ColumnIndex[index] , ColumnIndex[i]);  
        }  
    }  
}  
    
void Print(int ColumnIndex[] , int length)  
{  
    printf(”%d\n”,g_number);  
    for(int i = 0 ; i < length; ++i)  
        printf(”%d ”,ColumnIndex[i]);  
    printf(”\n”);  
}  
    
int main(void)  
{  
    EightQueen();  
    return 0;  
}  
```

## 题目：

	输入两个整数n和m，从数列1,2,3…n中随意取几个数，使其和等于m，要求列出所有的组合。


解决方案：

```
#include <iostream>  
#include <list>  
using namespace std;  
list<int> list1;  
void find_factor(int sum,int n)  
{  
    //递归出口  
    if(n<=0||sum<=0)  
        return;  
    //输出找到的数  
    if(sum==n)  
    {  
        list1.reverse();  
        for(list<int>::iterator iter=list1.begin();iter!=list1.end();iter++)  
            cout<<*iter<<”+”;  
        cout<<n<<endl;  
        list1.reverse();  
    }  
    list1.push_front(n);  
    find_factor(sum-n,n-1);//n放在里面  
    list1.pop_front();  
    find_factor(sum,n-1);//n不放在里面  
}  
    
int main(void)  
{  
    int sum,n;  
    cin>>sum>>n;  
    cout<<”所有可能的序列，如下：”<<endl;  
    find_factor(sum,n);  
    return 0;  
}  
```

</details>

## 高级

<details><summary>动态规划</summary>

|  | 动态规划 |  |

</details>

<details><summary>贪心算法</summary>

|  | 贪心算法 |  |

</details>

<details><summary>摊还分析</summary>

|  | 摊还分析 |  |

</details>

<details><summary>位操作</summary>

|  | 位操作 |  |

</details>

<details><summary>模运算</summary>

# 模运算


## 运算规则

    (a + b) % p = (a % p + b % p) % p  
    (a - b) % p = (a % p - b % p) % p  
    (a * b) % p = (a % p * b % p) % p  
    a ^ b % p = ((a % p)^b) % p


## 应用

### 1.判断奇偶数
```
bool IsEven( int n )
{
    return (n % 2 == 0);
}
```

### 2.判断素数

```
bool IsPrime( unsigned int n )
{
    unsigned maxFactor = sqrt( n );
    for ( unsigned int i = 2; i < n; i++ )
    {
        if ( n % i == 0 )
            return false;
    }
    return true;
}

```

### 3.最大公约数

使用欧几里德算法(辗转相除法)，原理：gcd(a, b) = gcd(b, a % b)

```
int Gcd( int a, int b )
{
    if ( b == 0 )
        return a;
    return gcd( b, a % b );
}
```


### 4.水仙花数
水仙花数是指一个 3 位数，它的每个位上的数字的 3次幂之和等于它本身（例如：$1^3 + 5^3+ 3^3 = 153$）

```
//求三位水仙花数：
int NarcissisticNumber()
{
    for ( int i = 100; i < 1000; i++ )
    {
        //按照水仙花的定义计算
        if ( pow(i%10, 3) + pow(i/10%10, 3) + pow(i/100%10, 3) == i )
            cout << i << endl;
    }
}
```

水仙花数其实是三位自幂数(自恋数)，求任意位数自幂数：
```
//任意位数水仙花数
int NarcissisticNumber( int digitsNum )
{
    long tempSum = 0, tempNum = 0;
    long beginN = pow( 10, digitsNum-1 );
    long endN = pow( 10, digitsNum );
    for ( long i = beginN; i < endN; i++ )
    {
        //每个digitsNum位数都使用定义判断
        for ( int j = 0; j < digitsNum; j++ )
        {
            tempNum = pow( 10, j );
            tempNum = i / tempNum;
            tempNum = tempNum % 10;
            tempNum = pow( tempNum, digitsNum );
            tempSum += tempNum;
        }
        if ( tempSum == i )
            cout << tempSum << endl;
    }
    return 0;
}
```

### 5.横幂问题

利用模运算的运算规则，简化某些运算，例如

[leetcode](https://leetcode-cn.com/problems/super-pow/)372.你的任务是计算$a^b$对1337取模，a是一个正整数，b是一个非常大的正整数且会以数组形式给出。

互质

基本概念：
* 欧拉定理：
 
    a,n为正整数，且a,n互质，那么$a^{\varphi(x)}\equiv1(mod\ n)$
 
* 互质(互素)：
* 欧拉函数：

    欧拉函数f(n)(n ( N<sup>*</sup>)是小于等于n的正整数中与n互质的数的个数
    
* 欧拉-费马降幂：

    a<sup>x</sup> = a<sup>(x%f()</sup>

* 快速幂：





### 6.孙子问题(中国剩余定理)

《孙子算经》上有这样一个问题：“今有物不知其数，三三数之剩二（除以3余2），五五数之剩三（除以5余3），七七数之剩二（除以7余2），问物几何？”这个问题被称为“孙子问题”，该问题的一般解法被称为“中国剩余定理”，具体解法分三步：
* 1.找出三个数：从3和5的公倍数中找出被7除余1的最小数15，从3和7的公倍数中找出被5除1的最小数21，最后从5和7的最小公倍数中找出除3余1的最小数70.
* 2.用15乘以2（2为最终结果除以7的余数），用21乘以3（3为最终结果除以5的余数），同理，用70乘以2（2为最终结果除以3的余数），然后把三个乘积相加`15*2+21*3+70*2`得到和233.
* 3.用233除以3,5,7三个数的最小公倍数105，得到余数23，即`233%105=23`。这个余数23就是符合条件的最小数。

具体的解法推导过程参考博文：[中国剩余定理](https://www.cnblogs.com/MashiroSky/p/5918158.html)

根据剩余定理，把此种解法推广到有n（n为自然数）个除数对应n个余数，求最小被除数的情况。输入n个除数（除数不能互相整除）和对应的余数，计算机将输出最小被除数。

```
/*
 * 函数名：ResidueTheorem
 * 函数功能：运用剩余定理，解决推广了的孙子问题，给定n个除数（除数不能互相整除）和对应余数，返回最小被除数
 * 输入值：devisor,存储了n个除数的数组；remainder,存储了n个余数的数组；length，这两个数组的长度
 * 返回值：最小被除数
 */
unsigned ResidueTheorem( const unsigned devisor[], const unsigned remainder[], int length )
{
    unsigned product = 1;    //所有除数的乘积
    
    for ( int i = 0; i < length; i++ )
    {
        product *= devisor[i];
    }
    
    //公倍数数组，表示除该元素(除数)之外其他除数的公倍数
    unsigned *commonUmltiple = new unsigned[length];
    for ( int i = 0; i < length; i++ )
    {
        commonUmltiple[i] = product / devisor[i];
    }
    
    //被除数，函数将返回的值
    unsigned dividend = 0;
    //计算被除数，但此时得到的不是最小被除数
    for ( int i = 0; i < length; i++ )
    {
        //按照剩余利落计算合适的公倍数，使得tempMul%devisor[i]==1
        unsigned tempMul = commonMultiple[i];
        while ( tempMul % devisor[i] != 1 )
        {
            tempMul += commonMultiple[i];
        }
        //用本除数得到的余数乘以其他除数的公倍数
        dividend += tempMul * remainder[i];
    }
    delete[] comonMultiple;
    //返回最小被除数
    return ( dividend % product );
}
```

### 7.凯撒密码





[^互质]：公约数只有1的两个整数，叫做互质整数

</details>



参考资料：

- 《算法》第四版
- [Wikipedia:Sorting algorithm](https://en.wikipedia.org/wiki/Sorting_algorithm)
