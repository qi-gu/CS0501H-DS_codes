#include <iostream>
using namespace std;


int pre[5005], mid[5005];



class tree
{
private:
	struct node
	{
		int data;
		node *left, *right;
		node() : left(NULL), right(NULL) {}
	};
	
	node *root;

	void postOrder(node *t) const
	{
		if (t->left)
			postOrder(t->left);
		if (t->right)
			postOrder(t->right);
		printf("%d ", t->data);
	}

	node *creat(int pre_s, int pre_e, int mid_s, int mid_e)
	{
		node *root = new node;
		root->data = pre[pre_s];
		if (pre_s == pre_e)
			return root;
		if (pre_s > pre_e)
			return NULL;
		int i = mid_s, newpre_s = pre_s + 1, newpre_e, newmid_s, newmid_e;
		while (mid[i] != pre[pre_s])
		{
			i++;
		}
		newpre_e = i - mid_s + pre_s;
		newmid_s = mid_s;
		newmid_e = i - 1;
		root->left = creat(newpre_s, newpre_e, newmid_s, newmid_e);
		newpre_s = newpre_e + 1;
		newpre_e = pre_e;
		newmid_s = newmid_e + 2;
		newmid_e = mid_e;
		root->right = creat(newpre_s, newpre_e, newmid_s, newmid_e);

		return root;
	}



public:
	void solve(int n)
	{
		root = creat(0, n - 1, 0, n - 1);
	}


	void postOrder()
	{
		postOrder(root);
	}
};

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &pre[i]);
	}
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &mid[i]);
	}
	tree res;
	res.solve(n);
	res.postOrder();

	return 0;
}
