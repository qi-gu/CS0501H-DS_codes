#include <iostream>
using namespace std;

int tree[400005], lazy[400005];
int b[100005], a[100005], n;

int min(int a, int b)
{
    return a < b ? a : b;
}

void pushup(int pos)
{
    tree[pos] = min(tree[pos << 1], tree[pos << 1 | 1]);
}

void pushdown(int pos, int l, int r)
{
    if (l == r || !lazy[pos])
        return;

    int lc = pos << 1;
    int rc = lc + 1;
    tree[lc] += lazy[pos];
    lazy[lc] += lazy[pos];
    tree[rc] += lazy[pos];
    lazy[rc] += lazy[pos];
    lazy[pos] = 0;
}

void build(int pos, int l, int r)
{
    if (l == r)
    {
        tree[pos] = b[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(pos << 1, l, mid);
    build(pos << 1 | 1, mid + 1, r);
    pushup(pos);
}

void update(int pos, int l, int r, int x, int y)		//区间内叶子节点全部-1
{
    pushdown(pos, l, r);
    if (l >= x && r <= y)
    {
        --tree[pos];
		--lazy[pos];
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= x)
        update(pos << 1, l, mid, x, y);
    if (mid < y)
        update(pos << 1 | 1, mid + 1, r, x, y);
    pushup(pos);
}

int query(int pos, int l, int r)		//查找最后0的下标
{
    pushdown(pos, l, r);
    if (l == r)
    {
        if (l != n)
        {
            update(1, 1, n, r + 1, n);
        }
        tree[pos] = 1000000;
        while (pos)
		{
            pos >>= 1;
            pushup(pos);
        }
        return l;
    }
    int mid = (l + r) >> 1;
    if (!tree[pos << 1 | 1])
        return query(pos << 1 | 1, mid + 1, r);
    return query(pos << 1, l, mid);

}

int main()
{
    int tmp;
    scanf("%d", &n);
    tmp = n;
    for (int i = 1; i <= n; ++i)
        scanf("%d", &b[i]);
    build(1, 1, n);

    while (tmp--)
    {
        int x = query(1, 1, n);
        a[x] = n - tmp;
    }

    for (int i = 1; i <= n; ++i)
        printf("%d ", a[i]);

    return 0;
}