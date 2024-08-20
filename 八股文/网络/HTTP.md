### HTTP



#### WebSocket

http不能有效解决的场景：需要服务端**主动**给客户端发信息。

解决扫码问题：

轮询http：隔一段时间客户端询问一次服务端。

长轮询机制：在较长时间内等待服务器响应。



http协议：**同一时间里**，客户端和服务器**只能有一方主动**发数据，这就是所谓的**半双工**。

没有利用TCP全双工的特性，双方都能主动发消息。

##### 怎么用

三次握手后再**两次握手**。

三次握手建立连接后，第一次统一用HTTP通信，客户端在请求里带上特殊header：

```tex
Connection: Upgrade
Upgrade: WebSocket
Sec-WebSocket-Key: T2a6wZlAwhgQNqruZ2YUyg==\r\n
```

包含升级websocket的请求和一串base64码。

服务器收到后如果支持websocket，则通过公开算法和base64码生成一个字符串，与浏览器生成的字符串比对。

![图片](https://cdn.xiaolincoding.com//mysql/other/117eebe06cc6b35ded3216a95706f080.png)

#### HTTP和HTTPS

区别：

1. HTTP是明文传输的，不安全，HTTPS在TCP和应用层间加了一个TLS/SSL的安全协议做**加密**
2. HTTP建立连接更简单，HTTPS在TCP三次握手后还要进行TLS/SSL的握手。
3. 默认端口：HTTP是80，HTTPS是443
4. HTTPS协议需要向权威机构申请证书，确保服务器身份可靠。



三个风险：

窃听，篡改，冒充



HTTPS怎么解决的：

加密，校验，身份验证（数字证书）



存储。上层查询。

实验：开发做了变更后，时长有没有变化。新的数据应该怎么存。

差异是否显著=》统计推断（方差，假设检验等

数据的策略分析