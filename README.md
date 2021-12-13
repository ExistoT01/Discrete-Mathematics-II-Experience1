# 离散数学 II 实验一（实验报告）

20020007095-叶鹏

盛艳秀-老师

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

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132128152.png" alt="image-20211213211727191" style="zoom: 80%;" />

4. 判断此度数列是否可图化、可简单图化，如果度数和为基数，则不可图化，也不能简单图化。如果可图化，继续判断是否可简单图化，先判断最大度是否小于等于n-1，不满足则不可简单图化，

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132110568.png" alt="image-20211213201252178" style="zoom:50%;" />

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132128186.png" alt="image-20211213211759825" style="zoom:80%;" />

接着使用**Havel的等价定理**

- `d1 + d2 + … + dn = 0 (mod 2)`
- `d1 + d2 + … + dr ≤ r(r-1) + min(r,dr+1) + min(r,dr+2) + … + min(r,dn)`

满足以上二条件，则可简单图化

5. Havel定理分步求简单图

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132110586.png" alt="image-20211213203334582" style="zoom:50%;" />

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132128323.png" alt="image-20211213211824476" style="zoom:80%;" />

6. Havel定理构造简单图，用邻接矩阵表示，采用贪心思想构造出最简的简单图

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132120857.png" alt="image-20211213211943636" style="zoom:50%;" />

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132128343.png" alt="image-20211213211959581" style="zoom:80%;" />

7. 求从1 \~ n-1的邻接矩阵幂之和B~n-1~，若B~n-1~中不存在0，则说明n个节点都**至少存在一条长度为1 \~ n-1的通路到另一节点**，说明图连通，反之说明不连通

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132130615.png" alt="image-20211213213037009" style="zoom:50%;" />

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132129151.png" alt="image-20211213212951285" style="zoom:80%;" />

8. 如果图连通，检查度数列，记录奇数顶点数，若存在奇数顶点，则说明不存在欧拉回路，若没有奇数顶点，再进行下一步判断

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132132669.png" alt="image-20211213213128768" style="zoom:50%;" />

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132132566.png" alt="image-20211213213235140" style="zoom:80%;" />


9. Fleury算法求欧拉回路，如非不要不走割边，搜索不是割边的边并扩展，如果没有点可以扩展，输出并出栈，否则 dfs 继续搜索欧拉路径

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132135603.png" alt="image-20211213213408892" style="zoom:50%;" />

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132135491.png" alt="image-20211213213541720" style="zoom:80%;" />

10. 程序结束




## 实验测试数据、代码及相关结果分析

### 源代码

程序代码如下

