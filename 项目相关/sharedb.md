#### sharedb

sharedb将websocket发送的消息都视为操作。每当收到websocket的操作，交给OT算法得到最终结果，广播通知所有正在监听的websocket。

用户收到后更新本地文档副本。

##### OT（Operational Transformation）

sharedb的核心。一种算法，能够将多个操作进行冲突合并，保持文档的一致性。

