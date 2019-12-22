# 条款04：确定对象被使用前已被初始化

c++对于"将对象初始化"这件事上总是反复无常，所以最简单有效的处理办法就是：永远在对象使用之前先将它初始化

**1、使用类构造函数的初始化列表为类的成员变量进行初始化**

规则：
  - 应该总在初始化列表中列出所有的成员变量

    对于需要使用default构造函数构造成员变量时，可以使用nothing作为初始化实参，例：
    ```
    ABEntry::ABEntry()
        :theName(), //调用theName的default构造函数
    {}
    ```
   - 成员是const或者references，必须使用初始化
   - 在拥有多个构造函数，每个构造函数有自己的成员初值列。
    这多少会导致一部分重复工作，所以可以适当的在初值列中“遗漏”那些”赋值表现的像初始化一样好“的成员变量，改用他们的赋值操作，并将那些赋值操作移往某个函数(通常是private)中


**2、类成员变量初始化次序**

c++有着固定的成员初始化次序：
  - base classes更早于其derived classes被初始化 
  - class的成员变量总是以其声明次序被初始化，与成员变量在初值列中出现的顺序无关，所以为了避免误会，当你在成员初值列中条列各个成员时，最好总是以其声明次序为次序


**3、“不同编译单元内定义的non-local static 对象”的初始化次序**

**概念：**
  - **static:**
  
    static对象，其寿命从被构造出来直到程序结束为止，包括*global对象*、定义于*namespace作用域内的对象*、在class内、函数内、以及在file作用域内*被声明为static的对象*
    
    已初始化的全局和静态C变量保存在`.data`段，未初始化的全局和静态C变量保存在`.bss`(Batter Save Space)段
    
  - **local static:**
  
    函数内的static对象被称为local static对象，local static对象会在”该函数被调用期间“”首次遇上该对象之定义式“时被初始化
    
  - **non-local static:**
  
    其他不在函数中定义的static对象成为non-local static对象
    
  - **编译单元：**
  
    指产出单一目标文件(single object file)的那些源码，基本上它是单一源码文件加上其所含入的头文件(#include file)

**提出问题：**

***如果某编译单元内的某个non-local static对象的初始化动作使用了另一个编译单元内的某个non-local static对象，它所用到的这个对象可能尚未被初始化，因为C++对”定义于不同编译单元内的non-local static对象“的初始化次序并无明确定义所以应该如何保证当前编译单元中的non-local static对象初始化时，所依赖的另一个编译单元的non-local static对象已经被初始化？***

  举例：

  ```
  //编译单元A.obj
  class FileSystem {
  public:
      ...
      std::size_t numDisks() const;
      ...
  };
  extern FileSystem tfs;

  //编译单元B.obj
  class Directory {
  public:
      Directory( params );
      ...
  };
  Directory::Directory( params ) {
      ...
      std::size_t disks = tfs.numDisks();
      ...
  }

  Directory tempDir( params ); //除非tfs在tempDir之前被初始化，否则tempDir的构造函数会用到未初始化的tfs
  ```
    
**解决办法：** 

**Singleton模式：** 将每个non-local static对象搬到自己的专属函数内(该对象在此函数内被声明为static)。 这些函数返回一个reference指向它所含的对象，然后用户调用这些函数，而不直接指涉这些对象。换句话说：non-local static对象被local static对象替换了

```
//编译单元A.obj
class FileSystem { ... };
FileSystem& tfs() {
    static FileSystem fs;
    return fs;
}

//编译单元B.obj
class Directory { ... };
Directory::Directory( params ) {
    ...
    std::size_t disks = tfs().numDisks();
    ...
}
Directory& tempDir() {
    static Directory td;
    return td;
} 
```

**仍然会存在的问题：**

”内含static对象“的函数在多线程系统中带有不确定性。

**处理这个麻烦的一种做法是：** 在程序的单线程启动阶段(single-threaded startup portion)手工调用所有(reference-returning)函数，这可以消除与初始化有关的"竞速形势(rate conditions)"
