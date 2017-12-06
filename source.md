# Part1 : 插头DP

### 从一道题讲起：

> 给你一个m * n的棋盘，有的格子是障碍，问共有多少条回路使得经过每个非障碍格子恰好一次 (m, n ≤ 12)

###  "基于连通性状态压缩的动态规划问题"

> ### Definition 1
> 插头 : 
> ![](http://images2017.cnblogs.com/blog/1099411/201712/1099411-20171202152641839-1649273081.jpg)

### 插头DP有两种实现方法：逐行和逐格
### 逐格不需要预处理出所有可行状态，较容易写

>#### 如图：
> ![](http://images2017.cnblogs.com/blog/1099411/201712/1099411-20171202153008761-987854215.jpg)


### 下面我们来关注这一个格子的转移
####状态：我们用一个三进制表示这一条轮廓上连通性
####括号表示法
####左括号：1，右括号：2
####For Example 该状态为：（0）（）  =>  10212
####分类讨论这个格子上的状态（若为障碍格，则只保留00的状态）
> + 00
> 生成两个个新的插头（11）
> ![](http://www.yhzq-blog.cc/wp-content/uploads/2017/03/83b897cf82530f952c9f69be1d304442.png)
> + 01 | 02（状态的延续）
> 该格子有两种选择：上下（10 | 20）或上右（01 | 02）
> ![](http://images.cnblogs.com/cnblogs_com/the-unbeatable/1124861/o_01.jpg)
> + 10 | 20（状态的延续）
> 同上，可以左下（10 | 20）或左右（01 | 02）
> + 11
> 连接两个联通分量（00）
> ![](http://www.yhzq-blog.cc/wp-content/uploads/2017/03/894f5d7da6a7acec6fdf3c4e8548c195.png)
> 这一步是$\mathcal{O(n)}$的，要找到匹配括号并修改其方向
> + 12
> 封口，统计答案
> ![](http://www.yhzq-blog.cc/wp-content/uploads/2017/03/7b37e741df899c3bc8aa50d74c9e877a.png)
> + 22（同11）
> + 21
> 连接两个联通分量
> ![](http://www.yhzq-blog.cc/wp-content/uploads/2017/03/899fecc55bc247d3f6ea69fa4c9c686c.png)

### 行与行的转移
> ![](http://images.cnblogs.com/cnblogs_com/the-unbeatable/1124861/o_aa.jpg)
> ```cpp
> for (int j = 1; j <= dp[cur].tot; j ++)
>      dp[cur].key[j] <<= 2;
> ```

### 复杂度
> + 除了11和22两种情况$\mathcal{O(n)}$，其它都是$\mathcal{O(1)}$的
> + 实际上总状态数远不到3^n，m=12时大约是14000个左右，是与2^m同阶
> + $O(nm·3^m)$

### 实现细节
> + 2进制
> + 哈希表

### 变式
> + 多条回路
> + 规定每个格子通过方向
> + 从左上角经过每个非障碍格子到达右下角
> + 无障碍，n ≤ 7，m <= 1e9，从左上角经过每个非障碍格子到达右下角
> + 哈密顿回路


## 一些例题
> ZJOI2007 多米诺骨牌 http://www.lydsy.com/JudgeOnline/problem.php?id=1435
有一个n × m 的矩形表格，其中有一些位置有障碍。现在要在这个表格内放一些1 × 2 或者2 × 1 的多米诺骨牌，满足任何相邻两行之间都有至少一个骨牌横跨，任何相邻两列之间也都至少有一个骨牌横跨。求有多少种不同的放 置方法，不需要放满所有没有障碍的格子。
1 ≤ n，m ≤ 15

### 参考
> https://wenku.baidu.com/view/f49801155f0e7cd18425368e.html?from=search
http://www.yhzq-blog.cc/%E6%8F%92%E5%A4%B4dp-%E4%BB%8E%E4%B8%8D%E4%BC%9A%E5%88%B0%E5%B4%A9%E6%BA%83/


#Part2：替罪羊树ScapegoatTree
### Template
> http://www.cnblogs.com/the-unbeatable/p/7136438.html
注：删除其实可以只是打一个标记，而不实际删除的，在rebuild时再删除

### 实现：
> ```cpp
> inline bool balance(int x) {
>   return ((double)max(sz[ch[x][0]], sz[ch[x][1]]) <= (double)sz[x] * a);
> }
> ```
> 每次插入后找到最高的不符合条件的点，将其子树暴力重建为最优形态

### 复杂度
>+ 树深
>$$  \alpha ^ {d(x)} · size(SGT) > size(x) $$
>$$  d(x) < log_{1 \over \alpha}size(SGT) $$
> #### Definition
> 节点x的势能为 $\phi(x) = |size[lc] - size[rc]|$
> 整棵树的总势能$\Phi(T)$为
> $$ \Phi(T) = \sum_{x ∈ T} \phi(x) $$

### 优势
> 重构,非旋转,能维护区间,树套树结构
> 带插入区间第k大

### Problem
> BZOJ3217 : ALOEXT
> Description : 维护序列,支持插入,查询区间第2大,区间中某数与给定数xor的最大值
> BZOJ WC2014 紫荆花之恋
> 带权树,x的点权为r(x),动态插入节点,查询整棵树中dis(i , j) <= r(i) + r(j) 的节点.

### 参考资料
> http://www.akira.ruc.dk/~keld/teaching/algoritmedesign_f07/Artikler/03/Galperin93.pdf
