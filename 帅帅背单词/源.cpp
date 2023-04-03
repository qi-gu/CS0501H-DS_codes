#include <iostream>
#include <cstring>
using namespace std;

#define base 233
#define mod 21788233

bool exist[mod];
int cal_num[mod], book[200005];

int Hash(char *s)
{
	int len = strlen(s), res = 0;
	for (int i = 0; i < len; ++i)
		res = ((long long)res * base + s[i]) % mod;
	return res % mod;
}

int main()
{
	int n, max_num = 0, min_length = 200005, left = 0, right = -1, num = 0;
	char *s = new char[15];
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s", s);
		exist[Hash(s)] = 1;
	}
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%s", s);
		book[i] = Hash(s);
		if (exist[book[i]] && !cal_num[book[i]])
		{
			++max_num;
			cal_num[book[i]] = true;
		}
	}
	if (!max_num)
	{
		printf("0\n0");
		return 0;
	}
	for (int i = 0; i < mod; ++i)
	{
		cal_num[i] = 0;
	}
	while (right < n)
	{
		while (num < max_num && right < n)
		{
			if (exist[book[++right]] && !(cal_num[book[right]]++))
				++num;
		}
		while (left <= right)
		{
			if (exist[book[left]])
			{
				if (!(--cal_num[book[left]]))
				{
					++left;
					break;
				}
			}
			++left;
		}
		--num;
		if (right < n)
			min_length = min_length < right - left + 2 ? min_length : right - left + 2;
	}
	printf("%d\n%d", max_num, min_length);

	return 0;
}