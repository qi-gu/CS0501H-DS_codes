#include <iostream>
#include <queue>
using namespace std;

int cnt, sweet[10005], head[10005], times[10005], n;
bool inq[10005];
queue<int> que;
struct edge
{
	int from, to, next;
} e[20005];

void add(int a, int b)		//a->b，a的糖果小于b
{
	e[++cnt].from = a;
	e[cnt].to = b;
	e[cnt].next = head[a];
	head[a] = cnt;
}

bool SPFA(int i)
{
	que.push(i);
	++times[i];
	inq[i] = true;
	while (!que.empty())
	{
		int u = que.front();
		que.pop();
		inq[u] = false;
		for (int i = head[u]; i; i = e[i].next)
		{
			int v = e[i].to;
			if (sweet[v] < sweet[u] + 1)
			{
				sweet[v] = sweet[u] + 1;
				if (!inq[v])
				{
					que.push(v);
					inq[v] = 1;
					++times[v];
				}
				if (times[v] > n)
					return false;
			}
		}
		
	}
	return true;
}

int main()
{
	int m, a, b;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; ++i)
	{
		scanf("%d %d", &a, &b);
		add(b, a);
		
	}
	for (int i = 1; i <= n; ++i)
	{
		if (!times[i])
			if (!SPFA(i))
			{
				printf("Poor Xed");
				return 0;
			}
	}

	long long num = 0;
	for (int i = 1; i <= n; ++i)
		num += sweet[i];
	printf("%lld", num + 100 * n);
	return 0;
}