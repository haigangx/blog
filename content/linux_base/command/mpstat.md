# mpstat

mpstat(multi-processor statistics)：实时监测多个处理器系统上每个CPU的使用情况
mpstat的典型用法是：
mpstat [-P {|ALL}] [interval [count]]
P 指定要监控的CPU号(0~CPU个数-1)，ALL表示监听所有CPU
interval：采样间隔(单位是s)，即每隔interval的时间输出一次统计情况
count：采样次数，即共输出count次统计信息