#include <iostream>
using namespace std;

int cnt;
int tree[1000005][26], fail[1000005];
bool e[1000005];

void insert(char *s)
{
	int root = 0;
	for (int i = 0; s[i]; ++i)
	{
		if (e[root])
			return;
		if (!tree[root][s[i] - 'a'])
			tree[root][s[i] - 'a'] = ++cnt;
		root = tree[root][s[i] - 'a'];
	}
	e[root] = 1;
}

void bfs(int root)
{
	int now = 0, pre = 0;
	for (int c = 0; c < 26; ++c)	//枚举每个子节点
	{
		if (!tree[root][c])		//不存在该子节点，处理下一个
			continue;
		pre = fail[root];		//对该子节点，先回到pre比较两者子节点
		while (pre != -1 && !(tree[pre][c]))	//pre不存在该子节点，继续回溯
		{
			pre = fail[pre];
		}
		if (pre == -1)			//回溯到头，该子节点fail为0，处理下一个子节点
		{
			fail[tree[root][c]] = 0;
			continue;
		}
		fail[tree[root][c]] = tree[pre][c];		//回溯没到头时比较成功，子节点fail设为回溯节点的同一个子节点
	}
	for (int i = 0; i < 26; ++i)				//对每一个子节点，处理其子节点
		if (tree[root][i])
			bfs(tree[root][i]);
}

bool find(char *s)
{
	fail[0] = -1;
	bfs(0);

	int i = 0, root = 0;
	while (s[i] && !e[root])
	{
		if (root == -1)		//若回溯到头，则从头开始比较文本中下一个字符
		{
			++root;
			++i;
		}
		else if (tree[root][s[i] - 'a'])	
		{
			root = tree[root][s[i] - 'a'];
			++i;
		}
		else	//kmp回溯
		{
			root = fail[root];
		}
	}
	if (e[root])
		return true;
	else
		return false;
}

int main()
{
	int n;
	char s[1000005];
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s", s);
		insert(s);
	}
	scanf("%s", s);
	if (find(s))
		printf("valar morghulis");
	else
		printf("valar dohaeris");

	return 0;
}