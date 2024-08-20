### Redis

#### 是什么

Redis 是一种基于内存的数据库，对数据的读写操作都是在内存中完成，因此**读写速度非常快**，常用于**缓存，消息队列、分布式锁等场景**。

#### 和Memorycached比较

**共同点**：

1. 都是基于**内存**的数据库，一般都用来当做缓存使用。
2. 都有**过期**策略。
3. 两者的性能都非常高。

Redis 与 Memcached **区别**：

- Redis 支持的**数据类型更丰富**（String、Hash、List、Set、ZSet），而 Memcached 只支持最简单的 key-value 数据类型；
- Redis 支持**数据的持久化**，可以将内存中的数据保持在磁盘中，重启的时候可以再次加载进行使用，而 Memcached 没有持久化功能，数据全部存在内存之中，Memcached 重启或者挂掉后，数据就没了；
- Redis 原生支持集群模式，Memcached 没有原生的集群模式，需要依靠客户端来实现往集群中分片写入数据；
- Redis 支持**发布订阅模型**、Lua 脚本、**事务**等功能，而 Memcached 不支持；

#### 为什么作为Mysql缓存

高性能：快

高并发：单机redis的QPS（Query per second）是mysql的十倍。