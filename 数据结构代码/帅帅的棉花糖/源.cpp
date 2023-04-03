#include <iostream>
#include <algorithm>
using namespace std;

int f[1005];

struct E
{
	int a, b, weight;
} edge[100005];

void swap(E &a, E &b)
{
	E tmp = a;
	a.a = b.a;
	a.b = b.b;
	a.weight = b.weight;
	b.a = tmp.a;
	b.b = tmp.b;
	b.weight = tmp.weight;
}

void sort(int l, int r)
{
	if (l >= r)
		return;
	int now = l, pos = l - 1, mid = edge[r].weight;
	for (; now < r; ++now)
	{
		if (edge[now].weight < mid)
		{
			swap(edge[now], edge[++pos]);
		}
	}
	swap(edge[++pos], edge[r]);
	sort(l, pos - 1);
	sort(pos + 1, r);
}

int find(int x)
{
	if (f[x] == x)
		return x;
	return f[x] = find(f[x]);
}

bool uni(int a, int b)
{
	int fa = find(a), fb = find(b);
	if (fa == fb)
		return false;

	f[fa] = fb;
	return true;
}

int main()
{
	int n, m, k, num;
	long long min_price = 0;
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; ++i)
		f[i] = i;
	for (int i = 1; i <= m; ++i)
	{
		scanf("%d %d %d", &edge[i].a, &edge[i].b, &edge[i].weight);
	}
	if (n < k)
	{
		printf("No Answer");
		return 0;
	}
	if (n - m > k)
	{
		printf("No Answer");
		return 0;
	}

	sort(1, m);
	num = n;

	int i = 1;
	while (num > k)
	{
		if (uni(edge[i].a, edge[i].b))
		{
			min_price += edge[i].weight;
			--num;
		}
		++i;
	}
	printf("%d", min_price);

	return 0;
}