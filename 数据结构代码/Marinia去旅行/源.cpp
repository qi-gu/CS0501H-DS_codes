#include <iostream>
#include <cstring>
using namespace std;

struct edge
{
    int next;
    int to;
} e[200005];

int cnt = 0, head[100005], f[100005][17], depth[100005];

int log(int a)
{
	int n = 0;
	while (a >>= 1)
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
        if (e[i].to == fa)
            continue;
        dfs(e[i].to, cur);
    }
}

int lca(int a, int b)
{
    if (depth[a] < depth[b])	//a½ÏÉî
    {
        a ^= b;
        b ^= a;
        a ^= b;
    }
    while (depth[a] > depth[b])
    {
        a = f[a][log(depth[a] - depth[b])];
    }
    if (a == b)
        return b;
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

int main()
{
	int t, n, m;
	scanf("%d", &t);
	for (int i = 0; i < t; ++i)
	{
		scanf("%d %d", &n, &m);
		while (--n)
		{
			int a, b;
			scanf("%d %d", &a, &b);
			add(a, b);
		}
		dfs(1, 0);
		while (m--)
		{
			int a, b, c, d;
			bool flag;
			scanf("%d %d %d %d", &a, &b, &c, &d);
			int x = lca(a, b), y = lca(c, d);
			int tmp = lca(x, y);
			flag = x != tmp && y != tmp;
			if (depth[x] > depth[y])
				flag = lca(x, c) != x && lca(x, d) != x;
			else
				flag = lca(y, a) != y && lca(y, b) != y;
			if (flag)
			{
				printf("NO\n");
			}
			else
				printf("YES\n");
		}
		cnt = 0;
		memset(head, 0, sizeof(head));
		memset(e, 0, sizeof(e));
		memset(f, 0, sizeof(f));
	}

	return 0;
}