#include <iostream>
using namespace std;

struct Node
{
	int a, b, num;
} node[100005];

int f[20005], enemy[20005], ran[20005];

inline void read(int &x)
{
	x = 0;
	char c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while (c >= '0' && c <= '9')
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
}

void swap(Node &a, Node &b)
{
	Node tmp = a;
	a.a = b.a;
	a.b = b.b;
	a.num = b.num;
	b.a = tmp.a;
	b.b = tmp.b;
	b.num = tmp.num;
}

void sort(int l, int r)
{
	if (l >= r)
		return;
	int j = l - 1;
	int mid = node[r].num;
	for (int now = l; now < r; ++now)
	{
		if (node[now].num > mid)
			swap(node[now], node[++j]);
	}
	swap(node[r], node[++j]);
	sort(l, j - 1);
	sort(j + 1, r);
}

int find(int x)
{
	if (x == f[x])
		return x;
	return f[x] = find(f[x]);
}

bool query(int x, int y)
{
	return find(x) == find(y);
}

void uni(int a, int b)
{
	int x = find(a), y = find(b);
	if (x == y)
		return;
	if (ran[x] < ran[y])
	{
		f[x] = y;
	}
	else if (ran[x] > ran[y])
	{
		f[y] = f[x];
	}
	else
	{
		f[x] = y;
		++ran[y];
	}
	
}

int main()
{
	int n, m;
	read(n); read(m);
	//scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i)
	{
		f[i] = i;
	}

	for (int i = 0; i < m; ++i)
	{
		read(node[i].a); read(node[i].b); read(node[i].num);
		//scanf("%d %d %d", &node[i].a, &node[i].b, &node[i].num);
	}
	sort(0, m - 1);

	
	enemy[node[0].a] = node[0].b; enemy[node[0].b] = node[0].a;
	for (int i = 1; i < m; ++i)
	{
		int fa = find(node[i].a), fb = find(node[i].b);
		if (fa == fb)
		{
			printf("%d", node[i].num);
			return 0;
		}
		if (!enemy[node[i].a])
			enemy[node[i].a] = node[i].b;
		else
			uni(node[i].b, enemy[node[i].a]);
		if (!enemy[node[i].b])
			enemy[node[i].b] = node[i].a;
		else
			uni(node[i].a, enemy[node[i].b]);
	}
	printf("0");
	return 0;
}