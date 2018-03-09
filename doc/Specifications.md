## Demo
### Framework
- MdReceiver
- TraderServer
- Strategy
### MdReceiver 
- Config File
```
ip = 
port = 
user = 
subscribeList = *
out = udp://192.168.1.101:8888
```

- Data Format
```
struct Data
{
price
volume
ask1
bid1
}
```

### Strategy
```
xxxxx
```


### TraderServer
```
ip
port
user
pwd =

in=tcp://192.168.1.101:9999
```

- Order Format
```
struct Order
{

}
```