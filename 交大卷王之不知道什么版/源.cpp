#include <iostream>
using namespace std;

struct edge
{
	int from, to, next;
} e[200005];

int head[100005], sum[100005], num;

inline void read(int &x)
{
	x = 0;
	char c = getchar();
	bool pos = true;
	while (c < '0' || c > '9')
	{
		if (c == '-')
			pos = false;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	if (!pos)
		x = -x;
}

void add(int a, int b)
{
	e[++num].from = a;
	e[num].to = b;
	e[num].next = head[a];
	head[a] = num;

	e[++num].from = b;
	e[num].to = a;
	e[num].next = head[b];
	head[b] = num;
}

void dfs(int n, int fa)
{
	for (int i = head[n]; i; i = e[i].next)
	{
		if (e[i].to == fa)
			continue;
		dfs(e[i].to, n);
		sum[n] += sum[e[i].to];
	}
}

int main()
{
	int n, a, b;
	read(n);
	for (int i = 1; i <= n; ++i)
	{
		read(sum[i]);
	}
	for (int i = 1; i < n; ++i)
	{
		read(a); read(b);
		add(a + 1, b + 1);
	}
	dfs(1, 0);

	for (int i = 1; i <= n; ++i)
		printf("%d\n", sum[i]);

	return 0;
}