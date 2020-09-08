# MySQL 基础 

<!-- TOC -->

- [一、数据库概念](#一数据库概念)
- [二、MySQL 操作](#二mysql-操作)
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
    - [4. 过滤数据 `WHERE`](#4-过滤数据-where)
    - [5.](#5)

<!-- /TOC -->

## 一、数据库概念

## 二、MySQL 操作

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

### 4. 过滤数据 `WHERE`

### 5. 


参考：

- 《MySQL必知必会》

- [《MySQL必知必会》样例表导入方法](https://blog.csdn.net/qq120633269/article/details/88321137)