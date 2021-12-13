# 离散数学 II 实验一

## 实验题目

可简单图化、连通图、欧拉图和哈密顿图的判断

## 实验目的

1. 掌握可简单图化的定义及判断方法；
2. 掌握连通图、欧拉图的判断方法；
3. 掌握欧拉回路的搜索方法；
4. 了解欧拉图的实际应用。

## 实验要求

1. 给定一非负整数序列（例如：(4,2,2,2,2)）。
2. 判断此非负整数序列是否是可图化的，是否是可简单图化的。
3. 如果是可简单图化的，根据 Havel 定理过程求出对应的简单图，并输出此图。
4. 判断此简单图是否是连通的。
5. 如果是连通图，判断此图是否是欧拉图。如果是欧拉图，请输出一条欧拉回路（输出形式如：v2->v1->v5->v3->v4->v5->v2）。
\*说明：要求学生设计的程序不仅对给定非负整数序列得出正确结果，还要对教师测试数据集得出正确结果。

## 实验内容和实验步骤

1. 考虑到要读入度数序列，每个节点有相应的索引值，因此定义一个结构体 *node* 来储存对应内容

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132109991.png" alt="image-20211213200627796" style="zoom:50%;" />

2. 所有函数，成员皆在类内定义，因此创建 *solution* 类

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132109972.png" alt="image-20211213200830276" style="zoom:50%;" />

3.  *main* 函数中实例化类，读入并初始化度数序列

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132109370.png" alt="image-20211213200945729" style="zoom:50%;" />

4. 判断此度数列是否可图化、可简单图化，如果度数和为基数，则不可图化，也不能简单图化。如果可图化，继续判断是否可简单图化，先判断最大度是否小于等于n-1，不满足则不可简单图化，

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132110568.png" alt="image-20211213201252178" style="zoom:50%;" />

接着使用**Havel的等价定理**

- `d1 + d2 + … + dn = 0 (mod 2)`
- `d1 + d2 + … + dr ≤ r(r-1) + min(r,dr+1) + min(r,dr+2) + … + min(r,dn)`

满足以上二条件，则可简单图化

5. Havel定理分步求简单图

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132110586.png" alt="image-20211213203334582" style="zoom:50%;" />




## 实验测试数据、代码及相关结果分析


## 实验总结
