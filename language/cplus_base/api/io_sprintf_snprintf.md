# sprintf和snprintf

- **sprintf函数：**

  ```
  #include <string>
  int sprintf(char *str, const char &format, ...);
  ```

  sprintf是字符串格式化命令，主要功能是把格式化的数据写入字符串str中，返回值为写入str的字节数，结束字符‘\0’不计入内。
  其中， str是指要写入的缓冲区，format控制要写入str中数据的格式，例如%s、%d、%x等。

- **snprintf函数：**

  ```
  int snprintf(char *str, size_t size, const char *format, ...);
  ```

  snprintf是字符串格式化命令，主要功能是把格式化的数据写入字符串str中，最多写size个字节，
  包括自动添加在字符串末尾处的结束字符‘\0’;返回值为写入str的字节数，包括结束字符‘\0’。

**Note：** 考虑到安全问题，应尽量使用sprintf代替snprintf

  sprintf可能会引起数组越界，如：

  ```
  char name1[6] = {'\0'}; //只能存储最多5个普通字符和末尾'\0'
  char name2[6] = {'\0'};

  //输出hello!，name1内存:hello!，末尾的'\0'保存到name1之外的第一个空间
  //如果此时name1相邻的内存中有数据，它将被结束字符'\0'覆盖，造成异常，但是这种异常不会引起编译器报错
  sprintf(name1, "%s", "hello!");
  ```    

  使用snprintf解决越界问题：
  ```
  snprintf(name2, sizeof(name2), "%s", "hello!"); //输出hello，name2内存中保存为hello'\0'
  ```
