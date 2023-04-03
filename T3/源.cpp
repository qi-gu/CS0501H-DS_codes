#include <iostream>

using namespace std;

template <typename T>
class LinkedList
{
protected:
	struct node
    {
        T val;
        node *next;
    };
    int len;
    node *head;

public:

    LinkedList(void)
    {
        len = 0;
        head = new node;
        head->next = NULL;
    }

    LinkedList(const LinkedList<T> &a)
    {
        len = a.len;
        head = new node;
        node *tmp = a.head, *now = head;
        while (tmp->next != NULL)
        {
            now->val = tmp->val;
            now->next = new node;
            now = now->next;
            tmp = tmp->next;
        }
        now->val = tmp->val;
        now->next = NULL;
    }

    ~LinkedList()
    {
        node *tmp = head, *last;
        while (tmp->next != NULL)
        {
            last = tmp;
            tmp = tmp->next;
            delete last;
        }
        delete tmp;
    }

    void pushFront(T a)
    {
        node *tmp = new node;
		tmp->val = a;
		tmp->next = head->next;
		head->next = tmp;
        len++;
    }

    void pushBack(T a)
    {
        node *now = head;
        int i = len;
        while (i--)
        {
            now = now->next;
        }
        now->next = new node;
        now->next->val = a;
        now->next->next = NULL;
        len++;
    }

    T popFront(void)
    {
        if (!len)
            return T();
		node *tmp = head->next;
        head->next = tmp->next;
        T x = tmp->val;
        delete tmp;
        len--;
        return x;
    }

    T popBack(void)
    {
        if (!len)
            return T();
        node *now = head;
        int i = len - 1;
        while (i--)
        {
            now = now->next;
        }
        T x = now->next->val;
        delete now->next;
        now->next = NULL;
        len--;
        return x;
    }

    int size(void) const
    {
        return len;
    }

    void print(void) const
    {
        int i = len - 1;
        node *now = head->next;
        while (i--)
        {
			cout << now->val << " ";
            now = now->next;
        }
		cout << now->val << endl;
    }

	virtual const char* name(void) {return "LinkedList";}
	virtual T peak(void) {return T();}
	virtual T pop(void) {return T();}
	virtual void push(T val) {}

};

template <typename T>
class Stack : public LinkedList <T>
{
public:
	const char* name(void) {return "Stack";}
	T peak(void)
	{
		return this->head->next->val;
	}
	T pop(void)
	{
		return this->popFront();
	}
	void push(T val)
	{
		this->pushFront(val);
	}
};

template <typename T>
class Queue : public LinkedList <T>
{
public:
	const char* name(void) {return "Queue";}
	T peak(void)
	{
		return this->head->next->val;
	}
	T pop(void)
	{
		return this->popFront();
	}
	void push(T val)
	{
		this->pushBack(val);
	}
};