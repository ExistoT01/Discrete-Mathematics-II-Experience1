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

	void display();

	void initialList() {
		cout << endl;
		cout << "#==========读入度数序列" << endl;
		cout << endl;

		for (int i = 1; i <= n; i++)
		{
			cin >> node[i].degree;
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
void solution::display() {
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


	for (int i = 1; i <= n; i++)
	{
		sort(fakeNode + 1 + i, fakeNode + n + 1, cmp);
		if (fakeNode[i].degree > n - i) return false;
		for (int j = i + 1; j <= i + fakeNode[i].degree; j++)
		{
			if (!fakeNode[j].degree) return false;
			fakeNode[j].degree--;
			adjMatrix[i][j] = 1;
			adjMatrix[j][i] = 1;
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
	cout << "#==========检查图是否联通" << endl;
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
					cout << endl << "不联通" << endl;
					isConnected = false;
				}
			}
		}
	}

	if (isConnected) {
		cout << endl << "联通" << endl;
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
		
		//检查是否联通
		method.checkConnected(method.node, n);
	
		//联通，求欧拉回路
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