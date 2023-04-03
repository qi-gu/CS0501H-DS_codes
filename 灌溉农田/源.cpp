#include <iostream>
using namespace std;

int main()
{
	int j = 0, n, pos, max = 0;
	scanf("%d", &n);
	int *left = new int[n], *right = new int[n], *tmp = new int[n], *data = new int[n];
	scanf("%d", &data[0]);
	tmp[0] = data[0];
	left[0] = right[0] = 0;
	for (int i = 1; i < n; i++)
	{
		scanf("%d", &data[i]);
		left[i] = right[i] = 0;
		pos = 1;
		while (tmp[j] <= data[i] && j>= 0)
		{
			left[i] += left[i - pos] + 1;
			pos += left[i - pos] + 1;
			j--;
		}
		tmp[++j] = data[i];
	}
	j = 0;
	tmp[0] = data[n - 1];
	for (int i = n - 2; i >= 0; i--)
	{
		pos = 1;
		while (tmp[j] <= data[i] && j >= 0)
		{
			right[i] += right[i + pos] + 1;
			pos += right[i + pos] + 1;
			j--;

		}
		tmp[++j] = data[i];

	}
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &tmp[i]);
		//printf("%d %d\n", left[i], right[i]);
		left[i] = (left[i] + right[i] + 1) * tmp[i];
		if (max < left[i])
		{
			max = left[i];
			pos = i;
		}

	}

	printf("%d %d", pos, max);



	return 0;
}