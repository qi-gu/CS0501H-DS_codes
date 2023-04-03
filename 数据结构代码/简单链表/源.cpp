#include <iostream>
using namespace std;

class list
{
private:
	struct node
	{
		int val;
		node *next;
	};
	node *head, *last;
public:
	list(void)
	{
		head = new node;
		last = head;
	}
	~list()
	{
		node *now = head, *last;
		while (now)
		{
			last = now;
			now = now->next;
			delete last;
		}
	}
	void insert(int x, int y)
	{
		node *now = head;
		while (x--)
		{
			now = now->next;
		}
		node *tmp = new node;
		tmp->val = y;
		tmp->next = now->next;
		now->next = tmp;
	}
	void del(int x)
	{
		node *now = head, *last;
		while (x--)
		{
			last = now;
			now = now->next;
		}
		last->next = now->next;
		delete now;
	}
	void push(int x)
	{
		node *tmp = new node;
		tmp->val = x;
		last->next = tmp;
		last = tmp;
		last->next = NULL;
	}
	void show()
	{
		node *now = head->next;
		while (now)
		{
			printf("%d ", now->val);
			now = now->next;
		}
	}
};


int main(void)
{
	int n, m, tmp, opt;
	list a;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &tmp);
		a.push(tmp);
	}
	while (m--)
	{
		scanf("%d", &opt);
		if (opt == 1)
		{
			scanf("%d %d", &opt, &tmp);
 			a.insert(opt, tmp);
		}
		else
		{
			scanf("%d", &tmp);
			a.del(tmp);
		}
	}
	a.show();

	return 0;
}