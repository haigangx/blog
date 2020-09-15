# MySQL 基础 

<!-- TOC -->

- [一、数据库概念](#一数据库概念)
- [二、MySQL 基本操作](#二mysql-基本操作)
    - [1. 选择和查看数据库](#1-选择和查看数据库)
        - [1.1 `USE` 选择数据库](#11-use-选择数据库)
        - [1.2 `SHOW` 查看数据库信息](#12-show-查看数据库信息)
    - [2. 检索数据 `SELECT FROM`](#2-检索数据-select-from)
        - [2.1 检索单个列](#21-检索单个列)
        - [2.1 检索用 `,` 隔开的多个列](#21-检索用--隔开的多个列)
        - [2.2 使用 `*` 检索所有列](#22-使用--检索所有列)
        - [2.3 利用 `DISTINCT` 关键字剔除检索出的重复行](#23-利用-distinct-关键字剔除检索出的重复行)
        - [2.4 使用 `LIMIT` 限制检索结果的显示范围](#24-使用-limit-限制检索结果的显示范围)
        - [2.5 检索过程中使用完全限定的名字](#25-检索过程中使用完全限定的名字)
    - [3. 排序检索数据 `ORDER BY` 子句](#3-排序检索数据-order-by-子句)
        - [3.1 使用 `ORDER BY` 子句使 `SELECT` 检索的结果根据某列排序输出](#31-使用-order-by-子句使-select-检索的结果根据某列排序输出)
        - [3.2 使用 `DESC` 关键字指定排序方向](#32-使用-desc-关键字指定排序方向)
    - [4. 过滤数据 `WHERE` 子句](#4-过滤数据-where-子句)
        - [4.1 检索时使用 `WHERE` 子句过滤数据](#41-检索时使用-where-子句过滤数据)
        - [4.2 使用 `BETWEEN` 操作符进行范围值过滤](#42-使用-between-操作符进行范围值过滤)
        - [4.3 使用 `IS NULL` 子句进行空值检查](#43-使用-is-null-子句进行空值检查)
        - [4.4 使用 `AND` 操作符组合 `WHERE` 子句](#44-使用-and-操作符组合-where-子句)
        - [4.5 使用 `OR` 操作符组合 `WHERE` 子句](#45-使用-or-操作符组合-where-子句)
        - [4.6 在 `WHERE` 子句中使用 `IN` 操作符](#46-在-where-子句中使用-in-操作符)
        - [4.7 在 `WHERE` 子句中使用 `NOT` 操作符](#47-在-where-子句中使用-not-操作符)
        - [4.8 `WHERE` 子句中使用通配符 `百分号` 过滤数据](#48-where-子句中使用通配符-百分号-过滤数据)
        - [4.9 `WHERE` 子句中使用通配符 `_` 过滤数据](#49-where-子句中使用通配符-_-过滤数据)
        - [4.10 在 `WHERE` 子句中使用 `REGEXP` 关键字启动正则表达式查询](#410-在-where-子句中使用-regexp-关键字启动正则表达式查询)
        - [4.11 使用正则表达式进行最基本的单个字串匹配](#411-使用正则表达式进行最基本的单个字串匹配)
        - [4.12 使用正则表达式元字符 `.` 进行匹配](#412-使用正则表达式元字符--进行匹配)
        - [4.13 使用正则表达式元字符 `|` 进行 OR 操作匹配多个字串](#413-使用正则表达式元字符--进行-or-操作匹配多个字串)
        - [4.14 使用正则表达式元字符 `[]` 匹配特定几个字符之一](#414-使用正则表达式元字符--匹配特定几个字符之一)
        - [4.15 使用正则表达式元字符 `-` 匹配某个范围内的字符](#415-使用正则表达式元字符---匹配某个范围内的字符)
        - [4.16 正则表达式匹配中使用 `\\` 来转义特殊字符来匹配特殊字符](#416-正则表达式匹配中使用-\\-来转义特殊字符来匹配特殊字符)
        - [4.17 正则表达式匹配中使用重复元字符指定字符匹配次数](#417-正则表达式匹配中使用重复元字符指定字符匹配次数)
        - [4.18 正则表达式中使用定位符指定匹配字符的位置](#418-正则表达式中使用定位符指定匹配字符的位置)
    - [5. 使用函数](#5-使用函数)
        - [5.1 使用 `Concat()` 函数拼接两列](#51-使用-concat-函数拼接两列)
        - [5.2 使用 `Trim()、LTrim()、RTrim()` 去掉数据两侧多余空格](#52-使用-trimltrimrtrim-去掉数据两侧多余空格)
        - [5.4 使用 `Upper()` 函数将文本转换为大写](#54-使用-upper-函数将文本转换为大写)
        - [5.5 使用 `Soundex()` 函数将文本串转换其发音](#55-使用-soundex-函数将文本串转换其发音)
        - [5.6 使用日期和时间处理函数](#56-使用日期和时间处理函数)
        - [5.7 使用 `+、-、*、/` 进行算术运算](#57-使用---进行算术运算)
        - [5.8 使用聚集函数 `AVG()` 计算列的平均值](#58-使用聚集函数-avg-计算列的平均值)
        - [5.9 使用聚集函数 `COUNT()` 计算列的行数](#59-使用聚集函数-count-计算列的行数)
        - [5.10 使用聚集函数 `MAX()` 计算列的最大值](#510-使用聚集函数-max-计算列的最大值)
        - [5.11 使用聚集函数 `MIN()` 计算列的最小值](#511-使用聚集函数-min-计算列的最小值)
        - [5.12 使用聚集函数 `SUM()` 计算列值和](#512-使用聚集函数-sum-计算列值和)
        - [5.13 使用 `DISTINCT` 参数仅聚集不同值](#513-使用-distinct-参数仅聚集不同值)
        - [5.14 组合聚集函数](#514-组合聚集函数)
    - [6. 数据分组 `GROUP BY` 子句和 `HAVING` 子句](#6-数据分组-group-by-子句和-having-子句)
        - [6.1 使用 `GROUP BY` 子句对检索进行分组](#61-使用-group-by-子句对检索进行分组)
        - [6.2 使用 `HAVING` 子句过滤分组](#62-使用-having-子句过滤分组)
        - [6.3 对 `GROUP BY` 的分组进行 `ORDER BY` 排序](#63-对-group-by-的分组进行-order-by-排序)
        - [6.4 `SELECT` 各子句执行顺序](#64-select-各子句执行顺序)
    - [7. 子查询](#7-子查询)
        - [7.1 利用子查询进行过滤](#71-利用子查询进行过滤)
        - [7.2 作为计算字段使用子查询](#72-作为计算字段使用子查询)
    - [8. 联结](#8-联结)
        - [8.1 什么是联结？为什么需要联结？](#81-什么是联结为什么需要联结)
        - [8.1 笛卡尔联结（叉联结）](#81-笛卡尔联结叉联结)
        - [8.2 `INNER JOIN` 等值联结（内部联结）](#82-inner-join-等值联结内部联结)
        - [8.3 `OUTER JOIN` 外部联结](#83-outer-join-外部联结)
    - [9. 组合查询](#9-组合查询)
        - [9.1 使用 `UNION` 连接多条 `SELECT` 语句组合查询](#91-使用-union-连接多条-select-语句组合查询)
        - [9.2 `UNION` 组合查询时使用 `` 包含或取消重复的行](#92-union-组合查询时使用--包含或取消重复的行)
        - [9.3 `UNION` 组合查询时使用 `ORDER BY` 对结果排序](#93-union-组合查询时使用-order-by-对结果排序)
    - [10. 全文本搜索](#10-全文本搜索)
        - [10.1 使用全文本搜索](#101-使用全文本搜索)
        - [10.2 使用查询扩展](#102-使用查询扩展)
        - [10.3 布尔文本搜索](#103-布尔文本搜索)
    - [11. 插入、更新、删除数据](#11-插入更新删除数据)
        - [11.1 使用 `INSERT` 插入一行数据](#111-使用-insert-插入一行数据)
        - [11.2 使用 `INSERT` 插入多行数据](#112-使用-insert-插入多行数据)
        - [11.3 使用 `INSERT` 插入检索出的数据](#113-使用-insert-插入检索出的数据)
        - [11.4 使用 `UPDATE` 更新数据](#114-使用-update-更新数据)
        - [11.5 使用 `DELETE` 删除数据](#115-使用-delete-删除数据)
    - [12. 创建和操纵表](#12-创建和操纵表)
        - [12.1 使用 `CREATE TABLE` 语句创建表](#121-使用-create-table-语句创建表)
        - [12.2 使用 `ALTER TABLE` 更新表结构](#122-使用-alter-table-更新表结构)
        - [12.3 使用 `DROP TABLE` 删除表](#123-使用-drop-table-删除表)
        - [12.4 使用 `RENAME TABLE` 重命名表](#124-使用-rename-table-重命名表)
    - [13. 视图](#13-视图)
        - [13.1 视图使用方法和规则](#131-视图使用方法和规则)
        - [13.2 利用视图简化复杂的联结](#132-利用视图简化复杂的联结)
        - [13.3 利用视图重新格式化检索出的数据](#133-利用视图重新格式化检索出的数据)
        - [13.4 利用视图过滤不想要的数据](#134-利用视图过滤不想要的数据)
        - [13.5 更新视图规则](#135-更新视图规则)
    - [14. 存储过程](#14-存储过程)
        - [14.1. 什么是存储过程？存储过程的使用和优缺点](#141-什么是存储过程存储过程的使用和优缺点)
        - [14.2 使用 `CREATE PROCEDURE` 创建存储过程](#142-使用-create-procedure-创建存储过程)
        - [14.3 使用 `CALL` 执行存储过程](#143-使用-call-执行存储过程)
        - [14.4 使用 `DROP PROCEDURE` 删除存储过程](#144-使用-drop-procedure-删除存储过程)
        - [14.4 存储过程使用参数](#144-存储过程使用参数)
        - [14.5 为存储过程增加其他流程控制语句](#145-为存储过程增加其他流程控制语句)
        - [14.6 检查存储过程](#146-检查存储过程)
    - [15. 游标](#15-游标)
        - [15.1 什么是游标？怎么用游标？](#151-什么是游标怎么用游标)
        - [15.2 使用 `DECLARE cursorname CURSOR` 创建游标](#152-使用-declare-cursorname-cursor-创建游标)
        - [15.3 使用 `OPEN CURSOR`、`CLOSE CURSOR` 打开和关闭游标](#153-使用-open-cursorclose-cursor-打开和关闭游标)
        - [15.4 利用 `FETCH` 语句使用游标数据](#154-利用-fetch-语句使用游标数据)
    - [16. 触发器](#16-触发器)
        - [16.1 什么是触发器？](#161-什么是触发器)
        - [16.2 使用 `CREATE TRIGGER` 语句创建触发器](#162-使用-create-trigger-语句创建触发器)
        - [16.3 使用 `DROP TRIGGER` 语句删除触发器](#163-使用-drop-trigger-语句删除触发器)
        - [16.4 使用 `INSERT` 触发器](#164-使用-insert-触发器)
        - [16.5 使用 `DELETE` 触发器](#165-使用-delete-触发器)
        - [16.6 使用 `UPDATE` 触发器](#166-使用-update-触发器)
    - [17. 事务处理](#17-事务处理)
        - [17.1 什么是事务处理？](#171-什么是事务处理)
        - [17.2 使用 `ROLLBACK` 回退 MySQL 语句](#172-使用-rollback-回退-mysql-语句)
        - [17.3 使用 `COMMIT` 提交事务](#173-使用-commit-提交事务)
        - [17.4 使用保留点](#174-使用保留点)
        - [17.5 更改默认的提交行为](#175-更改默认的提交行为)

<!-- /TOC -->

## 一、数据库概念

## 二、MySQL 基本操作

### 1. 选择和查看数据库

#### 1.1 `USE` 选择数据库

- `USE` 命令用于选择数据库，后续命令将基于选定数据库执行，例：

  ```
  mysql> USE crashcourse;
  Database changed
  ```

#### 1.2 `SHOW` 查看数据库信息

- `SHOW` 命令用来查看数据库信息：

  - `SHOW DATABASES` 返回可用数据库列表，例：

    ```
    mysql> SHOW DATABASES;
    +--------------------+
    | Database           |
    +--------------------+
    | crashcourse        |
    | information_schema |
    | mysql              |
    | performance_schema |
    | sys                |
    +--------------------+
    5 rows in set (0.00 sec)
    ```

  - `SHOW TABLES` 返回当前选定数据库内可用表的列表，例：

    ```
    mysql> SHOW TABLES;
    +-----------------------+
    | Tables_in_crashcourse |
    +-----------------------+
    | customers             |
    | orderitems            |
    | orders                |
    | productnotes          |
    | products              |
    | vendors               |
    +-----------------------+
    6 rows in set (0.00 sec)
    ```

  - `SHOW COLUMNS` 要求给出一个表名，它对表中每个字段返回一行，行中包含字段名、数据类型、是否允许 NULL、键信息以及其他信息，例：

    ```
    mysql> SHOW COLUMNS FROM customers;
    +--------------+-----------+------+-----+---------+----------------+
    | Field        | Type      | Null | Key | Default | Extra          |
    +--------------+-----------+------+-----+---------+----------------+
    | cust_id      | int       | NO   | PRI | NULL    | auto_increment |
    | cust_name    | char(50)  | NO   |     | NULL    |                |
    | cust_address | char(50)  | YES  |     | NULL    |                |
    | cust_city    | char(50)  | YES  |     | NULL    |                |
    | cust_state   | char(5)   | YES  |     | NULL    |                |
    | cust_zip     | char(10)  | YES  |     | NULL    |                |
    | cust_country | char(50)  | YES  |     | NULL    |                |
    | cust_contact | char(50)  | YES  |     | NULL    |                |
    | cust_email   | char(255) | YES  |     | NULL    |                |
    +--------------+-----------+------+-----+---------+----------------+
    9 rows in set (0.00 sec)
    ```

    MySQL 支持 `DESCRIBE` 作为 `SHOW COLUMNS FROM` 的一种快捷方式，因此，上面命令等同于 `DESCRIBE customers;`

  - `SHOW STATUS` 用于显示广泛的服务器状态信息
  - `SHOW CREATE DATABASE <database>` 和 `SHOW CREATE TABLE <table>` 分别用来显示创建特定数据库或表的 MySQL 语句
  - `SHOW GRANTS` 用来显示授予用户（所有用户或特定用户）的安全权限
  - `SHOW ERRORS` 和 `SHOW WARNINGS` 用来显示服务器错误或警告消息

  - 可以在 MySQL 命令行中执行命令 `HELP SHOW` 查看允许使用的 SHOW 语句

### 2. 检索数据 `SELECT FROM`

#### 2.1 检索单个列

可利用 `SELECT FROM` 语句从表中检索指定列：

```
mysql> SELECT prod_name FROM products;
+----------------+
| prod_name      |
+----------------+
| .5 ton anvil   |
| 1 ton anvil    |
| 2 ton anvil    |
| Detonator      |
| Bird seed      |
| Carrots        |
| Fuses          |
| JetPack 1000   |
| JetPack 2000   |
| Oil can        |
| Safe           |
| Sling          |
| TNT (1 stick)  |
| TNT (5 sticks) |
+----------------+
14 rows in set (0.00 sec)
```

需要注意的问题：

- `SELECT` **返回数据的顺序无任何意义**，这里的顺序和存储的数据结构有关，编程中不应该依赖此处的顺序

#### 2.1 检索用 `,` 隔开的多个列

在 `SELECT` 关键字后给出多个列名，列名之间以逗号分隔，用于在一个表中检索出多个列

```
mysql> SELECT prod_id, prod_name, prod_price FROM products;
+---------+----------------+------------+
| prod_id | prod_name      | prod_price |
+---------+----------------+------------+
| ANV01   | .5 ton anvil   |       5.99 |
| ANV02   | 1 ton anvil    |       9.99 |
| ANV03   | 2 ton anvil    |      14.99 |
| DTNTR   | Detonator      |      13.00 |
| FB      | Bird seed      |      10.00 |
| FC      | Carrots        |       2.50 |
| FU1     | Fuses          |       3.42 |
| JP1000  | JetPack 1000   |      35.00 |
| JP2000  | JetPack 2000   |      55.00 |
| OL1     | Oil can        |       8.99 |
| SAFE    | Safe           |      50.00 |
| SLING   | Sling          |       4.49 |
| TNT1    | TNT (1 stick)  |       2.50 |
| TNT2    | TNT (5 sticks) |      10.00 |
+---------+----------------+------------+
14 rows in set (0.00 sec)
```

注意：

- 多个列名以逗号分隔，且 **最后一个列名后不需要逗号**，否则会出错

#### 2.2 使用 `*` 检索所有列

通过通配符 `*` 可以表中检索所有的列：

```
mysql> SELECT * FROM orders;
+-----------+---------------------+---------+
| order_num | order_date          | cust_id |
+-----------+---------------------+---------+
|     20005 | 2005-09-01 00:00:00 |   10001 |
|     20006 | 2005-09-12 00:00:00 |   10003 |
|     20007 | 2005-09-30 00:00:00 |   10004 |
|     20008 | 2005-10-03 00:00:00 |   10005 |
|     20009 | 2005-10-08 00:00:00 |   10001 |
+-----------+---------------------+---------+
5 rows in set (0.00 sec)
```

注意：

- 应谨慎使用通配符 `*`，检索不需要的列通常会降低检索和应用程序的性能

#### 2.3 利用 `DISTINCT` 关键字剔除检索出的重复行

`SELECT` 语句中可以利用 `DISTINCT` 剔除检索出的重复行：

```
mysql> SELECT DISTINCT vend_id FROM products;
+---------+
| vend_id |
+---------+
|    1001 |
|    1002 |
|    1003 |
|    1005 |
+---------+
4 rows in set (0.00 sec)
```

注意：

- **不能部分使用 DISTINCT**，DISTINCT 关键字应用于所有列而不仅是前置它的列，如果给出 `SELECT DISTINCT vend_id, prod_price`，则除非指定的两个列都不同，否则所有行都将被检索出来

#### 2.4 使用 `LIMIT` 限制检索结果的显示范围

`SELECT` 语句返回所有匹配的行，它们可能是指定表中的每个行，为了返回第一行或前几行，可使用 `LIMIT` 子句：

```
mysql> SELECT prod_name FROM products LIMIT 5;
+--------------+
| prod_name    |
+--------------+
| .5 ton anvil |
| 1 ton anvil  |
| 2 ton anvil  |
| Detonator    |
| Bird seed    |
+--------------+
5 rows in set (0.00 sec)
```

注意：

- `LIMIT` 带一个值时表示总是从第一行开始，给出的数为返回的行数，如：`LIMIT 5` 指示 MySQL 返回不多于 5 行
- `LIMIT` 也可带两个值，第一个数为开始位置，第二个数为要检索的行数，如：`LIMIT 5,5` 指示 MySQL 返回从行 5 开始的 5 行
- **检索出的第一行为行 0 而不是 行 1**，因此，`LIMIT 1,1` 将检索出第二行而不是第一行
- 当 MySQL 可返回的行数小于 `LIMIT` 中指定的行数时，**MySQL将只返回它能返回的那么多行**
- MySQL 5 支持 LIMIT 的另一种替代语法：`LIMIT 4 OFFSET 3` 意为从行 3 开始取 4 行，同 `LIMIT 3,4`

#### 2.5 检索过程中使用完全限定的名字

可以使用 `表名.列名` 或 `数据库名.表名` 的完全限定名字的方式引用列或表：

```
mysql> SELECT products.prod_name FROM crashcourse.products;
```

### 3. 排序检索数据 `ORDER BY` 子句

#### 3.1 使用 `ORDER BY` 子句使 `SELECT` 检索的结果根据某列排序输出

```
mysql> SELECT prod_name FROM products ORDER BY prod_name;
+----------------+
| prod_name      |
+----------------+
| .5 ton anvil   |
| 1 ton anvil    |
| 2 ton anvil    |
| Bird seed      |
| Carrots        |
| Detonator      |
| Fuses          |
| JetPack 1000   |
| JetPack 2000   |
| Oil can        |
| Safe           |
| Sling          |
| TNT (1 stick)  |
| TNT (5 sticks) |
+----------------+
14 rows in set (0.00 sec)
```

- **也可以使用非检索的列排序数据**，这是完全合法的
- 可以使用逗号分隔多个列名，使结果按多个列排序，如：`ORDER BY prod_price, prod_name`，此时仅在多个行具有相同的 prod_price 值时才对产品按 prod_name 进行排序，如果 prod_price 列中所有的值都是唯一的，则不会按 prod_name 排序

#### 3.2 使用 `DESC` 关键字指定排序方向

默认情况下，`ORDER BY` 子句按照升序排序，可以利用关键字 `DESC` 进行降序排序：

```
mysql> SELECT prod_id, prod_price, prod_name
    -> FROM products
    -> ORDER BY prod_price DESC;
+---------+------------+----------------+
| prod_id | prod_price | prod_name      |
+---------+------------+----------------+
| JP2000  |      55.00 | JetPack 2000   |
| SAFE    |      50.00 | Safe           |
| JP1000  |      35.00 | JetPack 1000   |
| ANV03   |      14.99 | 2 ton anvil    |
| DTNTR   |      13.00 | Detonator      |
| FB      |      10.00 | Bird seed      |
| TNT2    |      10.00 | TNT (5 sticks) |
| ANV02   |       9.99 | 1 ton anvil    |
| OL1     |       8.99 | Oil can        |
| ANV01   |       5.99 | .5 ton anvil   |
| SLING   |       4.49 | Sling          |
| FU1     |       3.42 | Fuses          |
| FC      |       2.50 | Carrots        |
| TNT1    |       2.50 | TNT (1 stick)  |
+---------+------------+----------------+
14 rows in set (0.01 sec)
```

- **`DESC` 关键字只应用到直接位于其前面的列名**，若想在多个列上都进行降序排序，必须对每个列指定 `DESC` 关键字，例如：`ORDER BY prod_price DESC, prod_name` 中，只对 prod_price 列指定 DESC，对 prod_name 列不指定，因此，prod_price 列以降序排序，而 prod_name 列仍然按标准升序排序
- 与 `DESC` 相对应的是 `ASC` 升序排序，但是因为一般默认排序就是升序，所以显式指定 `ASC` 并无多大用处
- 在 MySQL 中，进行字典排序时，默认情况下，A 被视为与 a 相同；但是可以通过更改数据库属性改变该设置

### 4. 过滤数据 `WHERE` 子句

`WHERE` 子句可用条件操作符：

| 操作符 | 说明 |
| --- | --- |
| = | 等于 |
| <> | 不等于 |
| != | 不等于 |
| < | 小于 |
| <= | 小于等于 |
| > | 大于 |
| >= | 大于等于 |
| BETWEEN | 在指定的两值之间 |

#### 4.1 检索时使用 `WHERE` 子句过滤数据

- 相等检测：

  ```
  mysql> SELECT prod_name, prod_price 
      -> FROM products
      -> WHERE prod_name = 'fuses';
  +-----------+------------+
  | prod_name | prod_price |
  +-----------+------------+
  | Fuses     |       3.42 |
  +-----------+------------+
  1 row in set (0.00 sec)
  ```

- 列出价格小于 10 美元的产品：

  ```
  mysql> SELECT prod_name, prod_price
      -> FROM products
      -> WHERE prod_price < 10;
  +---------------+------------+
  | prod_name     | prod_price |
  +---------------+------------+
  | .5 ton anvil  |       5.99 |
  | 1 ton anvil   |       9.99 |
  | Carrots       |       2.50 |
  | Fuses         |       3.42 |
  | Oil can       |       8.99 |
  | Sling         |       4.49 |
  | TNT (1 stick) |       2.50 |
  +---------------+------------+
  7 rows in set (0.00 sec)
  ```

- 不匹配检测：

  ```
  mysql> SELECT vend_id, prod_name
      -> FROM products
      -> WHERE vend_id <> 1003;
  +---------+--------------+
  | vend_id | prod_name    |
  +---------+--------------+
  |    1001 | .5 ton anvil |
  |    1001 | 1 ton anvil  |
  |    1001 | 2 ton anvil  |
  |    1002 | Fuses        |
  |    1002 | Oil can      |
  |    1005 | JetPack 1000 |
  |    1005 | JetPack 2000 |
  +---------+--------------+
  7 rows in set (0.00 sec)
  ```

  - 不匹配检测也可以使用 `!=`，两者效果相同

#### 4.2 使用 `BETWEEN` 操作符进行范围值过滤

```
mysql> SELECT prod_name, prod_price
    -> FROM products
    -> WHERE prod_price BETWEEN 5 AND 10;
+----------------+------------+
| prod_name      | prod_price |
+----------------+------------+
| .5 ton anvil   |       5.99 |
| 1 ton anvil    |       9.99 |
| Bird seed      |      10.00 |
| Oil can        |       8.99 |
| TNT (5 sticks) |      10.00 |
+----------------+------------+
5 rows in set (0.00 sec)
```

- 使用 `BETWEEN` 时，必须指定两个值：范围的最低值和最高值，这两个值必须用 `AND` 连接，BETWEEN 匹配范围中所有的值，包括指定的开始值和结束值

#### 4.3 使用 `IS NULL` 子句进行空值检查

**空值 NULL** 指一个列不包含任何值，这与字段包含 0、空字符串或仅仅包含空格不同

`SELECT` 语句的 `IS NULL` 子句可用来检测具有 NULL 值得列

```
mysql> SELECT prod_name
    -> FROM products
    -> WHERE prod_price IS NULL;
Empty set (0.00 sec)
```

注意：

- 在过滤不具有特定值的行时，仍然不会返回具有 NULL 值的行，因为未知具有特殊的含义，数据库不知道它们是否匹配，因此在过滤数据时，要注意这点

#### 4.4 使用 `AND` 操作符组合 `WHERE` 子句

`AND` 操作符用在 `WHERE` 子句中，用来指示检索满足所有给定条件的行

```
mysql> SELECT prod_id, prod_price, prod_name
    -> FROM products
    -> WHERE vend_id = 1003 AND prod_price <= 10;
+---------+------------+----------------+
| prod_id | prod_price | prod_name      |
+---------+------------+----------------+
| FB      |      10.00 | Bird seed      |
| FC      |       2.50 | Carrots        |
| SLING   |       4.49 | Sling          |
| TNT1    |       2.50 | TNT (1 stick)  |
| TNT2    |      10.00 | TNT (5 sticks) |
+---------+------------+----------------+
5 rows in set (0.00 sec)
```

#### 4.5 使用 `OR` 操作符组合 `WHERE` 子句

`OR` 操作符指示 MySQL 检索匹配任一条件的行

```
mysql> SELECT prod_name, prod_price
    -> FROM products
    -> WHERE vend_id = 1002 OR vend_id = 1003;
+----------------+------------+
| prod_name      | prod_price |
+----------------+------------+
| Fuses          |       3.42 |
| Oil can        |       8.99 |
| Detonator      |      13.00 |
| Bird seed      |      10.00 |
| Carrots        |       2.50 |
| Safe           |      50.00 |
| Sling          |       4.49 |
| TNT (1 stick)  |       2.50 |
| TNT (5 sticks) |      10.00 |
+----------------+------------+
9 rows in set (0.00 sec)
```

- `WHERE` 中可包含任意数目的 `AND` 和 `OR` 操作符，允许两者结合以进行复杂和高级的过滤
- 在 `AND` 和 `OR` 组合使用过程中，`AND` 在计算次序中优先级更高，也可以使用括号来改变优先级顺序，如
  ```
  mysql> SELECT prod_name, prod_price
      -> FROM products
      -> WHERE (vend_id = 1002 OR vend_id = 1003) AND prod_price >= 10;
  ```
  建议在任何时候使用具有 `AND` 和 `OR` 操作符的 `WHERE` 子句时，都应该使用括号明确计算顺序，这样更加清晰，也可以消除歧义

#### 4.6 在 `WHERE` 子句中使用 `IN` 操作符

`IN` 操作符用来指定条件范围，范围中的每个条件都可以进行匹配，`IN` 取合法值的由逗号分隔的清单

```
mysql> SELECT prod_name, prod_price
    -> FROM products
    -> WHERE vend_id IN (1002,1003)
    -> ORDER BY prod_name;
+----------------+------------+
| prod_name      | prod_price |
+----------------+------------+
| Bird seed      |      10.00 |
| Carrots        |       2.50 |
| Detonator      |      13.00 |
| Fuses          |       3.42 |
| Oil can        |       8.99 |
| Safe           |      50.00 |
| Sling          |       4.49 |
| TNT (1 stick)  |       2.50 |
| TNT (5 sticks) |      10.00 |
+----------------+------------+
9 rows in set (0.00 sec)
```

- 其实，`IN` 完成了和 `OR` 相同的功能，使用 `IN` 替代 `OR` 具有以下优点：

  1. 在使用长的合法选项清单时，`IN` 操作符的语法更清楚且更直观
  2. 在使用 `IN` 时，计算的次序更容易管理
  3. `IN` 操作符一般比 `OR` 操作符清单执行更快
  4. `IN` 最大优点是可以包含其他 `SELECT` 语句，使得能够更动态地建立 `WHERE` 子句

#### 4.7 在 `WHERE` 子句中使用 `NOT` 操作符

`NOT` 操作符用于否定它之后所跟的任何条件：

```
mysql> SELECT prod_name, prod_price
    -> FROM products
    -> WHERE vend_id NOT IN (1002,1003)
    -> ORDER BY prod_name;
+--------------+------------+
| prod_name    | prod_price |
+--------------+------------+
| .5 ton anvil |       5.99 |
| 1 ton anvil  |       9.99 |
| 2 ton anvil  |      14.99 |
| JetPack 1000 |      35.00 |
| JetPack 2000 |      55.00 |
+--------------+------------+
5 rows in set (0.00 sec)
```

- MySQL 中支持使用 `NOT` 对 `IN`、`BETWEEN` 和 `EXISTS` 子句取反

#### 4.8 `WHERE` 子句中使用通配符 `百分号` 过滤数据

在 `WHERE` 子句中使用通配符必须使用 `LIKE` 操作符，`LIKE` 指示 MySQL 后跟的搜索模式利用通配符匹配而不是直接相等匹配

通配符 `%` 表示任何字符出现 0 次或多次

```
mysql> SELECT prod_id, prod_name
    -> FROM products
    -> WHERE prod_name LIKE 'jet%';
+---------+--------------+
| prod_id | prod_name    |
+---------+--------------+
| JP1000  | JetPack 1000 |
| JP2000  | JetPack 2000 |
+---------+--------------+
2 rows in set (0.00 sec)
```

#### 4.9 `WHERE` 子句中使用通配符 `_` 过滤数据

通配符 `_` 只能匹配单个字符而不是多个字符

```
mysql> SELECT prod_id, prod_name
    -> FROM products
    -> WHERE prod_name LIKE '_ ton anvil';
+---------+-------------+
| prod_id | prod_name   |
+---------+-------------+
| ANV02   | 1 ton anvil |
| ANV03   | 2 ton anvil |
+---------+-------------+
2 rows in set (0.00 sec)
```

注意：

- MySQL 中搜索 **默认不区分大小写**，但可以配置成区分大小写
- 使用通配符时要 **注意首尾空格**，这可能会干扰到通配符的匹配，可以使用函数去掉首尾空格
- 使用通配符不能匹配 `NULL` 值
- 通配符很有用，但是通配符搜索的处理一般要比不用通配符搜索花的时间更长，因此：

  1. 不要过度使用通配符，应尽量使用其他操作符
  2. 当确实要使用通配符时，尽量不要将通配符用在搜索模式的开始处，用在开始搜索起来是最慢的
  3. 注意正确放置通配符的位置

#### 4.10 在 `WHERE` 子句中使用 `REGEXP` 关键字启动正则表达式查询

`REGEXP` 关键字告诉 MySQL 后跟的东西作为正则表达式处理

| 模式 | 说明 |
| --- | --- |
| `.` | 匹配任意一个字符 |
| `|` | or 操作，匹配其中之一 |
| `[]` | 匹配 [] 括号内字符的其中之一 |
| `[1-3]` | 匹配范围，使用 - 定义一个范围 |
| `\\\` | `\\` + 特殊字符匹配特殊字符 |
| `[:alnum:]` | 任意字母和数字（同 `[a-zA-Z0-9]`）|
| `[:alpha:]` | 任意字符（同 `[a-zA-Z]`）|
| `[:blank:]` | 空格和制表（同 `[\\t]`）
| `[:cntrl:]` | ASCII 控制字符（ASCII 0 到 31 和 127） |
| `[:digit:]` | 任意数字（同 `[0-9]`）
| `[:graph:]` | 与 `[:print:]` 相同，但不包括空格 |
| `[:lower:]` | 任意小写字母（同 `[a-z]`）
| `[:print:]` | 任意可打印字符 |
| `[:punct:]` | 既不在 `[:alnum:]` 又不在 `[:cntrl:]` 中的任意字符 |
| `[:space:]` | 包括空格在内的任意空白字符（同 `[\\f\\n\\r\\t\\v]`） |
| `[:upper:]` | 任意大写字母（同 `[A-Z]`） |
| `[:xdigit:]` | 任意十六进制数字（同 `[a-fA-F0-9]`） |
| `*` | 0 个或多个匹配 |
| `+` | 1 个或多个匹配（等于 `{1,}`） |
| `?` | 0 个或 1 个匹配（等于 `{0,1}`） |
| `{n}` | 指定数目的匹配 |
| `{n,}` | 不少于指定数目的匹配 |
| `{n,m}` | 匹配数目的范围（m 不超过 255） |



- MySQL 中的正则表达式匹配不区分大小写，为区分大小写，可使用 `BINARY` 关键字

#### 4.11 使用正则表达式进行最基本的单个字串匹配

```
mysql> SELECT prod_name
    -> FROM products
    -> WHERE prod_name REGEXP '1000'
    -> ORDER BY prod_name;
+--------------+
| prod_name    |
+--------------+
| JetPack 1000 |
+--------------+
1 row in set (0.00 sec)
```

- 正则表达式和通配符区别：

  - `LIKE` 匹配整个列，如果被匹配的文本在列值中出现，LIKE 将不会找到它，相应的行也不会返回
  - `REGEXP` 在列值内进行匹配，如果被匹配的文本在列值中出现，REGEXP 将会找到它，相应的行被返回，REGEXP 也可以使用定位符 ^ 和 $ 匹配整个列值

  ```
  mysql> SELECT prod_name 
      -> FROM products
      -> WHERE prod_name LIKE '1000'
      -> ORDER BY prod_name;
  Empty set (0.00 sec)

  mysql> SELECT prod_name
      -> FROM products
      -> WHERE prod_name REGEXP '1000'
      -> ORDER BY prod_name;
  +--------------+
  | prod_name    |
  +--------------+
  | JetPack 1000 |
  +--------------+
  1 row in set (0.01 sec)
  ```

#### 4.12 使用正则表达式元字符 `.` 进行匹配

`.` 匹配任意一个字符

```
mysql> SELECT prod_name
    -> FROM products
    -> WHERE prod_name REGEXP '.000'
    -> ORDER BY prod_name;
+--------------+
| prod_name    |
+--------------+
| JetPack 1000 |
| JetPack 2000 |
+--------------+
2 rows in set (0.00 sec)
```

#### 4.13 使用正则表达式元字符 `|` 进行 OR 操作匹配多个字串

`|` 匹配两个串其中之一

```
mysql> SELECT prod_name
    -> FROM products
    -> WHERE prod_name REGEXP '1000|2000'
    -> ORDER BY prod_name;
+--------------+
| prod_name    |
+--------------+
| JetPack 1000 |
| JetPack 2000 |
+--------------+
2 rows in set (0.00 sec)
```

- 可以使用两个以上的 `|`，如 `1000|2000|3000` 将匹配 1000 或 2000 或 3000

#### 4.14 使用正则表达式元字符 `[]` 匹配特定几个字符之一

`[]` 内括起来的字符表示匹配其中任何之一

```
mysql> SELECT prod_name
    -> FROM products
    -> WHERE prod_name REGEXP '[123] Ton'
    -> ORDER BY prod_name;
+-------------+
| prod_name   |
+-------------+
| 1 ton anvil |
| 2 ton anvil |
+-------------+
2 rows in set (0.00 sec)
```

- 使用 `[^]` 在匹配时排除括号内的字符，如：`[^123]` 匹配除 1、2、3 字符外的任何东西

#### 4.15 使用正则表达式元字符 `-` 匹配某个范围内的字符

`-` 定义一个匹配范围，如 `[1-4]`、`[a-z]` 等

```
mysql> SELECT prod_name 
    -> FROM products
    -> WHERE prod_name REGEXP '[1-5] Ton'
    -> ORDER BY prod_name;
+--------------+
| prod_name    |
+--------------+
| .5 ton anvil |
| 1 ton anvil  |
| 2 ton anvil  |
+--------------+
3 rows in set (0.00 sec)
```

#### 4.16 正则表达式匹配中使用 `\\` 来转义特殊字符来匹配特殊字符

匹配特殊字符时，必须使用 `\\` 为前导，如：`\\-` 表示查找 -，`\\.` 表示查找 .

`\\` 也可以用来进行字符转义：

| 元字符 | 说明 |
| --- | --- |
| `\\f` | 换页 |
| `\\n` | 换行 |
| `\\r` | 回车 |
| `\\t` | 制表 |
| `\\v` | 纵向制表 |

```
mysql> SELECT vend_name 
    -> FROM vendors
    -> WHERE vend_name REGEXP '\\.'
    -> ORDER BY vend_name;
+--------------+
| vend_name    |
+--------------+
| Furball Inc. |
+--------------+
1 row in set (0.00 sec)
```

- 匹配反斜杠 `\` 本身时，需要使用 `\\\`
- MySQL 要求两个反斜杠是因为：MySQL 自己解释一个，正则表达式解释另一个

#### 4.17 正则表达式匹配中使用重复元字符指定字符匹配次数

重复元字符有：

| 元字符 | 说明 |
| --- | --- |
| `*` | 0 个或多个匹配 |
| `+` | 1 个或多个匹配（等于 `{1,}`） |
| `?` | 0 个或 1 个匹配（等于 `{0,1}`） |
| `{n}` | 指定数目的匹配 |
| `{n,}` | 不少于指定数目的匹配 |
| `{n,m}` | 匹配数目的范围（m 不超过 255） |


- 使用 `?`

  ```
  mysql> SELECT prod_name
      -> FROM products
      -> WHERE prod_name REGEXP '\\([0-9] sticks?\\)'
      -> ORDER BY prod_name;
  +----------------+
  | prod_name      |
  +----------------+
  | TNT (1 stick)  |
  | TNT (5 sticks) |
  +----------------+
  2 rows in set (0.00 sec)
  ```

  - 使用 `stick?` 匹配 stick 和 sticks

- 使用 `{n}`

  ```
  mysql> SELECT prod_name
      -> FROM products
      -> WHERE prod_name REGEXP '[[:digit:]]{4}'
      -> ORDER BY prod_name;
  +--------------+
  | prod_name    |
  +--------------+
  | JetPack 1000 |
  | JetPack 2000 |
  +--------------+
  2 rows in set (0.00 sec)
  ```

  - `[[:digit:]]{4}` 用于匹配连在一起的 4 个数字

#### 4.18 正则表达式中使用定位符指定匹配字符的位置

正则表达式中使用定位符可以匹配到特定位置的文本

定位符有：
cici
| 元字符 | 说明 |
| --- | --- |
| `^` | 文本的开始 |
| `$` | 文本的结尾 |
| `[[:<:]]` | 词的开始 |
| `[[:>:]]` | 词的结尾 |

下面用 `^[0-9\\.]` 匹配以数字或小数点开头的串

```
mysql> SELECT prod_name
    -> FROM products
    -> WHERE prod_name REGEXP '^[0-9\\.]'
    -> ORDER BY prod_name;
+--------------+
| prod_name    |
+--------------+
| .5 ton anvil |
| 1 ton anvil  |
| 2 ton anvil  |
+--------------+
3 rows in set (0.00 sec)
```

- `^` 有两种用途：在集合 `[]` 中，用于否定该集合，否则用于指串的开始处
- 通过用 `^` 开始每个表达式，以 `$` 结尾每个表达式，可以使 REGEXP 的作用与 LIKE 一样
- 可以在不使用数据库表的情况下用 `SELECT` 来测试正则表达式，REGEXP 检查总是返回 0（没有匹配）或 1（匹配），如：
  ```
  SELECT 'hello' REGEXP '[0-9]';
  ```
  该测试显然将返回 0

### 5. 使用函数

SQL 支持利用函数来处理数据，函数主要有以下四种类型：

1. 用户处理文本串的文本函数
2. 用于在数值数据上进行算术操作的数值函数
3. 用于处理日期和时间值的日期和时间函数
4. 返回 DBMS 正使用的特殊信息的系统函数

常用的文本处理函数有：

| 函数 | 说明 |
| --- | --- |
| Left() | 返回串左边的字符 |
| Length() | 返回串的长度 |
| Locate() | 找出串的一个字串 |
| Lower() | 将串转换为小写 |
| LTrim() | 去掉串左边的空格 |
| RTrim() | 去掉串右边的空格 |
| Trim() | 去掉串左右两边的空格 |
| Right() | 返回串右边的字符 |
| Soundex() | 返回串的 SOUNDEX 值 |
| SubString() | 返回子串的字符 |
| Upper() | 将串转换为大写 |
| Concat() | 拼接指定的多个串 |

常用的日期和时间函数：

| 函数 | 说明 |
| --- | --- |
| AddData() | 增加一个日期（天、周等） |
| AddTime() | 增加一个时间（时、分等） |
| CurDate() | 返回当前日期 |
| CurTime() | 返回当前时间 |
| Date() | 返回日期时间的日期部分 |
| DateDiff() | 计算两个日期之差 |
| Date_Add() | 高度灵活的日期运算函数 |
| Date_Format() | 返回一个格式化的日期或时间串 |
| Day() | 返回一个日期的天数部分 |
| DayOfWeek() | 对于一个日期，返回对应的星期几 |
| Hour() | 返回一个时间的小时部分 |
| Minute() | 返回一个时间的分钟部分 |
| Month() | 返回一个日期的月份部分 |
| Now() | 返回当前日期和时间 |
| Second() | 返回一个时间的秒部分 |
| Time() | 返回一个日期时间的时间部分 |
| Year() | 返回一个日期的年份部分 |

常用的算术操作符或数值函数有：

| 操作符/函数 | 说明 |
| --- | --- |
| + | 加 |
| - | 减 |
| * | 乘 |
| / | 除 |
| Abs() | 返回一个数的绝对值 |
| Cos() | 返回一个角度的余弦 |
| Exp() | 返回一个数的指数值 |
| Mod() | 返回除操作的余数 |
| Pi() | 返回圆周率 |
| Rand() | 返回一个随机数 |
| Sin() | 返回一个角度的正弦 |
| Sqrt() | 返回一个数的平方根 |
| Tan() | 返回一个角度的正切 |
| AVG() | 返回某列的平均值 |
| COUNT() | 返回某列的行数 |
| MAX() | 返回某列的最大值 |
| MIN() | 返回某列的最小值 |
| SUM() | 返回某列值之和 |

#### 5.1 使用 `Concat()` 函数拼接两列

`Concat()` 将指定的多个串连接起来形成一个较长的串

```
mysql> SELECT Concat(vend_name, ' (', vend_country, ' )')
    -> FROM vendors
    -> ORDER BY vend_name;
+---------------------------------------------+
| Concat(vend_name, ' (', vend_country, ' )') |
+---------------------------------------------+
| ACME (USA )                                 |
| Anvils R Us (USA )                          |
| Furball Inc. (USA )                         |
| Jet Set (England )                          |
| Jouets Et Ours (France )                    |
| LT Supplies (USA )                          |
+---------------------------------------------+
6 rows in set (0.00 sec)
```

#### 5.2 使用 `Trim()、LTrim()、RTrim()` 去掉数据两侧多余空格

`Trim()` 函数去掉值左右两边的空格；`LTrim()` 函数去掉值左边的空格；`RTrim()` 函数去掉值右边的空格

```
mysql> SELECT Concat(RTrim(vend_name), ' (', RTrim(vend_country), ' )')
    -> FROM vendors
    -> ORDER BY vend_name;
+-----------------------------------------------------------+
| Concat(RTrim(vend_name), ' (', RTrim(vend_country), ' )') |
+-----------------------------------------------------------+
| ACME (USA )                                               |
| Anvils R Us (USA )                                        |
| Furball Inc. (USA )                                       |
| Jet Set (England )                                        |
| Jouets Et Ours (France )                                  |
| LT Supplies (USA )                                        |
+-----------------------------------------------------------+
6 rows in set (0.00 sec)
```

可以用 `AS` 为列名指定别名，以为上面输出的列指定别名 vend_title 为例：

```
mysql> SELECT Concat(RTrim(vend_name), ' (', RTrim(vend_country), ' )') AS vend_title 
    -> FROM vendors
    -> ORDER BY vend_name;
+--------------------------+
| vend_title               |
+--------------------------+
| ACME (USA )              |
| Anvils R Us (USA )       |
| Furball Inc. (USA )      |
| Jet Set (England )       |
| Jouets Et Ours (France ) |
| LT Supplies (USA )       |
+--------------------------+
6 rows in set (0.00 sec)
```

- `SELECT` 提供了测试和试验函数与计算的途径：如 `SELECT 3*2` 将返回 6，`SELECT Trim(' abc')` 将返回 abc，`SELECT Now()` 利用 Now() 返回当前日期和时间

#### 5.4 使用 `Upper()` 函数将文本转换为大写

`Upper()` 函数将文本转换为大写

```
mysql> SELECT vend_name, Upper(vend_name) AS vend_name_upcase
    -> FROM vendors
    -> ORDER BY vend_name;
+----------------+------------------+
| vend_name      | vend_name_upcase |
+----------------+------------------+
| ACME           | ACME             |
| Anvils R Us    | ANVILS R US      |
| Furball Inc.   | FURBALL INC.     |
| Jet Set        | JET SET          |
| Jouets Et Ours | JOUETS ET OURS   |
| LT Supplies    | LT SUPPLIES      |
+----------------+------------------+
6 rows in set (0.00 sec)
```

#### 5.5 使用 `Soundex()` 函数将文本串转换其发音

`Soundex()` 函数可以将任何文本串转换为描述其语音表示的字母数字模式

下面的例子使用 `Soundex()` 函数进行搜索，它将匹配所有发音类似于 Y.Lie 的联系名

```
mysql> SELECT cust_name, cust_contact
    -> FROM customers
    -> WHERE Soundex(cust_contact) = Soundex('Y Lie');
+-------------+--------------+
| cust_name   | cust_contact |
+-------------+--------------+
| Coyote Inc. | Y Lee        |
+-------------+--------------+
1 row in set (0.00 sec)
```

#### 5.6 使用日期和时间处理函数

- 无论你什么时候指定一个日期，不管是插入或更新表值还是用 `WHERE` 子句进行过滤，日期必须为格式 `yyyy-mm-dd`，并且应该总是使用 4 位数字的年份

  ```
  mysql> SELECT cust_id, order_num
      -> FROM orders
      -> WHERE order_date = '2005-09-01';
  +---------+-----------+
  | cust_id | order_num |
  +---------+-----------+
  |   10001 |     20005 |
  +---------+-----------+
  1 row in set (0.00 sec)
  ```

- 有时候，存储的日期值可能为 `2005-09-01 11:30:05`，但是我们只想指定年月日的记录，这时可以使用 `Date()` 仅提取列的日期部分：

  ```
  mysql> SELECT cust_id, order_num
      -> FROM orders
      -> WHERE Date(order_date) = '2005-09-01';
  +---------+-----------+
  | cust_id | order_num |
  +---------+-----------+
  |   10001 |     20005 |
  +---------+-----------+
  1 row in set (0.00 sec)
  ```

  记住：如果你想要的仅是日期，那么请总是使用 `Date()`

- 可以使用 `BETWEEN` 指定要匹配的日期范围

  ```
  mysql> SELECT cust_id, order_num
      -> FROM orders
      -> WHERE Date(order_date) BETWEEN '2005-09-01' AND '2005-09-30';
  +---------+-----------+
  | cust_id | order_num |
  +---------+-----------+
  |   10001 |     20005 |
  |   10003 |     20006 |
  |   10004 |     20007 |
  +---------+-----------+
  3 rows in set (0.00 sec)
  ```


#### 5.7 使用 `+、-、*、/` 进行算术运算

可以对检索出的数据进行 `+-*/` 的算术运算：

```
mysql> SELECT prod_id,
    ->        quantity,
    ->        item_price,
    ->        quantity*item_price AS expanded_price
    -> FROM orderitems
    -> WHERE order_num = 20005;
+---------+----------+------------+----------------+
| prod_id | quantity | item_price | expanded_price |
+---------+----------+------------+----------------+
| ANV01   |       10 |       5.99 |          59.90 |
| ANV02   |        3 |       9.99 |          29.97 |
| TNT2    |        5 |      10.00 |          50.00 |
| FB      |        1 |      10.00 |          10.00 |
+---------+----------+------------+----------------+
4 rows in set (0.00 sec)
```

- 可以用圆括号改变优先顺序

#### 5.8 使用聚集函数 `AVG()` 计算列的平均值

**聚集函数** 指运行在行组上，计算和返回单个值的函数

`AVG()` 通过对表中行数计数并计算特定列值之和，求得该列的平均值

```
mysql> SELECT AVG(prod_price) AS avg_price
    -> FROM products;
+-----------+
| avg_price |
+-----------+
| 16.133571 |
+-----------+
1 row in set (0.00 sec)
```

#### 5.9 使用聚集函数 `COUNT()` 计算列的行数

利用 `COUNT()` 函数可以确定表中行的数目或符合特定条件的行的数目

- `COUNT(*)` 对所有行计数，包括 NULL 值的行

  ```
  mysql> SELECT COUNT(*) AS num_cust
      -> FROM customers;
  +----------+
  | num_cust |
  +----------+
  |        5 |
  +----------+
  1 row in set (0.01 sec)
  ```

- `COUNT(cust_email)` 对 cust_email 列中有值的行进行计数

  ```
  mysql> SELECT COUNT(cust_email) AS num_cust
      -> FROM customers;
  +----------+
  | num_cust |
  +----------+
  |        3 |
  +----------+
  1 row in set (0.00 sec)
  ```

#### 5.10 使用聚集函数 `MAX()` 计算列的最大值

`MAX()` 返回指定列中的最大值

```
mysql> SELECT MAX(prod_price) AS max_price
    -> FROM products;
+-----------+
| max_price |
+-----------+
|     55.00 |
+-----------+
1 row in set (0.00 sec)
```

- `MAX()` 可以用来返回任意类型列的最大值，包括数值、日期值和文本数据，在用于文本数据时，如果数据按相应的列排序，则 MAX() 返回最后一行
- `MAX()` 函数忽略列值为 NULL 的行

#### 5.11 使用聚集函数 `MIN()` 计算列的最小值

`MIN()` 返回指定列的最小值

```
mysql> SELECT MIN(prod_price) AS min_price
    -> FROM products;
+-----------+
| min_price |
+-----------+
|      2.50 |
+-----------+
1 row in set (0.00 sec)
```

- 同 `MAX()` 一样， `MIN()` 可以用来返回任意类型列的最大值，包括数值、日期值和文本数据，在用于文本数据时，如果数据按相应的列排序，则 MIN() 返回最后一行
- `MIN()` 函数忽略列值为 NULL 的行

#### 5.12 使用聚集函数 `SUM()` 计算列值和

`SUM()` 用来返回指定列值得和

```
mysql> SELECT SUM(quantity) AS itmes_ordered
    -> FROM orderitems
    -> WHERE order_num = 20005;
+---------------+
| itmes_ordered |
+---------------+
|            19 |
+---------------+
1 row in set (0.00 sec)
```

- `SUM()` 函数忽略列值为 NULL 的行

#### 5.13 使用 `DISTINCT` 参数仅聚集不同值

使用 `DISITINCT` 参数时，聚集函数在计算时仅考虑不同值得行

```
mysql> SELECT AVG(DISTINCT prod_price) AS avg_price
    -> FROM products
    -> WHERE vend_id = 1003;
+-----------+
| avg_price |
+-----------+
| 15.998000 |
+-----------+
1 row in set (0.00 sec)
```

- 因为使用了 `DISTINCT` 参数，因此平均值只考虑各个不同的价格
- `DISTINCT` 在用于 `COUNT()` 时，必须指定列名，不能用于 `COUNT(*)`，即不能使用 `COUNT(DISTINCT)`

#### 5.14 组合聚集函数

`SELECT` 语句可根据需要包含多个聚集函数

```
mysql> SELECT COUNT(*) AS num_items,
    ->        MIN(prod_price) AS price_min,
    ->        MAX(prod_price) AS price_max,
    ->        AVG(prod_price) AS price_avg
    -> FROM products;
+-----------+-----------+-----------+-----------+
| num_items | price_min | price_max | price_avg |
+-----------+-----------+-----------+-----------+
|        14 |      2.50 |     55.00 | 16.133571 |
+-----------+-----------+-----------+-----------+
1 row in set (0.00 sec)
```

### 6. 数据分组 `GROUP BY` 子句和 `HAVING` 子句

#### 6.1 使用 `GROUP BY` 子句对检索进行分组

分组允许把数组分为多个逻辑组，以便能对每个组分别进行聚集计算，分组是在 `SELECT` 语句的 `GROUP BY` 子句中建立的

在使用 `GROUP BY` 子句时，需要注意以下规定：

- `GROUP BY` 子句可以包含任意数目的列，这使得能对分组进行嵌套，为数据分组提供更细致的控制
- 如果在 `GROUP BY` 子句中嵌套了分组，数据将在最后规定的分组上进行汇总。换句话说，在建立分组时，指定的所有列都一起计算（所以不能从个别的列取回数据）
- `GROUP BY` 子句中列出的每个列都必须是检索列或有效的表达式（但不能是聚集函数）。如果在 `SELECT` 中使用表达式，则必须在 `GROUP BY` 子句中指定相同的表达式，不能使用别名
- 除聚集计算语句外，`SELECT` 语句中的每个列都必须在 `GROUP BY` 子句中给出
- 如果分组列中具有 `NULL` 值，则 `NULL` 将作为一个分组返回，如果列中有多行 NULL 值，它们将分为一组
- `GROUP BY` 子句必须出现在 `WHERE` 子句中，`ORDER BY` 子句之前

```
mysql> SELECT vend_id, COUNT(*) AS num_pords
    -> FROM products
    -> GROUP BY vend_id;
+---------+-----------+
| vend_id | num_pords |
+---------+-----------+
|    1001 |         3 |
|    1002 |         2 |
|    1003 |         7 |
|    1005 |         2 |
+---------+-----------+
4 rows in set (0.00 sec)
```

- 上面的 `SELECT` 语句指定了两个列，vend_id 包含产生供应商的 ID，num_prods 为计算字段

- `GROUP BY` 子句指示 MySQL 对 vend_id 排序并分组数据，这导致对每个 vend_id 而不是整个表计算 num_prods 一次，从输出中可以看到，供应商 1001 有 3 个产品，供应商 1002 有 2 个产品，供应商 1003 有 7 个产品，而供应商 1005 有 2 个产品

- 还可以使用 `WITH ROLLUP` 关键字，可以得到每个分组以及每个分组汇总级别的值：

  ```
  mysql> SELECT vend_id, COUNT(*) AS num_prods
      -> FROM products
      -> GROUP BY vend_id WITH ROLLUP;
  +---------+-----------+
  | vend_id | num_prods |
  +---------+-----------+
  |    1001 |         3 |
  |    1002 |         2 |
  |    1003 |         7 |
  |    1005 |         2 |
  |    NULL |        14 |
  +---------+-----------+
  5 rows in set (0.00 sec)
  ```

#### 6.2 使用 `HAVING` 子句过滤分组

`HAVING` 子句非常类似与 `WHERE`，事实上，`HAVING` 支持所有的 `WHERE` 操作符，包括通配符和各种子句，两者的区别是，`WHERE` 过滤行，而 `HAVING` 过滤分组：`WHERE` 在数据分组前进行过滤，而 `HAVING` 在数据分组后进行过滤

```
mysql> SELECT vend_id, COUNT(*) AS num_prods
    -> FROM products
    -> GROUP BY vend_id
    -> HAVING COUNT(*) >= 2;
+---------+-----------+
| vend_id | num_prods |
+---------+-----------+
|    1001 |         3 |
|    1002 |         2 |
|    1003 |         7 |
|    1005 |         2 |
+---------+-----------+
4 rows in set (0.00 sec)
```

`HAVING` 可以和 `WHERE` 同时使用，通过 `WHERE` 过滤的行将不包括在分组中：

```
mysql> SELECT vend_id, COUNT(*) AS num_prods
    -> FROM products
    -> WHERE prod_price >= 10
    -> GROUP BY vend_id
    -> HAVING COUNT(*) >= 2;
+---------+-----------+
| vend_id | num_prods |
+---------+-----------+
|    1003 |         4 |
|    1005 |         2 |
+---------+-----------+
2 rows in set (0.01 sec)
```

#### 6.3 对 `GROUP BY` 的分组进行 `ORDER BY` 排序

我们经常能发现用 `GROUP BY` 分组的数据确实是以分组顺序输出的，但情况并不总是这样，它并不是 SQL 规范所要求的，因此，千万不要仅依赖 `GROUP BY` 分组排序数据，在需要保证数据正确排序时，必须明确提供 `ORDER BY` 子句，即使其效果等同于 `GROUP BY` 子句也应如此

下面的例子检索总计订单价格大于等于 50 的订单的订单号和总计订单价格，并使用 `ORDER BY` 按总计订单价格排序输出：

```
mysql> SELECT order_num, SUM(quantity*item_price) AS ordertotal
    -> FROM orderitems
    -> GROUP BY order_num
    -> HAVING SUM(quantity*item_price) >= 50
    -> ORDER BY ordertotal;
+-----------+------------+
| order_num | ordertotal |
+-----------+------------+
|     20006 |      55.00 |
|     20008 |     125.00 |
|     20005 |     149.87 |
|     20007 |    1000.00 |
+-----------+------------+
4 rows in set (0.00 sec)
```

#### 6.4 `SELECT` 各子句执行顺序

下表展示了 `SELECT` 中各子句的顺序：

| 子句 | 说明 | 是否必须使用 |
| --- | --- | --- |
| `SELECT` | 要返回的列或表达式 | 是 |
| `FROM` | 从中检索数据的表 | 仅在从表选择数据时使用 |
| `WHERE` | 行级过滤 | 否 |
| `GROUP BY` | 分组说明 | 仅在按组计算聚集时使用 |
| `HAVING` | 组级过滤 | 否 |
| `ORDER BY` | 输出排序顺序 | 否 |
| `LIMIT` | 要检索的行数 | 否 |

### 7. 子查询

子查询即嵌套在其他查询中的查询

#### 7.1 利用子查询进行过滤

有以下数据库表结构：

- `orders` 表存储了每个订单的订单号、客户 ID、订单日期
- `orderitems` 表保存了各订单中的物品
- `customers` 表存储了客户信息

假设我们有以下操作需求：

1. 检索包含物品 TNT2 的所有订单的编号
2. 检索具有前一步骤列出的订单编号的所有客户的 ID
3. 检索前一步骤返回的所有客户 ID 的客户信息

上面的每一步都可用一条 `SELECT` 语句完成：

1. 从 orderitems 表中找出 prod_id 为 TNT2 的所有订单，输出其订单编号 order_num 列：

  ```
  mysql> SELECT order_num
      -> FROM orderitems
      -> WHERE prod_id = 'TNT2';
  +-----------+
  | order_num |
  +-----------+
  |     20005 |
  |     20007 |
  +-----------+
  2 rows in set (0.00 sec)
  ```

2. 从 orders 表中查询具有订单 20005 和 20007 的客户 ID

  ```
  mysql> SELECT cust_id
      -> FROM orders
      -> WHERE order_num IN (20005,20007);
  +---------+
  | cust_id |
  +---------+
  |   10001 |
  |   10004 |
  +---------+
  2 rows in set (0.00 sec)
  ```

3. 下一步，从 customers 表中检索出客户 10001 和 10004 的信息：

  ```
  mysql> SELECT cust_name, cust_contact
      -> FROM customers
      -> WHERE cust_id IN (10001,10004);
  +----------------+--------------+
  | cust_name      | cust_contact |
  +----------------+--------------+
  | Coyote Inc.    | Y Lee        |
  | Yosemite Place | Y Sam        |
  +----------------+--------------+
  2 rows in set (0.00 sec)
  ```

其实，可以将上面三条 `SELECT` 语句通过子查询合并为一条 SQL 语句：

```
mysql> SELECT cust_name, cust_contact
    -> FROM customers
    -> WHERE cust_id IN (SELECT cust_id
    ->                   FROM orders
    ->                   WHERE order_num IN (SELECT order_num
    ->                                       FROM orderitems
    ->                                       WHERE prod_id = 'TNT2'));
+----------------+--------------+
| cust_name      | cust_contact |
+----------------+--------------+
| Coyote Inc.    | Y Lee        |
| Yosemite Place | Y Sam        |
+----------------+--------------+
2 rows in set (0.00 sec)
```

使用子查询时要注意：

- 虽然 SQL 语句对能嵌套的子查询的数目没有限制，不过在实际使用时由于性能的限制，不能嵌套太多的子查询
- 在 `WHERE` 子句中使用子查询时，应该保证 `SELECT` 语句具有与 `WHERE` 子句中相同数目的列。通常，子查询将返回单个列并且与单个列匹配，但如果需要也可以使用多个列
- 子查询一般与 IN 操作符结合使用，但也可以用于测试等于（=）、不等于（<>）等
- 一般的嵌套检索问题可以通过子查询解决，但为性能考虑，子查询并非解决该问题的最好方法

#### 7.2 作为计算字段使用子查询

子查询也可以作为计算字段在 `SELECT` 语句中使用：

假设我们需要显示 customers 表中每个客户的订单总数，需要执行以下步骤：

1. 从 customers 表中检索客户列表
2. 对于检索出的每个客户，统计其在 orders 表中的订单数目

可将 `COUNT(*)` 作为一个子查询：

```
mysql> SELECT cust_name,
    ->        cust_state,
    ->        (SELECT COUNT(*)
    ->         FROM orders
    ->         WHERE orders.cust_id = customers.cust_id) AS orders
    -> FROM customers
    -> ORDER BY cust_name;
+----------------+------------+--------+
| cust_name      | cust_state | orders |
+----------------+------------+--------+
| Coyote Inc.    | MI         |      2 |
| E Fudd         | IL         |      1 |
| Mouse House    | OH         |      0 |
| Wascals        | IN         |      1 |
| Yosemite Place | AZ         |      1 |
+----------------+------------+--------+
5 rows in set (0.01 sec)
```

### 8. 联结

#### 8.1 什么是联结？为什么需要联结？



#### 8.1 笛卡尔联结（叉联结）

笛卡尔联结：由没有联结条件的表关系返回的结果为笛卡尔积，因此又称叉联结，其检索出的行的数目将是第一个表中的行数乘以第二个表中的行数

```
mysql> SELECT vend_name, prod_name, prod_price
    -> FROM vendors, products
    -> ORDER BY vend_name, prod_name;
+----------------+----------------+------------+
| vend_name      | prod_name      | prod_price |
+----------------+----------------+------------+
| ACME           | .5 ton anvil   |       5.99 |
| ACME           | 1 ton anvil    |       9.99 |
| ACME           | 2 ton anvil    |      14.99 |
| ACME           | Bird seed      |      10.00 |
| ACME           | Carrots        |       2.50 |
| ACME           | Detonator      |      13.00 |
| ACME           | Fuses          |       3.42 |
| ACME           | JetPack 1000   |      35.00 |
| ACME           | JetPack 2000   |      55.00 |
| ACME           | Oil can        |       8.99 |
| ACME           | Safe           |      50.00 |
| ACME           | Sling          |       4.49 |
| ACME           | TNT (1 stick)  |       2.50 |
| ACME           | TNT (5 sticks) |      10.00 |
| Anvils R Us    | .5 ton anvil   |       5.99 |
| Anvils R Us    | 1 ton anvil    |       9.99 |
| Anvils R Us    | 2 ton anvil    |      14.99 |
| Anvils R Us    | Bird seed      |      10.00 |
| Anvils R Us    | Carrots        |       2.50 |
| Anvils R Us    | Detonator      |      13.00 |
| Anvils R Us    | Fuses          |       3.42 |
| Anvils R Us    | JetPack 1000   |      35.00 |
| Anvils R Us    | JetPack 2000   |      55.00 |
| Anvils R Us    | Oil can        |       8.99 |
| Anvils R Us    | Safe           |      50.00 |
| Anvils R Us    | Sling          |       4.49 |
| Anvils R Us    | TNT (1 stick)  |       2.50 |
| Anvils R Us    | TNT (5 sticks) |      10.00 |
| Furball Inc.   | .5 ton anvil   |       5.99 |
| Furball Inc.   | 1 ton anvil    |       9.99 |
| Furball Inc.   | 2 ton anvil    |      14.99 |
| Furball Inc.   | Bird seed      |      10.00 |
| Furball Inc.   | Carrots        |       2.50 |
| Furball Inc.   | Detonator      |      13.00 |
| Furball Inc.   | Fuses          |       3.42 |
| Furball Inc.   | JetPack 1000   |      35.00 |
| Furball Inc.   | JetPack 2000   |      55.00 |
| Furball Inc.   | Oil can        |       8.99 |
| Furball Inc.   | Safe           |      50.00 |
| Furball Inc.   | Sling          |       4.49 |
| Furball Inc.   | TNT (1 stick)  |       2.50 |
| Furball Inc.   | TNT (5 sticks) |      10.00 |
| Jet Set        | .5 ton anvil   |       5.99 |
| Jet Set        | 1 ton anvil    |       9.99 |
| Jet Set        | 2 ton anvil    |      14.99 |
| Jet Set        | Bird seed      |      10.00 |
| Jet Set        | Carrots        |       2.50 |
| Jet Set        | Detonator      |      13.00 |
| Jet Set        | Fuses          |       3.42 |
| Jet Set        | JetPack 1000   |      35.00 |
| Jet Set        | JetPack 2000   |      55.00 |
| Jet Set        | Oil can        |       8.99 |
| Jet Set        | Safe           |      50.00 |
| Jet Set        | Sling          |       4.49 |
| Jet Set        | TNT (1 stick)  |       2.50 |
| Jet Set        | TNT (5 sticks) |      10.00 |
| Jouets Et Ours | .5 ton anvil   |       5.99 |
| Jouets Et Ours | 1 ton anvil    |       9.99 |
| Jouets Et Ours | 2 ton anvil    |      14.99 |
| Jouets Et Ours | Bird seed      |      10.00 |
| Jouets Et Ours | Carrots        |       2.50 |
| Jouets Et Ours | Detonator      |      13.00 |
| Jouets Et Ours | Fuses          |       3.42 |
| Jouets Et Ours | JetPack 1000   |      35.00 |
| Jouets Et Ours | JetPack 2000   |      55.00 |
| Jouets Et Ours | Oil can        |       8.99 |
| Jouets Et Ours | Safe           |      50.00 |
| Jouets Et Ours | Sling          |       4.49 |
| Jouets Et Ours | TNT (1 stick)  |       2.50 |
| Jouets Et Ours | TNT (5 sticks) |      10.00 |
| LT Supplies    | .5 ton anvil   |       5.99 |
| LT Supplies    | 1 ton anvil    |       9.99 |
| LT Supplies    | 2 ton anvil    |      14.99 |
| LT Supplies    | Bird seed      |      10.00 |
| LT Supplies    | Carrots        |       2.50 |
| LT Supplies    | Detonator      |      13.00 |
| LT Supplies    | Fuses          |       3.42 |
| LT Supplies    | JetPack 1000   |      35.00 |
| LT Supplies    | JetPack 2000   |      55.00 |
| LT Supplies    | Oil can        |       8.99 |
| LT Supplies    | Safe           |      50.00 |
| LT Supplies    | Sling          |       4.49 |
| LT Supplies    | TNT (1 stick)  |       2.50 |
| LT Supplies    | TNT (5 sticks) |      10.00 |
+----------------+----------------+------------+
84 rows in set (0.00 sec)
```

一般来说，叉联结都会带 `WHERE` 子句从结果中过滤出想要的数据：

```
mysql> SELECT vend_name, prod_name, prod_price
    -> FROM vendors, products
    -> WHERE vendors.vend_id = products.vend_id
    -> ORDER BY vend_name, prod_name;
+-------------+----------------+------------+
| vend_name   | prod_name      | prod_price |
+-------------+----------------+------------+
| ACME        | Bird seed      |      10.00 |
| ACME        | Carrots        |       2.50 |
| ACME        | Detonator      |      13.00 |
| ACME        | Safe           |      50.00 |
| ACME        | Sling          |       4.49 |
| ACME        | TNT (1 stick)  |       2.50 |
| ACME        | TNT (5 sticks) |      10.00 |
| Anvils R Us | .5 ton anvil   |       5.99 |
| Anvils R Us | 1 ton anvil    |       9.99 |
| Anvils R Us | 2 ton anvil    |      14.99 |
| Jet Set     | JetPack 1000   |      35.00 |
| Jet Set     | JetPack 2000   |      55.00 |
| LT Supplies | Fuses          |       3.42 |
| LT Supplies | Oil can        |       8.99 |
+-------------+----------------+------------+
14 rows in set (0.00 sec)
```

也可以对同一张表进行自联结：

```
mysql> SELECT p1.prod_id, p1.prod_name
    -> FROM products AS p1, products AS p2
    -> WHERE p1.vend_id = p2.vend_id
    ->   AND p2.prod_id = 'DTNTR';
+---------+----------------+
| prod_id | prod_name      |
+---------+----------------+
| DTNTR   | Detonator      |
| FB      | Bird seed      |
| FC      | Carrots        |
| SAFE    | Safe           |
| SLING   | Sling          |
| TNT1    | TNT (1 stick)  |
| TNT2    | TNT (5 sticks) |
+---------+----------------+
7 rows in set (0.00 sec)
```

- SQL 对一条 SELECT 语句中可以联结的表的数目没有限制，但是联结的表越多，性能下降越厉害

#### 8.2 `INNER JOIN` 等值联结（内部联结）

等值联结，也称为内部联结，它是基于两个表之间的相等测试

```
SELECT vend_name, prod_name, prod_price
FROM vendors INNER JOIN products
ON vendors.vend_id = products.vend_id;
```

- 此处 `INNER JOIN` 的内部联结和有 `WHERE` 子句的叉联结效果是等同的
- 可以在联结中使用聚集函数：

  ```
  mysql> SELECT customers.cust_name,
      ->        customers.cust_id,
      ->        COUNT(orders.order_num) AS num_ord
      -> FROM customers INNER JOIN orders
      -> ON customers.cust_id = orders.cust_id
      -> GROUP BY customers.cust_id;
  +----------------+---------+---------+
  | cust_name      | cust_id | num_ord |
  +----------------+---------+---------+
  | Coyote Inc.    |   10001 |       2 |
  | Wascals        |   10003 |       1 |
  | Yosemite Place |   10004 |       1 |
  | The Fudds      |   10005 |       1 |
  +----------------+---------+---------+
  4 rows in set (0.00 sec)
  ```

#### 8.3 `OUTER JOIN` 外部联结

外部联结有两种形式：左外部联结 `LEFT OUTER JOIN` 和右外部联结 `RIGHT OUTER JOIN`：
- `LEFT OUTER JOIN`：从左边表中选出所有行，再从右边表中选出某些行联结到左边表
- `RIGHT OUTER JOIN`：从右边表中选出所有行，再从左边表中选出某些行联结到右边表

下面是一个左外部联结的例子：

```
mysql> SELECT customers.cust_id, orders.order_num
    -> FROM customers LEFT OUTER JOIN orders
    -> ON customers.cust_id = orders.cust_id;
+---------+-----------+
| cust_id | order_num |
+---------+-----------+
|   10001 |     20005 |
|   10001 |     20009 |
|   10002 |      NULL |
|   10003 |     20006 |
|   10004 |     20007 |
|   10005 |     20008 |
|   10007 |      NULL |
|   10008 |      NULL |
|   10009 |      NULL |
+---------+-----------+
9 rows in set (0.00 sec)
```

### 9. 组合查询

#### 9.1 使用 `UNION` 连接多条 `SELECT` 语句组合查询

可在 `UNION` 操作符来组合数条 SQL 查询，用法是给出每条 SELECT 语句，然后在各条语句之间放上关键字 `UNION`

下面的例子检索出价格小于等于 5 的所有物品，同时检索供应商 1001 和 1002 生产的所有物品：

```
mysql> SELECT vend_id, prod_id, prod_price
    -> FROM products
    -> WHERE prod_price <= 5
    -> UNION
    -> SELECT vend_id, prod_id, prod_price
    -> FROM products
    -> WHERE vend_id IN (1001,1002);
+---------+---------+------------+
| vend_id | prod_id | prod_price |
+---------+---------+------------+
|    1003 | FC      |       2.50 |
|    1002 | FU1     |       3.42 |
|    1003 | SLING   |       4.49 |
|    1003 | TNT1    |       2.50 |
|    1001 | ANV01   |       5.99 |
|    1001 | ANV02   |       9.99 |
|    1001 | ANV03   |      14.99 |
|    1002 | OL1     |       8.99 |
+---------+---------+------------+
8 rows in set (0.00 sec)
```

`UNION` 使用简单，但在使用时也需要注意以下几点：

- `UNION` 中每个查询必须包含相同的列、表达式或聚集函数（不过不需要以相同的次序列出）
- 列数据类型必须兼容，类型不必完全相同，但必须是 DBMS 可以隐含地转换的类型
- 大多数情况下，`UNION` 语句都可用 `WHERE` 子句替代，有时 `WHERE` 子句可能比 `UNION` 更加简单，但是在更复杂的过滤条件下，或者从多个表（而不是单个表）中检索数据的情形，使用 UNION 可能会使处理更加简单

#### 9.2 `UNION` 组合查询时使用 `` 包含或取消重复的行

默认情况下，`UNION` 从查询结果集中自动去除了重复的行（也就是说，它的行为与单条 SELECT 语句中使用多个 WHERE 子句条件一样），但是如果想返回所有匹配行，可使用 `UNION ALL`

```
mysql> SELECT vend_id, prod_id, prod_price
    -> FROM products
    -> WHERE prod_price <= 5
    -> UNION ALL
    -> SELECT vend_id, prod_id, prod_price
    -> FROM products
    -> WHERE vend_id IN (1001,1002);
+---------+---------+------------+
| vend_id | prod_id | prod_price |
+---------+---------+------------+
|    1003 | FC      |       2.50 |
|    1002 | FU1     |       3.42 |
|    1003 | SLING   |       4.49 |
|    1003 | TNT1    |       2.50 |
|    1001 | ANV01   |       5.99 |
|    1001 | ANV02   |       9.99 |
|    1001 | ANV03   |      14.99 |
|    1002 | FU1     |       3.42 |
|    1002 | OL1     |       8.99 |
+---------+---------+------------+
9 rows in set (0.00 sec)
```

- 前面说到，`UNION` 几乎总是完成和 `WHERE` 子句相同的工作，但是 `UNION ALL` 完成了 `WHERE` 子句无法完成的工作，如果确实需要每个条件的匹配行全部出现（包括重复行），则必须使用 `UNION ALL` 而不是 `WHERE`

#### 9.3 `UNION` 组合查询时使用 `ORDER BY` 对结果排序

使用 `UNION` 组合查询时，只能使用一条 `ORDER BY` 子句，且它必须出现在最后一条 `SELECT` 语句之后，对于结果集，不存在用一种方式排序一部分，而又用另一种方式排序另一部分的情况，因此，不允许使用多条 `ORDER BY` 子句

```
mysql> SELECT vend_id, prod_id, prod_price
    -> FROM products
    -> WHERE prod_price <= 5
    -> UNION
    -> SELECT vend_id, prod_id, prod_price
    -> FROM products
    -> WHERE vend_id IN (1001,1002)
    -> ORDER BY vend_id, prod_price;
+---------+---------+------------+
| vend_id | prod_id | prod_price |
+---------+---------+------------+
|    1001 | ANV01   |       5.99 |
|    1001 | ANV02   |       9.99 |
|    1001 | ANV03   |      14.99 |
|    1002 | FU1     |       3.42 |
|    1002 | OL1     |       8.99 |
|    1003 | FC      |       2.50 |
|    1003 | TNT1    |       2.50 |
|    1003 | SLING   |       4.49 |
+---------+---------+------------+
8 rows in set (0.00 sec)
```

### 10. 全文本搜索

前文说到，`LIKE` 关键字和正则表达式都可以对文本进行搜索，但是都存在以下几个重要的限制：

- 性能低下：通配符和正则表达式通常要求 MySQL 尝试匹配表中所有行，因此由于被搜索行数不断增加，这些搜索可能非常耗时
- 明确控制：使用通配符和正则表达式匹配时，很难明确地控制匹配什么和不匹配什么
- 智能化的结果：虽然基于通配符和正则表达式的搜索提供了非常灵活的搜索，但它们都不能提供一种智能化的选择结果的方法。

全文本搜索解决了这些限制，但并非所有引擎都支持全文本搜索，MySQL 中两个最常见的引擎 MyISAM 和 InnoDB 中，仅前者支持全文搜索

#### 10.1 使用全文本搜索

使用全文本搜索前，需要开启全文本搜索，一般在创建表时通过 `FULLTEXT` 子句开启，也可以在表创建完成后给出：

```
CREATE TABLE productnotes2
(
  note_id       int         NOT NULL AUTO_INCREMENT,
  prod_id       char(10)    NOT NULL,
  note_date     datetime    NOT NULL,
  note_text     text        NULL,
  PRIMARY KEY(note_id),
  FULLTEXT(note_text)
)ENGINE=MyISAM;
```

- MySQL 会自动为 `FULLTEXT()` 中指定的列维护索引，在增加、更新或删除行时，索引随之自动更新，`FULLTEXT` 可以索引单个列，也可以索引以逗号分隔的多个列列表
- 不要在导入数据时使用 `FULLTEXT`，而应该在导入所有数据之后，然后再修改表，定义 `FULLTEXT`，这样有助于更快地导入数据

建立索引之后，可以使用 `Match()` 和 `Against()` 进行全文本搜索，其中 `Match()` 指定被搜索的列，`Against()` 指定要使用的搜索表达式

```
mysql> SELECT note_text FROM productnotes WHERE Match(note_text) Against('rabbit');
+----------------------------------------------------------------------------------------------------------------------+
| note_text                                                                                                            |
+----------------------------------------------------------------------------------------------------------------------+
| Customer complaint: rabbit has been able to detect trap, food apparently less effective now.                         |
| Quantity varies, sold by the sack load.
All guaranteed to be bright and orange, and suitable for use as rabbit bait. |
+----------------------------------------------------------------------------------------------------------------------+
2 rows in set (0.00 sec)
```

- 上面执行的全文本搜索返回了两列，其中每列都含有指定词 'rabbit'
- 注意：传递给 `Match()` 的值必须与 `FULLTEXT()` 定义的相同，如果指定多个列，则必须按顺序列出它们
- 全文本搜索不区分大小写，除非指定使用 `BINARY` 方式

注意，上面的搜索结果是通过排序后输出的，两行都含 'rabbit'，但包含词作为第 3 个词的行的等级比作为第 20 个词的行高，全文本搜索对结果进行排序，具有较高等级的行先返回

为了说明排序如何工作，请看如下例子：

```
mysql> SELECT note_text,
    ->        Match(note_text) Against('rabbit') AS rank
    -> FROM productnotes;
ERROR 1064 (42000): You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near 'rank
FROM productnotes' at line 2
mysql> SELECT note_text,
    ->        Match(note_text) Against('rabbit') AS ret
    -> FROM productnotes;
+-----------------------------------------------------------------------------------------------------------------------------------------------------------+--------------------+
| note_text                                                                                                                                                 | ret                |
+-----------------------------------------------------------------------------------------------------------------------------------------------------------+--------------------+
| Customer complaint:
Sticks not individually wrapped, too easy to mistakenly detonate all at once.
Recommend individual wrapping.                          |                  0 |
| Can shipped full, refills not available.
Need to order new can if refill needed.                                                                          |                  0 |
| Safe is combination locked, combination not provided with safe.
This is rarely a problem as safes are typically blown up or dropped by customers.         |                  0 |
| Quantity varies, sold by the sack load.
All guaranteed to be bright and orange, and suitable for use as rabbit bait.                                      | 1.5905543565750122 |
| Included fuses are short and have been known to detonate too quickly for some customers.
Longer fuses are available (item FU1) and should be recommended. |                  0 |
| Matches not included, recommend purchase of matches or detonator (item DTNTR).                                                                            |                  0 |
| Please note that no returns will be accepted if safe opened using explosives.                                                                             |                  0 |
| Multiple customer returns, anvils failing to drop fast enough or falling backwards on purchaser. Recommend that customer considers using heavier anvils.  |                  0 |
| Item is extremely heavy. Designed for dropping, not recommended for use with slings, ropes, pulleys, or tightropes.                                       |                  0 |
| Customer complaint: rabbit has been able to detect trap, food apparently less effective now.                                                              | 1.6408053636550903 |
| Shipped unassembled, requires common tools (including oversized hammer).                                                                                  |                  0 |
| Customer complaint:
Circular hole in safe floor can apparently be easily cut with handsaw.                                                                |                  0 |
| Customer complaint:
Not heavy enough to generate flying stars around head of victim. If being purchased for dropping, recommend ANV02 or ANV03 instead.   |                  0 |
| Call from individual trapped in safe plummeting to the ground, suggests an escape hatch be added.
Comment forwarded to vendor.                            |                  0 |
+-----------------------------------------------------------------------------------------------------------------------------------------------------------+--------------------+
14 rows in set (0.00 sec)
```

如上所示，全文本搜索通过对每行值计算出一个匹配结果等级值，等级由 MySQL 根据行中词的数目、唯一词的数目、整个索引中词的总数以及包含该词的行的数目计算出来，排序也是根据此值排序的

#### 10.2 使用查询扩展

查询扩展用来设法放宽所返回的全文本搜索结果的范围，在使用查询扩展时，MySQL 对数据和索引进行两边扫描来完成搜索：

1. 首先，进行一个基本的全文本搜索，找出与搜索条件匹配的所有行
2. 其次，MySQL 会检查这些匹配行并选择所有有用的词
3. 最后，MySQL 会再次进行全文本搜索，这次不仅使用原来的条件，而且还使用所有有用的词

如此，利用查询扩展，能找出可能相关的结果，即使它们并不精确包含所查找的词

```
mysql> SELECT note_text
    -> FROM productnotes
    -> WHERE Match(note_text) Against('anvils' WITH QUERY EXPANSION);
+----------------------------------------------------------------------------------------------------------------------------------------------------------+
| note_text                                                                                                                                                |
+----------------------------------------------------------------------------------------------------------------------------------------------------------+
| Multiple customer returns, anvils failing to drop fast enough or falling backwards on purchaser. Recommend that customer considers using heavier anvils. |
| Customer complaint:
Sticks not individually wrapped, too easy to mistakenly detonate all at once.
Recommend individual wrapping.                         |
| Customer complaint:
Not heavy enough to generate flying stars around head of victim. If being purchased for dropping, recommend ANV02 or ANV03 instead.  |
| Please note that no returns will be accepted if safe opened using explosives.                                                                            |
| Customer complaint: rabbit has been able to detect trap, food apparently less effective now.                                                             |
| Customer complaint:
Circular hole in safe floor can apparently be easily cut with handsaw.                                                               |
| Matches not included, recommend purchase of matches or detonator (item DTNTR).                                                                           |
+----------------------------------------------------------------------------------------------------------------------------------------------------------+
7 rows in set (0.00 sec)
```

上面的全文本搜索，目标词为 'anvils'，但是仅第一行包含了 'anvils'，而第二行包含了第一行中的两个词 'customer' 和 'recommend'，所以也被检索出来了，其他行类似

正如所见，查询扩展极大地增加了返回的行数，但这样做也增加了你实际上并不想要的行的数目

#### 10.3 布尔文本搜索

MySQL 也支持在全文本搜索的时候使用布尔方式（boolean mode），以布尔方式可以提供关于如下内容的细节：

1. 要匹配的词
2. 要排斥的词
3. 排列提示（指定某些词比其他词重要，更重要的词等级更高）
4. 表达式分组

> 布尔方式即使没有 FULLTEXT 索引也可以使用，但是非常缓慢

下面匹配包含 heavy 但不包含任意以 rope 开始的词的行：

```
mysql> SELECT note_text
    -> FROM productnotes
    -> WHERE Match(note_text) Against('heavy -rope*' IN BOOLEAN MODE);
+---------------------------------------------------------------------------------------------------------------------------------------------------------+
| note_text                                                                                                                                               |
+---------------------------------------------------------------------------------------------------------------------------------------------------------+
| Customer complaint:
Not heavy enough to generate flying stars around head of victim. If being purchased for dropping, recommend ANV02 or ANV03 instead. |
+---------------------------------------------------------------------------------------------------------------------------------------------------------+
1 row in set (0.00 sec)
```

MySQL 支持的全文本布尔操作符有：

| 布尔操作符 | 说明 |
| --- | --- |
| `+` | 包含，此词必须存在 |
| `-` | 排除，词必须不存在 |
| `>` | 包含，而且增加等级值 |
| `<` | 包含，且减少等级值 |
| `()` | 把词组成子表达式（允许这些子表达式作为一个组被包含、排除、排列等） |
| `-` | 取消一个词的排序值 |
| `*` | 词尾的通配符 |
| `""` | 定义一个短语（与单个词的列表不一样，它匹配整个短语以便包含或排除这个短语） |

下面举例说明某些操作符该如何用：

- ```
  SELECT note_text
  FROM productnotes
  WHERE Match(note_text) Against('heavy -rope*' IN BOOLEAN MODE);
  ```


- ```
  SELECT note_text
  FROM productnotes
  WHERE Match(note_text) Against('+rabbit +bait' IN BOOLEAN MODE);
  ```

  搜索包含词 rabbit 和 bait 的行

- ```
  SELECT note_text
  FROM productnotes
  WHERE Match(note_text) Against('rabbit bait' IN BOOLEAN MODE);
  ```

  搜索包含 rabbit 和 bait 中的至少一个词的行

- ```
  SELECT note_text
  FROM productnotes
  WHERE Match(note_text) Against('"rabbit bait"' IN BOOLEAN MODE);
  ```

  搜索匹配短语 rabbit bait 而不是匹配单个词

- ```
  SELECT note_text
  FROM productnotes
  WHERE Match(note_text) Against('>rabbit <carrot' IN BOOLEAN MODE);
  ```

  匹配 rabbit 和 carrot ，增加前者的等级，降低后者的等级

- ```
  SELECT note_text
  FROM productnotes
  WHERE Match(note_text) Against('+safe +(<combination)' IN BOOLEAN MODE);
  ```

  搜索匹配词 safe 和 combination，降低后者的等级

### 11. 插入、更新、删除数据

#### 11.1 使用 `INSERT` 插入一行数据

`INSERT` 语句要求指定表名和被插入到新行中的值

下面是插入一行数据的例子：

```
mysql> INSERT INTO customers
    -> VALUES(NULL,
    ->     'Pep E. LaPew',
    ->     '100 Main Street',
    ->     'Los Angeles',
    ->     'CA',
    ->     '90046',
    ->     'USA',
    ->     NULL,
    ->     NULL);
Query OK, 1 row affected (0.00 sec)
```

上面插入的各个值以各个列在表中定义的次序填充，虽然简单，但不安全，因为它高度依赖于表中列的定义次序，若表的结构有变，则该 SQL 语句将无法产生正确结果

安全的插入数据的方法是插入时指定列名，如下：

```
mysql> INSERT INTO customers(cust_name,
    ->     cust_address,
    ->     cust_city,
    ->     cust_state,
    ->     cust_zip,
    ->     cust_country,
    ->     cust_contact,
    ->     cust_email)
    -> VALUES('Pep E. LaPew',
    ->     '100 Main Street',
    ->     'Los Angeles',
    ->     'CA',
    ->     '90046',
    ->     'USA',
    ->     NULL,
    ->     NULL);
Query OK, 1 row affected (0.01 sec)
```

- 使用 `INSERT` 插入数据时应该总是指出列名
- 如果某列无值或该值由系统提供（有默认值或设置了自动增量值），应该指定 NULL 值，
- 可以在 `INSERT` 中省略某些列，省略的行必须允许被设置为 NULL 值或者表定义中定义了默认值

#### 11.2 使用 `INSERT` 插入多行数据

可以使用如下组合语句用 `INSERT` 插入多行数据

```
mysql> INSERT INTO customers(cust_name,
    ->     cust_address,
    ->     cust_city,
    ->     cust_state,
    ->     cust_zip,
    ->     cust_country)
    -> VALUES(
    ->         'Pep E. LaPew',
    ->         '100 Main Street',
    ->         'Los Angeles',
    ->         'CA',
    ->         '90046',
    ->         'USA'
    ->     ),
    ->     (
    ->         'M. Martian',
    ->         '42 Galaxy Way',
    ->         'New York',
    ->         'NY',
    ->         '11213',
    ->         'USA'
    ->     );
Query OK, 2 rows affected (0.01 sec)
```

- 使用上面组合语句插入多行数据性能由于使用多条 `INSERT` 语句插入多行数据

#### 11.3 使用 `INSERT` 插入检索出的数据

可以使用如下的 `INSERT SELECT` 方法插入检索出的数据

```
INSERT INTO customers(cust_id,
    cust_contact,
    cust_email,
    cust_name,
    cust_address,
    cust_city,
    cust_state,
    cust_zip,
    cust_country)
SELECT cust_id,
    cust_contact,
    cust_email,
    cust_name,
    cust_address,
    cust_city,
    cust_state,
    cust_zip,
    cust_country
FROM custnew;
```

- 如何不想导入某列，只需简单的从 `INSERT` 和 `SELECT` 中省略这行
- `INSERT SELECT` 中不一定要求列名匹配，MySQL 甚至不关心 SELECT 返回的列名，仅关注每个列的位置
- `INSERT SELECT` 中 SELECT 语句可包含 `WHERE` 子句以过滤插入的数据

#### 11.4 使用 `UPDATE` 更新数据

使用 `UPDATE` 更新单列：

```
mysql> UPDATE customers
    -> SET cust_email = 'elmer@fudd.com'
    -> WHERE cust_id = 10005;
Query OK, 1 row affected (0.01 sec)
Rows matched: 1  Changed: 1  Warnings: 0
```

使用 `UPDATE` 更新多列：

```
mysql> UPDATE customers
    -> SET cust_name = 'The Fudds',
    ->     cust_email = 'elmer@fudd.com'
    -> WHERE cust_id = 10005;
Query OK, 1 row affected (0.01 sec)
Rows matched: 1  Changed: 1  Warnings: 0
```

- `UPDATE` 语句以 `WHERE` 子句结束，它告诉 MySQL 更新哪一行，如果没有 `WHERE` 子句，MySQL 将会用修改应该到所有行，除非确实要修改所有行，否则千万不要忘记加 `WHERE` 子句
- `UPDATE` 语句中可以使用子查询，使得能用 `SELECT` 语句检索出的数据更新列数据
- 为了删除某个列的值，可设置它为 `NULL`
- 默认情况下，如果用 `UPDATE` 语句更新多行，并且在更新这些行中的一行或多行时出现一个错误，则整个 UPDATE 操作被取消（错误发生前更新的所有行被恢复到它们原来的值），如果想要即使发生错误，也继续进行更新，可使用 `IGNORE` 关键字，如下所示：
  ```
  UPDATE IGNORE customers ...
  ```

#### 11.5 使用 `DELETE` 删除数据

```
mysql> DELETE FROM customers
    -> WHERE cust_id = 10006;
Query OK, 1 row affected (0.01 sec)
```

- 使用 `DELETE` 时要注意是否需要 `WHERE` 子句，不加 `WHERE` 子句将删除表中所有行
- `DELETE` 语句从表中删除行，甚至是删除表中所有行，但是，`DELETE` 不删除表本身
- 如果想从表中删除所有行，不需要使用 `DELETE`，可使用效率更高的 `TRUNCATE TABLE` 语句（TRUNCATE 实际上是删除原来的表并重新创建一个表，而不是逐行删除表中的数据）
- 在对 `UPDATE` 或 `DELETE` 语句使用 `WHERE` 子句前，应该使用 `SELECT` 进行测试，保证它过滤的是正确的记录，以防编写的 `WHERE` 子句不正确
- `UPDATE` 和 `WHERE` 之后无法撤销，所以更新和修改数据前要慎重

### 12. 创建和操纵表

#### 12.1 使用 `CREATE TABLE` 语句创建表

```
mysql> CREATE TABLE IF NOT EXISTS customers 
    -> (
    ->   cust_id       int         NOT NULL AUTO_INCREMENT,
    ->   cust_name     char(50)    NOT NULL ,
    ->   cust_address  char(50)    NULL ,
    ->   cust_city     char(50)    NULL ,
    ->   cust_state    char(50)    NULL ,
    ->   cust_zip      int         NOT NULL DEFAULT 1,
    ->   cust_country  char(50)    NULL ,
    ->   cust_contact  char(50)    NULL ,
    ->   cust_email    char(255)   NULL ,
    ->   PRIMARY KEY (cust_id)
    -> )ENGINE=InnoDB;
Query OK, 0 rows affected, 1 warning (0.00 sec)
```

- 创建表时，表名紧跟在 `CREATE TABLE` 关键字后，实际的表各列的定义在圆括号中，各列之间用逗号分隔，每列的定义以列名开始，后跟列���数据类型，即是否可为 NULL 值等信息
- 创建新表时，指定的表明必须不存在，否则将出错，可以为其指定 `IF NOT EXISTS` 关键字，这样你就可以仅在一个表不存在时创建它，`IF NOT EXISTS` 关键字不检查已有表的模式是否与你打算创建的表模式相匹配，它只是查看表名是否存在，并且仅在表名不存在时创建它
- 表定义的第三列 `NULL` 和 `NOT NULL` 指定该表列是否允许为 NULL 值：

  - 该表列或为 `NULL` 列，或为 `NOT NULL` 列，若创建时未明确指定，则默认为 `NULL` 列
  - `NULL` 与空串不同，二者必须区分

- `AUTO_INCREMENT` 为该列设置自动增量属性：
  - 没当执行 INSERT 操作时，MySQL 自动对该列增量，给该列赋予下一个可用的值，这样该列的每行将分配一个唯一的 ID
  - 每个表只允许一个 `AUTO_INCREMENT` 列，而且它必须被索引（如，通过使它成为主键）
  - 可以手动覆盖 `AUTO_INCREMENT` 值：可以简单的在 INSERT 语句中指定一个值，只要它是唯一的即可，该值将被用来替代自动生成的值，且后续的增量将开始使用该手工插入的值
  - 可以使用 `SELECT last_insert_id()` 返回最后一个 `AUTO_INCREMENT` 值

- `PRIMARY KEY` 用于在创建表时指定表的主键：

  - 表的主键值必须唯一：如果主键使用单列，则每个行必须具有唯一主键值；如果使用多个列，则这些列的组合值必须唯一
  - 为创建由多个列组成的主键，应该以逗号分隔的列表给出各列名，如：
    ```
    PRIMARY KEY (order_num, order_item)
    ```
  - 主键中只能使用 `NOT NULL` 的列
  - 主键可以在创建表时定义，也可以在创建表之后使用 `ALTER TABLE` 定义

- 使用 `DEFAULT` 为列指定默认值，MySQL 不允许使用函数作为默认值，只支持常量
- 可以在 `CREATE TABLE` 末尾使用 `ENGINE=` 指定内部引擎，如果省略它，则使用默认引擎（很可能是 MyISAM）


#### 12.2 使用 `ALTER TABLE` 更新表结构

表创建完成之后可以使用 `ALTER TABLE` 更新表结构：

例如：

- 给表添加一个列：

  ```
  ALTER TABLE vendors
  ADD vend_phone CHAR(20);
  ```

- 给表删除一个列：

  ```
  ALTER TABLE vendors
  DROP COLUMN vend_phone;
  ```

- 还可以用 `ALTER TABLE` 定义外键：

  ```
  ALTER TABLE orderitems
  ADD CONSTRAINT fk_orderitems_orders
  FOREIGN KEY (order_num) REFERENCES orders (order_num);
  ```

使用 `ALTER TABLE` 时要注意：

- 理想状态下，当表中存储数据以后，该表就不应该再被更新，在表的设计过程中需要花费大量时间来考虑，以便后期不对该表进行大改动
- 如果一个表结构进行大量改动，一般需要删除该表后再重建：
  1. 用新的列布局创建一个新表
  2. 使用 `INSERT SELECT` 语句从旧表复制数据到新表。如有必要，可使用转换函数和计算字段
  3. 检验包含所需数据的新表
  4. 重命名旧表（暂不删除，以便恢复）
  5. 用旧表原来的名字重命名新表
  6. 根据需要，重新创建触发器、存储过程、索引和外键
- `ALTER TABLE` 进行的更改不可撤销，因此要谨慎并及时备份

#### 12.3 使用 `DROP TABLE` 删除表

```
DROP TABLE customers2;
```

- `DROP` 用于删除整个表，而不是表内容
- 删除表没有确认，也不能撤销，执行这条语句将永久删除该表

#### 12.4 使用 `RENAME TABLE` 重命名表

下面使用 `RENAME TABLE` 重命名一个表：

```
REANME TABLE customers2 TO customers;
```

也可以对多个表重命名：

```
RENAME TABLE backup_customers TO customers,
             backup_vendors TO vendors,
             backup_products TO products;
```

### 13. 视图

#### 13.1 视图使用方法和规则


视图创建之后，可以与表基本相同的方式利用它们，可以对视图执行 `SELECT` 操作，过滤和排序数据，将视图联结到其他视图或表，甚至能添加和更新数据

使用方法：

- 视图用 `CREATE VIEW` 语句创建
- 使用 `SHOW CREATE VIEW viewname` 来查看创建视图的语句
- 用 `DROP VIEW viewname` 删除视图
- 更新视图：
  - 可以先用 `DROP` 再用 `CREATE`
  - 也可以直接用 `CREATE OR REPLACE VIEW`：如果要更新的视图不存在，则会创建一个视图，如果要更新的视图存在，则替换原有视图

使用规则：

- 与表一样，视图必须唯一命名
- 对于可以创建的视图数目没有限制
- 为了创建视图，必须具有足够的访问权限
- 视图可以嵌套，即可以利用从其他视图中检索数据的查询来构造一个视图
- `ORDER BY` 可以用在视图，但如果从该视图检索数据 `SELECT` 中也含有 `ORDER BY`，那么该视图中的 `ORDER BY` 将被覆盖
- 视图不能索引，也不能有关联的触发器或默认值
- 视图可以和表一起使用

使用视图的优点：

- 重用 SQL 语句
- 简化复杂的 SQL 操作
- 使用表的组成部分而不是整个表
- 包含数据，可以给用户授予表的特定部分的访问权限而不是整个表的访问权限
- 更改数据格式和表示：视图可返回与底层表的表示和格式不同的数据

使用视图时要注意性能问题：

视图仅仅是用来查看存储在别处的数据的一种设施，视图本身不包含数据，它们返回的数据都是从其他表中检索出来的，在添加或更改这些表中的数据时，视图将返回改变过的数据，因此每次使用视图时，都必须处理查询执行时所需的每个检索，如果用到多个视图或嵌套视图，则性能下降会很厉害


#### 13.2 利用视图简化复杂的联结

```
mysql> CREATE VIEW productcustomers AS
    -> SELECT cust_name, cust_contact, prod_id
    -> FROM customers, orders, orderitems
    -> WHERE customers.cust_id = orders.cust_id
    ->   AND orderitems.order_num = orders.order_num;
Query OK, 0 rows affected (0.01 sec)
```

上面的 SQL 语句创建了视图 productcustomers，下面使用该视图：

```
mysql> SELECT cust_name, cust_contact
    -> FROM productcustomers
    -> WHERE prod_id = 'TNT2';
+----------------+--------------+
| cust_name      | cust_contact |
+----------------+--------------+
| Coyote Inc.    | Y Lee        |
| Yosemite Place | Y Sam        |
+----------------+--------------+
2 rows in set (0.00 sec)
```

#### 13.3 利用视图重新格式化检索出的数据

将检索出的数据保存为一个视图：

```
mysql> CREATE VIEW vendorlocations AS
    -> SELECT concat(RTrim(vend_name), '(', RTrim(vend_country), ')')
    ->        AS vend_title
    -> FROM vendors
    -> ORDER BY vend_name;
Query OK, 0 rows affected (0.02 sec)
```

使用这个视图如同使用表：

```
mysql> SELECT *
    -> FROM vendorlocations;
+------------------------+
| vend_title             |
+------------------------+
| ACME(USA)              |
| Anvils R Us(USA)       |
| Furball Inc.(USA)      |
| Jet Set(England)       |
| Jouets Et Ours(France) |
| LT Supplies(USA)       |
+------------------------+
6 rows in set (0.01 sec)
```

#### 13.4 利用视图过滤不想要的数据

视图可以简化计算字段的使用，并且在视图中可使用 `WHERE` 子句

```
mysql> CREATE VIEW orderitemsexpanded AS
    -> SELECT order_num,
    ->        prod_id,
    ->        quantity,
    ->        item_price,
    ->        quantity*item_price AS expanded_price
    -> FROM orderitems;
Query OK, 0 rows affected (0.01 sec)
```

```
mysql> SELECT *
    -> FROM orderitemsexpanded
    -> WHERE order_num = 20005;
+-----------+---------+----------+------------+----------------+
| order_num | prod_id | quantity | item_price | expanded_price |
+-----------+---------+----------+------------+----------------+
|     20005 | ANV01   |       10 |       5.99 |          59.90 |
|     20005 | ANV02   |        3 |       9.99 |          29.97 |
|     20005 | TNT2    |        5 |      10.00 |          50.00 |
|     20005 | FB      |        1 |      10.00 |          10.00 |
+-----------+---------+----------+------------+----------------+
4 rows in set (0.01 sec)
```

#### 13.5 更新视图规则

视图是可更新的，即可以对它们使用 `INSERT`、`UPDATE` 和 `DELETE`。更新一个视图将更新其基表，如果你对视图增加或删除行，实际上是对其基表增加或删除行

并非所有视图都是可更新的，如果 MySQL 不能正确地确定被更新的基数据，则不允许更新（包括插入和删除），这意味着，如果视图中有以下操作，则不能进行视图的更新：

- 分组（使用 `GROUP BY` 和 `HAVING`）
- 联结
- 子查询
- 并
- 聚集函数（Min()、Count()、Sum() 等）
- DISTINCT
- 导出（计算）列

应该注意，一般应该将视图用于检索而不用于更新


### 14. 存储过程

#### 14.1. 什么是存储过程？存储过程的使用和优缺点

存储过程即是为以后的使用而保存的一条或多条 MySQL 语句的集合

下面是为什么要使用存储过程的一些理由：

- 通过把处理封装在容易使用的单元中，简化了复杂的操作
- 当所有人都是用相同的存储过程处理数据库时，可以更好的保证数据的完整性和一致性
- 简化对变动的管理：如果表名、列名或业务逻辑有变化，只需要更改存储过程的代码，使用它的人员甚至不需要知道这些变化，同时因为存储过程限制了对基础数据的访问而减少了数据讹误的机会，这提高了数据的安全性
- 提高性能：因为使用存储过程比使用单独的 SQL 语句要快
- 存在一些只能用在单个请求中的 MySQL 元素和特性，存储过程可以使用它们来编写功能更强更灵活的代码

使用存储过程的问题：

- 存储过程的编写比基本 SQL 语句复杂，编写存储过程需要更高的技能，更丰富的经验
- 创建存储过程需要一定的安全访问权限

#### 14.2 使用 `CREATE PROCEDURE` 创建存储过程

```
CREATE PROCEDURE productpricing()
BEGIN
   SELECT Avg(prod_price) AS priceaverage
   FROM products;
END;
```

这里需要注意：如果你是在 MySQL 命令行运行上述语句，应该按照如下方式运行，否则会出现语法错误：

```
DELIMITER //

CREATE PROCEDURE productpricing()
BEGIN
   SELECT Avg(prod_price) AS priceaverage
   FROM products;
END //

DELIMITER ;
```

- 因为默认的 MySQL 语句分隔符为 `;`，但是由于命令行程序会解释存储过程里的 `;`，这会导致上面语句提前结束，导致语法错误
- 解决方法是使用 `DELIMITER` 临时更改命令行程序的语句分隔符，在存储过程创建完毕之后需要恢复语句分隔符，如上面例子所示
- 除 `\` 符号之外，任何字符都可以用作语句分隔符

#### 14.3 使用 `CALL` 执行存储过程

可以使用 `CALL` 执行存储过程：

```
mysql> CALL productpricing();
+--------------+
| priceaverage |
+--------------+
|    16.133571 |
+--------------+
1 row in set (0.00 sec)
```

#### 14.4 使用 `DROP PROCEDURE` 删除存储过程

存储过程在创建之后，被保存在服务器上以供使用，直至被删除，删除命令从服务器中删除存储过程

删除存储过程，如果指定的存储过程不存在将出错：

```
mysql> DROP PROCEDURE productpricing;
Query OK, 0 rows affected (0.02 sec)
```

仅当存储过程存在时才删除它：

```
mysql> DROP PROCEDURE IF EXISTS productpricing;
Query OK, 0 rows affected, 1 warning (0.01 sec)
```

- 删除时仅指定存储过程名，不需要后面的 `()`

#### 14.4 存储过程使用参数

- 所有 MySQL 变量都必须以 `@` 开始
- 存储过程中指定参数时有 `OUT`、`IN`、`INOUT`：
  - `OUT` 指出相应的参数用来从存储过程传出一个值返回给调用者
  - `IN` 指调用者向存储过程内传递值
  - `INOUT` 对存储过程传入传出
- 存储过程的参数允许的数据类型与表中使用的数据类型相同


下面创建的存储过程传出 3 个参数：
```
CREATE PROCEDURE productpricing(
   OUT pl DECIMAL(8,2),
   OUT ph DECIMAL(8,2),
   OUT pa DECIMAL(8,2)
)
BEGIN
   SELECT Min(prod_price)
   INTO pl
   FROM products;
   SELECT Max(prod_price)
   INTO ph
   FROM products;
   SELECT Avg(prod_price)
   INTO pa
   FROM products;
END;
```

下面是使用上面创建的带参数的存储过程：

```
mysql> CALL productpricing(@pricelow,
    ->                     @pricehigh,
    ->                     @priceaverage);
Query OK, 1 row affected, 1 warning (0.00 sec)

mysql> SELECT @pricehight, @pricelow, @priceaverage;
+--------------------------+-----------+---------------+
| @pricehight              | @pricelow | @priceaverage |
+--------------------------+-----------+---------------+
| 0x                       |      2.50 |         16.13 |
+--------------------------+-----------+---------------+
1 row in set (0.00 sec)
```

下面创建了带参数的存储过程，其中一个参数为 `IN` 类型：

```
CREATE PROCEDURE ordertotal(
   IN onumber INT,
   OUT ototal DECIMAL(8,2)
)
BEGIN
   SELECT Sum(item_price*quantity)
      FROM orderitems
      WHERE order_num = onumber
      INTO ototal;
END;

```

下面展示了如何使用上面创建的带参数的存储过程：

```
mysql> CALL ordertotal(20005, @total);
Query OK, 1 row affected (0.01 sec)

mysql> SELECT @total;
+--------+
| @total |
+--------+
| 149.87 |
+--------+
1 row in set (0.00 sec)

```

#### 14.5 为存储过程增加其他流程控制语句

```
-- Name: ordertotal
-- Parameters: onumber = order number
--             taxable = 0 if not taxable, 1 if taxable
--             ototal  = order total variable

CREATE PROCEDURE ordertotal(
   IN onumber INT,
   IN taxable BOOLEAN,
   OUT ototal DECIMAL(8,2)
) COMMENT 'Obtain order total, optionally adding tax'
BEGIN
   -- Declare variable for total
   DECLARE total DECIMAL(8,2);
   -- Declare tax percentage
   DECLARE taxrate INT DEFAULT 6;
   
   -- Get the order total
   SELECT Sum(item_price*quantity)
   FROM orderitems
   WHERE order_num = onumber
   INTO total;
   
   -- Is this taxable?
   IF taxable THEN
      -- Yes, so add taxrate to the total
      SELECT total+(total/100*taxrate) INTO total;
   END IF;
   
   -- And finally, save to out variable
   SELECT total INTO ototal;
END;
```

- `--` 为注释行
- `DECLARE` 语句用来定义变量
- `IF` 语句检查 taxable 是否为真
- `COMMENT` 关键字指定的值将在 `SHOW PROCEDURE STATUS` 中显示

#### 14.6 检查存储过程

- 使用 `SHOW CREATE PROCEDURE` 语句显示用来创建一个存储过程的 `CREATE` 语句：

  ```
  SHOW CREATE PROCEDURE ordertotal;
  ```

- 使用 `SHOW PROCEDURE STATUS` 语句列出所有存储过程的列表，其中包括何时、由谁创建等详细信息

- `SHOW PROCEDURE STATUS` 列出所有存储过程列表，可使用 `LIKE` 为其指定一个过滤模式：

  ```
  SHOW PROCEDURE STATUS LIKE 'ordertotal';
  ```

### 15. 游标

#### 15.1 什么是游标？怎么用游标？

游标（cursor）是一个存储在 MySQL 服务器上的数据库查询，它不是一条 SELECT 语句，而是被该语句检索出来的结果集，在存储了游标之后，应用程序可以根据需要滚动或浏览其中的数据

游标主要用于交互式应用，其中用户需要滚动屏幕上的数据，并对数据进行浏览或做出更改，MySQL 中游标只能用于存储过程（和函数）

使用游标需要以下几个步骤：

1. 在能够使用游标前，必须定义它，这个过程实际上没有检索数据，只是定义要使用的 SELECT 语句
2. 声明之后，必须打开游标以供使用，这个过程用前面定义的 SELECT 语句把数据实际检索出来
3. 对于填有数据的游标，根据需要取出各行
4. 在结束游标使用时，必须关闭游标

#### 15.2 使用 `DECLARE cursorname CURSOR` 创建游标

下面使用 `DECLARE` 语句创建了名为 ordernumbers 的游标：

```
CREATE PROCEDURE processorders()
BEGIN
   DECLARE ordernumbers CURSOR
   FOR
   SELECT order_num FROM orders;
END；
```

上面的存储过程只是创建了游标，并没有打开并使用它，当存储过程结束时，游标就会结束，因为它仅限于存储过程

#### 15.3 使用 `OPEN CURSOR`、`CLOSE CURSOR` 打开和关闭游标

在定义游标之后，只有打开它才能使用，游标用 `OPEN CURSOR` 语句来打开，游标处理完成之后，使用 `CLOSE` 语句关闭游标：

```
CREATE PROCEDURE processorders()
BEGIN
   -- Declare the cursor
   DECLARE ordernumbers CURSOR
   FOR
   SELECT order_num FROM orders;

   -- Open the cursor
   OPEN ordernumbers;

   -- Close the cursor
   CLOSE ordernumbers;
END；
```

- 在处理 `OPEN` 语句时执行查询，存储检索出的数据以供浏览和滚动
- `CLOSE` 释放游标使用的所有内部内存和资源，因为在每个游标不再需要时都应该关闭
- 游标关闭后，被声明过的游标不需要再次声明就可重新打开
- 如果不明确关闭游标，MySQL 将会在到达 END 语句时自动关闭它

#### 15.4 利用 `FETCH` 语句使用游标数据

游标被打开之后，可以使用 `FETCH` 语句分别访问它的每一行，`FETCH` 指定检索什么数据（所需的列），检索出来的数据存储在什么地方，它还向前移动游标中的内部行指针，使下一条 `FETCH` 语句检索下一行

下面的例子中，利用游标，遍历访问检索的数据，从第一行到最后一行：

```
CREATE PROCEDURE processorders()
BEGIN
   -- Declare local variables
   DECLARE done BOOLEAN DEFAULT 0;
   DECLARE o INT;

   -- Declare the cursor
   DECLARE ordernumbers CURSOR
   FOR
   SELECT order_num FROM orders;

   -- Declare continue handler
   DECLARE CONTINUE HANDLER FOR SQLSTATE '02000' SET done=1;

   -- Open the cursor
   OPEN ordernumbers;

   -- Loop through all rows
   REPEAT

      -- Get order number
      FETCH ordernumbers INTO o;

   -- End of loop
   UNTIL done END REPEAT;

   -- Close the cursor
   CLOSE ordernumbers;
END；
```

- 上面例子中的 `FETCH` 在 `REPEAT` 内，因此它反复执行直到 done 为真（`UNTIL done END REPEAT`），done 定义时赋值为 0，通过下面语句设置为 1：
   `DECLARE CONTINUE HANDLER FOR SQLSTATE '02000' SET done=1;`
   - 这条语句定义了一个 `CONTINUE HANDLER`，它是在条件出现时被执行的代码，它指出当 `SQLSTATE '02000'` 出现时，`SET done=1`，`SQLSTATE '02000'` 是一个未找到条件，当 `REPEAT` 由于没有更多的行供循环而不能继续时，出现这个条件

- 使用 `DECLARE` 定义各类型数据时具有特定的次序，用 `DECLARE` 语句定义的局部变量必须在定义任意游标或句柄之前定义，而句柄必须在游标之后定义

### 16. 触发器

#### 16.1 什么是触发器？

**触发器** 是 MySQL 响应以下任意语句而自动执行的一条 MySQL 语句（或位于 BEGIN 和 END 语句之间的一组语句），其他 MySQL 语句不支持触发器：
- `DELETE`
- `INSERT`
- `UPDATE`

注意：

- 只有表才支持触发器，视图不支持（临时表也不支持）
- 定义触发器时，每个表每个事件每次只允许一个触发器，因此，每个表最多支持 6 个触发器（每条 INSERT、UPDATE 和 DELETE 的之前和之后）
- 单一触发器不能与多个事件或多个表关联，所以，如果你需要一个对 INSERT 和 UPDATE 操作执行的触发器，则应该定义两个触发器
- 如果 BEFORE 触发器失败，则 MySQL 将不执行请求的操作，如果 BEFORE 触发器或语句本身失败，MySQL 将不执行 AFTER 触发器
- 创建触发器可能需要特殊的安全访问权限，但是触发器的执行是自动的，如果 `INSERT`、`UPDATE`、`DELETE` 语句能够执行，则相关的触发器也能执行
- 应该用触发器来保证数据的一致性，在触发器中执行这种类型的处理的优点是它总是进行这种处理，而且是透明的进行，与客户机应用无关
- 触发器的一种非常有意义的使用是创建审计跟踪，使用触发器，把更改记录到另一个表非常容易
- MySQL 触发器中不支持 `CALL` 语句，这表示不能从触发器内调用存储过程，所需的存储过程代码需要复制到触发器内

#### 16.2 使用 `CREATE TRIGGER` 语句创建触发器

在创建触发器时，需要给出 4 条信息：

1. 唯一的触发器名
2. 触发器关联的表
3. 触发器应该相应的活动（`DELETE`、`INSERT` 或 `UPDATE`）
4. 触发器何时执行（`BEFORE` 或 `AFTER`）

使用 `CREATE TRIGGER` 创建触发器：

```
CREATE TRIGGER newproduct AFTER INSERT ON products
FOR EACH ROW SELECT 'Product added';
```

上面的触发器表示，每当向 products 表中插入一行时，将显示一次 'Product added'

- `CREATE TRIGGER` 用来创建名为 newproduct 的新触发器
- 触发器可在一个操作发生之前或之后执行，这里的 `AFTER INSERT` 表示此触发器将在 `INSERT` 成功执行后执行
- `FOR EACH ROW` 表示触发器的代码在每个插入行执行

#### 16.3 使用 `DROP TRIGGER` 语句删除触发器

```
DROP TRIGGER newproduct;
```

- 触发器不可更新或覆盖，为了修改一个触发器，必须先删除它，然后再重新创建

#### 16.4 使用 `INSERT` 触发器

`INSERT` 触发器在 `INSERT` 语句执行之前或之后执行，使用时要明白：

- 在 `INSERT` 触发器代码内，可引用一个名为 `NEW` 的虚拟表，访问被插入的行
- 在 `BEFORE INSERT` 触发器中，`NEW` 中的值也可以被更新（允许更改被插入的值）
- 对于 `AUTO_INCREMENT` 列，`NEW` 在 `INSERT` 执行之前包含 0，在 `INSERT` 之后包含新的自动生成值

```
CREATE TRIGGER neworder AFTER INSERT ON orders
FOR EACH ROW SELECT NEW.order_num;
```

- 上例创建了一个名为 neworder 的触发器，它按照 `AFTER INSERT ON orders` 执行
- 在插入一个新订单到 orders 表时，MySQL 生成一个新订单号并保存到 order_num 中，触发器从 `NEW.order_num` 取得这个值并返回它，此触发器必须按照 `AFTER_INSERT` 执行，因为在 `BEFORE_INSERT` 语句执行之前，新 order_num 还没有生成，对于 orders 的每次插入使用这个触发器将总是返回新的订单号

#### 16.5 使用 `DELETE` 触发器

`DELETE` 触发器在 `DELETE` 语句执行之前或之后执行：

- 在 `DELETE` 触发器代码内，你可以引用一个名为 `OLD` 的虚拟表，访问被删除的行
- `OLD` 中的值全都是只读的，不能更新

下面 SQL 语句演示了使用 OLD 保存将要被删除的行到一个存档表中：

```
CREATE TRIGGER deleteorder BEFORE DELETE ON orders
FOR EACH ROW
BEGIN
   INSERT INTO archive_orders(order_num, order_date, cust_id)
   VALUES(OLD.order_num, OLD.order_date, OLD.cust_id)
END;
```

#### 16.6 使用 `UPDATE` 触发器

`UPDATE` 触发器在 UPDATE 语句执行之前或之后执行：

- 在 UPDATE 触发器代码中，你可以引用一个名为 `OLD` 的虚拟表访问以前（UPDATE 语句前）的值，引用一个名为 `NEW` 的虚拟表访问新更新的值
- 在 `BEFORE UPDATE` 触发器中，NEW 中的值可能也被更新（允许更改将要用于 UPDATE 语句中的值）
- `OLD` 中的值全都是只读的，不能更新

下面的例子保证州名缩写总是大写：

```
CREATE TRIGGER updatevendor BEFORE UPDATE ON vendors
FOR EACH ROW SET NEW.vend_state = Upper(NEW.vend_state);
```

### 17. 事务处理

#### 17.1 什么是事务处理？

**事务处理（transaction processing）** 可以用来维护数据库的完整性，它保证成批的 MySQL 操作要么完全执行，要么完全不执行

MySQL 中并非所有引擎都支持事务处理，MyISAM 和 InnoDB 是两种最常使用的引擎，前者不支持明确的事务处理管理，而后者支持

事务处理中的几个术语：

1. **事务（transaction）** 指一组 SQL 语句
2. **回退（rollback）** 指撤销指定 SQL 语句的过程
3. **提交（commit）** 指将未存储的 SQL 语句结果写入数据库表
4. **保留点（savepoint）** 指事务处理中设置的临时占位符，你可以对它发布回退

MySQL 中使用下面的语句标识事务的开始：

```
START TRANSACTION
```

#### 17.2 使用 `ROLLBACK` 回退 MySQL 语句

MySQL 的 `ROLLBACK` 命令用来回退（撤销）MySQL 语句：

```
SELECT * FROM ordertotals;
START TRANSACTION;
DELETE FROM ordertotals;
SELECT * FROM ordertotals;
ROLLBACK;
SELECT * FROM ordertotals;
```

- 上面例子中，`ROLLBACK` 语句回退了 `START TRANSACTION` 语句之后的所有语句
- `ROLLBACK` 只能在一个事务处理内使用（在执行一条 `START TRANSACTION` 命令之后）
- 在事务处理中，你不能回退 `SELECT`、`CREATE`、`DROP` 操作，如果你执行回退，它们也不会撤销


#### 17.3 使用 `COMMIT` 提交事务

一般 MySQL 语句都是直接针对数据库表执行和编写的，其提交操作都是自动进行的，即隐含提交（implicit commit）

在事务处理中，提交不会隐含的进行，必须使用 `COMMIT` 语句明确提交：

```
START TRANSACTION;
DELETE FROM orderitems WHERE order_num = 20010;
DELETE FROM orders WHERE order_num = 20010;
COMMIT;
```

- 当 `COMMIT` 或 `ROLLBACK` 语句执行后，事务会自动关闭

#### 17.4 使用保留点

简单的 `ROLLBACK` 和 `COMMIT` 语句可以撤销或写入整个事务处理，但是有时候我们还需要部分提交和回退

为了能支持回退部分事务处理，在事务处理块中合适的位置放置占位符，如果需要回退，可以回退到某个占位符，这些占位符称为保留点，可用 `SAVEPOINT` 语句创建保留点：

```
SAVEPOINT deletel;
```

每个保留点都必须有唯一的名字，以便使用 `ROLLBACK TO` 回退到指定点：

```
ROLLBACK TO deletel;
```

- 可以在代码中设置任意多的保留点，越多越好，这样可以灵活的进行回退
- 保留点在事务处理完成后自动释放，也可以用 `RELEASE SAVEPOINT` 明确地释放保留点

#### 17.5 更改默认的提交行为

上面说到，默认的 MySQL 行为会自动提交所有更改，为了指示 MySQL 不自动提交更改，需要使用以下语句：

```
SET autocommit=0;
```

- `autocommit` 标志决定是否自动提交更改
- `autocommit` 标志是针对每个连接而不是服务器的



参考：

- 《MySQL必知必会》

- [《MySQL必知必会》样例表导入方法](https://blog.csdn.net/qq120633269/article/details/88321137)