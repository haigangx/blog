# 条款31：将文件间的编译依存关系降至最低

## 问题：

```
#include <string>

//编译器必须在编译期间知道对象大小，只有访问到定义式才能得到对象大小，所有需要包含头文件
#include "date.h" 
#include "address.h"

class Person {
public:
    Person(const std::string& name, const Date& birthday, const Address& addr);
    std::string name() const;
    std::string birthDate() const;
    std::string address() const;
    ...
private:
  std::string theName;  //实现细目
  Date theBirthDate;    //实现细目
  Address theAddress;   //实现细目
}；
```
如上，Person定义文件和其包含的头文件date.h,address.h之间形成了一种编译依存关系(compilation dependency).如果这些头文件中有任何一个被改变，或这些头文件所依赖的其他头文件有任何改变，那么每一个包含Person class的文件就的重新编译，任何使用Person class的文件也必须重新编译。这样的连串编译依存关系(cascading compilation dependencies)会对许多项目造成难以形容的灾难。

## 解决方案一：前置声明+用pimpl手法将对象实现细目隐藏于指针背后

把Person分割为两个class，一个只提供接口，另一个负责实现该接口。将负责实现的implementation class取名为PersonImpl，Person将定义如下：
```
#include <string>   //标准程序库组建不该被前置声明，标准库头文件一般不会成为编译瓶颈
#include <memory>

//前置声明
class PersonImpl;
class Date;
class Address;

class Person {
public:
    //class作为函数声明的参数或返回值时，不需要该class定义式
    Person(const std::string& name, const Date& birthday, const Address& addr);
    std::string name() const /*{ pImpl->name(); }*/;
    std::string birthDate() const;
    std::string address() const;
    ...
private:
    std::tr1::shared_ptr<PersonImpl> pImpl;   //pImpl指针指向Person的实现类PersonImpl
};
```

这样的设计之下，Person的客户就完全与Dates，Address以及Persons的实现细目分离了。那些class的任何实现修改都不需要Person客户端重新编译。此外由于客户无法看到Person的实现细目，也就不可能写出什么“取决于那些细目”的代码，这是真正的“接口与实现分离”！

### 规则

- **如果使用 object references 或 object pointers 可以完成任务，那就不要使用 object. **
  
  你可以只靠一个类型声明式就定义出指向该类型的reference和pointer；但如果定义某类型的object，就需要用到该类型的定义式

- **尽量以class声明式替换class定义式**

  当你声明一个函数而它用到某个class时，你并不需要该class的定义；纵使函数以by value方式传递该类型的参数或返回值亦然

- **为声明式和定义式提供不同的头文件**

  ```
  #include "datefwd.h"  //头文件内声明(但未定义)class Date
  Date today();
  void clearAppointments(Date d);
  ```

## 解决方案二：抽象基类作为接口类

针对Person而写的interface class如下：

```
class Person {
public:
    virtual ~Person();
    virtual std::string birthDate() const = 0;
    virtual std::string address() const = 0;
    ...
};
```

支持Person接口类的具体类RealPerson如下：

```
class RealPerson : public Person {
public:
    RealPerson(const std::string& name, const Date& birthday, const Address& addr)
      : theName(name), theBirthDate(birthday), theAddress(addr)
    {}
    virtual ~RealPerson() { }
    std::string name() const;
    std::string birthDate() const;
    std::string address() const;
private:
    std::string theName;
    Date theBirthDate;
    Address theAddress;
};
```

用户使用如下：

```
std::string name;
Date dateOfBirth;
Address address;
...
std::tr1::shared_ptr<Person> pp(Person::Create(name, dateOfBirth, address));
...
std::cout << pp->name();
...
```
除非interface class的接口被修改否则其客户不需要重新编译
