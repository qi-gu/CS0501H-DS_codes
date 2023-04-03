#include <iostream>
using namespace std;

#define sq(x) x * x

double arr[400005];
double num[400005], sqr[400005], lz[400005];

void pushup(int pos)
{
	num[pos] = num[pos << 1] + num[pos << 1 | 1];
	sqr[pos] = sqr[pos << 1] + sqr[pos << 1 | 1];
}

void change(int pos, int l, int r, double dx)
{
	sqr[pos] += (r - l + 1) * sq(dx) + 2 * dx * num[pos];
	num[pos] += (r - l + 1) * dx;
	lz[pos] += dx;
}

void pushdown(int pos, int l, int r)
{
	if (!lz[pos])
		return;
	if (l == r)
		lz[pos] = 0;
	else
	{
		int mid = (l + r) >> 1;
		change(pos << 1, l, mid, lz[pos]);
		change(pos << 1 | 1, mid + 1, r, lz[pos]);
		lz[pos] = 0;
	}
}

void build(int pos, int l, int r)
{
	if (l == r)
	{
		num[pos] = arr[l];
		sqr[pos] = sq(arr[l]);
		return;
	}
	int mid = (l + r) >> 1;
	build(pos << 1, l, mid);
	build(pos << 1 | 1, mid + 1, r);
	pushup(pos);
}

void update(int pos, int x, int y, int l, int r, double d)
{
	pushdown(pos, l, r);
	if (x <= l && y >= r)
	{
		change(pos, l, r, d);
		return;
	}
	int mid = (l + r) >> 1;
	if (x <= mid)
		update(pos << 1, x, y, l, mid, d);
	if (y > mid)
		update(pos << 1 | 1, x, y, mid + 1, r, d);
	pushup(pos);
}

double quiry_sum(int pos, int x, int y, int l, int r)
{
	pushdown(pos, l, r);
	if (x  <= l && y >= r)
		return num[pos];
	if (x > r || y < l)
		return 0;
	int mid = (l + r) >> 1;
	return quiry_sum(pos << 1, x, y, l, mid) + quiry_sum(pos << 1 | 1, x, y, mid + 1, r);
}

double quiry_sqr(int pos, int x, int y, int l, int r)
{
	pushdown(pos, l, r);
	if (x <= l && y >= r)
		return sqr[pos];
	if (x > r || y < l)
		return 0;
	int mid = (l + r) >> 1;
	return quiry_sqr(pos << 1, x, y, l, mid) + quiry_sqr(pos << 1 | 1, x, y, mid + 1, r);

}

int main()
{
	int n, m, op, x, y;
	double c;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%lf", &arr[i]);
	build(1, 1, n);

	while (m--)
	{
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			scanf("%d %d %lf", &x, &y, &c);
			update(1, x, y, 1, n, c);
			break;
		case 2:
			scanf("%d %d", &x, &y);
			printf("%d\n", (int)(quiry_sum(1, x, y, 1, n) / (y - x + 1) * 100));
			break;
		case 3:
			scanf("%d %d", &x, &y);
			double s = quiry_sum(1, x, y, 1, n);
			double aver = s / (y - x + 1);
			printf("%d\n", (int)(
				(quiry_sqr(1, x, y, 1, n) / (y - x + 1) - sq(aver))
				* 100));
		}
	}

	return 0;
}