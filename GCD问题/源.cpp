#include <iostream>
using namespace std;

int log(int x)
{
	int n = 0;
	while (x >>= 1)
		n++;
	return n;
}


int cal(int x, int y)
{
	if (x < y)
	{
		x ^= y;
		y ^= x;
		x ^= y;
	}

	int d = x % y;
	if (!d)
		return y;
	
	return cal(y, d);
}

int quiry(int l, int r, int **st)
{
	int tmp = log(r - l + 1);
	return cal(st[l][tmp], st[r - (1 << tmp) + 1][tmp]);
}


int main()
{
	getchar();
    int n, m, l, r, res, tmp, tmpL, tmpR;
    scanf("%d %d", &n, &m);
	int *data = new int[n], **st = new int*[n], depth = log(n);
    for(int i = 0; i < n; ++i)
	{
        scanf("%d", &data[i]);
		st[i] = new int[depth];
		st[i][0] = data[i];
    }

    for(int j = 1; j <= depth; ++j)
	{
        for(int i = 0; i + (1 << j) - 1 < n; ++i)
		{
			st[i][j] = cal(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
		}
	}
    while (m--)
	{
		scanf("%d %d", &l, &r);
		--l;--r;
		res = quiry(l, r, st);
		
		int l_an;
		tmpL = l, tmpR = r;
		while (tmpL < tmpR)
		{
			tmp = (tmpL + tmpR) >> 1;
			if (quiry(l, tmp, st) > res)
			{
				tmpL = tmp + 1;
			}
			else
				tmpR = tmp;
		}
		l_an = tmpL;

		tmpL = r, tmpR = n - 1;
		while (tmpL < tmpR)
		{
			tmp = (tmpL + tmpR + 1) >> 1;
			if (quiry(l, tmp, st) < res)
			{
				tmpR = tmp - 1;
			}
			else
				tmpL = tmp;
		}
		if (r == n - 1 && l < r)
			tmpR = n - 1;
		printf("%d %d\n", res, tmpR - l_an);
    }

	fflush(stdin);
	getchar();
    return 0;
}