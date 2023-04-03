#include <iostream>
using namespace std;

int f[10005], enemy[10005];

int find(int x)
{
	if (x == f[x])
		return x;
	return f[x] = find(f[x]);
}
bool uni(int a, int b)
{
	int fa = find(a), fb = find(b);
	if (fa == fb)
		return false;
	f[fa] = fb;
	return true;
}

int main()
{
	int n, m, a, b, max, tmp;
	char r;
	cin >> n;
	cin >> m;
	max = n;
	for (int i = 1; i <= n; ++i)
	{
		f[i] = i;
	}
	//for (int i = 0; i < m; ++i)
	while (m--)
	{
		cin >> r >> a >> b;
		if (r == 'F')
		{
			if (uni(a, b))
				--max;
		}
		else
		{
			if (!enemy[a])
			{
				enemy[a] = b;
			}
			else
			{
				if (uni(enemy[a], b))
					--max;
			}
			if (!enemy[b])
			{
				enemy[b] = a;
			}
			else
			{
				if (uni(a, enemy[b]))
					--max;
			}
		}
	}
	printf("%d", max);

	return 0;
}