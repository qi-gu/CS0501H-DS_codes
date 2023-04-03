#ifndef SJTU_LIST_HPP
#define SJTU_LIST_HPP

#include "exceptions.hpp"
#include "algorithm.hpp"

#include <climits>
#include <cstddef>

namespace sjtu {
/**
 * a data container like std::list
 * allocate random memory addresses for data and they are doubly-linked in a list.
 */
template<typename T>
class list {
protected:
    class node {
    public:
        /**
         * add data members and constructors & destructor
         */
		T *data;
		node *next;
		node *pre;
		node() : data(NULL), next(NULL), pre(NULL) {}
		
		~node()
		{
			if (data)
				delete data;
		}
    };

    /**
     * add data members for linked list as protected members
     */
	node *head, *tail;
	long long length;
    /**
     * insert node cur before node pos
     * return the inserted node cur
     */
    node *insert(node *pos, node *cur)
	{
		cur->pre = pos->pre;
		cur->next = pos;

		cur->pre->next = cur;
		pos->pre = cur;
		++length;
		return cur;
	}
    /**
     * remove node pos from list (no need to delete the node)
     * return the removed node pos
     */
    node *erase(node *pos)
	{
		pos->pre->next = pos->next;
		pos->next->pre = pos->pre;
		--length;
		return pos;
	}

public:
    class const_iterator;
    class iterator {
    public:
        list *target;
		node *pos;

    public:
		iterator(const iterator &a)
		{
			target = a.target;
			pos = a.pos;
		}
		iterator(list *t = NULL, node *n = NULL) : target(t), pos(n) {}

        /**
         * iter++
         */
        iterator operator++(int)
		{
            if (!pos->next)
                throw invalid_iterator();
			iterator tmp(*this);
			pos = pos->next;
			return tmp;
		}
        /**
         * ++iter
         */
        iterator & operator++()
		{
            if (!pos->next)
                throw invalid_iterator();
			pos = pos->next;
			return *this;
		}
        /**
         * iter--
         */
        iterator operator--(int)
		{
            if (!pos->pre || !pos->pre->pre)
                throw invalid_iterator();
			iterator tmp(*this);
			pos = pos->pre;
			return tmp;
		}
        /**
         * --iter
         */
        iterator & operator--()
		{
            if (!pos->pre  || !pos->pre->pre)
                throw invalid_iterator();
			pos = pos->pre;
			return *this;
		}
        /**
         * TODO *it
         * remember to throw if iterator is invalid
         */
        T & operator *() const
		{
			if (!pos->next || !pos->pre)
				throw invalid_iterator();
			return *pos->data;
		}
        /**
         * TODO it->field
         * remember to throw if iterator is invalid
         */
        T * operator ->() const //noexcept
		{
			if (!pos->next || !pos->pre)
				throw invalid_iterator();
			return pos->data;
		}
        /**
         * a operator to check whether two iterators are same (pointing to the same memory).
         */
        bool operator==(const iterator &rhs) const
		{
			return (pos == rhs.pos);
		}
        bool operator==(const const_iterator &rhs) const
		{
			return (pos == rhs.pos);
		}
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const
		{
			return !(pos == rhs.pos);
		}
        bool operator!=(const const_iterator &rhs) const
		{
			return !(pos == rhs.pos);
		}
    };
    /**
     * TODO
     * has same function as iterator, just for a const object.
     * should be able to construct from an iterator.
     */
    class const_iterator {
	public:
        const list *target;
		const node *pos;

    public:
        /**
         * iter++
         */
		const_iterator(const iterator &a)
		{
			target = a.target;
			pos = a.pos;
		}
		const_iterator(const const_iterator &a)
		{
			target = a.target;
			pos = a.pos;
		}
		const_iterator(const list *t = NULL, const node *n = NULL) : target(t), pos(n) {}

