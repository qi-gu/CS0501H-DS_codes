#include <iostream>
using namespace std;

int tree[500005], n;

int lowbit(int x)
{
	return x & -x;
}

void build()
{
	for (int i = 1; i <= n; ++i)
	{
		if (i + lowbit(i) <= n)
		{
			tree[i + lowbit(i)] += tree[i];
		}
	}
}

void update(int l, int r, int val)
{
	++r;
	while (l <= n)
	{
		tree[l] += val;
		l += lowbit(l);
	}
	while (r <= n)
	{
		tree[r] -= val;
		r += lowbit(r);
	}
}

int sum(int x)
{
	int a = 0;
	while (x)
	{
		a += tree[x];
		x -= lowbit(x);
	}
	return a;
}

int main()
{
	int m, op, x, y, k;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &tree[i]);
	for (int i = n; i >= 2; --i)
		tree[i] -= tree[i - 1];

	build();
	while (m--)
	{
		scanf("%d", &op);
		if (op == 1)
		{
			scanf("%d %d %d", &x, &y, &k);
			update(x, y, k);
		}
		else
		{
			scanf("%d", &x);
			printf("%d\n", sum(x));
		}

	}


	return 0;
}