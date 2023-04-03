#include <iostream>
using namespace std;

int f[100005], num[100005];

inline void read(int &x)
{
	bool posi = true;
	x = 0;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			posi = false;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
	if (!posi)
		x = (~x) + 1;
}

void init(int n)
{
	for (int i = 1; i <= n; ++i)
	{
		f[i] = i;
		num[i] = 1;
	}
}

int find(int x)
{
	if (f[x] == x)
		return x;
	return f[x] = find(f[x]);
}

void uni(int a, int b)
{
	int fa = find(a), fb = find(b);
	if (fa == fb)
		return;
	f[fa] = fb;
	num[fb] += num[fa];
}


int main()
{
	int n, m, p, q, male, female, a, b;
	read(n); read(m); read(p); read(q);
	init(n);
	while (p--)
	{
		read(a); read(b);
		uni(a, b);
	}
	male = num[find(1)];
	init(m);
	while (q--)
	{
		read(a); read(b);
		uni(-a, -b);
	}
	female = num[find(1)];
	printf("%d", male < female ? male : female);
	return 0;
}