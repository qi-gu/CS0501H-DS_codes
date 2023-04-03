#include <iostream>
using namespace std;
#define min(a, b) a < b ? a : b

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
	int popBack()
	{
		edge *tmp = tail->pre;
		int val = tmp->val;
		tail->pre = tmp->pre;
		tail->pre->next = tail;
		delete tmp;
		--num;
		return val;
	}
	bool empty()
	{
		return !num;
	}
	int size()
	{
		return num;
	}
	int front()
	{
		return head->next->val;
	}
} q, neg;

struct edge
{
	int from, to, weight, next;
} e[10005];

int cnt, head[5005], n, pre[5005];

void add(int a, int b, int w)
{
	e[++cnt].from = a;
	e[cnt].to = b;
	e[cnt].weight = w;
	e[cnt].next = head[a];
	head[a] = cnt;
}

int dis[5005], times[5005];
bool inq[5005];

bool exist[5005];
void find(int root)
{
	neg.push(root);
	exist[root] = true;
	int now = pre[root];
	while (!exist[now])
	{
		neg.push(now);
		exist[now] = true;
		now = pre[now];
	}
	while (neg.front() != now)
		neg.pop();
}

bool SPFA()
{
	for (int i = 2; i <= n; ++i)
		dis[i] = 0x3f3f3f3f;
	dis[1] = 0;
	inq[1] = true;
	++times[1];
	q.push(1);
	int u, v;
	while(!q.empty())
	{
		u = q.pop();
		inq[u] = false;
		for(int i = head[u]; i; i = e[i].next)
		{
			v = e[i].to;
			if(dis[v] > dis[u] + e[i].weight)
			{
				dis[v] = dis[u] + e[i].weight;
				pre[v] = u;
				if(!inq[v])
				{
					if (times[v] > n)
					{
						find(v);
						return false;
					}
					q.push(v);
					inq[v] = 1;
					++times[v];
				}
			}
		}
	}
	return true;
}

int main()
{
	int m, a, b, w;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; ++i)
	{
		scanf("%d %d %d", &a, &b, &w);
		add(a, b, w);
	}
	if (SPFA())
	{
		printf("0");
		return 0;
	}
	printf("%d\n", neg.size());
	while (!neg.empty())
	{
		printf("%d ", neg.popBack());
	}

	return 0;
}