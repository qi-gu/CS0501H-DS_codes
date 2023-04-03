#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include "exceptions.hpp"

namespace sjtu {

/**
 * a container like std::priority_queue which is a heap internal.
 */
template<typename T, class Compare = std::less<T>>
class priority_queue {
private:
	struct node
	{
		T *val;
		node *left;
		node *right;
	};


	int num;
	node *root;

	node *copy(node *other)
	{
		if (!other)
		{
			return NULL;
		}
		node *tmp;
		tmp = (node*)malloc(sizeof(node));
		tmp->val = (T*)malloc(sizeof(T));
		new(tmp->val) T(*(other->val));
		tmp->left = copy(other->left);
		tmp->right = copy(other->right);
		return tmp;
	}
	
	void clear(node *r)
	{
		if (r->left)
			clear(r->left);
		if (r->right)
			clear(r->right);
		r->val->~T();
		free(r->val);
		free(r);
	}
	
	node *merge_node(node *my, node *other)
	{
		if (!my)
			return other;
		if (!other)
			return my;
		
		if (Compare()(*(my->val), *(other->val)))
		{
			other->right = merge_node(other->right, my);
			node *tmp = other->right;
			other->right = other->left;
			other->left = tmp;
			return other;
		}
		else
		{
			my->right = merge_node(my->right, other);
			node *tmp = my->right;
			my->right = my->left;
			my->left = tmp;
			return my;
		}
	}
public:
	/**
	 * TODO constructors
	 */
	
	priority_queue() : num(0), root(NULL) {}
	priority_queue(const priority_queue &other)
	{
		num = other.num;
		//root = (node*)malloc(sizeof(node));
		root = copy(other.root);
	}
	/**
	 * TODO deconstructor
	 */

	~priority_queue()
	{
		if (num)
			clear(root);
	}
	/**
	 * TODO Assignment operator
	 */
	priority_queue &operator=(const priority_queue &other)
	{
		if (this == &other)
			return *this;
		if (num)
			clear(root);
		num = other.num;
		root = copy(other.root);
		return *this;
	}
	/**
	 * get the top of the queue.
	 * @return a reference of the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	const T & top() const
	{
		if (!num)
			throw container_is_empty();
		return *(root->val);
	}
	/**
	 * TODO
	 * push new element to the priority queue.
	 */
	void push(const T &e)
	{
        ++num;
		node *tmp = (node*)malloc(sizeof(node));
		tmp->val = (T*)malloc(sizeof(T));
		new(tmp->val) T(e);
		tmp->left = tmp->right = NULL;
		root = merge_node(root, tmp);
	}
	/**
	 * TODO
	 * delete the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	void pop()
	{
		if (!num)
			throw container_is_empty();
        --num;
		node *l = root->left, *ri = root->right;
		root->val->~T();
		free(root->val);
		free(root);
		root = merge_node(l, ri);
	}
	/**
	 * return the number of the elements.
	 */
	size_t size() const
	{
		return num;
	}
	/**
	 * check if the container has at least an element.
	 * @return true if it is empty, false if it has at least an element.
	 */
	bool empty() const
	{
		return !num;
	}
	/**
	 * merge two priority_queues with at least O(logn) complexity.
	 * clear the other priority_queue.
	 */

	void merge(priority_queue &other)
	{
		num += other.num;
		root = merge_node(root, other.root);
		other.root = NULL;
		other.num = 0;
	}
};

}

#endif