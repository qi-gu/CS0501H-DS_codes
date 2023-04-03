#include <iostream>
using namespace std;

#define mod1 122777
#define mod2 1226959

bool hash_1[mod1], hash_2[mod2]; 

inline void read(long long &x)
{
	x = 0;
	char c = getchar();

	while (c < '0' || c > '9')
		c = getchar();
	while (c >= '0' && c <= '9')
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
}


int main()
{
	long long t, n, m1, m2;
	long long tmp;
	read(t);
	while (t--)
	{
		read(n);
		while (n--)
		{
			read(tmp);
			m1 = tmp % mod1;
			m2 = tmp % mod2;
			if (!(hash_1[m1] && hash_2[m2]))
			{
				printf("%lld ", tmp);
				hash_1[m1] = 1;
				hash_2[m2] = 1;
			}
		}
		printf("\n");
		for (tmp = 0; tmp < 122777; ++tmp)
			hash_2[tmp] = hash_1[tmp] = 0;
		for (;tmp < 1226959; ++tmp)
			hash_2[tmp] = 0;
	}
	return 0;
}