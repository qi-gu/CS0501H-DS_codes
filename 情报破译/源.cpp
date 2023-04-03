#include <iostream>
using namespace std;

int main()
{
	int n, i = 0, k = -1;
	scanf("%d", &n);
	char *s = new char[n + 1];
	scanf("%s", s);
	int *next = new int[n];
	next[0] = k;

	while (s[i] != '\0')
	{
		if (k == -1 || s[i] == s[k])
		{
			i++;
			k++;
			next[i] = k;
		}
		else
		{
			k = next[k];
		}
	}

	/*for (int i = 0; i < n; i++)
	{
		cout << next[i] << " ";
	}*/
	cout << n - next[n - 1] - 1;
	return 0;
}