#include <iostream>
using namespace std;

int tot = 0;
int tree[1000005][26];
bool e[1000005];

void insert(char *s)
{
	int root = 0;
	for (int i = 0; s[i]; ++i)
	{
		if (!tree[root][s[i] - 'a'])
			tree[root][s[i] - 'a'] = ++tot;
		root = tree[root][s[i] - 'a'];
	}
	e[root] = true;
}

void del(char *s)
{
	int root = 0, i = 0;
	for (; s[i + 1]; ++i)
	{
		if (!tree[root][s[i] - 'a'])
			return;
		root = tree[root][s[i] - 'a'];
	}
	
	tree[root][s[i] - 'a'] = 0;
	if (e[root])
		return;
	for (int x = 0; x < 26; ++x)
	{
		if (tree[root][x])
		{
			return;
		}
	}
	
	if (i > 0)
	{
		s[i] = '\0';
		del(s);
	}
}

bool search(char *s)
{
	int root = 0, i = 0;
	for (; s[i]; ++i)
	{
		if (!tree[root][s[i] - 'a'])
			return false;
		root = tree[root][s[i] - 'a'];
	}
	return true;
}

int main()
{
	int n;
	char *s = new char[31];
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s", s);
		switch (s[0])
		{
		case 'i':
			scanf("%s", s);
			insert(s);
			break;
		case 's':
			scanf("%s", s);
			if (search(s))
				printf("Yes\n");
			else
				printf("No\n");
			break;
		case 'd':
			scanf("%s", s);
			del(s);
		}
	}
	fflush(stdin);
	getchar();

	return 0;
}
