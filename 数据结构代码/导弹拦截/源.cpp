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

int height[2005], need[2005], dp[2005];	//need为1到n的需要炮数，dp[i]为从i到n的数量


int main()
{
	int n, need_num = 1, one_num = 1;
	read(n);
	for (int i = 1; i <= n; ++i)
	{
		read(height[i]);
		need[i] = 1;
	}
	for (int i = 2; i <= n; ++i)
	{
		for(int j = 1; j < i; ++j)
			if (height[j] < height[i] && need[j] >= need[i])
				need[i] = need[j] + 1;
		need_num = need_num > need[i] ? need_num : need[i];
	}
	dp[n] = 1;
	for (int l = n - 1; l >= 1; --l)
	{
		int max = 0;
		for (int r = l; r <= n; ++r)
		{
			if (dp[r] > max && height[r] <= height[l])
				max = dp[r];
		}
		dp[l] = max + 1;
		one_num = one_num > dp[l] ? one_num : dp[l];
	}
	printf("%d\n%d", one_num, need_num);

	return 0;
}