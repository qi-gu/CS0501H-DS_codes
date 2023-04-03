#include <iostream>
using namespace std;
#define max(a, b) a > b ? a : b

int f[1001][1001];

void inline read(int &x)
{
	x = 0; 
	char c = getchar();
	while (c < '0' || c > '9')
	{
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
}

int main()
{
	int n;
	read(n);
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= i; ++j)
			read(f[i][j]);
	}
	for (int i = 2; i <= n; ++i)
	{
		f[i][1] += f[i - 1][1];
		for (int j = 2; j <= i; ++j)
			f[i][j] += max(f[i - 1][j - 1], f[i - 1][j]);
	}
	int m = f[n][1];
	for (int i = 2; i <= n; ++i)
		m = max(m, f[n][i]);
	printf("%d", m);
	return 0;
}