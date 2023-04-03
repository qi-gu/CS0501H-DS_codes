#include <iostream>
#include <cstring>
using namespace std;

#define mod 1226959

struct edge
{
	int *length;
	edge *next;
	edge()
	{
		length = NULL;
		next = NULL;
	}
	edge(int *x)
	{
		next = NULL;
			length = new int[6];
		for (int i = 0; i < 6; ++i)
		{
			length[i] = x[i];
		}
	}
};

edge **hash1 = new edge*[mod];

int Hash1(int *x)
{
	int res = 0;
	for (int i = 0; i < 6; ++i)
	{
		res += (long long)x[i] * x[i] % mod;
		res %= mod;
	}
	return res;
}

bool equa(int *a, int *b)
{
	int st, i, j;
	for (st = 0; st < 6; ++st)
	{
		for (i = st, j = 0; j < 6; j++, i = (i + 1) % 6)
		{
			if (a[i] != b[j])
				break;
		}
		if (j == 6)
			return true;
	}
	for (st = 0; st < 6; ++st)
	{
		for (i = st, j = 0; j < 6; j++, i = (i + 5) % 6)
		{
			if (a[i] != b[j])
				break;
		}
		if (j == 6)
			return true;
	}
	return false;
}

bool insert(int *x)
{
	int pos = Hash1(x);
	if (!hash1[pos])
	{
		hash1[pos] = new edge(x);
		return true;
	}
	
	edge *now = hash1[pos];
	while (now->next != NULL)
	{
		if (!equa(now->length, x))
			now = now->next;
		else
			return false;
	}
	if (equa(now->length, x))
		return false;

	now->next = new edge(x);
	return true;
}

int main()
{
	int n, m, length[6];
	bool flag;
	scanf("%d", &n);
	while (n--)
	{
		for (int i = 0; i < mod; ++i)
			hash1[i] = NULL;

		flag = 0;
		scanf("%d", &m);
		for (int i = 0; i < m; ++i)
		{
			for (int i = 0; i < 6; ++i)
				scanf("%d", &length[i]);
			if (!flag)
			{
				if (!insert(length))
				{
					flag = 1;
				}
			}
		}
		if (flag)
			printf("Twin snowflakes found.\n");
		else
			printf("No two snowflakes are alike.\n");
	}


	return 0;
}