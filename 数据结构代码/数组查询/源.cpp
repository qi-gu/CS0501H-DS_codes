#include <iostream>

using namespace std;

#define pushup(a) tree[a] = tree[a << 1] + tree[a << 1 | 1]

long long tree[2000005];
long long arr[500005];
long long lazy[2000005];

void build(long long rt, long long l, long long r)
{
	if (l == r)
	{
		tree[rt] = arr[l];
		return;
	}
	long long mid = (l + r) >> 1;
	build(rt << 1, l, mid);
	build(rt << 1 | 1, mid + 1, r);
	pushup(rt);
}

void change(long long rt, long long l, long long r, long long lz)
{
	tree[rt] += (l - r + 1) * lz;
	lazy[rt] += lz;
}

void pushdown(long long rt, long long l, long long r)
{
	if (l == r)
		lazy[rt] = 0;
	else if (lazy[rt])
	{
		long long mid = (l + r) >> 1;
		change(rt << 1, l, mid, lazy[rt]);
		change(rt << 1 | 1, mid + 1, r, lazy[rt]);
		lazy[rt] = 0;
	}
}

void update(long long rt, long long l, long long r, long long x, long long y, long long z)
{
	pushdown(rt, l, r);
	if (x <= l && y >= r)
	{
		change(rt, l, r, z);
		return;
	}

	long long mid = (l + r) >> 1;
	if (x <= mid)
		update(rt << 1, l, mid, x, y, z);
	if (y > mid)
		update(rt << 1 | 1, mid + 1, r, x, y, z);
	pushup(rt);
}

long long quiry(long long rt, long long x, long long l, long long r)
{
	pushdown(rt, l, r);
	long long mid = (l + r) >> 1;
	if (l == r)
		return tree[rt];
	else if (x <= mid)
		return quiry(rt << 1, x, l, mid);
	else
		return quiry(rt << 1 | 1, x, mid + 1, r);
}

int main()
{
	long long n, m, op, x, y, k;
	scanf("%lld %lld", &n, &m);
	for (long long i = 1; i <= n; ++i)
		scanf("%lld", &arr[i]);
	build(1, 1, n);
	while (m--)
	{
		scanf("%lld", &op);
		if (op == 1)
		{
			scanf("%lld %lld %lld", &x, &y, &k);
			update(1, 1, n, x, y, k);
		}
		else
		{
			scanf("%lld", &x);
			printf("%lld\n", quiry(1, x, 1, n));
		}

	}

	return 0;
}
