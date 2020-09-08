# 设计模式总结

<!-- TOC -->

- [创建型模式](#创建型模式)
- [1. Abstract Factory](#1-abstract-factory)
- [2. Builder](#2-builder)
- [3. Factory Method](#3-factory-method)
- [4. Prototype](#4-prototype)
- [5. Singleton](#5-singleton)
    - [懒汉式：](#懒汉式)
        - [懒汉式多线程安全改进(双检锁)：](#懒汉式多线程安全改进双检锁)
    - [饿汉式：](#饿汉式)
    - [其他问题](#其他问题)
        - [单例对象的析构：](#单例对象的析构)
- [结构型模式](#结构型模式)
- [6. Adapter](#6-adapter)
- [7. Bridge](#7-bridge)
- [行为模式](#行为模式)

<!-- /TOC -->

## 创建型模式

## 1. Abstract Factory

## 2. Builder

## 3. Factory Method

## 4. Prototype

## 5. Singleton

保证一个类仅有一个实例，并提供一个访问它的全局访问点
- 懒汉式：类文件加载的时候已经创建好了对象，如果对象一直没有使用，则类对象浪费空间
- 饿汉式：使用时才创建实例，多线程访问的时候线程不安全(双检锁)

```
class Singleton
{
public:
    static Singleton* Instance();
    ~Singleton() {}
    
protected:
    Singleton() {}
    
private:
    static Singleton * _instance;
    
};
```


### 懒汉式：
```
Singleton* Singleton::_instance = NULL;
Singleton* Singleton::Instance() {
    if (_instance == NULL) {
        _instance = new Singleton();
    }
    return _instance;
}
```

#### 懒汉式多线程安全改进(双检锁)：
```
Singleton* Singleton::Instance() {
    if (_instance == NULL) {
        lock();
        if (_instance == NULL)
            _instance = new Singleton();
        unlock();
    }
    return _instance;
}
```

- 为什么要使用双检锁？

  所谓双重检查加锁机制，指的是：并不是每次进入`Instance()`方法都需要同步，而是先不同步，进入方法过后，先检查实例是否存在，如果不存在才进入下面的同步块，这是第一重检查。进入同步块过后，再次检查实例是否存在，如果不存在，就在同步的情况下创建一个实例，这是第二重检查。这样一来，就只需要同步一次了，而减少了多次在同步情况下进行判断所浪费的时间

- CPU 换序执行给双检锁带来的问题

TODO:

  参见《程序员的自我修养——编译、连接、库》1.6.2 线程安全：过度优化

### 饿汉式：

```
Singleton* Singleton::_instance = new Singleton();
Singleton* Singleton::Instance() {
    return _instance;
}
```

### 其他问题

#### 单例对象的析构：
* **m_pInstance 指向的空间什么时候释放呢？更严重的问题是，该实例的析构函数什么时候执行？**

  如果在类的析构行为中有必须的操作，比如关闭文件，释放外部资源，那么上面的代码无法实现这个要求。我们需要一种方法，正常的删除该实例。

  可以在程序结束时调用GetInstance()，并对返回的指针掉用delete操作。这样做可以实现功能，但不仅很丑陋，而且容易出错。因为这样的附加代码很容易被忘记，而且也很难保证在delete之后，没有代码再调用GetInstance函数。

  一个妥善的方法是让这个类自己知道在合适的时候把自己删除，或者说把删除自己的操作挂在操作系统中的某个合适的点上，使其在恰当的时候被自动执行。

  我们知道，程序在结束的时候，系统会自动析构所有的全局变量。事实上，系统也会析构所有的类的静态成员变量，就像这些静态成员也是全局变量一样。利 用这个特征，我们可以在单例类中定义一个这样的静态成员变量，而它的唯一工作就是在析构函数中删除单例类的实例。如下面的代码中的CGarbo类 （Garbo意为垃圾工人）
  ```
  class Singleton {
  public:
      static Singleton* Instance() {}
      
  private:
      class Garbo {
      public:
          ~Garbo() {
              if (Singleton::_instance != NULL)
                  delete Singleton::_instance;
          }
      };
      
  private:
      static Singleton* _instance;
      static Garbo _garbo;
  };
  ```
  类CGarbo被定义为CSingleton的私有内嵌类，以防该类被在其他地方滥用。

  程序运行结束时，系统会调用CSingleton的静态成员Garbo的析构函数，该析构函数会删除单例的唯一实例。
  
  使用这种方法释放单例对象有以下特征：

  - 在单例类内部定义专有的嵌套类；

  - 在单例类内定义私有的专门用于释放的静态成员；

  - 利用程序在结束时析构全局变量的特性，选择最终的释放时机；

  - 使用单例的代码不需要任何操作，不必关心对象的释放。
  
  **进一步的讨论：**
  
  但是添加一个类的静态对象，总是让人不太满意，所以有人用如下方法来重新实现单例和解决它相应的问题，代码如下：
  ```
  class CSingleton
  {
    //其他成员
    public:
        static Singleton &GetInstance() {
            static Singleton instance;
            return instance;
        }

    private:
        Singleton() {};
  };
  ```
  使用局部静态变量，非常强大的方法，完全实现了单例的特性，而且代码量更少，也不用担心单例销毁的问题。但使用此种方法也会出现问题，当如下方法使用单例时问题来了，

  ```Singleton singleton = Singleton :: GetInstance();```

  这么做就出现了一个类拷贝的问题，这就违背了单例的特性。产生这个问题原因在于：编译器会为类生成一个默认的构造函数，来支持类的拷贝。这时我才想起可以将拷贝构造函数和重载=操作符等显示的声明为私有类成员，新的单例类如下：
  ```
  class Singleton
  {
  //其他成员
  public:
      static Singleton &GetInstance() {
          static Singleton instance;
          return instance;
      }
  private:
      Singleton() {};
      Singleton(const Singleton);
      Singleton & operate = (const Singleton&);
  };
  ```

  关于Singleton(const Singleton)和 Singleton & operate = (const Singleton&)函数，需要声明成私有的，并且只声明不实现。这样，如果用上面的方式来使用单例时，不管是在友元类中还是其他的，编译器都是报错。


  还可以通过让GetInstance()函数返回一个指针而不是返回一个引用解决这个问题，函数的代码改为如下：

  ```
  static Singleton *GetInstance()
  {
      static Singleton instance;
      return &instance;
  }
  ```


## 结构型模式

## 6. Adapter

## 7. Bridge

## 行为模式