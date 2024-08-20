### Docker

#### 隔离环境和资源限制

##### namespace

Docker 使用 Linux 的命名空间（**namespaces**）功能来提供隔离的工作环境。命名空间确保一个容器的进程**看不到系统上的其他进程**，从而在进程树、网络接口、挂载点、用户ID等方面提供隔离。

- **PID Namespace**：隔离进程ID，每个容器都有自己的 PID 1。
- **Net Namespace**：提供独立的网络环境，如 IP 地址、路由表等。
- **IPC Namespace**：隔离 System V IPC 和 POSIX 消息队列。
- **MNT Namespace**：隔离挂载点。
- **User Namespace**：隔离用户和用户组ID，允许容器内的用户映射到宿主机上不同的用户。



#### Cgroups 

Docker 使用 Linux 的控制组（cgroups）功能来限制、记录和隔离容器可以使用的物理资源（如 CPU、内存、磁盘I/O等）。通过cgroups，Docker 可以确保单个容器或一组容器不会消耗过多的资源，从而影响到系统上的其他容器或宿主机的正常运行。主要的资源限制包括：

- **CPU**：限制容器可以使用的CPU时间比例或核心数。
- **内存**：限制容器可以使用的最大内存量。
- **磁盘I/O**：限制容器的读写速率。
- **网络**：虽然网络带宽限制不直接通过cgroups实现，但Docker可以使用类似tc（traffic control）这样的工具来限制网络流量。