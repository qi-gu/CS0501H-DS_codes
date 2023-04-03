#include <iostream>
using namespace std;

bool state[200005], exist[200005];
int f[200005], head[200005], delNode[200005];
int cnt;

inline void read(int &x)
{
	x = 0;
	char c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while (c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
}

struct E
{
	int from, to, next;
} edge[400005];

void add(int a, int b)
{
	edge[++cnt].from = a;
	edge[cnt].to = b;
	edge[cnt].next = head[a];
	head[a] = cnt;

	edge[++cnt].from = b;
	edge[cnt].to = a;
	edge[cnt].next = head[b];
	head[b] = cnt;
}

int find(int x)
{
	if (f[x] == x)
		return x;
	return f[x] = find(f[x]);
}

bool uni(int a, int b)
{
	int fa = find(a), fb = find(b);
	if (fa == fb)
		return false;
	f[fa] = fb;
	return true;
}

int main()
{
	int n, m, a, b;
	read(n); read(m);
	for (int i = 0; i < m; ++i)
	{
		read(a); read(b);
		add(a, b);
	}
	for (int i = 1; i <= n; ++i)
	{
		read(delNode[i]);
		f[i] = i;
	}
	int num = 0;	//边数
	for (int i = n; i >= 1; --i)
	{
		exist[delNode[i]] = true;
		for (int j = head[delNode[i]]; j; j = edge[j].next)
		{
			if (exist[edge[j].to] && uni(edge[j].from, edge[j].to))		//如果新增的节点有一个邻点和该节点不在同一个集合，新增一条边连起来
				++num;
		}
		if (num == n - i)
			state[i] = true;
	}
	for (int i = 1; i <= n; ++i)
	{
		if (state[i])
			printf("YES\n");
		else
			printf("NO\n");
	}

	return 0;
}