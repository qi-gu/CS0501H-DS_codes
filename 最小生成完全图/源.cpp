#include <iostream>
using namespace std;

void inline read(int &x)
{
	x = 0;
	char c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while (c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
}

int fa[100005], num[100005];

struct edge
{
	int a, b, weight;
} e[100005];

int find(int x)
{
	if (fa[x] == x)
		return x;
	return fa[x] = find(fa[x]);
}

void swap(edge &a, edge &b)
{
	edge tmp = a;
	a = b;
	b = tmp;
}

void sort(int l, int r)
{
	if (l > r)
		return;
	int tmp = e[r].weight;
	int mid = l;
	for (int i = l; i < r; ++i)
	{
		if (e[i].weight < tmp)
			swap(e[i], e[mid++]);
	}
	swap(e[r], e[mid]);
	sort(l, mid - 1);
	sort(mid + 1, r);
}

int main()
{
	int n;
	long long ans = 0;
	read(n);
	for (int i = 1; i < n; ++i)
	{
		read(e[i].a); read(e[i].b); read(e[i].weight);
	}
	sort(1, n - 1);
	for (int i = 1; i <= n; ++i)
	{
		fa[i] = i;
		num[i] = 1;
	}
	for (int i = 1; i < n; ++i)
	{
		int faa = find(e[i].a), fab = find(e[i].b);
		ans += (long long)num[faa] * num[fab] * (e[i].weight + 1) - 1;
		fa[faa] = fab;
		num[fab] += num[faa];
	}
	printf("%lld", ans);

	return 0;
}