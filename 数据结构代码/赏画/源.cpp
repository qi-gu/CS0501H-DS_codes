#include <iostream>
using namespace std;


int main()
{
	int n, m, cnt = 0, start = 0, length = 1000001, tmp_s = 0;
	scanf("%d %d", &n, &m);
	int *data = new int[n], *times = new int[m + 1];
	for (int i = 0; i <= m; ++i)
		times[i] = 0;
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &data[i]);
		if (!times[data[i]])
			++cnt;
		++times[data[i]];
		if (cnt == m)
		{
			while (--times[data[tmp_s++]]);
			--cnt;
			if (i - tmp_s + 2 < length)
			{
				length = i - tmp_s + 2;
				start = tmp_s - 1;
			}
			
		}

	}

	printf("%d %d", start + 1, start + length);

	return 0;
}
