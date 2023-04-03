#include <iostream>
using namespace std;

struct edge
{
	int next;	//下一个同起点的边
	int to;		//指向的节点编号
	int weight;	//权重
} e[200005];		//节点编号从1开始

int cnt = 0, head[100005], f[100005][17], sum[100005][17], depth[100005];

void add(int u, int v, int w)
{
	e[++cnt].next = head[u];
	e[cnt].to = v;
	e[cnt].weight = w;
	head[u] = cnt;

	e[++cnt].next = head[v];		//双向前向星，保证构成一棵正确的树
	e[cnt].to = u;
	e[cnt].weight = w;
	head[v] = cnt;
}

void dfs(int cur, int fa)
{
	depth[cur] = depth[fa] + 1;
	f[cur][0] = fa;
	for (int i = 1; i < 17; ++i)
	{
		f[cur][i] = f[f[cur][i - 1]][i - 1];
		if (f[cur][i])
			sum[cur][i] = sum[f[cur][i - 1]][i - 1] + sum[cur][ i - 1];
	}
	for (int i = head[cur]; i; i = e[i].next)
	{
		if (e[i].to == fa)
			continue;
		sum[e[i].to][0] = e[i].weight;
		dfs(e[i].to, cur);
	}
}

int sum_lca(int a, int b)
{
	if (depth[a] > depth[b])
	{
		a ^= b;
		b ^= a;
		a ^= b;
	}

	int res = 0;
	int i = 17;
	while (i--)
	{
		if (depth[f[b][i]] >= depth[a])
		{
			res += sum[b][i];
			b = f[b][i];
		}
	}
	if (a == b)
		return res;
	i = 17;
	while (i--)
	{
		if (f[a][i] != f[b][i])
		{
			res += sum[a][i] + sum[b][i];
			a = f[a][i];
			b = f[b][i];
		}
	}
	res += sum[a][0] + sum[b][0];
	return res;
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; ++i)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		add(u, v, w);
	}
	dfs(1, 0);
	scanf("%d", &n);
	while (n--)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		printf("%d\n", sum_lca(a, b));
	}


	return 0;
}