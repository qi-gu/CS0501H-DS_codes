#include <iostream>
using namespace std;

int tree[20000005][2], tot = 0;

void insert(int x)
{
	int root = 0, n = sizeof(int) * 8;
	while (n--)
	{
		int tmp = (x >> n) & 1;
		if (!tree[root][tmp])
			tree[root][tmp] = ++tot;
		root = tree[root][tmp];
	}
}

int find(int data)
{
	int res = 0, root = 0, n = sizeof(int) * 8;
	while (n--)
	{
		int tmp = (data >> n) & 1;
		if (tree[root][!tmp])
		{
			root = tree[root][!tmp];
			res = res | (1 << n);
		}
		else
		{
			root = tree[root][tmp];
		}
	}
	return res;

}

int main()
{
	int n, m, tmp;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &tmp);
		insert(tmp);
	}
	for (int i = 0; i < m; ++i)
	{
		scanf("%d", &tmp);
		printf("%d\n", find(tmp));
	}


	return 0;
}