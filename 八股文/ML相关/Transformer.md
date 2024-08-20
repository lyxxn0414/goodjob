## Transformer

### 整体结构

组成：encoder+decoder

![img](https://pic4.zhimg.com/80/v2-4544255f3f24b7af1e520684ae38403f_1440w.webp)

1. 将句子拆分成多个词向量，分别和自己的位置embedding相加，得到向量矩阵。
   ![img](https://pic4.zhimg.com/80/v2-7dd39c44b0ae45d31a3ae7f39d3f883f_1440w.webp)

2. 经过encode block得到输出编码矩阵，NxD(n是单词个数)
   ![img](https://pic3.zhimg.com/80/v2-45db05405cb96248aff98ee07a565baa_1440w.webp)
3. 解码。根据单词1-i的结果翻译i+1.有一个mask盖住下面的单词
   ![img](https://pic2.zhimg.com/80/v2-5367bd47a2319397317562c0da77e455_1440w.webp)

### 输入

单词embedding：可以通过word2vec等预训练得到。

位置embedding：由于Transformer用的不是RNN，而是**全局信息**，**不能保持单词位置信息**。

一般用一个和位置相关的公式计算得到。

![img](https://pic3.zhimg.com/80/v2-8b442ffd03ea0f103e9acc37a1db910a_1440w.webp)

### 自注意力机制

计算文本之间的相似度

skip connect:残差连接。**将输出表述为输入和输入的一个非线性变换的线性叠加**。

防止网络退化。

![img](https://pic4.zhimg.com/80/v2-f6380627207ff4d1e72addfafeaff0bb_1440w.webp)

多头注意力：由多个self-attention组成。上方还有一个add&norm（残差连接+归一化）