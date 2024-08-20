### CPU架构

#### CPU Cache缓存

Cache由多个Cache Line组成

![图片](https://mmbiz.qpic.cn/mmbiz_png/J0g14CUwaZf0RnQxwibdcyFOTw0NvInPPqq0bdialqhibQeqDqhQEChs66jiaSS6Is6bsVChd7h8Edcr6ics7hHFSWQ/640?wx_fmt=png&tp=wxpic&wxfrom=5&wx_lazy=1&wx_co=1)

#### Cache和Memory同步

**write back**:只将数据写到cache block中，**只有当修改过的cache block被替换时才写入内存**。



![图片](https://mmbiz.qpic.cn/mmbiz_png/J0g14CUwaZf0RnQxwibdcyFOTw0NvInPP4mia18R69AbGx4dxQfekrlm0GIpBf4TZeGlFl5uzoEvmCwo3ibfr26mA/640?wx_fmt=png&tp=wxpic&wxfrom=5&wx_lazy=1&wx_co=1)



#### Cache Coherence

**MESI协议**：

- *Modified*，已修改：即上文中的dirty
- *Exclusive*，独占：只有该CPU的Cache拥有该数据，不存在cache coherence问题
- *Shared*，共享：多个CPU的Cache上有该数据。
- *Invalidated*，已失效：当在共享状态下，有CPU修改了对应的Cache Line，其它CPU Cache Line失效。

状态转换：

已修改和独占情况下不需要通过**总线嗅探**通知其它CPU.

共享状态时：修改前必须先通知其它CPU Cache改行**已失效**，然后标记为Modified并修改。

已失效：读：通知持有该数据且标记为M的cache**更新到内存**，从内存读，并都变为S。（也有可能只剩它了，就变成E）

写：先让为M的Cache将数据写回内存，自己再从内存拿取，并写到Cache，标记为M。（其它人变I）

![图片](https://mmbiz.qpic.cn/mmbiz_png/J0g14CUwaZf0RnQxwibdcyFOTw0NvInPP3P2XZDHKy7EzWzfnOUugqByGVarxSnst6y78DkSmNHksLMlcd2Vlpg/640?wx_fmt=png&tp=wxpic&wxfrom=5&wx_lazy=1&wx_co=1)



##### 伪共享问题

如果多个Cache缓存了同一数据并经常做读写（主要是写），会导致**CPU Cache失效**的问题（要经常write back）

避免伪共享：让经常被读写的变量不要在同一个Cache Line。





#### CPU和GPU

1. 架构上：CPU是**通用计算**设备，GPU转为**并发多任务**而生。（最大的特点：核多，其它部分精简。）

![图片](https://mmbiz.qpic.cn/mmbiz_png/9BK2WL6kfcRXJEh4vVFVpISFwwaRAmv2aZgO3zGlNwbAJsBibczY5ZNtDlOZxPTL7BgOovx7aRfKJFBjL3DyF1w/640?wx_fmt=png&tp=wxpic&wxfrom=5&wx_lazy=1&wx_co=1)

CPU部分cache和控制部分占了很大面积，计算单元占比很少；

GPU只有很简单的控制单元，剩下的**大部分都被计算单元占据**。（但**核的能力并不强**）

（多个小学生一起做加减法。）

2. 工作方式：CPU：多指令多数据。同一时间，核上可以运行不同的机器指令。

   GPU：单指令多数据（SIMD）。所有核必须执行的是同一个指令，但可以操作不同的数据。

3. 指令集：GPU非常简单，只做计算。CPU还需要负责内存管理，中断处理，I/O等。

   CPU与GPU的协作方式：只将计算交给它。

   ![image-20240307000403851](C:\Users\pc\AppData\Roaming\Typora\typora-user-images\image-20240307000403851.png)
   
   GPU采用了数量**众多的计算单元**和**超长的流水线**，但只有非常**简单的控制逻辑**并**省去了Cache**。
   
   GPU面对的则是**类型高度统一**的、**相互无依赖**的**大规模**数据和**不需要被打断**的纯净的计算环境。

### GPU

和CPU相比更大的SIMD，更大的寄存器，更多的核，更小的控制单元，没有cache。

通过提供大量线程来进行并行执行。



工作流程：

1. 顶点处理
2. 光栅化计算（矢量变像素）
3. 纹理贴图（类似多边形表面贴上图片）
4. 像素处理（确定每个像素的最终属性）

![img](https://pic1.zhimg.com/80/v2-6d9b9a359ced210dc397d616335a8c78_1440w.webp)

有一个Giga Thread Engine来管理正在进行的工作。

GPU被分为8个GPC（图形处理簇），GPC内部有多个SM和一个光栅化引擎。部件通过总线相连

#### SM

**流处理器（Streaming Multiprocessors, SMs）**: SM是GPU核心的**基本计算单元**，包含**若干个执行核心**，用于处理浮点运算、整数运算等。每个SM可以并行执行数百个线程，提高计算吞吐量。

每个SM可以包含64个warp（线程束，有32个线程）。~~每4个warp可以进行并发执行？~~

线程可以在不同的warp上进行调度。

里面包含

1. Cuda Core，Tensor Core等计算加速单元
2. 负责调度warp的warp scheduler
3. dispatch unit：根据指令，将线程分发到具体的执行单元（1中的计算单元）
4. 多级缓存
5. 寄存器
6. 访问存储单元(LD/ST)，负责数据处理。

![img](https://pic1.zhimg.com/80/v2-c92f968ec9cdb40a01a26f2ea1572df0_1440w.webp)

A100中有108个SM



##### Cuda Core=》取消

SM的核心。一个SM中有两组，各16个cuda core，包含一个浮点运算单元和一个整点运算单元。

取消原因：SM可以支持int和浮点并发执行。分成了INT Core和FP core（听起来像是1拆2了）

![image-20240314002606932](C:\Users\pc\AppData\Roaming\Typora\typora-user-images\image-20240314002606932.png)





计算强度(compute intensity)：描述计算强度=内存访问量 (字节)/浮点操作数 (FLOPs)。（计算操作/内存操作）

##### Warp

SM**基本执行单元**。从硬件上来说，并非每个thread都能在同一时刻同时执行。

warp中32个线程执行SIMT模式，以锁步方式执行同一条指令，但是操作不同的数据。

#### CUDA

compute unified device architecture

并行计算架构和编程模型，编程体系。 还提供了对其它编程语言的支持。

更好地完成软硬件解耦。

##### Kernel（核函数）

cuda文件中通过调用核函数进行并行计算。

**一个kernel执行时启动的所有线程称为一个grid**

##### Thread Block

grid中包含多个thread block.

代表一组**同时执行的线程**。线程块内的线程可以**协作**执行复杂任务。

它们**共享SM内的快速共享内存**（减少对全局内存的依赖），能够进行同步操作和数据交换。

每个线程有自己的寄存器。

##### 和GPU硬件架构的对应

一个thread block在一个SM上被warp engine调度，thread会被分配到cuda core上执行。

一个kernel可能需要多个SM。

![image-20240314005727331](C:\Users\pc\AppData\Roaming\Typora\typora-user-images\image-20240314005727331.png)

#### 内存结构

![image-20240313234719858](C:\Users\pc\AppData\Roaming\Typora\typora-user-images\image-20240313234719858.png)

从显存(high bandwidth mem)到L1 Cache，带宽逐渐增加，延迟逐渐减小。

为什么不用CPU 内存？PCIe传输过来的延迟很高，跟不上GPU的高带宽传输速度和计算速度。

