# handy项目剖析

<!-- TOC -->

- [0. 目标(6.15)](#0-目标615)
- [1. noncopyable](#1-noncopyable)
- [1. EventsImp](#1-eventsimp)
- [2. PollerBase](#2-pollerbase)
- [3. Channel](#3-channel)
- [4. Signal](#4-signal)
- [5. Ip4Addr](#5-ip4addr)
- [6. TcpServer](#6-tcpserver)
- [7. TcpConn](#7-tcpconn)

<!-- /TOC -->

## 0. 目标(6.15)
- 第一步：先剖析源代码，搞清楚总体如何设计，局部实现方案，总结归纳为剖析文档(预计6.19晚完成)
  - 首先，搞清楚大概框架，了解每部分的主要功能，对实现细节不必太过在意，把握总体框架，输出 **基本功能文档**，即本文档的1.0版本
  - 对每部分进行详细分析，**对基本功能文档进行完善**，即本文档的2.0版本
- 第二步：根据该项目设计思想，设计自己的项目，这一步的实现步骤如下：(预计6.28完成)
  - 首先，理清项目主要框架，将原来项目的复杂工具简单实现，实现第一个版本：凸显设计框架，某些工具类空实现或者简单实现，力求用最少代码搭建一个可以实现原服务器60%以上功能的 **1.0版本**
  - 接下来，**完善框架部分，完善必要的工具代码**，力图实现原有服务器90%以上的功能
  - 然后，就是 **正确完全实现原有服务器100%的功能**，这一步应该已经完全搞清楚这个项目的来龙去脉
  - 最后，争取在原有项目基础上进行一部分的 **优化** 工作


[项目地址](https://github.com/yedf/handy)

Handy是一个简洁高效的C++11网络库，支持linux与mac平台，使用异步IO模型

## 1. noncopyable

handy中大部分的类都继承于 `noncopyable` ，关于该类的具体请参考： [noncopyable](../cpp_summary/C++实现不可被拷贝的类.md)

## 1. EventsImp 

## 2. PollerBase

PollerBase是IO复用接口函数的封装，其派生出来的PollerEpoll和PollerKqueue分别对应Linux和Mac OS下的IO复用工具。

其对Channel进行管理


## 3. Channel

Channel用于管理文件描述符和文件描述符上的读写事件处理函数，相当于高级的文件描述符

## 4. Signal

仅有一个signal函数，用于注册信号处理函数，其中有使用map来记录信号和对应处理函数之间的映射关系

## 5. Ip4Addr

IP地址的抽象，封装了一些IP处理的函数

## 6. TcpServer

负责服务器的建立，包括服务器的bind和accept

## 7. TcpConn

对建立的TCP连接的抽象，包括连接的建立，连接的读取和发送数据，连接的关闭等

