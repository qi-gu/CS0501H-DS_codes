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
	for (int c = 0; c < 26; ++c)	//ö��ÿ���ӽڵ�
	{
		if (!tree[root][c])		//�����ڸ��ӽڵ㣬������һ��
			continue;
		pre = fail[root];		//�Ը��ӽڵ㣬�Ȼص�pre�Ƚ������ӽڵ�
		while (pre != -1 && !(tree[pre][c]))	//pre�����ڸ��ӽڵ㣬��������
		{
			pre = fail[pre];
		}
		if (pre == -1)			//���ݵ�ͷ�����ӽڵ�failΪ0��������һ���ӽڵ�
		{
			fail[tree[root][c]] = 0;
			continue;
		}
		fail[tree[root][c]] = tree[pre][c];		//����û��ͷʱ�Ƚϳɹ����ӽڵ�fail��Ϊ���ݽڵ��ͬһ���ӽڵ�
	}
	for (int i = 0; i < 26; ++i)				//��ÿһ���ӽڵ㣬�������ӽڵ�
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
		if (root == -1)		//�����ݵ�ͷ�����ͷ��ʼ�Ƚ��ı�����һ���ַ�
		{
			++root;
			++i;
		}
		else if (tree[root][s[i] - 'a'])	
		{
			root = tree[root][s[i] - 'a'];
			++i;
		}
		else	//kmp����
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