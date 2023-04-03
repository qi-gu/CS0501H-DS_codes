#include <iostream>
using namespace std;

long long **num;
//long long num[5000][5000];
int n, m;

long long lowbit(long long x)
{
	return x & -x;
}

void update(long long x, long long y, long long k)
{
	for (long long i = x; i <= n; i += lowbit(i))
		for (long long j = y; j <= m; j += lowbit(j))
			num[i][j] += k;
}

long long sum(int x, int y)
{
	if (!x || !y)
		return 0;
	long long a = 0;
	for (int i = x; i; i -= lowbit(i))
		for (int j = y; j; j -= lowbit(j))
			a += num[i][j];
	return a;
}

long long quiry(int x1, int y1, int x2, int y2)
{
	int x, y, a, b;
	if (x1 < x2)
	{
		x = x1;
		a = x2;
	}
	else
	{
		x = x2;
		a = x1;
	}
	if (y1 < y2)
	{
		y = y1;
		b = y2;
	}
	else
	{
		y = y2;
		b = y1;
	}
	return sum(x - 1, y - 1) + sum(a, b) - sum(x - 1, b) - sum(a, y - 1);
}

int main()
{
	int x, y, a, b;
	int op;
	scanf("%d %d", &n, &m);
	num = new long long*[n + 1];
	for (long long i = 0; i <= n; ++i)
	{
		num[i] = new long long[m + 1];
		for (int j = 0; j <= m; ++j)
			num[i][j] = 0;
	}
	while (scanf("%d", &op) != EOF)
	{
		if (op == 1)
		{
			scanf("%d %d %d", &x, &y, &a);
			update(x, y, a);
		}
		else
		{
			scanf("%d %d %d %d", &x, &y, &a, &b);
			printf("%lld\n", quiry(x, y, a, b));
		}
	}


	return 0;
}