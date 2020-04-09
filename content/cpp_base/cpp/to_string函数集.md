# C++ to_string函数集

- **函数原型：**

  ```
  string to_string (int val);
  string to_string (long val);
  string to_string (long long val);
  string to_string (unsigned val);
  string to_string (unsigned long val);
  string to_string (unsigned long long val);
  string to_string (float val);
  string to_string (double val);
  string to_string (long double val);
  ```

- **功能：**

  将数值转化为字符串。返回对应的字符串。

- **例子：**

  ```
  #include <iostream>   
  #include <string>     
  using namespace std;

  int main()
  {
      string pi = "pi is " + std::to_string(3.1415926);
      string perfect = to_string(1 + 2 + 4 + 7 + 14) + " is a perfect number";
      cout << pi << '\n';
      cout << perfect << '\n';
      return 0;
  }
  ```