```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

const int maxn = 50;


struct Node {
	int id, degree;
};

bool cmp(Node a, Node b) {
	return a.degree > b.degree;
}


int tem[maxn][maxn];



class solution {
public:
	bool canSimpleGraphRealization;
	bool isConnected;

	Node* node = new Node[maxn];
	int stk[maxn];


	int n;
	int top;

	int adjMatrix[maxn][maxn];
	int sumLink[maxn][maxn];



	//constructor
	solution(int n) {
		this->n = n;
		this->canSimpleGraphRealization = false;
		this->isConnected = true;
		memset(adjMatrix, 0, sizeof(adjMatrix));
		memset(sumLink, 0, sizeof(sumLink));
		memset(tem, 0, sizeof(tem));
	}

	~solution() {
		delete[] node;
	}

	void display(Node* node);

	void initialList() {
		cout << endl;
		cout << "#==========读入度数序列" << endl;
		cout << endl;

		for (int i = 1; i <= n; i++)
		{
			cin >> node[i].degree;
			node[i].id = i;
		}
	}

	void copyList(Node* targetNode) {
		for (int i = 1; i <= n; i++)
		{
			targetNode[i].degree = node[i].degree;
			targetNode[i].id = node[i].id;
		}
	}

	void checkGraphRealization(Node* node, int n);
	void Havel(Node* node, int n);
	bool allZERO(Node* node, int s, int n);
	bool buildSimpleGraph(Node* node, int n);
	void checkConnected(Node* node, int n);
	void clearTemLink();
	void fleury(int startIndex);
	void dfs(int x);

};

//displaydegree
void solution::display(Node* node) {
	for (int i = 1; i <= n; i++)
	{
		cout << "degree[" << i << "]" << "= " << node[i].degree << endl;
	}
}

void solution::checkGraphRealization(Node* node, int n) {

	cout << endl;
	cout << "#==========判断是否可图化/可简单图化" << endl;
	cout << endl;

	int sum = 0;

	//先判断是否可图化
	for (int i = 1; i <= n; i++)
	{
		sum += node[i].degree;
	}

	if (sum % 2) {
		cout << "不可图化，亦不可简单图化" << endl;
		return;
	}


	//如果可图化，继续判断是否可简单图化

	cout << "可图化";

	sort(node + 1, node + n + 1, cmp);

	//先判断最大度是否小于等于n-1
	if (node[0].degree > n - 1) {
		cout << ",不可简单图化" << endl;
		return;
	}

	else {
		for (int r = 1; r <= n; r++)
		{
			int left = 0;
			for (int index = 1; index <= r; index++)
			{
				left += node[index].degree;
			}

			int right = r * (r - 1);
			for (int index = r + 1; index <= n; index++)
			{
				right += min(r, node[index].degree);
			}

			//如果不满足
			if (left > right) {
				cout << ",不可简单图化" << endl;
				return;
			}
		}
	}

	//如果都没问题，则可以简单图化
	cout << ",可简单图化" << endl;
	canSimpleGraphRealization = true;


}

void solution::Havel(Node* node, int n) {
	cout << endl;
	cout << "#==========Havel定理求对应简单图" << endl;
	cout << endl;


	Node* fakeNode = new Node[n+1];
	
	copyList(fakeNode);

	int lptr, rptr;
	lptr = 1;
	rptr = n;
	cout << "(";
	for (int i = lptr; i <= rptr; i++)
	{
		cout << fakeNode[i].degree;
		if (i != rptr) cout << ", ";
	}
	cout << ")";
	cout << "可简单图化" << endl;

	while (!allZERO(fakeNode, lptr, rptr))
	{

		//cout << endl << "lptr=" << lptr << endl;
		for (int i = lptr + 1; i <= lptr + fakeNode[lptr].degree; i++)
		{
			fakeNode[i].degree -= 1;
		}


		//cout << "before ";
		//display();

		sort(fakeNode+1+lptr, fakeNode+1+n, cmp);

		lptr++;

		//cout << "after ";
		//display();

		cout << "<=>";
		cout << "(";
		for (int i = lptr; i <= rptr; i++)
		{
			cout << fakeNode[i].degree;
			if (i != rptr) cout << ", ";
		}
		cout << ")";
		cout << "可简单图化" << endl;
	}

	delete[] fakeNode;
}

bool solution::allZERO(Node* node, int s, int n) {
	int sum = 0;
	for (int i = s; i <= n; i++)
	{
		sum += node[i].degree;
	}
	if (!sum)
		return true;
	else
		return false;
}

bool solution::buildSimpleGraph(Node* node, int n)
{
	cout << endl;
	cout << "#==========Havel定理构造对应简单图(邻接矩阵)" << endl;
	cout << endl;

	Node* fakeNode = new Node[n + 1];

	copyList(fakeNode);

	//display(fakeNode);


	for (int i = 1; i <= n; i++)
	{
		sort(fakeNode + i, fakeNode + n + 1, cmp);
		if (fakeNode[i].degree > n - i) return false;
		for (int j = i + 1; j <= i + fakeNode[i].degree; j++)
		{
			if (!fakeNode[j].degree) return false;
			fakeNode[j].degree--;
			adjMatrix[fakeNode[i].id][fakeNode[j].id] = 1;
			adjMatrix[fakeNode[j].id][fakeNode[i].id] = 1;
		}
		fakeNode[i].degree = 0;
	}

	cout << "index";
	for (int i = 1; i <= n; i++)
	{
		printf("%5d", i);
	}
	cout << endl << endl;

	for (int i = 1; i <= n; i++) {
		printf("%5d", i);
		for (int j = 1; j <= n; j++) {
			printf("%5d", adjMatrix[i][j]);
		}			
		cout << endl;
	}	

	delete[] fakeNode;

	return true;
}

void solution::clearTemLink() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			tem[i][j] = adjMatrix[i][j];
		}
	}
}

void solution::checkConnected(Node* node, int n)
{
	cout << endl;
	cout << "#==========检查图是否连通" << endl;
	cout << endl;

	for (int t = 1; t < n; t++)
	{
		clearTemLink();
		int tt = t;
		while (tt-1)
		{
			int ans[maxn][maxn];
			memset(ans, 0, sizeof(ans));

			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					for (int k = 1; k <= n; k++) {
						ans[i][j] += adjMatrix[i][k] * tem[k][j];
					}
				}
			}

			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= n; j++)
				{
					tem[i][j] = ans[i][j];
				}
			}

			tt--;
		}

		cout << "A^" << t << " = " << endl;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				printf("%5d", tem[i][j]);
			}
			cout << endl;
		}
		cout << endl;
		
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				sumLink[i][j] += tem[i][j];
			}
		}

	}

	cout << "B^" << n - 1 << " = " << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%5d", sumLink[i][j]);
		}
		cout << endl;
	}

	for (int i = 1; i <= n && isConnected; i++) {
		for (int j = 1; j <= n && isConnected; j++) {
			if (i != j) {
				if (sumLink[i][j] == 0) {
					cout << endl << "不连通" << endl;
					isConnected = false;
				}
			}
		}
	}

	if (isConnected) {
		cout << endl << "连通" << endl;
	}
}


void solution::dfs(int x) {
	stk[top++] = x;
	for (int i = 1; i <= n; ++i) {
		if (adjMatrix[x][i]) {
			adjMatrix[x][i] = adjMatrix[i][x] = 0; // 删除此边
			dfs(i);
			break;
		}
	}
}


void solution::fleury(int startIndex) {
	cout << endl;
	cout << "#==========搜索欧拉回路" << endl;
	cout << endl;

	//cout << "start = " << startIndex << endl;

	int brige;
	top = 0;
	stk[top++] = startIndex; // 将起点放入Euler路径中
	while (top > 0) {
		brige = 1;
		for (int i = 1; i <= n; ++i) { // 试图搜索一条边不是割边（桥） 
			if (adjMatrix[stk[top - 1]][i]) {
				brige = 0;
				break;
			}
		}
		if (brige) { // 如果没有点可以扩展，输出并出栈
			cout << "v" << stk[--top] << " -> ";
		}
		else { // 否则继续搜索欧拉路径
			dfs(stk[--top]);
		}
	}
	cout << "done." << endl;
}



int main() {

	cout << "#==========读入序列长度" << endl;
	cout << endl;
	int n;
	int oddNum = 0;
	
	cout << "n = ";
	cin >> n;

	solution method(n);

	method.initialList();

	method.checkGraphRealization(method.node, n);

	//如果可简单图化，根据 Havel 定理过程求出对应的简单图，并输出此图
	if (method.canSimpleGraphRealization) {
		method.Havel(method.node, n);

		//如果可简单图化，根据 Havel 定理构造对应简单图
		if (method.canSimpleGraphRealization)method.buildSimpleGraph(method.node, n);
		
		//检查是否连通
		method.checkConnected(method.node, n);
	
		//连通，求欧拉回路
		int startIndex = 1;

		//method.display();

		if (method.isConnected) {
			for (int i = 1; i <= n; i++)
			{
				if (method.node[i].degree % 2) {
					oddNum++;
					startIndex = i;
				}
			}

			cout << endl;
			cout << "#==========检查是否有欧拉回路" << endl;
			cout << endl;

			if (oddNum == 0) {
				cout << "有欧拉回路！" << endl;
				method.fleury(startIndex);
			}
			else {
				cout << "没有欧拉回路！" << endl;
			}
		}

	}
	

	return 0;
}
```

### 测试数据

从民间收集了5个具有代表性的测试数据

#### case 1

- input
  `3, 3, 2, 2, 1`

- output

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132142652.png" alt="image-20211213214226816" style="zoom:80%;" />

#### case 2

- input
  `3, 3, 2`
- output

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132148896.png" alt="image-20211213214336710" style="zoom:80%;" />

#### case 3

- input
  `1, 1, 1, 1`
- output

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132148766.png" alt="image-20211213214604678" style="zoom: 80%;" />

#### case 4

- input
  `3, 2, 2, 1`
- output

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132149966.png" alt="image-20211213214730768" style="zoom:80%;" />

#### case 5

- input
  `3, 2, 2, 1`
- output

<img src="https://expicture.oss-cn-beijing.aliyuncs.com/img/202112132149362.png" alt="image-20211213214843142" style="zoom:80%;" />

## 实验总结

本次实验，通过动手编写程序，掌握了可简单图化的定义，连通图、欧拉图的判断方法，欧拉回路的搜索方法，熟悉了Havel定理以及Fleury算法，首次系统地将离散数学的理论知识应用到程序实践上，加深对图论知识的印象，锻炼了代码能力。