        const_iterator operator++(int)
		{
            if (!pos->next)
                throw invalid_iterator();
			const_iterator tmp(*this);
			pos = pos->next;
			return tmp;
		}
        /**
         * ++iter
         */
        const_iterator & operator++()
		{
            if (!pos->next)
                throw invalid_iterator();
			pos = pos->next;
			return *this;
		}
        /**
         * iter--
         */
        const_iterator operator--(int)
		{
            if (!pos->next || !pos->pre->pre)
                throw invalid_iterator();
			const_iterator tmp(*this);
			pos = pos->pre;
			return tmp;
		}
        /**
         * --iter
         */
        const_iterator & operator--()
		{
            if (!pos->next || !pos->pre->pre)
                throw invalid_iterator();
			pos = pos->pre;
			return *this;
		}
        /**
         * TODO *it
         * remember to throw if iterator is invalid
         */
        T & operator *() const
		{
			if (!pos->next || !pos->pre)
				throw invalid_iterator();
			return *pos->data;
		}
        /**
         * TODO it->field
         * remember to throw if iterator is invalid
         */
        T * operator ->() const //noexcept
		{
			if (!pos->next || !pos->pre)
				throw invalid_iterator();
			return pos->data;
		}
        /**
         * a operator to check whether two iterators are same (pointing to the same memory).
         */
        bool operator==(const iterator &rhs) const
		{
			return (pos == rhs.pos);
		}
        bool operator==(const const_iterator &rhs) const
		{
			return (pos == rhs.pos);
		}
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const
		{
			return !(pos == rhs.pos);
		}
        bool operator!=(const const_iterator &rhs) const
		{
			return !(pos == rhs.pos);
		}
    };
    /**
     * TODO Constructs
     * Atleast two: default constructor, copy constructor
     */
    list() : length(0)
	{
		head = new node();
		tail = new node();
		head->next = tail;
		tail->pre = head;
	}
    list(const list &other) : length(0)
	{
		head = new node;
		tail = new node;
		head->next = tail;
		tail->pre = head;

		for (node *tmp = other.head->next; tmp != other.tail; tmp = tmp->next)
		{
			push_back(*tmp->data);
		}
	}
    /**
     * TODO Destructor
     */
    virtual ~list()
	{
		clear();
		delete head;
		delete tail;
	}
    /**
     * TODO Assignment operator
     */
    list &operator=(const list &other)
	{
		if (this == &other)
			return *this;
		clear();
		for (node *tmp = other.head->next; tmp != other.tail; tmp = tmp->next)
		{
			push_back(*tmp->data);
		}
		return *this;
	}
    /**
     * access the first / last element
     * throw container_is_empty when the container is empty.
     */
    const T & front() const
	{
		if (!length)
			throw container_is_empty();
		return *(head->next->data);
	}
    const T & back() const
	{
		if (!length)
			throw container_is_empty();
		return *(tail->pre->data);
	}
    /**
     * returns an iterator to the beginning.
     */
    iterator begin()
	{
		return iterator(this, head->next);
	}
    const_iterator cbegin() const
	{
		return const_iterator(this, head->next);
	}
    /**
     * returns an iterator to the end.
     */
    iterator end()
	{
		return iterator(this, tail);
	}
    const_iterator cend() const
	{
		return const_iterator(this, tail);
	}
    /**
     * checks whether the container is empty.
     */
    virtual bool empty() const
	{
		return !length;
	}
    /**
     * returns the number of elements
     */
    virtual size_t size() const
	{
		return length;
	}

