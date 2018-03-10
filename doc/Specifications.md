## Demo
### Framework
分为三个程序来实现
- MdReceiver
- TraderServer
- Strategy

### MdReceiver 
实现接收数据，并将数据转化成统一的数据结构广播到其他的Strategy进程（out）   
同一时刻只有一个在运行着的MdReceiver
- Config.ini
```
ip = 
port = 
user = 
subscribeList = *
out = udp://192.168.1.101:8888
...
```
- DataFormat.h
```
struct Data
{
price
volume
ask1
bid1
...
}
```
- MdEngine.h
```
subscribe()
onRtnDepthMarketData()
...
```
- MdEngine.cpp

### Strategy
Strategy模块接收来自MdReceiver的数据，并根据数据进行处理，选择下单撤单等。
同一时刻可以有多个运行着的策略
- Config.ini
```
in :
out :`
```
- Strategy.h
```
onMarketData()
onTrade()
onOrder()
insertOrder()
...
```
- Strategy.cpp
### TraderServer
接收来自策略模块的发单撤单请求，并与Ctp直接交互。将Trader的数据结构统一（为
适应不同的期货交易API），需要实现一个Adapter
一个TraderServer只运行着一个帐号
- Config.ini
```
ip
port
user
pwd =
in=tcp://192.168.1.101:9999
```
- OrderFormat.h
```
struct ReqOrder
{
BrokerId
LimitPrice
Volume
}
```
- TdEngine.h
```
reqOrderInsert(ReqOrder, ...)
onOrder(RtnOrder, ...)
onTrade(RtnTrade, ...)
```
- TdEngine.cpp

###数据流
    MarketData: MdReciever -> Strategy 
    OrderData: TraderServer -> Strategy 
   
### 关于统一数据结构的OrderFomat.h DataFormat.h
    实现起来较为麻烦，需要对业务很了解和熟悉多个平台的API，所以建议直接用别人的已经写好的。
    可以参考本项目中的include/wzadapter中的文件