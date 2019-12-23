# ifstat

ifstat(interface statistics)：简单的网络流量监测工具
常用选项如下：
-a 监测系统上的所有网卡接口
-i 指定要监测的网卡接口
-t 在每行输出信息前加上时间戳
-b 以Kbit/s为单位显示数据，而不是默认的KB/s
delay 采样间隔(单位为s)，即每隔delay的时间输出一次统计信息
count 采样次数，即共输出count次统计信息
