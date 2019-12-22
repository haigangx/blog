# 日志

Linux系统日志体系图(p115 图7-1 日后添加，暂时用文本简单描述)：

```
                    终端输出内核信息
                           ^
                           1
内核  ---printk()-->  内核环状缓存  --->  /proc/kmsg
                                             l
                                             V
用户过程 --syslog()--->  /dev/log  --->  syslogd  ---配置文件-->  /var/log/*
```

syslog函数：
```
#include <syslog.h>
void syslog(int priority, const char* message, ...);
```
- priority：设施值与日志级别的按位或,设施的默认值为LOG_USER，设施值在大多数情况下都为这一种，日志级别有如下几种情况：
  ```
  #include <syslog.h>
  #define LOG_EMERG       0 //系统不可用
  #define LOG_ALERT       1 //报警，需要立即采取动作
  #define LOG_CRIT        2 //非常严重的情况
  #define LOG_ERR         3 //错误
  #define LOG_WARNING     4 //警告
  #define LOG_NOTICE      5 //通知
  #define LOG_INFO        6 //信息
  #define LOG_DEBUG       7 //调试
  ```

openlog函数可以改变syslog的默认输出方式，进一步结构化日志内容：

```
#include <syslog.h>
void openlog(const char* ident, int logopt, int facility);
```

- ident：参数指定的字符串将被添加到日志消息的日期和时间之后，通常设置为程序的名字
- logopt：为后续syslog调用的行为进行配置，可取为下列值得按位或：
  ```
  #define LOG_PID         0x01    //日志消息中包含程序PID
  #define LOG_CONS        0x02    //如果消息不能记录到日志文件，则打印至终端
  #define LOG_ODELAY      0x04    //延迟打开日志功能直到第一次调用syslog
  #define LOG_NDELAY      0x08    //不延迟打开日志功能
  ```
- facility：可以用来修改syslog函数中的默认设施值

setlogmask函数用来设置日志掩码，日志级别大于日志掩码的日志信息会被系统忽略

程序在开发阶段可能需要输出很多调试信息，而发布之后我们又需要将这些调试信息关闭，这时候就需要日志过滤功能

```
#include <syslog.h>
int setlogmask(int maskpri);
```
- maskpri：指定日志掩码值，返回调用进程先前的日志掩码值，该函数始终会成功

closelog函数用来关闭日志功能：
#include <syslog.h>
void closelog();
