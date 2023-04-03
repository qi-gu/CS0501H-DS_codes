#include <iostream>
using namespace std;

struct edge
{
	int next;	//��һ��ͬ���ı�
	int to;		//ָ��Ľڵ���
	int weight;	//Ȩ��
} e[100005];		//�ڵ��Ŵ�1��ʼ

int cnt = 0, head[50005], f[50005][16], sum[50005][16], depth[50005];

void add(int u, int v, int w)
{
	e[++cnt].next = head[u];
	e[cnt].to = v;
	e[cnt].weight = w;
	head[u] = cnt;

	e[++cnt].next = head[v];		//˫��ǰ���ǣ���֤����һ����ȷ����
	e[cnt].to = u;
	e[cnt].weight = w;
	head[v] = cnt;
}

void dfs(int cur, int fa)
{
	depth[cur] = depth[fa] + 1;
	f[cur][0] = fa;
	for (int i = 1; (1 << i) <= depth[cur]; ++i)
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
	int i = 16;
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
	i = 16;
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
	int n;
	scanf("%d", &n);
	for (int i = 1; i < n; ++i)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		add(u, v, w);
	}
	dfs(1, 0);
	scanf("%d", &n);
	while (n--)
	{
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);

		printf("%d\n", (sum_lca(a, b) + sum_lca(a, c) + sum_lca(b, c)) / 2);
	}


	return 0;
}