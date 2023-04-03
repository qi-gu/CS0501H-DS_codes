#include <iostream>
using namespace std;

int tree[6005][6005], tran_m, tran_n;

inline int read()
{
    char ch = getchar();
	if (ch == EOF)
		return -1;
    int x = 0, f = 1;
    while(ch < '0' || ch > '9') 
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9') 
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    } 
    return x * f;
}
int lowbit(int x)
{
	return x & -x;
}

void add(int x, int y, int d)
{
	for(int i = x; i <= tran_m; i += lowbit(i))
		for(int j = y; j <= tran_n; j += lowbit(j))
			tree[i][j] += d;
}

int query_sum(int x, int y)
{
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
		for (int j = y; j; j -= lowbit(j))
			ans += tree[i][j];
	return ans;
}

int main()
{
	int op, x, y, d, m, n;
	m = read();
	n = read();
	tran_m = tran_n = m + n;

	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n; ++j)
		{
			add(i + j, i - j + n, read());
		}

	while ((op = read()) != -1)
	{
		y = read(); x = read(); d = read();
		if (op == 1)
		{
			add(x + y, x - y + n, d);
		}
		else
		{
			int ans = query_sum(x + y + d, x - y + n + d) + query_sum(x + y - d - 1, x - y + n - d - 1)
				- query_sum(x + y - d - 1, x - y + n + d) - query_sum(x + y + d, x - y + n - d - 1);
			printf("%d\n", ans);
		}
	}



	return 0;
}