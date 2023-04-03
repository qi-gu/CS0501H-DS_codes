/**
 * implement a container like std::map
 */
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

// only for std::less<T>
#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {

    template<
            class Key,
            class T,
            class Compare = std::less<Key>
    > class map {
    public:
        /**
         * the internal type of data.
         * it should have a default constructor, a copy constructor.
         * You can use sjtu::map as value_type by typedef.
         */
        typedef pair<const Key, T> value_type;
        class Node
        {
        public:
            value_type *data;
            Node *left;
            Node *right;
            Node *father;
            int hei;
            Node() : data(NULL), left(NULL), right(NULL), hei(1), father(NULL) {}
            ~Node()
            {
                delete data;
            }
        };

        Node *getPre(Node *x) const
        {
            Node* tmp = x->left;
            if (tmp)
            {
                while (tmp->right)
                    tmp = tmp->right;
                return tmp;
            }
            tmp = x;
            while (tmp->father && tmp->father->right != tmp)
                tmp = tmp->father;
            return tmp->father;
        }

        Node *getNext(Node *x) const
        {
            if (x == nil)
                return NULL;
            Node *tmp = x->right;
            if (tmp)
            {
                while (tmp->left)
                    tmp = tmp->left;
                return tmp;
            }
            tmp = x;
            while (tmp->father && tmp->father->left != tmp)
                tmp = tmp->father;
            return tmp->father;
        }

        Node *getFirst() const
        {
            Node *res = nil;
            while (res->left)
                res = res->left;
            return res;
        }

    private:
        Node *nil;
        int num;

        void update_height(Node *x)
        {
            int l_height, r_height;
            l_height = x->left ? x->left->hei : 0;
            r_height = x->right ? x->right->hei : 0;
            x->hei = l_height > r_height ? l_height + 1 : r_height + 1;
        }

        int height(Node *x) const
        {
            if (!x)
                return 0;
            return x->hei;
        }

        void copy(Node *&x, Node *ori)
        {
            x->hei = ori->hei;
            x->data = new value_type(*(ori->data));
            if (ori->left)
            {
                x->left = new Node();
                x->left->father = x;
                copy(x->left, ori->left);
            }
            if (ori->right)
            {
                x->right = new Node();
                x->right->father = x;
                copy(x->right, ori->right);
            }
        }

        void clear(Node *&x)
        {
            if (!x)
                return;
            clear(x->left);
            clear(x->right);
            delete x;
            x = NULL;
        }

        void L(Node *&x)
        {
            Node* l = x->left;
            x->left = l->right;
            if (x->left)
                x->left->father = x;
            l->right = x;
            l->father = x->father;
            x->father = l;
            x = l;
            update_height(x->right);
            update_height(x);
        }
        void R(Node *&x)
        {
            Node *r = x->right;
            x->right = r->left;
            if (x->right)
                x->right->father = x;
            r->left = x;
            r->father = x->father;
            x->father = r;
            x = r;
            update_height(x->left);
            update_height(x);
        }
        void LR(Node *&x)
        {
            R(x->left);
            L(x);
        }
        void RL(Node *&x)
        {
            L(x->right);
            R(x);
        }

        Node *Find(Node *start, const Key &target) const
        {
            if (!start)
                return NULL;
            if (Compare()(start->data->first, target))
                return Find(start->right, target);
            else if (Compare()(target, start->data->first))
                return Find(start->left, target);
            else
                return start;
        }

        Node *Insert(Node *&x, Node *fa, const value_type &val)
        {
            if (!x)
            {
                x = new Node();
                x->data = new value_type(val);
                x->father = fa;
                return x;
            }
            Node *tmp;
            if (Compare()(x->data->first, val.first))
            {
                tmp = Insert(x->right, x, val);
                if (height(x->right) - height(x->left) >= 2)
                {
                    if (Compare()(x->right->data->first, val.first))
                        R(x);
                    else
                        RL(x);
                }
            }
            else
            {
                tmp = Insert(x->left, x, val);
                if (height(x->left) - height(x->right) >= 2)
                {
                    if (Compare()(val.first, x->left->data->first))
                        L(x);
                    else
                        LR(x);
                }
            }
            update_height(x);
            return tmp;
        }

        Node *Insert(const value_type &val)
        {
            ++num;
            return Insert(nil->left, nil, val);
        }

        bool adjust(Node *&x, int subtree)
        {
            int lh = height(x->left);
            int rh = height(x->right);
            if (subtree)
            {
                if (lh == rh)
                {
                    update_height(x);
                    return false;
                }
                if (lh - rh == 1)
                    return true;

                if (height(x->left->right) > height(x->left->left))
                {
                    LR(x);
                    return false;
                }
                else
                {
                    L(x);

                    if (height(x->right) == height(x->left))
                        return false;
                    else
                        return true;
                }
            }
            else
            {
                if (rh == lh)
                {
                    update_height(x);
                    return false;
                }
                if (rh - lh == 1)
                    return true;

                if (height(x->right->left) > height(x->right->right))
                {
                    RL(x);
                    return false;
                }
                else
                {
                    R(x);
                    if (height(x->right) == height(x->left))
                        return false;
                    else
                        return true;
                }
            }
        }

        bool Erase(Node *&x, const value_type &val)
        {
            if (!x)     //true为高度平衡
                return true;
            if (Compare()(x->data->first, val.first))
            {
                if (Erase(x->right, val))
                    return true;
                else
                    return adjust(x, 1);
            }
            else if (Compare()(val.first, x->data->first))
            {
                if (Erase(x->left, val))
                    return true;
                else
                    return adjust(x, 0);
            }
            else
            {
                if (!x->left || !x->right)
                {
                    Node *tmp = x;
                    x = x->left ? x->left : x->right;
                    if (x)
                        x->father = tmp->father;
                    delete tmp;
                    return false;
                }
                else
                {
                    Node *fin = x->right;
                    while (fin->left)
                        fin = fin->left;

                    /*value_type *t = x->data;
                    x->data = fin->data;
                    fin->data = t;
                    if (Erase(x->right, val))
                        return true;
                    return adjust(x, 1);*/

                    Node* newNode = new Node;
                    newNode->data = new value_type(*(fin->data));
                    newNode->father = fin->father;
                    newNode->left = fin->left;
                    newNode->right = fin->right;
                    update_height(newNode);

                    if (newNode->right)
                        newNode->right->father = newNode;
                    if (newNode->father->left == fin)
                        newNode->father->left = newNode;
                    else
                        newNode->father->right = newNode;


                    fin->father = x->father;
                    fin->left = x->left;
                    fin->right = x->right;
                    update_height(fin);

                    fin->left->father = fin;
                    fin->right->father = fin;


                    Node *tmp = x;
                    x = fin;
                    delete tmp;

                    if (Erase(x->right,*(x->data)))
                        return true;
                    else
                        return adjust(x,1);
                }
            }
        }

    public:
        /**
         * see BidirectionalIterator at CppReference for help.
         *
         * if there is anything wrong throw invalid_iterator.
         *     like it = map.begin(); --it;
         *       or it = map.end(); ++end();
         */
        class const_iterator;
        class iterator {
        private:
            /**
             * TODO add data members
             *   just add whatever you want.
             */

        public:
            map<Key,T,Compare>* this_ptr;
            Node *to;

            iterator() : this_ptr(NULL), to(NULL) {}
            iterator(const iterator &other)
            {
                // TODO
                this_ptr = other.this_ptr;
                to = other.to;
            }
            iterator(map<Key,T,Compare>* a, Node *b) : this_ptr(a), to(b) {};
            /**
             * return a new iterator which pointer n-next elements
             *   even if there are not enough elements, just return the answer.
             * as well as operator-
             */
            /**
             * TODO iter++
             */
            iterator operator++(int)
            {
                if (!this_ptr)
                    throw invalid_iterator();
                Node *tmp = to;
                //to = this_ptr->getPre(to);
                Node *next = this_ptr->getNext(to);
                if (!next)
                    throw invalid_iterator();
                to = next;
                return iterator(this_ptr, tmp);
            }
            /**
             * TODO ++iter
             */
            iterator & operator++()
            {
                if (!this_ptr)
                    throw invalid_iterator();
                //to = this_ptr->getNext(to);
                Node *next = this_ptr->getNext(to);
                if (!next)
                    throw invalid_iterator();
                to = next;
                return *this;
            }
            /**
             * TODO iter--
             */
            iterator operator--(int)
            {
                if (!this_ptr)
                    throw invalid_iterator();
                Node *tmp = to;
                //to = this_ptr->getPre(to);
                Node *p = this_ptr->getPre(to);
                if (!p)
                    throw invalid_iterator();
                to = p;
                return iterator(this_ptr, tmp);
            }
            /**
             * TODO --iter
             */
            iterator & operator--()
            {
                if (!this_ptr)
                    throw invalid_iterator();
                //to = this_ptr->getPre(to);
                Node *p = this_ptr->getPre(to);
                if (!p)
                    throw invalid_iterator();
                to = p;
                return *this;
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            value_type & operator*() const
            {
                if (!to)
                    throw invalid_iterator();
                return *(to->data);
            }
            bool operator==(const iterator &rhs) const
            {
                return to == rhs.to && this_ptr == rhs.this_ptr;
            }
            bool operator==(const const_iterator &rhs) const
            {
                return to == rhs.to && this_ptr == rhs.this_ptr;
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const
            {
                return !(*this == rhs);
            }
            bool operator!=(const const_iterator &rhs) const
            {
                return !(*this == rhs);
            }

            /**
             * for the support of it->first.
             * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
             */
            value_type* operator->() const noexcept
            {
                if (!to)
                    throw invalid_iterator();
                return to->data;
            }
        };
        class const_iterator {
            // it should has similar member method as iterator.
            //  and it should be able to construct from an iterator.
        private:
            // data members.
        public:
            const map<Key,T,Compare>* this_ptr;
            Node *to;
            const_iterator() : this_ptr(NULL), to(NULL) {}
            const_iterator(const const_iterator &other) {
                // TODO
                this_ptr = other.this_ptr;
                to = other.to;
            }
            const_iterator(const iterator &other) {
                // TODO
                this_ptr = other.this_ptr;
                to = other.to;
            }
            const_iterator(const map<Key,T,Compare>* a, Node *b) : this_ptr(a), to(b) {};
            // And other methods in iterator.
            // And other methods in iterator.
            // And other methods in iterator.

            /**
             * TODO iter++
             */
            const_iterator operator++(int)
            {
                if (!this_ptr)
                    throw invalid_iterator();
                Node *tmp = to;
                //to = this_ptr->getNext(to);
                Node *next = this_ptr->getNext(to);
                if (!next)
                    throw invalid_iterator();
                to = next;
                return const_iterator(this_ptr, tmp);
            }
            /**
             * TODO ++iter
             */
            const_iterator & operator++()
            {
                if (!this_ptr)
                    throw invalid_iterator();
                //to = this_ptr->getNext(to);
                Node *next = this_ptr->getNext(to);
                if (!next)
                    throw invalid_iterator();
                to = next;
                return *this;
            }
            /**
             * TODO iter--
             */
            const_iterator operator--(int)
            {
                if (!this_ptr)
                    throw invalid_iterator();
                Node *tmp = to;
                //to = this_ptr->getPre(to);
                Node *p = this_ptr->getPre(to);
                if (!p)
                    throw invalid_iterator();
                to = p;
                return const_iterator(this_ptr, tmp);
            }
            /**
             * TODO --iter
             */
            const_iterator & operator--()
            {
                if (!this_ptr)
                    throw invalid_iterator();
                //to = this_ptr->getPre(to);
                Node *p = this_ptr->getPre(to);
                if (!p)
                    throw invalid_iterator();
                to = p;
                return *this;
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            const value_type & operator*() const
            {
                if (!to)
                    throw invalid_iterator();
                return *(to->data);
            }
            bool operator==(const iterator &rhs) const
            {
                return to == rhs.to && this_ptr == rhs.this_ptr;
            }
            bool operator==(const const_iterator &rhs) const
            {
                return to == rhs.to && this_ptr == rhs.this_ptr;
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const
            {
                return !(*this == rhs);
            }
            bool operator!=(const const_iterator &rhs) const
            {
                return !(*this == rhs);
            }

            /**
             * for the support of it->first.
             * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
             */
            const value_type* operator->() const noexcept
            {
                if (!this_ptr || to == this_ptr->nil)
                    throw invalid_iterator();
                return to->data;
            }
        };
        /**
         * TODO two constructors
         */
        map() : num(0)
        {
            nil = new Node();
        }
        map(const map &other) : num(other.num)
        {
            nil = new Node();
            if (!other.nil->left)
                return;
            nil->left = new Node();
            nil->left->father = nil;
            copy(nil->left, other.nil->left);
        }
        /**
         * TODO assignment operator
         */
        map & operator=(const map &other)
        {
            if (this == &other)
                return *this;
            clear(nil->left);
            num = other.num;
            if (!other.nil->left)
                return *this;
            nil->left = new Node();
            nil->left->father = nil;
            copy(nil->left, other.nil->left);
            return *this;
        }
        /**
         * TODO Destructors
         */
        ~map()
        {
            clear(nil);
        }
        /**
         * TODO
         * access specified element with bounds checking
         * Returns a reference to the mapped value of the element with key equivalent to key.
         * If no such element exists, an exception of type `index_out_of_bound'
         */
        T & at(const Key &key)
        {
            Node *res = Find(nil->left, key);
            if (!res)
                throw index_out_of_bound();
            return res->data->second;
        }
        const T & at(const Key &key) const
        {
            Node *res = Find(nil->left, key);
            if (!res)
                throw index_out_of_bound();
            return res->data->second;
        }
        /**
         * TODO
         * access specified element
         * Returns a reference to the value that is mapped to a key equivalent to key,
         *   performing an insertion if such key does not already exist.
         */
        T & operator[](const Key &key)
        {
            Node *res = Find(nil->left, key);
            if (!res)
                res = Insert(value_type(key, T()));
            return res->data->second;
        }
        /**
         * behave like at() throw index_out_of_bound if such key does not exist.
         */
        const T & operator[](const Key &key) const
        {
            return at(key);
        }
        /**
         * return a iterator to the beginning
         */
        iterator begin()
        {
            return iterator(this, getFirst());
        }
        const_iterator cbegin() const
        {
            const_iterator tmp;
            tmp.to = getFirst();
            tmp.this_ptr = this;
            return tmp;
        }
        /**
         * return a iterator to the end
         * in fact, it returns past-the-end.
         */
        iterator end()
        {
            return iterator(this, nil);
        }
        const_iterator cend() const
        {
            const_iterator tmp;
            tmp.to = nil;
            tmp.this_ptr = this;
            return tmp;
        }
        /**
         * checks whether the container is empty
         * return true if empty, otherwise false.
         */
        bool empty() const
        {
            return !num;
        }
        /**
         * returns the number of elements.
         */
        size_t size() const
        {
            return num;
        }
        /**
         * clears the contents
         */
        void clear()
        {
            num = 0;
            clear(nil->left);
        }
        /**
         * insert an element.
         * return a pair, the first of the pair is
         *   the iterator to the new element (or the element that prevented the insertion),
         *   the second one is true if insert successfully, or false.
         */
        pair<iterator, bool> insert(const value_type &value)
        {
            Node *tmp = Find(nil->left, value.first);
            if (!tmp)
            {
                tmp = Insert(value);
                return pair<iterator, bool>(iterator(this, tmp), true);
            }
            return pair<iterator, bool>(iterator(this, tmp), false);
        }
        /**
         * erase the element at pos.
         *
         * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
         */
        void erase(iterator pos)
        {
            if (pos.to == nil || pos.this_ptr != this)
                throw invalid_iterator();

            --num;
            Erase(nil->left, *(pos.to->data));
        }
        /**
         * Returns the number of elements with key
         *   that compares equivalent to the specified argument,
         *   which is either 1 or 0
         *     since this container does not allow duplicates.
         * The default method of check the equivalence is !(a < b || b > a)
         */
        size_t count(const Key &key) const
        {
            Node *tmp = Find(nil->left, key);
            if (!tmp)
                return 0;
            return 1;
        }
        /**
         * Finds an element with key equivalent to key.
         * key value of the element to search for.
         * Iterator to an element with key equivalent to key.
         *   If no such element is found, past-the-end (see end()) iterator is returned.
         */
        iterator find(const Key &key)
        {
            Node *tmp = Find(nil->left, key);
            if (!tmp)
                return iterator(this, nil);
            return iterator(this, tmp);
        }
        const_iterator find(const Key &key) const
        {
            Node *tmp = Find(nil->left, key);
            if (!tmp)
                return const_iterator(this, nil);
            return const_iterator(this, tmp);
        }
    };

}

#endif