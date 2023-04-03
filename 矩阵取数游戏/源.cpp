#include <iostream>
using namespace std;

int max(int a, int b)
{
	return a > b ? a : b;
}

int val(int i)
{
	return i * i + i + 1;
}

long long dp[81][81];
int num[81];

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	long long res = 0;

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			scanf("%d", &num[j]);
		}

		for (int k = 1; k < m; ++k)	//第k次取数
		{
			for (int l = 1; l <= k + 1; ++l)	//dp[l][r]为k次取数之后最大分数
			{
				int r = m - k + l - 1;
				if (l > 1)
				{
					int tmp = dp[l - 1][r] + val(k) * num[l - 1];
					dp[l][r] = max(dp[l][r], dp[l - 1][r] + val(k) * num[l - 1]);
				}
				if (r < m)
				{
					int tmp = dp[l][r + 1] + val(k) * num[r + 1];
					dp[l][r] = max(dp[l][r], dp[l][r + 1] + val(k) * num[r + 1]);
				}
			}

		}
		long long a = 0;
		for (int i = 1; i <= m; ++i)
		{
			dp[i][i] += val(m) * num[i];
			a = max(a, dp[i][i]);
		}
		res += a;
		for (int i = 0; i < 81; i++)
            for (int j = 0; j < 81; j++)
                dp[i][j] = 0;
	}
	printf("%lld", res);
	return 0;
}