#include <iostream>
using namespace std;

int max_s;
long long *queue;

void enq(long long x)
{
	int pos = ++max_s;
	while (x < queue[pos / 2])
	{
		queue[pos] = queue[pos / 2];
		pos /= 2;
	}
	queue[pos] = x;
}

long long deq(void)
{
	long long min = queue[1];
	long long tmp = queue[max_s--], pos = 1, child;
	while (pos * 2 <= max_s)
	{
		getchar();
		child = pos * 2;
		if (child != max_s && queue[child] > queue[child + 1])
			++child;
		if (queue[child] < tmp)
		{
			queue[pos] = queue[child];
			pos = child;
		}
		else
			break;
	}
	queue[pos] = tmp;

	return min;
}



int main(void)
{
	int n, m, zero;
	long long tmp, res = 0;
	max_s = 0;
	scanf("%d %d", &n ,&m);
	
	zero = (m - (n % (m - 1))) % (m - 1);
	queue = new long long[n + zero + 1];
	for (int i = 0; i < zero; ++i)
		enq(0);
	for (int i = 0; i < n; ++i)
	{
		scanf("%lld", &tmp);
		enq(tmp);
	}

	while (max_s > 1)
	{
		tmp = 0;
		for (int i = 0; i < m; ++i)
		{
			tmp += deq();
		}
		enq(tmp);
		res += tmp;
	}
	printf("%lld", res);
	fflush(stdin);
	getchar();

	return 0;
}
