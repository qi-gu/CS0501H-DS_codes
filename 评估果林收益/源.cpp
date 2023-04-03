#include <iostream>
using namespace std;


int main()
{
	int n, k, head = 0, tail = 0, i = 0;
	scanf("%d %d", &n, &k);
	int *data = new int[n], *min = new int[n], *result = new int[n];
	min[0] = 0;

	for (; i < k - 1; i++)
	{
		scanf("%d", &data[i]);		//要求最小，递增单调队列
		while (head <= tail && data[i] < data[min[tail]])
		{
			tail--;
		}
		min[++tail] = i;
		while (i - min[head] >= k)
			head++;
	}
	for (; i < n; i++)
	{
		scanf("%d", &data[i]);		//要求最小，递增单调队列
		while (head <= tail && data[i] < data[min[tail]])
		{
			tail--;
		}
		min[++tail] = i;
		while (i - min[head] >= k)
			head++;
		
		result[i - k + 1] = data[min[head]];
	}
/*
	scanf("%d", &k);
	printf("%d", result[k]);
	tmp = getchar();
	if (tmp == EOF)
		return 0;*/
	while (cin >> k)
	{
		printf("%d\n", result[k]);
	}

	return 0;
}