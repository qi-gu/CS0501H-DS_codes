#include <iostream>
using namespace std;

int f(int n, int m, int start)
{
	if (n == 1)
		return 0;
	if (n == 2)
		return (start + m) % 2;

	int del = (m + start - 1) % (2 * n - 2), res;
	if (del < n - 1)
	{
		res = f(n - 1, m, del);
	}
	else
	{
		res = f(n - 1, m, del - 1);
	}

	if (del >= n)
		del = 2 * n - 2 - del;

	if (res >= del)
		res++;

	return res;

}


int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	printf("%d", f(n, m, 0) + 1);
	return 0;
}