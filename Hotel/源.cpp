#include <iostream>
using namespace std;

int *maxlen, *lazy, *rlen, *llen;

int max(int a, int b, int c)
{
	a = a > b ? a : b;
	return a > c ? a : c;
}

void pushup(int pos, int l, int r)
{
	int mid = (l + r) >> 1, lc = pos << 1, rc = pos << 1 | 1;
	llen[pos] = mid - l + 1 == maxlen[lc] ? mid - l + 1 + llen[rc] : llen[lc];
	rlen[pos] = r - mid == maxlen[rc] ? r - mid + rlen[lc] : rlen[rc];
	maxlen[pos] = max(maxlen[lc], maxlen[rc], rlen[lc] + llen[rc]);
}

void pushdown(int pos, int l, int r)
{
	if (!lazy[pos] || l == r)
		return;

	int lc = pos << 1, rc = pos << 1 | 1;
	if (lazy[pos] == 1)
	{
		maxlen[lc] = llen[lc] = rlen[lc] =
			maxlen[rc] = llen[rc] = rlen[rc] = 0;
		lazy[lc] = lazy[rc] = 1;
	}
	else
	{
		int mid = (l + r) >> 1;
		maxlen[lc] = llen[lc] = rlen[lc] = mid - l + 1;
		maxlen[rc] = llen[rc] = rlen[rc] = r - mid;
		lazy[lc] = lazy[rc] = 2;
	}
	lazy[pos] = 0;
}

void build(int pos, int l, int r)
{
	if (l == r)
	{
		maxlen[pos] = llen[pos] = rlen[pos] = 1;
		lazy[pos] = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(pos << 1, l, mid);
	build(pos << 1 | 1, mid + 1, r);
	pushup(pos, l, r);
}

int query(int pos, int l, int r, int num)		//查找
{
	if (num > maxlen[pos])
		return 0;
	pushdown(pos, l, r);
	int lc = pos << 1, rc = pos << 1 | 1, mid = (l + r) >> 1;
	if (maxlen[lc] >= num)
		return query(lc, l, mid, num);
	if (rlen[lc] + llen[rc] >= num)
		return mid - rlen[lc] + 1;
	return query(rc, mid + 1, r, num);
}

void update(int pos, int l, int r, int x, int y, int op)		//1为入住x~y，2为离开x~y
{
	pushdown(pos, l, r);
	if (l >= x && r <= y)
	{
		switch (op)
		{
			case 1:
				lazy[pos] = 1;
				maxlen[pos] = llen[pos] = rlen[pos] = 0;
				break;
			case 2:
				lazy[pos] = 2;
				maxlen[pos] = llen[pos] = rlen[pos] = r - l + 1;
		}
		return;
	}
	int mid = (l + r) >> 1;
	if (x <= mid)
		update(pos << 1, l, mid, x, y, op);
	if (y > mid)
		update(pos << 1 | 1, mid + 1, r, x, y, op);
	pushup(pos, l, r);
}

int main()
{
	int n, m, op, x, y, tmp;
	scanf("%d %d", &n, &m);
	tmp = (n + 1) << 2;
	maxlen = new int[tmp];
	lazy = new int[tmp];
	rlen = new int[tmp];
	llen = new int[tmp];
	build(1, 1, n);
	while (m--)
	{
		scanf("%d", &op);
		switch (op)
		{
			case 1:
				scanf("%d", &x);
				tmp = query(1, 1, n, x);
				printf("%d\n", tmp);
				if (tmp)
					update(1, 1, n, tmp, tmp + x - 1, 1);
				break;

			case 2:
				scanf("%d %d", &x, &y);
				update(1, 1, n, x, x + y - 1, 2);
		}
	}


	return 0;
}