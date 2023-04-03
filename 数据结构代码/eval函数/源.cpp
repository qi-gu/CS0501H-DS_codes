#include <iostream>
using namespace std;

char str[4000001];
long long pos;

int read()
{
	int x = 0;
	while (str[pos] >= '0' && str[pos] <= '9')
	{
		x = x * 10 + str[pos] - '0';
		++pos;
	}
	return x;
}

template <typename T>
class stack
{
private:
	struct node
	{
		T data;
		node *next;
		node() : next(NULL) {}
	};
	node *head;
public:
	stack()
	{
		head = new node;
		head->next = NULL;
	}
	void push(T i)
	{
		node *tmp = new node;
		tmp->data = i;
		tmp->next = head->next;
		
		head->next = tmp;
	}

	T pop()
	{
		T tmp = head->next->data;
		node *x = head->next;
		head->next = x->next;
		delete x;
		return tmp;
	}

	T top()
	{
		return head->next->data;
	}
	bool empty()
	{
		if (head->next)
			return false;
		else
			return true;
	}


};

int cal(char c, int a, int b)
{
	if (c == '+')
		return a + b;
	if (c == '-')
		return b - a;
	return a ^ b;
}



int main()
{
	scanf("%s", str);
	int wei[128];
	char tmp;
	wei['^'] = 1;
	wei['-'] = wei['+'] = 2;
	stack<int> num;
	stack<char> op;
	while (str[pos])
	{
		if (str[pos] >= '0' && str[pos] <= '9')
			num.push(read());
		else if (str[pos] == ')')
		{
			while ((tmp = op.pop()) != '(')
			{
				int a = num.pop();
				int b = num.pop();
				num.push(cal(tmp, a, b));
			}
			++pos;
		}
		else if ((!op.empty()) && str[pos] != '(' && op.top() != '(' && wei[str[pos]] <= wei[op.top()])
		{
			int a = num.pop();
			int b = num.pop();
			num.push(cal(op.pop(), a, b));
			op.push(str[pos++]);
		}
		else
			op.push(str[pos++]);
	}

	while (!op.empty())
	{
		int a = num.pop();
		int b = num.pop();
		tmp = op.pop();
		num.push(cal(tmp, a, b));
	}

	printf("%d", num.top());

	return 0;
}