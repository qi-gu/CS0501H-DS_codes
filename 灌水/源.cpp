#include <iostream>
using namespace std;

int w[305][305], dis[305];
bool exist[305];

inline int read()
{
	int x = 0;
	char c = getchar();
	bool pos = true;
	while (c < '0' || c > '9')
	{
		if (c == '-')
			pos = false;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	if (!pos)
		x = -x;
	return x;
}



int main()
{
	int n, cost = 0;
	n = read();
	for (int i = 1; i <= n; ++i)
	{
		w[n + 1][i] = w[i][n + 1] = read();
		dis[i] = 0x3f3f3f3f;
	}
	dis[n + 1] = dis[0] = 0x3f3f3f3f;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
			w[i][j] = read();
	}
	dis[1] = 0;
	for (int i = -1; i < n; ++i)
	{
		int pos = 0;
		for (int j = 1; j <= n + 1; ++j)
		{
			if (!exist[j] && dis[j] < dis[pos])
				pos = j;
		}
		exist[pos] = true;
		cost += dis[pos];
		for (int nxt = 1; nxt <= n + 1; ++nxt)
		{
			if (exist[nxt])
				continue;

			dis[nxt] = dis[nxt] < w[pos][nxt] ? dis[nxt] : w[pos][nxt];
		}

	}
	printf("%d", cost);



	return 0;
}