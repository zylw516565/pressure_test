# PressureTest is a TCP client simulation and pressure testing tool based on the Muduo network library

# PressureTest 是一个基于Muduo网络库的TCP客户端模拟和压测工具
## 工具配置:
  压测工具的配置文件位于etc\PressureTest.ini. 使用之前应先进行配置。
  配置项说明: 
    ip, port,是被压测服务的IP地址和端口
    threadcount设定客户端启动线程数
    sessioncount,指定客户端使用多少连接对服务进行压测

## 启动方法与说明:
  ./run.sh 1 0.00001 10
  run.sh脚本后面的启动参数说明:
  1:代表登录后1s开始压测,  (默认为1s,不建议修改)
  0.00001: 代表0.00001s(即10us)发送一次请求,使用此参数调整压测的QPS
  10: 代表总压测时长10s. 10s后程序自动结束

## 压测结果:
  程序结束后,在最后的日志输出中,会输出如下类似日志.
  TotalReqCount [15107], TotalRspCount[15103], QPS[1510], totalPressureTime_[10]
  TotalReqCount: 总请求数
  TotalRspCount: 总响应数
  totalPressureTime_: 总压测时长
  QPS: 每秒查询数,反映了性能指标.

## 备注
本工具暂不支持SSL连接的压测.
