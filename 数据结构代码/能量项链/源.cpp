#include <iostream>
using namespace std;

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


int m[205], dp[205][205];

int max(int a, int b)
{
	return a > b ? a : b;
}

int main()
{
	int n, res = 0;
	read(n);
	for (int i = 1; i <= n; i++)
	{
		read(m[i]);
		m[n + i] = m[i];
	}
	for (int i = 2; i <= n + 1; i++)
	{
		for (int l = 1; l + i - 1 <= n << 1; ++l)
		{
			int r = l + i - 1;
			for (int k = l + 1; k < r; ++k)
				dp[l][r] = max(dp[l][r], dp[l][k] + dp[k][r] + m[l] * m[k] * m[r]);
		}
	}
    for (int i = 1; i <= n; ++i)
        res = max(res, dp[i][n + i]);
	printf("%d", res);
	return 0;
}