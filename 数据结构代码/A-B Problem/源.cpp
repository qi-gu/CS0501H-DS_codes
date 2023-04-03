#include <iostream>
#include <cstring>
using namespace std;

int *arr, *help;
void merge(int l, int r)
{
	for (int i = l; i <= r; ++i)
		help[i] = arr[i];
    
	int mid = (l + r) >> 1;
	int i = l, j = mid + 1;
	for (int k = l; k <= r; ++k)
	{
		if (j > r || (i <= mid && help[i] < help[j]))
			arr[k] = help[i++];
		else
			arr[k] = help[j++];
    }
}

void sort(int l, int r)
{
	if (l >= r)
		return;
	int mid = (l + r) >> 1;
	sort(l, mid);
	sort(mid + 1, r);
	merge(l, r);
}

int main()
{
	int n, c, s = 0, b = 1, num = 0, tmp;
	scanf("%d %d", &n, &c);
	arr = new int[n];
	help = new int[n];
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &arr[i]);
	}
	sort(0, n - 1);
	
	if (n == 1 && !c)
	{
		printf("1");
		return 0;
	}
	else if (n == 1)
	{
		printf("0");
		return 0;
	}

	while (b < n)
	{
		tmp = arr[b] - arr[s];
		if (tmp == c)
		{
			int m = s, n = b;
			while (arr[s] == arr[m])
				++s;
			while (arr[b] == arr[n])
				++b;
			num += (s - m) * (b - n);
		}
		else if (tmp > c)
			++s;
		else
			++b;
	}
	printf("%d", num);

	return 0;
}