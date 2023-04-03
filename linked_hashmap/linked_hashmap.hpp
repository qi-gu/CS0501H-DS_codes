#ifndef SJTU_LINKED_HASHMAP_HPP_STD
#define SJTU_LINKED_HASHMAP_HPP_STD

#include <cstddef>
#include <functional>
#include "utility.hpp"
#include "algorithm.hpp"
#include "exceptions.hpp"
#include "list.hpp"

namespace sjtu {
	/**
	 *  Maintains key-value pairs just like MAP
	 *  Dynamically sized hash table who handles collision with linked lists
	 *  Iterators arrange in order of insertion (maintained by base class LIST)
	 */

template <
        class Key,
        class Value,
        class Hash = std::hash<Key>,
        class Equal = std::equal_to<Key>
>
class linked_hashmap : public list<pair<const Key, Value> > {
public:
    using value_type = pair<const Key, Value>;

private:
    int capacity;
    Hash key_hash;

    class Node : public list<value_type>::node {
    public:
        /**
         * add data members in addition to class node in LIST
         */
        Node *right;
        Node() : right(nullptr), list<value_type>::node() {}
        Node(const Key &k, const Value &v) : right(nullptr), list<value_type>::node(value_type(k, v)) {}
        Node(const value_type &v) : right(nullptr), list<value_type>::node(v) {}
        ~Node() = default;
    };

    /**
     * singly-linked list used for hash collision
     */
    class BucketList {
    public:
        /**
         * data members, constructors and destructor
         */
        Node *head;
        Equal key_equal;
        BucketList() {head = new Node();}
        ~BucketList()
        {
            delete head;
        }
        /**
         *  TODO find corresponding Node with key o
         */
        Node * find(const Key &o)
        {
            Node *now = head->right;
            while (now)
            {
                if (key_equal(now->val->first, o))
                    return now;
                now = now->right;
            }
            return nullptr;
        }
        /**
         * TODO insert key-value pair(k, v) into this BucketList
         * return this new Node
         */
        Node * insert(const Key &k, const Value &v)
        {
            Node *n = new Node(k, v);
            n->right = head->right;
            head->right = n;

            return n;
        }
        Node * insert(const value_type &kv)
        {
            Node *n = new Node(kv);
            n->right = head->right;
            head->right = n;
            return n;
        }

        void insert_node(Node *t)
        {
            t->right = head->right;
            head->right = t;
        }
        /**
         * TODO remove the Node with key k from this BucketList (no need to delete)
         * return the removed Node
         */
        Node * erase(const Key &k)
        {
            Node *now = head;
            while (now->right)
            {
                if (key_equal(now->right->val->first, k))
                {
                    Node *tmp = now->right;
                    now->right = tmp->right;
                    return tmp;
                }
                now = now->right;
            }
            return nullptr;
        }
    };

    /**
     * add data members as needed and necessary private function such as resize()
     */
     BucketList *map;

     void resize(int new_size)
     {
         capacity = new_size;
         delete []map;
         map = new BucketList[capacity];
         typename list<value_type>::node *now = this->head->nxt;
         while (now != this->nil)
         {
             Node *t = dynamic_cast<Node *>(now);
             map[key_hash(t->val->first) % capacity].insert_node(t);

             now = now->nxt;
         }
     }


public:
    /**
     * iterator is the same as LIST
     */
    using iterator = typename list<value_type>::iterator;
    using const_iterator = typename list<value_type>::const_iterator;

