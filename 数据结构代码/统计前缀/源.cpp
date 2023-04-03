#include <iostream>
using namespace std;

int tree[1000005][26], tot = 0;
int e[1000005];

void insert(char *s)
{
	int root = 0;
	for (int i = 0; s[i]; ++i)
	{
		if (!tree[root][s[i] - 'a'])
			tree[root][s[i] - 'a'] = ++tot;
		root = tree[root][s[i] - 'a'];
	}
	e[root] = 1;
	
}

int search(int root)
{
	int num = 0;
	for (int i = 0; i < 26; ++i)
	{
		if (!tree[root][i])
			continue;
		num += search(tree[root][i]);
	}
	
	if (e[root])
		++num;
	return num;
}

int q(char *s)
{
	int num = 0, i = 0, root = 0;
	for (; s[i]; ++i)
	{
		if (!tree[root][s[i] - 'a'])
			return 0;
		root = tree[root][s[i] - 'a'];
	}
	return search(root);
}


int main()
{
	int n;
	char *s = new char[11];
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%s", s);
		insert(s);
	}
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%s", s);
		printf("%d\n", q(s));
	}

	fflush(stdin);
	getchar();
	return 0;
}
