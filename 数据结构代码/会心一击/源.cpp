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

int pre_0(int x, int i)
{
	return i + 1 - x;
}

int main()
{
	int n, m, j, tmp, opt, l, r;
	scanf("%d %d", &n, &m);
	j = log(n);
	int *x = new int[n], **len = new int*[n], *sum = new int[n], **crit = new int*[n - 1];
	len[0] = new int[j]; crit[0] = new int[j];
	scanf("%d", &x[0]);
	sum[0] = len[0][0] = crit[0][0] = x[0];
	for (int i = 1; i < n; i++)		//计算前缀和
	{
		len[i] = new int[j];
		crit[i] = new int[j];
		len[i][0] = 0;
		scanf("%d", &x[i]);
		sum[i] = len[i][0] = len[i - 1][0] + x[i];
		if (x[i - 1] == 0 && x[i] == 1)
			crit[i - 1][0] = 2;
		else
			crit[i - 1][0] = 1;
	}
	for (int i = 0; i < n; i++)		//计算当前节点为转换点的子序列长度,包含本位0、包含本位1
	{
		len[i][0] = pre_0(len[i][0], i) + len[n - 1][0] - len[i][0] + x[i];
	}
	for (tmp = 1; tmp <= j; tmp++)		//建表
	{
		for (int i = 0; i + (1 << tmp) - 1 < n; i++)
		{
			len[i][tmp] = max(len[i][tmp - 1], len[i + (1 << (tmp - 1))][tmp - 1]);
			if (i != n - 1)
				crit[i][tmp] = max(crit[i][tmp - 1], crit[i + (1 << (tmp - 1))][tmp - 1]);
		}
	}

	while (m--)			//开始查找
	{
		scanf("%d %d %d", &opt, &l, &r);
		l--;r--;
		if (opt == 1)		//攻击力
		{
			if (r == l)
				tmp = 1;
			else
			{
				j = log(r - l + 1);
				tmp = max(len[l][j], len[r + 1 - (1 << j)][j]);
				tmp = tmp - pre_0(sum[l], l) + !(x[l]) - (sum[n - 1] - sum[r]);
				
			}
		}
		else			//暴击率
		{
			if (r == l)
				tmp = 1;
			else
			{
				j = log(r - l);
				tmp = max(crit[l][j], crit[r - (1 << j)][j]);
			}
		}
		printf("%d\n", tmp);
	}
	
	return 0;
}