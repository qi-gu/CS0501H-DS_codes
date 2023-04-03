#include <iostream>
using namespace std;


int main()
{
	int n, m, k, sum_price = 0, head = 0, tail = 0, max = 0, tmp;
	scanf("%d %d %d", &n, &m, &k);
	int *baseP = new int[n];
	int *best_row = new int[m];
	int *honest_row = new int[m];
	int *queue = new int [m];
	queue[0] = 0;
	

	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &baseP[i]);
		sum_price += baseP[i];
	}

	for (int i = 0; i < m; ++i)
	{
		best_row[i] = 0;
		honest_row[i] = 0;
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			scanf("%d", &tmp);
			best_row[j] = best_row[j] > tmp ? best_row[j] : tmp;
			honest_row[j] += baseP[i] * tmp;
		}
	}


	for (int i = 1; i < m; ++i)
	{
		honest_row[i] += honest_row[i - 1];
	}

	for (int i = 0; i < m; ++i)
	{
		while (tail >= head && best_row[i] > best_row[queue[tail]])
			--tail;
		queue[++tail] = i;
		while (i - queue[head] >= k)
			++head;
		if (i == k - 1)
		{
			tmp = best_row[queue[head]] * k * sum_price - honest_row[i];
			max = max > tmp ? max : tmp;
		}
		else if (i >= k)
		{
			tmp = best_row[queue[head]] * k * sum_price - honest_row[i] + honest_row[i - k];
			max = max > tmp ? max : tmp;
		}

	}

	printf("%d", max);

	return 0;
}
