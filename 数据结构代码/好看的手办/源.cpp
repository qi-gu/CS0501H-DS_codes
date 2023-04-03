#include <iostream>
#include <stack>
using namespace std;

int height[100005], L[100005], R[100005], tree[100001];
stack<int> l, r;

int lowbit(int x)
{
	return x & -x;
}

void insert(int x)
{
	for (int i = x; i <= 100000; i += lowbit(i))
	{
		++tree[i];
	}

}

int query(int x)
{
	int res = 0;
	for (int i = x; i; i -= lowbit(i))
		res += tree[i];
	return res;
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &height[i]);
	}
	for (int i = 1; i <= n; ++i)
	{
		L[i] = i - 1 - query(height[i]);
		insert(height[i]);
	}
	for (int i = 1; i <= 100000; ++i)
		tree[i] = 0;
	for (int i = n; i >= 1; --i)
	{
		R[i] = n - i - query(height[i]);
		insert(height[i]);
	}
	


	int num = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (L[i] > (R[i] << 1) || R[i] > (L[i] << 1))
			++num;
	}
	printf("%d", num);

	return 0;
}