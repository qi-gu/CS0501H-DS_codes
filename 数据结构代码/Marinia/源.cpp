#include <iostream>
using namespace std;

struct edge
{
    int next;
    int to;
} e[200005];

int cnt = 0, head[100005], f[100005][17], depth[100005], all_money[100005][17], money[100005];

int log(int x)
{
	int a = 0;
	while (x >>= 1)
		++a;
	return a;
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
	all_money[cur][0] = money[cur] | money[fa];
    for (int i = 1; (1 << i) <= depth[cur]; ++i)
    {
        f[cur][i] = f[f[cur][i - 1]][i - 1];
        all_money[cur][i] |= all_money[cur][i - 1] | all_money[f[cur][i - 1]][i - 1];
    }

    for (int i = head[cur]; i; i = e[i].next)
    {
        if (e[i].to == fa)
            continue;
        dfs(e[i].to, cur);
    }
}

bool lca(int a, int b, int need)
{
    int had = 0;

    if (depth[a] < depth[b])	//a½ÏÉî
    {
        a ^= b;
        b ^= a;
        a ^= b;
    }
    int k = log(depth[a] - depth[b]) + 1;


    while (k--)
    {
        if (depth[f[a][k]] >= depth[b])
        {
            had |= all_money[a][k];
            a = f[a][k];
        }
    }
	/*
	while (depth[a] > depth[b])
    {
        had |= all_money[a][log(depth[a] - depth[b])];
        a = f[a][log(depth[a] - depth[b])];
    }*/



    if (a == b)
	{
		had |= money[a];
        for (int i = 0; i < 32; ++i)
			if(need & (1 << i) && !(had & (1 << i)))
				return false;
		return true;
	}
    k = 17;
    while (k--)
    {
        if (f[a][k] != f[b][k])
        {
			had |= all_money[a][k] | all_money[b][k];
            a = f[a][k];
            b = f[b][k];
        }
    }
    had |= all_money[a][0] | all_money[b][0];
    for (int i = 0; i < 32; ++i)
		if(need & (1 << i) && !(had & (1 << i)))
			return false;
	return true;
}

int main()
{
    int n, m, x;
    int need = 0;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        int num;
        scanf("%d", &num);
        while (num--)
		{
            scanf("%d", &x);
			money[i] |= 1 << x;
		}
    }
    for (int i = 1; i < n; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        add(a, b);
    }

    dfs(1, 0);

    scanf("%d", &m);
    while (m--)
    {
        int a, b, num, tmp;
		need = 0;
        scanf("%d %d %d", &a, &b, &num);
        while (num--)
        {
            scanf("%d", &tmp);
            need |= 1 << tmp;
        }
		if (!num)
		{
			printf("YES\n");
			continue;
		}

        if (lca(a, b, need))
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}