#include <iostream>
#include <cstring>
using namespace std;


int arr[100005];
int heap[100005];
int len;



void insert(int x)
{
	int root = ++len;
	heap[root] = x;
	while (x > heap[root >> 1] && root > 1)
	{
		int fa = root >> 1;
		swap(heap[fa], heap[root]);
		root = fa;
	}
}

void down(int pos)
{
	int son = pos << 1;
	if (son < len && heap[son] < heap[son + 1])
		++son;
	if (heap[pos] < heap[son] && son <= len)
	{
		swap(heap[pos], heap[son]);
		down(son);
	}
}

int pop()
{
	int tmp = heap[1];
	heap[1] = heap[len--];
	down(1);
	return tmp;
}

int main()
{
	int n, tmp;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &tmp);
		insert(tmp);
	}

	for (int i = 1; i <= n; ++i)
	{
		printf("%d ", heap[i]);
	}
	printf("\n");
	for (int i = n; i; --i)
	{
		arr[i] = pop();
	}
	for (int i = 1; i <= n; ++i)
	{
		printf("%d ", arr[i]);
	}


	return 0;
}