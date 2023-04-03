#include <iostream>
using namespace std;

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

struct edge
{
	int from, to, next, weight;
} e[20005];

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
	void clear()
	{
		head = new edge;
		tail = new edge;
		tail->pre = head;
		head->next = tail;
	}
} q;

int cnt, head[1005], n, k;


int num[1005];	//到这个点所需最少的 大于len的电线的数量
bool vis[1005];
bool spfa(int len)
{
	q.clear();

	for (int i = 2; i <= n; ++i)
		num[i] = 0x3f3f3f3f;
	num[1] = 0;
	vis[1] = true;
	q.push(1);
	while (!q.empty())
	{
		int u = q.pop();
		vis[u] = false;
		for (int i = head[u]; i; i = e[i].next)
		{
			int v = e[i].to;
			int longer = e[i].weight > len;
			if (num[v] > num[u] + longer)
			{
				num[v] = num[u] + longer;
				if (!vis[v])
				{
					vis[v] = true;
					q.push(v);
				}
			}

		}
	}
	return num[n] <= k;
}

void add(int a, int b, int w)
{
	e[++cnt].from = a;
	e[cnt].to = b;
	e[cnt].next = head[a];
	e[cnt].weight = w;
	head[a] = cnt;
	
	e[++cnt].from = b;
	e[cnt].to = a;
	e[cnt].next = head[b];
	e[cnt].weight = w;
	head[b] = cnt;
}



int main()
{
	int p, a, b, l, max = 0, ans = 0;
	read(n); read(p); read(k);
	for (int i = 1; i <= p; ++i)
	{
		read(a); read(b); read(l);
		add(a, b, l);
		if (l > max)
			max = l;
	}
	a = 0;
	b = max;
	while (a <= b)
	{
		int mid = (a + b) >> 1;
		if (spfa(mid))
		{
			b = mid - 1;
			ans = mid;
		}
		else
		{
			a = mid + 1;
		}
	}
	printf("%d", ans);
	


	return 0;
}