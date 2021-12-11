#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 50;



bool cmp(int a, int b) {
	return a > b;
}

struct node {
	int id, nb;
}frog[maxn];

bool operator<(const node& a, const node& b) {
	return a.nb > b.nb;
}

int link[maxn][maxn];
int sumLink[maxn][maxn];
int tem[maxn][maxn];


bool build(int n)
{
	
	memset(link, 0, sizeof(link));
	memset(sumLink, 0, sizeof(sumLink));
	memset(tem, 0, sizeof(tem));
	for (int i = 0; i < n; i++)
	{
		sort(frog + i, frog + n);
		if (frog[i].nb > n - i - 1) return false;
		for (int j = i + 1; j <= i + frog[i].nb; j++)
		{
			if (!frog[j].nb) return false;
			frog[j].nb--;
			link[frog[i].id][frog[j].id] = 1;
			link[frog[j].id][frog[i].id] = 1;
		}
		frog[i].nb = 0;
	}
	//printf("YES\n");
	for (int i = 0; i < n; i++, printf("\n"))
		for (int j = 0; j < n; j++)
			printf("%d ", link[i][j]);

	int t = n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sumLink[i][j] = link[i][j];
		}
	}

	while (t - 1) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					tem[i][j] += link[i][k] * link[k][j];
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				sumLink[i][j] += tem[i][j];
			}
		}
		t--;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << sumLink[i][j] << " ";
		}
		cout << endl;
	}

	bool flag = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j) {
				if (sumLink[i][j] == 0) {
					cout << endl << "不联通" << endl;
					flag = false;
				}
			}
		}
	}
	if (flag) {
		cout << endl << "联通" << endl;
	}

	return true;
}



class solution {
public:
	vector<int> degree;
	int n;

	//constructor
	solution(int n) {
		degree.push_back(-1);
		this->n = n;
	}

	void display();

	void initialList() {
		int d;
		for (int i = 0; i < n; i++)
		{
			cin >> d;
			degree.push_back(d);
		}
	}

	void checkGraphRealization(vector<int>& degree, int n);
	void Havel(vector<int>& degree, int n);
	bool allZERO(vector<int>& degree, int s, int n);

};

//displaydegree
void solution::display() {
	for (int i = 0; i < degree.size(); i++)
	{
		cout << "degree[" << i << "]" << "= " << degree[i] << endl;
	}
}

void solution::checkGraphRealization(vector<int>& degree, int n) {

	int sum = 0;

	//先判断是否可图化
	for (int i = 1; i <= n; i++)
	{
		sum += degree[i];
	}

	if (sum % 2) {
		cout << "不可图化，亦不可简单图化" << endl;
		return;
	}


	//如果可图化，继续判断是否可简单图化

	cout << "可图化";

	auto start = degree.begin() + 1;
	auto end = degree.end();

	sort(start, end, cmp);

	//先判断最大度是否小于等于n-1
	if (degree[0] > n - 1) {
		cout << ",不可简单图化" << endl;
		return;
	}

	else {
		for (int r = 1; r <= n; r++)
		{
			int left = 0;
			for (int index = 1; index <= r; index++)
			{
				left += degree[index];
			}

			int right = r * (r - 1);
			for (int index = r + 1; index <= n; index++)
			{
				right += min(r, degree[index]);
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

	//如果可简单图化，根据 Havel 定理过程求出对应的简单图，并输出此图
	Havel(degree, n);

}

void solution::Havel(vector<int>& degree, int n) {
	vector<int>copyDegree(degree);

	auto start = copyDegree.begin() + 1;
	auto end = copyDegree.end();

	int lptr, rptr;
	lptr = 1;
	rptr = n;
	cout << "(";
	for (int i = lptr; i <= rptr; i++)
	{
		cout << copyDegree[i];
		if (i != rptr) cout << ", ";
	}
	cout << ")";
	cout << "可简单图化" << endl;

	while (!allZERO(copyDegree, lptr, rptr))
	{

		//cout << endl << "lptr=" << lptr << endl;
		for (int i = lptr + 1; i <= lptr + copyDegree[lptr]; i++)
		{
			copyDegree[i] -= 1;
		}

		start = copyDegree.begin() + lptr + 1;
		end = copyDegree.end();

		//cout << "before ";
		//display();

		sort(start, end, cmp);

		lptr++;

		//cout << "after ";
		//display();

		cout << "<=>";
		cout << "(";
		for (int i = lptr; i <= rptr; i++)
		{
			cout << copyDegree[i];
			if (i != rptr) cout << ", ";
		}
		cout << ")";
		cout << "可简单图化" << endl;
	}
}

bool solution::allZERO(vector<int>& degree, int s, int n) {
	int sum = 0;
	for (int i = s; i <= n; i++)
	{
		sum += degree[i];
	}
	if (!sum)
		return true;
	else
		return false;
}


//define the Stack container
struct Stack {
	int top;
	int vertex[maxn];
}s;



void dfs(int start, int numVertex) {
	//push the start vertex into stack;
	s.vertex[++s.top] = start;
	for (int i = 0; i < numVertex; i++) {
		//update the visited vertex
		if (link[i][start] > 0) {
			link[i][start] = link[start][i] = 0;
			//iterative call the dfs algorithm to find the connection path
			dfs(i, numVertex);
			break;
		}
	}
}



void fleury(int start, int numVertex) {
	s.top = 0;
	s.vertex[s.top] = start;
	bool flag;
	while (s.top >= 0) {
		flag = false;
		//find the connection vertex and set flag
		for (int i = 0; i < numVertex; i++) {
			if (link[s.vertex[s.top]][i] > 0) {
				flag = true;
				break;
			}
		}
		//the vertex has only one connection vertex
		if (!flag) {
			cout << (s.vertex[s.top--] + 1) << " -> ";
			//the vertex has more than one connection vertex
		}
		else {
			dfs(s.vertex[s.top--], numVertex);
		}
	}
}



int main() {
	int n;
	
	cout << "n=";
	cin >> n;

	solution method(n);

	method.initialList();


	method.checkGraphRealization(method.degree, n);

	for (int i = 0; i < n; i++) frog[i].id = i;
	for (int i = 0; i < n; i++)
	{
		frog[i].nb = method.degree[i + 1];
		//cout << "frog[" << i << "].nb = " << frog[i].nb << endl;

	}
	
	build(n);

	int start = 0, num = 0;
	int u, v, totalDegree;

	//claculate the degree of vertex
	for (int i = 0; i < n; i++) {
		totalDegree = 0;
		for (int j = 0; j < n; j++) {
			totalDegree += link[i][j];
		}
		//odd number degree case
		if (totalDegree & 1) {
			start = i;
			num++;
		}
	}
	//only the degree of vertex is even, than there will exist the Eular loop
	if (num == 0 || num == 2) {
		fleury(start, n);
	}
	else {
		cout << "没有欧拉回路!" << endl;
	}
	cout << " done ." << endl;

	return 0;
}