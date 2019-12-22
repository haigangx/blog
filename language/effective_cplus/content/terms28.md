# 条款28：避免返回handles指向对象内部成分

成员函数返回指向对象内部成分(类的protected、private成员)的hanldes(pointer或reference)带来的问题：

- 破坏封装性：会导致成员变量的封装性最多只等于"返回其reference"的函数的访问级别

- handles所指向的成员变量会在外部被改变，如果const成员函数传出一个reference，后者所指数据与对象自身有关联，
  而它又被存储于对象之外，那么这个函数的调用者可以修改那笔数据，这是bitwise constness的附带结果

  例：

  ```
  class Point { ... };
  struct RectData
  {
      Point ulhc;     //ulhc = "upper left-hand corner"左上角
      Point lrhc;     //lrhc = "lower right-hand corner"右下角
  };
  class Rectangle
  {
  public:
      ...
      Point& upperLeft() const { return pData->ulhc; }    //可以通过编译但是是错误的
      Point& lowerRight() const { return pData->lrhc; }   //可以通过编译但是是错误的
      ...
  private:
      std::tr1::shared_ptr<RectData> pData;
  };
  ```

  upperLeft和lowerRight函数被声明为const成员函数，本意是提供给客户一个得知Rectangle相关坐标点的方法，
  而不是让客户修改Rectangle，但是这两个函数却都返回reference和pointer内部数据，调用者可以通过这些reference更改内部数据

- 令成员函数返回一个指针指向“访问级别较低”的成员函数，如果这么做，后者的实际访问级别就会提高的如前者一样，
  因为客户可以取得一个指针指向哪个“访问级别较低”函数，然后通过哪个指针调用它

  例：一个public成员函数返回一个private成员函数的指针，外界可以通过这个函数指针调用类的private成员函数

- 可能导致dangling handles(虚吊句柄)的情况
  
  针对2中的问题可以为两个const函数的返回类型加上const解决，如：
  
  ```
  class Rectangle
  {
  public:
      ...
      const Point& upperLeft() const { return pData->ulhc; }
      const Point& lowerRight() const { return pData->lrhc; }
      ...
  };
  ```
  
  但这样还是会存在问题，例如：
  
  ```
  class GUIObject { ... };
  //以by value方式返回一个矩形
  const Rectangle boundingBox( const GUIObject& obj );
  ```
  
  如果这样使用该函数：
  
  ```
  GUIObject* pgo;
  ...
  const Point* pUpperLeft = &(boundingBox(*pgo).upperLeft());
  ```
  
  上面对boundingBox的调用将获得一个新的、暂时的Rectangle对象，然后对临时对象调用upperLeft函数，返回临时对象内部的成分交给pUpperLeft，
  然而，在本行语句分号结束之后，这个临时Rectangle对象就会被销毁，返回的对象内部的成分也会消失，pUpperLeft将变成野指针，
  也即是空悬、虚吊的(dangling)!
  
  总之，一旦有可能“handle比其所指对象更长寿”，那么这个handle就有虚吊的危险

**Remember：**

  尽量避免返回handles(包括pointer、reference、迭代器)指向对象内部
