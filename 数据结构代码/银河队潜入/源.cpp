#include <iostream>
using namespace std;

#define MOD 10000009

class queue
{
private:
	struct edge
	{
		int val;
		edge *next, *pre;
		edge() : next(NULL), pre(NULL) {}
		edge(int x) : next(NULL), pre(NULL), val(x) {}
	};
	edge *head, *tail;
	int num;
public:
	queue() : num(0)
	{
		head = new edge;
		tail = new edge;
		tail->pre = head;
		head->next = tail;
	}
	void push(int x)
	{
		edge *tmp = new edge(x);
		tmp->next = tail;
		tmp->pre = tail->pre;
		tail->pre->next = tmp;
		tail->pre = tmp;
		++num;
	}
	int pop()
	{
		edge *tmp = head->next;
		int val = tmp->val;
		head->next = tmp->next;
		head->next->pre = head;
		delete tmp;
		--num;
		return val;
	}
	bool empty()
	{
		return !num;
	}
} q;

inline int read()
{
	int x = 0;
	char c = getchar();
	bool neg = false;
	while (c < '0' || c > '9')
	{
		if (c == '-')
			neg = true;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	if (neg)
		x = -x;
	return x;
}

struct edge
{
	int to, next, weight;
} e[1200005];

int cnt, table[MOD], head[300005 + MOD];

int Hash(int x)
{
	int p = x > 0 ? x : -x;
    p = p % MOD;
    while (table[p] && table[p] != x)
		p = (p + 1) % MOD;
    table[p] = x;
    return p;
}

void add(int a, int b, int weight)
{
	e[++cnt].to = b;
	e[cnt].weight = weight;
	e[cnt].next = head[a];
	head[a] = cnt;

	e[++cnt].to = a;
	e[cnt].weight = weight;
	e[cnt].next = head[b];
	head[b] = cnt;
}

int dis[300005 + MOD];
bool inq[300005 + MOD];

void spfa()
{
	for (int i = 0; i < 300005 + MOD; ++i)
		dis[i] = 0x3f3f3f3f;
	dis[MOD + 1] = 0;
	q.push(MOD + 1);
	inq[MOD + 1] = true;
	while (!q.empty())
	{
		int u = q.pop();
		inq[u] = false;
		for (int i = head[u]; i; i = e[i].next)
		{
			int v = e[i].to;
			if (dis[v] > e[i].weight + dis[u])
			{
				dis[v] = e[i].weight + dis[u];
				if (!inq[v])
				{
					q.push(v);
					inq[v] = true;
				}
			}
		}
	}
}

int main()
{
	int n;
	n = read();
	if (n == 1)
	{
		printf("0");
		return 0;
	}
	for (int i = 1; i < n; ++i)
	{
		add(MOD + i, MOD + i + 1, 2);
	}
	for (int i = 1; i <= n; ++i)
	{
		add(Hash(read()), MOD + i, 1);
	}
	spfa();
	printf("%d", dis[MOD + n] / 2);

	return 0;
}