    /**
     * clears the contents
     */
    virtual void clear()
	{
		int a = length;
		while (a--)
			pop_back();

	}
    /**
     * insert value before pos (pos may be the end() iterator)
     * return an iterator pointing to the inserted value
     * throw if the iterator is invalid
     */
    virtual iterator insert(iterator pos, const T &value)
	{
		if (pos.target != this || pos.pos == head)
			throw invalid_iterator();
		node *p = new node;
		p->pre = pos.pos->pre;
		p->next = pos.pos;
		pos.pos->pre = p;
		p->pre->next = p;
        p->data = new T(value);
        ++length;

		return iterator(this, p);
	}
    /**
     * remove the element at pos (the end() iterator is invalid)
     * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
     * throw if the container is empty, the iterator is invalid
     */
    virtual iterator erase(iterator pos)
	{
		if (!length)
			throw container_is_empty();
		if (pos.target != this || pos.pos == tail || pos.pos == head)
			throw invalid_iterator();
		node *tmp = pos.pos;
        ++pos;
		tmp->pre->next = tmp->next;
		tmp->next->pre = tmp->pre;
        --length;
		delete tmp;
		return pos;
	}
    /**
     * adds an element to the end
     */
    void push_back(const T &value)
	{
		node *tmp = new node;
		tmp->data = new T(value);
		tmp->next = tail;
		tmp->pre = tail->pre;
		tmp->pre->next = tmp;
		tail->pre = tmp;
		++length;
	}
    /**
     * removes the last element
     * throw when the container is empty.
     */
    void pop_back()
	{
		if (!length)
			throw container_is_empty();
		node *tmp = tail->pre;
		tail->pre = tmp->pre;
		tail->pre->next = tail;
		delete tmp;
		--length;

	}
    /**
     * inserts an element to the beginning.
     */
    void push_front(const T &value)
	{
		++length;
		node *tmp = new node;
		tmp->next = head->next;
		tmp->pre = head;
		head->next = tmp;
		tmp->next->pre = tmp;
		tmp->data = new T(value);
	}
    /**
     * removes the first element.
     * throw when the container is empty.
     */
    void pop_front()
	{
		if (!length)
			throw container_is_empty();
		node *tmp = head->next;
		head->next = tmp->next;
		head->next->pre = head;
		delete tmp;
		--length;
	}
    /**
     * sort the values in ascending order with operator< of T
     */
    void sort()
	{
		if (length == 1 || !length)
			return;
        auto cmp = [](const T *a, const T *b)->bool
        {
            return *a < *b;
        };
        T **da = new T*[length];
        node *now = head->next;
        for (int i = 0; i < length; ++i)
        {
            da[i] = new T(*now->data);
            now->data->~T();
            now = now->next;
        }
        sjtu::sort<T*>(da, da + length, cmp);
        now = head->next;
        for (int i = 0; i < length; ++i)
        {
            new(now->data) T(*da[i]);
            now = now->next;
            delete da[i];
        }
        delete[] da;
	}
    /**
     * merge two sorted lists into one (both in ascending order)
     * compare with operator< of T
     * container other becomes empty after the operation
     * for equivalent elements in the two lists, the elements from *this shall always precede the elements from other
     * the order of equivalent elements of *this and other does not change.
     * no elements are copied or moved
     */
    void merge(list &other)
	{
		if (!other.length)
			return;
        node *p = head->next, *q = other.head->next;
        while (q != other.tail)
        {
            if (p == tail || *(q->data) < *(p->data))
            {
                node *tmp = other.erase(q);
                q = q->next;
                insert(p, tmp);
            }
            else
				p = p->next;
        }
	}
    /**
     * reverse the order of the elements
     * no elements are copied or moved
     */
    void reverse()
	{
		node *a = head;
        while (a != NULL)
        {
            node *tmp = a->next;
            a->next = a->pre;
            a->pre = tmp;
            a = a->pre;
        }
        a = head;
        head = tail;
        tail = a;
	}
    /**
     * remove all consecutive duplicate elements from the container
     * only the first element in each group of equal elements is left
     * use operator== of T to compare the elements.
     */
    void unique()
	{
		if (!length || length == 1)
			return;
        node *p = head->next, *q;
        while (p->next != tail)
        {
            if (*(p->next->data) == *(p->data))
            {
                q = erase(p->next);
                delete q;
            }
            else
				p = p->next;
        }
	}
};

}

#endif //SJTU_LIST_HPP
