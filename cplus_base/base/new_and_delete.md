# operator new、operator new[]、operator delete、operator delete[]、placement new

## new表达式和delete表达式的行为：

- **当我们使用一条new表达式时，实际执行了三步操作：**

  ```
  //new表达式
  string *sp = new string("a value"); //分配并初始化一个string对象
  string *arr = new string[10];       //分配10个默认初始化的string对象
  ```

  - new表达式调用一个名为operator new(或者operator new[])的标准库函数。该函数负责分配一块足够大的、原始的、
    未命名的内存空间以便存储特定类型的对象(或对象数组)

  - 编译器运行相应的构造函数以构造这些对象，并为其传入初始值

  - 对象被分配了空间并构造完成，返回一个指向该对象的指针

- **当我们使用一条delete表达式删除一个动态分配的对象时，实际执行了两步操作：**

  ```
  delete sp;      //销毁*sp，然后释放sp指向的内存空间
  delete [] arr;  //销毁数组中的元素，然后释放对应的内存空间
  ```

  - 对sp所指对象或者arr所指的数组中的元素执行对应的析构函数

  - 编译器调用名为operator delete(或operator delete[])的标准库函数释放内存空间

- **我们可以自定义operator new和operator delete这两个函数的行为，但是无法定义new表达式和delete表达式的行为**

  如果用户希望自己控制内存分配的过程，则需要自定义自己的 **operator new函数** 和 **operator delete函数**

  应用程序可以在全局作用域中定义operator new函数和operator delete函数，也可以将它们定义为成员函数，用户查找可供调用的operator函数的规则是：

  - 如果被分配(释放)的对象是类类型，则编译器首先在类及其基类的作用域中查找

  - 否则，编译器在全局作用域查找匹配的函数，

  如果编译器找到了用户自定义的版本，则使用该版本执行new表达式或delete表达式；如果没找到，则使用标准库定义的版本

  可以使用作用域运算符令new表达式或delete表达式忽略定义在类中的函数，直接执行全局作用域中的版本，例如：
  ::new只在全局作用域中查找匹配的operator new函数，::delete也一样

  标准库中operator new函数和operator delete函数的8个重载版本：

  ```
  //这些版本可能抛出异常
  void *operator new(size_t);                 //分配一个对象
  void *operator new[](size_t);              //分配一个数组
  void *operator delete(void*) noexcept;      //释放一个对象
  void *operator delete[](void*) noexcept;   //释放一个数组
  ```

  ```
  //这些版本承认不会抛出异常
  void *operator new(size_t, nothrow_t&) noexcept;
  void *operator new[](size_t, nothrow_t&) noexcept;
  void *operator delete(void*, nothrow_t&) noexcept;
  void *operator delete[](void*, nothrow_t&) noexcept;
  ```

  - 类型nothrow_t是定义在new头文件中的一个struct，在这个类型中不包含任何成员，用户通过这个对象来请求new的非抛出版本

  - 当将上述运算符函数定义为类成员时，它们是隐式静态的，无须显式声明static，因为operator new用在对象构造之前
    而operator delete用在对象销毁之后，所以这两个成员(new和delete)必须是静态的，而且它们不能操纵类的任何数据成员

  **自定义的operator new和operator delete的一种简单方式：**

  ```
  //使用malloc和free开辟释放空间
  void *operator new(size_t size)
  {
      if (void *mem = malloc(size))
          return mem;
      else
          throw bad_alloc();
  }
  void operator delete(void *mem) noexcept 
  {
      free(mem);
  }
  ```

## 定位new表达式：

- **定位new允许我们在一个特定的、预先分配的内存地址上构造对象**

  ```
  new (place_address) type
  new (place_address) type (initializers)
  new (place_address) type [size]
  new (place_address) type [size] {braced initializer list}
  ```

  - place_address必须为一个指针
  - initializers中提供一个(可能为空)的以逗号分隔的初始值列表，该初始值用于构造新分配的对象

- **显式的析构函数调用：**

  例：

  ```
  string *sp = new string("a value");     //分配并初始化一个string对象
  sp->~string();      //显式调用析构函数
  ```

  调用析构函数可以清楚给定的对象但是不会释放该对象所在的空间。如果需要的话，我们可以重新使用该空间