    /**
    * TODO two constructors
    */
    linked_hashmap() : capacity(100)
    {
        map = new BucketList[capacity];
    }
    linked_hashmap(const linked_hashmap &other) : capacity(other.capacity), list<value_type>::list()
    {
        map = new BucketList[capacity];
        typename list<value_type>::node *now = other.head->nxt;
        Node *tmp;
        while (now != other.nil)
        {
            tmp = map[key_hash(now->val->first) % capacity].insert(*(now->val));
            list<value_type>::insert(this->nil, tmp);

            now = now->nxt;
        }
    }
    /**
	 * TODO assignment operator
	 */
    linked_hashmap &operator=(const linked_hashmap &other)
    {
        if (&other == this)
            return *this;
        clear();
        capacity = other.capacity;
        map = new BucketList[capacity];
        typename list<value_type>::node *now = other.head->nxt;
        Node *tmp;
        while (now != other.nil)
        {
            tmp = map[key_hash(now->val->first) % capacity].insert(*(now->val));
            list<value_type>::insert(this->nil, tmp);

            now = now->nxt;
        }
        return *this;
    }
    /**
	 * TODO Destructors
	 */
    ~linked_hashmap() {delete []map;}
    /**
	 * TODO access specified element with bounds checking
	 * Returns a reference to the mapped value of the element with key equivalent to key.
	 * If no such element exists, an exception of type `index_out_of_bound'
	 */
    Value &at(const Key &key)
    {
        if (!map)
            throw index_out_of_bound();
        Node *tmp = map[key_hash(key) % capacity].find(key);
        if (!tmp)
            throw index_out_of_bound();
        return tmp->val->second;
    }
    const Value &at(const Key &key) const
    {
        Node *tmp = map[key_hash(key) % capacity].find(key);
        if (!tmp)
            throw index_out_of_bound();
        return tmp->val->second;
    }
    /**
	 * TODO access specified element
	 * Returns a reference to the value that is mapped to a key equivalent to key,
	 *   performing an insertion if such key does not already exist.
	 */
    Value &operator[](const Key &key)
    {
        if (!map)
            return insert(value_type(key, Value())).first->second;
        Node *tmp = map[key_hash(key) % capacity].find(key);
        if (!tmp)
        {
            return insert(value_type(key, Value())).first->second;
        }
        return tmp->val->second;
    }
    /**
	 * behave like at() throw index_out_of_bound if such key does not exist.
	 */
    const Value &operator[](const Key &key) const
    {
        return at(key);
    }
    /**
	 * TODO override clear() in LIST
	 */
    void clear() override
    {
        if (!map)
            return;
        list<value_type>::clear();
        delete []map;
        capacity = 0;
        map = nullptr;
    }
    /**
	 * TODO insert an element.
	 * return a pair, the first of the pair is
	 *   the iterator to the new element (or the element that prevented the insertion),
	 *   the second one is true if insert successfully, or false.
	 */
    pair<iterator, bool> insert(const value_type &value)
    {
        if (!capacity)
            resize(100);
        else if (this->num > capacity >> 1)
            resize(capacity << 1);
        Node *tmp = map[key_hash(value.first) % capacity].find(value.first);
        if (tmp)
        {
            return pair<iterator, bool>(iterator(tmp, this), false);
        }
        tmp = map[key_hash(value.first) % capacity].insert(value);
        list<value_type>::insert(this->nil, tmp);
        return pair<iterator, bool>(iterator(tmp, this), true);
    }
    /**
	 * TODO erase the element at pos.
	 * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
     * return anything, it doesn't matter
	 */
    iterator erase(iterator pos) override
    {
        if (this->num <= (capacity >> 2))
            resize(capacity >> 1);
        if (!map || pos.invalid(this))
            throw invalid_iterator();
        map[key_hash((*pos).first) % capacity].erase((*pos).first);
        return list<value_type>::erase(pos);
    }
    /**
	 * TODO Returns the number of elements with key
	 *   that compares equivalent to the specified argument,
	 *   which is either 1 or 0
	 *     since this container does not allow duplicates.
	 */
    size_t count(const Key &key) const
    {
        //Node *tmp = map[key_hash(key) % capacity].find(key);
        if (map && map[key_hash(key) % capacity].find(key))
            return 1;
        else
            return 0;
    }
    /**
	 * TODO Finds an element with key equivalent to key.
	 * return iterator to an element with key equivalent to key.
	 *   If no such element is found, past-the-end (see end()) iterator is returned.
	 */
    iterator find(const Key &key)
    {
        if (!map)
            return this->end();
        Node *tmp = map[key_hash(key) % capacity].find(key);
        if (!tmp)
        {
            return this->end();
        }
        return iterator(tmp, this);
    }
    const_iterator find(const Key &key) const
    {
        if (!map)
            return this->cend();
        Node *tmp = map[key_hash(key) % capacity].find(key);
        if (!tmp)
        {
            return this->cend();
        }
        return const_iterator(tmp, this);
    }
};

}

#endif