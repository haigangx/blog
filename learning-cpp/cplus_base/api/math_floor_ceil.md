# floor()和ceil()

- **向下取整：floor函数**

  floor(x)，其功能是“向下取整”，或者说“向下舍入”，即取不大于x的最大整数（与“四舍五入”不同，下取整是直接取按照数轴上最接近要求值的左边值）

  ```
  #include <math.h>
  double floor( double arg );
  ```

  例:

  ```
  floor(3.14) = 3.0
  floor(9.999999) = 9.0
  floor(-3.14) = -4.0
  floor(-9.999999) = -10.0
  ```

- **向上取整：ceil函数**

  ceil(x)，其功能是向上取整，即取大于或者等于指定表达式的最小整数，即取按照数轴上最接近要求值的右边值

  ```
  #include <math.h>
  double ceil( double x );
  ```

  例：

  ```
  ceil(3.14) = 4.0
  ceil(9.999999) = 10
  ceil(-3.14) = -3.0
  ceil(-9.999999) = -9.0
  ```