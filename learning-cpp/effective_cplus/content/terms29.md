# 条款29：为“异常安全”而努力是值得的

假如有一个拥有背景图片的GUI菜单类，class中有一个用于改变背景图片的方法，并且希望这个class用于多线程环境，所以它有个互斥锁(mutex)作为并发控制之用：

```
class PrettyMenu
{
public:
    ...
    void changeBackground(std::istream& imgSrc);    //改变背景图像
    ...
private:
    Mutex mutex;    //互斥锁
    Image* bgImage; //目前的背景图像
    int imageChanges;   //背景图片被改变次数
};
```

一个PrettyMenu的changeBackground的可能实现：

```
void PrettyMenu::changeBackground(std::istream& imgSrc)
{
    lock(&mutex);       //取得互斥锁
    delete bgImage;     //摆脱旧的背景图片
    ++imageChanges;     //修改图像修改次数
    bgImage = new Image(imgSrc);    //安装新的背景图像
    unlock(&mutex);     //释放互斥锁
}
```

这个函数不具备“异常安全性”，异常安全的两个条件，这个函数没有满足任何一个：

- 不泄露任何资源。

  一旦“new Image(imgSrc)”发生异常，对unlock的调用就绝不会执行，于是互斥锁被永远被锁，changeBackground函数没有做到这点

- 不允许数据败坏。

  如果“new Image(imgSrc)”抛出异常，bgImage就是指向一个已被删除的对象，imageChhuanges也已被累加，而其实并没有新的图像被成功安装起来
  
资源泄露的问题可以通过资源管理类来解决，如使用Lock类：

```
void PrettyMenu::changeBackground(std::istream& imgSrc)
{
    Lock ml(&mutex);    条款14：获得互斥锁并确保它稍后被释放
    delete bgImage;
    ++imageChanges;
    bgImage = new Image(imgSrc);
}
```

对于数据败坏的问题：

首先，异常安全函数(Exception-safe function)提供以下三个保证之一：

- 基本承诺：

  如果异常被抛出，程序内的任何事物仍然保持在有效状态下。没有任何对象或数据结构会因此而败坏，所有对象都处于一种
  内部前后一致的状态(例如所有的class约束条件都继续获得满足)。然而程序的现实状态(exact state)恐怕不可预料。
  
  举例：我们可以撰写changeBackground使得一旦有异常被抛出时，PrettyMenu对象可以继续拥有原背景图像，或是令它们拥有某个缺省背景图像，
  但客户无法预期哪一种情况，如果想知道，它们恐怕必须调用某个成员函数以得知当时的背景图像是什么。

- 强烈保证：

  如果异常被抛出，程序状态不改变。调用这样的函数需有这样的认知：如果函数成功，就是完全成功，如果函数失败，程序会回复到“调用函数之前”的状态。
  
  在调用一个提供强烈保证的函数后，程序状态只有两种可能：如预期般地到达函数成功执行后地状态，或回到函数被调用前地状态。与此成对比地是，如果调用一个只提供基本承诺地函数，而真的出现异常，程序有可能处于任何状态——只要那是个合法状态

- 不抛出异常(nothrow)保证：
  
  承诺绝不抛出异常，因为它们总是能够完成它们原先承诺地功能，作用于内置类型(如int，指针等)身上地所有操作都提供nothrow保证。

对changeBackground提供强烈保证：

- 通过资源管理类：

  ```
  class PrettyMenu
  {
      ...
      //智能指针代替普通Image指针
      std::tr1::shared_ptr<Image> bgImage;
      ...
  };
  void PrettyMenu::changeBackground(std::istream& imgSrc)
  {
      Lock ml(&mutex);
      //以"new Image"的执行结果设定bgImage内部指针
      bgImage.reset(new Image(imgSrc));   
      ++imageChanges;
  }
  ```

  首先，这里不再需要手动delete旧图像，因为这个动作已经由智能指针内部处理掉了。

  然后，删除动作只发生在新图像被成功创建之后。更正确的说，tr1::shared_ptr::reset函数只有在其参数(也就是“new Image(imgSrc)”)被
  成功生成之后才会被调用。delete只在reset函数内被使用，所以如果从未进入那个函数也就绝不会使用delete
  这两个改变几乎足够让changeBackground提供强烈的异常安全保证，美中不足的是参数imgSrc，imgSrc参数在传递过程中
  会发生异常，在解决这个问题之前该函数只能提供最基本的异常安全保证，可以通过将参数imgSrc的类型，从istream改为一个内含图像数据的文件
  名称来解决这个问题，使其达到强烈异常安全保证

