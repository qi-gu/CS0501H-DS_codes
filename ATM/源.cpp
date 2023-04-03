#include <iostream>
using namespace std;
#define MAX 0x3f3f3f3f
#define min(a, b) a < b ? a : b

struct edge
{
	int from, to, next;
} e[500005], new_e[500005];
int max(int a, int b)
{
	return a > b ? a : b;
}
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

int head[500005], cnt, new_cnt, num, centre;
int money[500005];
bool bar[500005];

inline int read()
{
	int x = 0;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	return x;
}

void add(int a, int b)
{
	e[++cnt].from = a;
	e[cnt].to = b;
	e[cnt].next = head[a];
	head[a] = cnt;
}

void add_new(int a, int b)
{
	new_e[++new_cnt].from = a;
	new_e[new_cnt].to = b;
	new_e[new_cnt].next = head[a];
	head[a] = new_cnt;
}

int dfn[500005], low[500005];
int col[500005], color;
int stack[500005], top;
int superMoney[500005];
bool superBar[500005];

void tarjan(int x)
{
	int v;
	low[x] = dfn[x] = ++num;
	stack[++top] = x;
	for (int i = head[x]; i; i = e[i].next)
	{
		v = e[i].to;

		if (!dfn[v])
		{
			tarjan(v);
			low[x] = min(low[v], low[x]);
		
		}
		else if (!col[v])
			low[x] = min(low[x], dfn[v]);
	}
	if (dfn[x] == low[x])
	{
		++color;
		int sum_money = 0;
		while (stack[top] != x)
		{
			col[stack[top]] = color;
			sum_money += money[stack[top]];
			if (bar[stack[top]])
				superBar[color] = true;
			if (centre == stack[top])
				centre = color;
			--top;
		}
		col[x] = color;
		superMoney[color] = sum_money + money[x];
		if (bar[x])
			superBar[color] = true;
		if (centre == x)
			centre = color;
		--top;
	}
}

int dis[500005];
bool inq[500005];
void SPFA()
{
	dis[centre] = -superMoney[centre];
	inq[centre] = true;
	q.push(centre);
	int u, v;
	while(!q.empty())
	{
		u = q.pop();
		inq[u] = false;
		for(int i = head[u]; i; i = new_e[i].next)
		{
			v = new_e[i].to;
			if(dis[v] > dis[u] - superMoney[v])
			{
				dis[v] = dis[u] - superMoney[v];
				if(!inq[v])
				{
					q.push(v);
					inq[v] = 1;
				}
			}
		}
	}
}

int main()
{
	int n, m, bar_num;
	n = read(); m = read();

	for (int i = 0; i < m; ++i)
	{
		int a = read(), b = read();
		add(a, b);
	}
	for (int i = 1; i <= n; ++i)
		money[i] = read();
	centre = read(); bar_num = read();
	for (int i = 0; i < bar_num; ++i)
		bar[read()] = true;
	for (int i = 1; i <= n; ++i)
		if (!dfn[i])
			tarjan(i);
	for (int i = 0; i <= n; ++i)
		head[i] = 0;

	for (int i = 1; i <= m; ++i)	//重新建立之间边的关系
	{
		if (col[e[i].from] != col[e[i].to])
			add_new(col[e[i].from], col[e[i].to]);
	}
	SPFA();
	int maxm = 0;
	for (int i = 1; i <= color; ++i)
	{
		if (dis[i] < maxm && superBar[i])
			maxm = dis[i];
	}
	printf("%d", -maxm);


	return 0;
}