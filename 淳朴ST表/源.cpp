#include <iostream>
using namespace std;

int log(int x)
{
	int n = 0;
	while (x >>= 1)
		n++;
	return n;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	int **x = new int*[n];
	int tmp = log(n);
	for (int i = 0; i < n; i++)
	{
		x[i] = new int[tmp + 1];
		scanf("%d", &x[i][0]);
	}
	for (int j = 1; j <= tmp; j++)
		for (int i = 0; i + (1 << j) - 1 < n; i++)
			x[i][j] = max(x[i][j - 1], x[i + (1 << (j - 1))][j - 1]);
	for (int i = 0; i < m; i++)
	{
		int l, r;
		scanf("%d %d", &l, &r);
		tmp = log(r - l);
		printf("%d\n", max(x[l - 1][tmp], x[r - (1 << tmp)][tmp]));
	}
	return 0;
}