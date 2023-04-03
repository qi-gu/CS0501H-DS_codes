#include <iostream>
#define mod % 49999999
using namespace std;

struct e
{
	int to;
	int next;
} edge[205];

int cnt, group, head[105], len[105], cmp[30005][2];
long long Hash[105];

int prime[105] =
{
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
	53,	59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
	127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197,
	199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
	283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379,
	383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
	467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571
};

void add(int a, int b)
{
	edge[++cnt].to = b;
	edge[cnt].next = head[a];
	head[a] = cnt;

	edge[++cnt].to = a;
	edge[cnt].next = head[b];
	head[b] = cnt;
}

void dfs(int root, int fa)
{
	len[root] = 0;
	Hash[root] = 1;
	for (int i = head[root]; i; i = edge[i].next)
	{
		if (edge[i].to == fa)
			continue;
		dfs(edge[i].to, root);
		Hash[root] += Hash[edge[i].to] * prime[len[edge[i].to]];
		++len[root];
	}
	Hash[root] = Hash[root] mod;
}

int main()
{
	int n, m, root, a, b, time;
	scanf("%d %d", &n, &m);
	while (m--)
	{
		scanf("%d", &root);
		++root;
		for (int i = 1; i < n; ++i)
		{
			scanf("%d %d", &a, &b);
			add(a + 1, b + 1);
		}
		dfs(root, 0);
		for (time = 1; time <= group; ++time)
		{
			if (cmp[time][0] == Hash[root])
			{
				++cmp[time][1];
				break;
			}
		}
		if (time > group)
		{
			cmp[++group][0] = Hash[root];
			cmp[group][1] = 1;
		}
		cnt = 0;
		for (int i = 0; i < 105; ++i)
			head[i] = 0;
	}
	m = 0;
	for (time = 1; time <= group; ++time)
	{
		m = m > cmp[time][1] ? m : cmp[time][1];
	}
	printf("%d", m);

	return 0;
}