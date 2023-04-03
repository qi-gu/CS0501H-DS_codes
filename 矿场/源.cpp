#include <iostream>
using namespace std;
#define ll unsigned long long
#define min(a, b) a < b ? a : b

int cnt, head[10005];
struct edge
{
	int from, to, next;
} e[100005];

void add(int a, int b)
{
	e[++cnt].from = a;
	e[cnt].to = b;
	e[cnt].next = head[a];
	head[a] = cnt;
	
	e[++cnt].from = b;
	e[cnt].to = a;
	e[cnt].next = head[b];
	head[b] = cnt;
}

bool cut[10005];
int dfn[10005], low[10005], num, need_num, top, tmp;
int stack[10005], visit[10005];

void tarjan(int x, int root)
{
	int v, son = 0;
	low[x] = dfn[x] = ++num;
	for (int i = head[x]; i; i = e[i].next)
	{
		v = e[i].to;
		if (!dfn[v])
		{
			if (x == root)
				++son;
			tarjan(v, root);
			if (low[v] >= dfn[x])
				cut[x] = true;
			low[x] = min(low[v], low[x]);
		}
		else
			low[x] = min(low[x], dfn[v]);
	}
	if (x == root)
		if (son > 1)
			cut[x] = true;
		else
			cut[x] = false;
	
}

void dfs(int u)
{
	++tmp;
	visit[u] = true;
	for(int i = head[u]; i; i = e[i].next)
	{
		int v = e[i].to;
		if(visit[v])
			continue;
		if(cut[v])
		{
			stack[++top] = v;
			visit[v] = true;
			continue;
		}
		dfs(v);
	}
}

int main()
{
	int n, ca = 0, m = 0;
	while (1)
	{
		scanf("%d", &n);
		if (!n)
			break;
		ll plans = 1;
		for (int i = 0; i < n; ++i)
		{
			int a, b;
			scanf("%d %d", &a, &b);
			add(a, b);
			a = a > b ? a : b;
			m = m > a ? m : a;
		}
		for (int i = 1; i <= n; ++i)
			if (!dfn[i])
				tarjan(i, i);

		for (int i = 1; i <= m; ++i)
		{
			tmp = top = 0;

			if(!cut[i] && !visit[i])
			{
				dfs(i);
				if (tmp && !top)
				{
					need_num += 2;
					plans *= (tmp * (tmp - 1) >> 1);
				}
				else if (tmp && top < 2)
				{
					++need_num;
					plans *= tmp;
				}
				for (int k = 1; k <= top; ++k)
					visit[stack[k]] = false;
			}
		}

		if (!need_num)
		{
			need_num = 2;
			plans = n * (n - 1) >> 1;
		}
		printf("Case %d: %d %llu\n", ++ca, need_num, plans);

		//clear
		for (int i = 0; i < 10001; ++i)
			head[i] = dfn[i] = low[i] = visit[i] = cut[i] = 0;
		for (int i = 1; i <= cnt; ++i)
			e[i].from = e[i].to = e[i].next = 0;
		cnt = need_num = num = 0;
		m = 0;
	}
	return 0;
}