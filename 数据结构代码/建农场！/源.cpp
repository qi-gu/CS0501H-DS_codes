#include <iostream>
using namespace std;

int main()
{
	int n, m, a, res = 1133774, head, tail, tmp;
	scanf("%d %d %d",&n, &m, &a);
	int **time = new int*[n], **max = new int*[n], **min = new int*[n], *queue = new int[n];
	int **min_line = new int*[n];

	for (int i = 0; i < n; ++i)
	{
		time[i] = new int[m];
		max[i] = new int[m];
		min[i] = new int[m];
		min_line[i] = new int[m];
		for (int j = 0; j < m; ++j)
			scanf("%d", &time[i][j]);
	}

	for (int j = 0; j < m; j++)
	{
		queue[0] = head = tail = 0;
		for (int i = 0; i < n; ++i)		//	分别单调队列计算每一列，元素往后k个的最大、最小值
		{
			while (head <= tail && time[queue[tail]][j] >= time[i][j])
				--tail;
			queue[++tail] = i;
			while (i - queue[head] >= a)
				++head;

			if (i >= a - 1)
				min[i - a + 1][j] = time[queue[head]][j];

		}

		queue[0] = head = tail = 0;
		for (int i = 0; i < n; ++i)
		{
			while (head <= tail && time[queue[tail]][j] <= time[i][j])
				--tail;
			queue[++tail] = i;
			while (i - queue[head] >= a)
				++head;

			if (i >= a - 1)
				max[i - a + 1][j] = time[queue[head]][j];

		}
	}

	
	delete []queue;
	queue = new int[m];		//每一行单调队列，从元素开始往后k个最大、最小值，res存储最小差

	for (int i = 0; i < n - a + 1; ++i)
	{
		queue[0] = head = tail = 0;;
		for (int j = 0; j < m; ++j)
		{
			while (tail >= head && min[i][queue[tail]] >= min[i][j])
				--tail;
			queue[++tail] = j;
			while (j - queue[head] >= a)
				++head;

			if (j >= a - 1)
				min_line[i][j - a + 1] = min[i][queue[head]];
		}

		queue[0] = head = tail = 0;
		for (int j = 0; j < m; ++j)
		{
			while (tail >= head && max[i][queue[tail]] <= max[i][j])
				--tail;
			queue[++tail] = j;
			while (j - queue[head] >= a)
				++head;

			if (j >= a - 1)
			{
				tmp = max[i][queue[head]];
				res = res < (tmp - min_line[i][j - a + 1]) ? res : (tmp - min_line[i][j - a + 1]);
			}
		}

	}
	

	printf("%d", res);

	return 0;
}
