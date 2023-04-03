#include <iostream>
using namespace std;

struct edge
{
	int next;
	int to;
} e[200005];

int cnt = 0, head[100005], f[100005][17], depth[100005], cups[100005], max_num;

int log(int x)
{
	int n = 0;
	while (x >>= 1)
		++n;
	return n;
}

void add(int u, int v)
{
	e[++cnt].next = head[u];
	e[cnt].to = v;
	head[u] = cnt;

	e[++cnt].next = head[v];
	e[cnt].to = u;
	head[v] = cnt;
}

void dfs(int cur, int fa)
{
	depth[cur] = depth[fa] + 1;
	f[cur][0] = fa;
	for (int i = 1; (1 << i) <= depth[cur]; ++i)
	{
		f[cur][i] = f[f[cur][i - 1]][i - 1];
	}
	for (int i = head[cur]; i; i = e[i].next)
	{
		if (e[i].to != fa)
			dfs(e[i].to, cur);
	}
}

int lca(int a, int b)
{
	if (depth[a] > depth[b])
	{
		a ^= b;
		b ^= a;
		a ^= b;
	}

	while (depth[a] < depth[b])
		b = f[b][log(depth[b] - depth[a])];
	if (a == b)
		return a;

	for (int i = log(depth[a]); i >= 0; --i)
	{
		if (f[a][i] != f[b][i])
		{
			a = f[a][i];
			b = f[b][i];
		}
	}
	return f[a][0];
}

void put(int a, int b)
{
	++cups[a];
	++cups[b];
	int anc = lca(a, b);
	--cups[anc];
	--cups[f[anc][0]];
}

int get_sum(int root)
{
	int sum = cups[root];
	if (!head[root])
	{
		max_num = max_num > sum ? max_num : sum;
		return sum;
	}
	for (int i = head[root]; i; i = e[i].next)
	{
		if (e[i].to != f[root][0])
			sum += get_sum(e[i].to);
	}
	max_num = max_num > sum ? max_num : sum;
	return sum;
}

int main()
{
	int n, k, a, b;
	scanf("%d %d", &n, &k);
	while (--n)
	{
		scanf("%d %d %d", &a, &b);
		add(a, b);
	}
	dfs(1, 0);

	while (k--)
	{
		scanf("%d %d", &a, &b);
		put(a, b);
	}
	get_sum(1);
	printf("%d", max_num);


	return 0;
}