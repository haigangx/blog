# Redis 操作

<!-- TOC -->

- [一、Redis 数据结构](#一redis-数据结构)
    - [1. 字符串](#1-字符串)
    - [2. 列表](#2-列表)
    - [3. 集合](#3-集合)
    - [4. 散列](#4-散列)
    - [5. 有序集合](#5-有序集合)

<!-- /TOC -->

## 一、Redis 数据结构

### 1. 字符串

Redis 中，字符串可以存储以下 3 中类型的值：

- 字节串
- 整数
- 浮点数

| 命令 | 用例 | 描述 |
| --- | --- | --- |
| `GET` | `GET key-name` | 获取给定键的值 |
| `SET` | `SET key-name value` | 设置给定键的值 |
| `DEL` | `DEL key-name` | 删除给定键的值 |

整数或浮点数所特有的自增自减操作如下：

| 命令 | 用例 | 描述 |
| --- | --- | --- |
| `INCR` | `INCR key-name` | 键存储的值 + 1 |
| `DECR` | `DECR key-name` | 键存储的值 - 1 |
| `INCRBY` | `INCRBY key-name amount` | 键存储的值加上整数 amount |
| `DECRBY` | `DECRBY key-name amount` | 键存储的值减去整数 amount |
| `INCRBYFLOAT` | `INCRBYFLOAT key-name amount` | 键存储的值加上浮点数 amount | 

- 当用户将一个可被解释为十进制整数或浮点数的值存储到 Redis 字符串中时，Redis 可察觉到这一点，并且允许用户对这个字符串执行各种自增和自减命令

- 当用户对一个不存在的键或一个保存了空串的键执行自增或自减操作时，那么 Redis 在执行操作时会将这个键的值当作是 0 处理

- 当用户对一个无法被解释为整数或者浮点数的字符串键执行自增或自减操作时，Redis 将向用户返回一个错误


下面是供 Redis 处理子串和二进制位的命令：

| 命令 | 用例 | 描述 |
| --- | --- | --- |
| `APPEND` | `APPEND key-name value` | 将 value 追加到给定键存储值的末尾 |
| `GETRANGE` | `GETRANGE key-name start end` | 获取偏移量 [start, end] 范围的子串 |
| `SETRANGE` | `SETRANGE key-name offset value` | 将从偏移量 offset 开始的子串设为给定 value |
| `GETBIT` | `GETBIT key-name offset` | 将字节串看作二进制位串，并返回位串中偏移量为 offset 的二进制的值 |
| `SETBIT` | `SETBIT key-name offset value` | 将字节串看作二进制位串，并将位串中偏移量为 offset 的二进制的值设置为 value |
| `BITCOUNT` | `BITCOUNT key-name [start end]` | 统计二进制位串里面值为 1 的二进制位的数量，如果给定可选的 start 和 end 偏移量，那么只对偏移量指定范围内的二进制位进行统计 |
| `BITOP` | `BITOP operation dest-key key-name [key-name ...]` | 对一个或多个二进制位串执行包括并（AND）、或（OR）、异或（XOR）、非（NOT）在内的任意一种按位运算操作，并将结果保存在 dest-key 键里面 |

- 使用 `SETRANGE` 和 `SETBIT` 命令对字符串进行写入的时候，如果字符串当前的长度不能满足写入要求，那么 Redis 会自动使用空字节（null）将字符串拓展至所需的长度再进行写入或更新操作
- 使用 `GETRANGE` 读取字符串时，超出字符串末尾的数据会被视为空串，而在使用 `GETBIT` 读取二进制位串时，超出字符串末尾的二进制位会被视为 0

### 2. 列表

列表结构可以有序的存储多个字符串

一些常用的列表命令：

| 命令 | 用例 | 描述 |
| --- | --- | --- |
| `RPUSH` | `RPUSH key-name value [value ...]` | 将一个或多个值推入列表的右端 |
| `LPUSH` | `LPUSH key-name value [value ...]` | 将一个或多个值推入列表的左端 |
| `RPOP` | `RPOP key-name` | 移除并返回列表最右端的元素 |
| `LPOP` | `LPOP key-name` | 移除并返回列表最左端的元素 |
| `LINDEX` | `LINDEX key-name offset` | 返回列表中偏移量为 offset 的元素 |
| `LRANGE` | `LRANGE key-name start end` | 返回列表 [start, end] 范围的元素 |
| `LTRIM` | `LTRIM key-name start end` | 对列表进行裁剪，只保留 [start, end] 范围内的元素 |

阻塞式的列表弹出命令以及在列表之间移动元素的命令：

| 命令 | 用例 | 描述 |
| --- | --- | --- |
| `BLPOP` | `BLPOP key-name [key-name ...] timeout` | 从第一个非空列表中弹出位于最左端的元素，或者在 timeout 秒之内阻塞并等待可弹出的元素出现 |
| `BRPOP` | `BRPOP key-name [key-name ...] timeout` | 从第一个非空列表中弹出位于最右端的元素，或者在 timeout 秒之内阻塞并等待可弹出的元素出现 |
| `RPOPLPUSH` | `RPOPLPUSH source-key dest-key` | 从 source-key 列表中弹出位于最右端的元素，然后将这个元素推入 dest-key 列表的最左端，并向用户返回这个元素 |
| `BRPOPLPUSH` | `BRPOPLPUSH source-key dest-key timeout` | 功能同 `RPOPLPUSH`，区别在于如果 source-key 为空，那么在 timeout 秒之内阻塞并等待可弹出的元素出现 |

### 3. 集合

集合结构使用无序的方式存储多个字符串，且通过使用散列表保证存储的每个字符串都是不同的

常用的集合命令：

| 命令 | 用例 | 描述 |
| --- | --- | --- |
| `SADD` | `SADD key-name item [item ...]` | 将一个或多个元素添加到集合里面，返回成功添加的元素数量 |
| `SREM` | `SREM key-name item [item ...]` | 从集合里面移除一个或多个元素，并返回被移除的元素数量 |
| `SISMEMBER` | `SISMEMBER key-name item` | 检查元素 item 是否存在于集合 key-name 里 |
| `SCARD` | `SCARD key-name` | 返回集合包含的元素的数量 |
| `SMEMBERS` | `SMEMBERS key-name` | 返回集合包含的所有元素 |
| `SRANDMEMBER` | `SRANDMEMBER key-name [count]` | 从集合里面随机返回一个或 [count] 个元素，count > 0 时，返回的的元素不重复，count 大于等于集合大小时返回整个集合；count < 0 时，返回的元素可重复，返回元素为 count 的绝对值 |
| `SPOP` | `SPOP key-name` | 随机移除集合中的一个元素，并返回被移除的元素 |
| `SMOVE` | `SMOVE source-key dest-key item` | 从集合 source-key 中移除元素 item，并将其添加到 dest-key 中，命令成功执行返回 1，否则返回 0 |

用于组合和处理多个集合的 Redis 命令：

| 命令 | 用例 | 描述 |
| --- | --- | --- |
| `SDIFF` | `SDIFF key-name [key-name ...]` | 返回存在于第一个集合，但不存在其他集合的元素（差集） |
| `SDIFFSTORE` | `SDIFFSTORE dest-key key-name [key-name ...]` | 将 `SDIFF` 的结果存储在 dest-key 中 |
| `SINTER` | `SINTER key-name [key-name ...]` | 返回同时存在于所有集合的元素（交集） |
| `SINTERSTORE` | `SINTERSTORE dest-key key-name [key-name ...]` | 将 `SINTER` 的结果存储在 dest-key 中 |
| `SUNION` | `SUNION key-name [key-name ...]` | 返回至少存在于一个集合中的元素（并集） |
| `SUNIONSTORE` | `SUNION dest-key key-name [key-name ...]` | 将 `SUNION` 的结果存储在 dest-key 中 |

### 4. 散列

散列结构可以存储多个键值对之间的映射，和字符串一样，散列存储的值既可以是字符串又可以是数字值，用户也可以对散列存储的数字值执行自增操作或自减操作

用于添加和删除键值对的散列操作：

| 命令 | 用例 | 描述 |
| --- | --- | --- |
| `HMGET` | `HMGET key-name key [key ...]` | 从散列里面获取一个或多个键的值 |
| `HMSET` | `HMSET key-name key value [key value ...]` | 为散列里面的一个或多个键设置值 |
| `HDEL` | `HDEL key-name key [key ...]` | 删除散列里面的一个或多个键值对，返回成功找到并删除的键值对数量 |
| `HLEN` | `HLEN key-name` | 返回散列包含的键值对数量 |

展示 Redis 散列的更高级特性：

| 命令 | 用例 | 描述 |
| --- | --- | --- |
| `HEXISTS` | `HEXISTS key-name key` | 检查指定键是否存在于散列中 |
| `HKEYS` | `HKEYS key-name` | 获取散列包含的所有键 |
| `HVALS` | `HVALS key-name` | 获取散列包含的所有值 |
| `HGETALL` | `HGETALL key-name` | 获取散列包含的所有键值对 |
| `HINCRBY` | `HINCRBY key-name key increment` | 将键 key 存储的值加上整数 increment |
| `HINCRBYFLOAT` | `HINCRBYFLOAT key-name key increment` | 将键 key 存储的值加上浮点数 increment |


### 5. 有序集合

| 命令 | 用例 | 描述 |
| --- | --- | --- |
| `ZADD` | `ZADD key-name score member [score member ...]` | 将带有给定分值的成员添加到有序集合中 |
| `ZREM` | `ZREM key-name member [member ...]` | 从有序集合里面移除给定的成员，并返回被移除成员的数量 |
| `ZCARD` | `ZCARD key-name` | 返回有序集合包含的成员数量 |
| `ZINCRBY` | `ZINCRBY key-name increment member` | 将 member 成员的分值加上 increment |
| `ZCOUNT` | `ZCOUNT key-name min max` | 返回分值介于 min 和 max 之间的成员数量 |
| `ZRANK` | `ZRANK key-name member` | 返回成员 member 在有序集合中的排名 |
| `ZSCORE` | `ZSCORE key-name member` | 返回成员 member 的分值 |
| `ZRANGE` | `ZRANGE key-name start stop [WITHSCORES]` | 返回有序集合中排名介于 start 和 stop 之间的成员，指定 WITHSCORES 将同时成员分值 |


有序集合的范围型数据获取命令和范围型数据删除命令，以及并集命令和交集命令

| 命令 | 用例 | 描述 |
| --- | --- | --- |
| `ZREVRANK` | `ZREVRANK key-name member` | 返回有序集合里成员 member 的排名，成员按照分值从大到小排列 |
| `ZREVRANGE` | `ZREVRANGE key-name start stop [WITHSCORES]` | 返回有序集合给定排名范围内的成员，成员按照分值从大到小排序 |
| `ZRANGBYSCORE` | `ZRANGBYSCORE key min max [WITHSCORES] [LIMIT offset count]` | 返回有序集合中，分值介于 min 和 max 之间的所有成员 |
| `ZREVRANGBYSCORE` | `ZREVRANGBYSCORE key max min [WITHSCORES] [LIMIT offset count]` | 获取有序集合中分值介于 min 和 max 之间的所有成员，并按照分值从大到小的顺序来返回它们 |
| `ZREMRANGBYRANK` | `ZREMRANGBYRANK key-name start stop` | 移除有序集合中排名介于 start 和 stop 之间的所有成员 |
| `ZREMRANGEBYSCORE` | `ZREMRANGBYSCORE key-name min max` | 移除有序集合中分值介于 min 和 max 之间的所有成员 |
| `ZINTERSTORE` | `ZINTERSTORE dest-key key-count key [key ...] [WEIGHTS weight] [weight ...] [AGGREGATE SUM | MIN | MAX]` | 对给定的有序集合执行类似于集合的交集运算 |
| `ZUNIONSTORE` | `ZUNIONSTORE dest-key key-count key [key ...] [WEIGHTS weight] [weight ...] [AGGREGATE SUM | MIN | MAX]` | 对给定的有序集合执行类似于集合的并集运算 |