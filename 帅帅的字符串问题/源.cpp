#include <iostream>
#include <cstring>
using namespace std;

#define base 233;
#define mod 1000000007;

char s[1000005];
int hash[1000005];

int main()
{
	int length, i;
	while (1)
	{
		scanf("%s", s);
		if (s[0] == '.')
			break;
		length = strlen(s);
		for (i = 1; i <= length >> 1; ++i)
		{
			if (length % i)
				continue;
			int now = i;
			while (now < length && s[now] == s[now % i])
				++now;
			if (now == length)
			{
				printf("%d\n", length / i);
				break;
			}
		}
		if (i > length >> 1)
			printf("1\n");
	}

	return 0;
}