- 通过copy and swap策略：

  copy and swap：为你打算修改的对象做一份副本，然后在那副本身上做一切必要修改，若有任何修改动作抛出异常，原对象仍保持未改变状态，
  待所有改变都成功后，再将修改过的那个副本和原对象在一个不抛出异常的操作中置换(swap)

  实现上通常是将所有"隶属对象的数据"从原对象放进另一个对象内，然后赋予原对象一个指针，
  指向那个所谓的实现对象(implementation object，即副本)这种手法常被成为pimpl idiom

  例：

  ```
  struct PMImpl
  {
      std::tr1::shared_ptr<Image> bgImage;
      int imageChanges;
  };
  class PrettyMenu
  {
      ...
  private:
      Mutex mutex;
      std::tr1::shared_ptr<PMImpl> pImpl;
  };
  void PrettyMenu::changeBackground(std::istream& imgSrc)
  {
      using std::swap;
      Lock ml(&mutex);
      std::tr1::shared_ptr<PMImpl> pNew(new PMImpl(*pImpl));

      pNew->bgImage.reset(new Image(imgSrc);
      ++pNew->imageChanges;

      swap(pImpl, pNew);
  }
  ```

  - "copy-and-swap"策略是对对象状态“全有或全无”改变的一个很好的办法，但一般而言它并不保证整个函数有强烈的异常安全性。
  
    考虑changeBackground的一个抽象概念：someFunc，它使用copy-and-swap策略，但函数内还包括对两外两个函数f1和f2的调用：

    ```
    void someFunc()
    {
        ...     //对local状态做一份副本
        f1();
        f2();
        ...     //将修改后的状态置换过来
    }
    ```

    问题：


    (1)如果f1或f2的异常安全性比“强烈保证”低，就很难让someFunc成为“强烈异常安全”。举例，假设f1只提供基本保证，那么为了让someFunc提供强烈保证，
    我们必须写出代码获得调用f1之前的整个程序状态、捕捉f1的所有可能异常、然后恢复原状态

    (2)如果f1和f2都是“强烈异常安全”，情况并不就此好转。毕竟如果f1圆满结束，程序状态在任何方面都可能有所改变，因此如果f2随后抛出异常，
    程序状态和someFunc被调用前并不相同，甚至当f2没有改变任何东西时也是如此。

    出现上述问题的原因是“连带影响(side effects)”，如果函数只操作局部性状态(local state,例如someFunc只影响其“调用者对象”的状态)，
    便相对容易地提供强烈保证。但是当函数对“非局部性数据”(non-local data)有连带影响时，提供强烈保证就困难的多

  - "copy-and-swap"策略存在的另一个问题是效率：
  
    copy and swap的关键在于“修改对象数据的副本，然后在一个不抛异常的函数中将修改后的数据和原件置换”，因此必须为每一个即将被改动的对象做出一个副本，那得牺牲一部分运行时间和空间。

  上述得两个问题为我们带来启示：“强烈保证”并非在任何时刻都显得实际，当提供“强烈保证”不切实际或者很困难时，就必须提供“基本保证”

**Remember：**

- 异常安全函数(Exception-safe function)即使发生异常亦不会泄露资源或允许数据结构败坏，这样的函数区分为三种可能的保证：基本型、强烈型、不抛异常型

- “强烈保证”往往能够以copy-and-swap实现出来，但“强烈保证”并非对所有函数都可实现或具备现实意义

- 函数提供的“异常安全保证”通常最高只等于其所调用之各个函数的“异常安全保证”中的最弱者
