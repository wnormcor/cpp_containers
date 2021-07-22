#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include <cstddef>
#include <iostream>

namespace ft
{
	template <class T, class Pointer, class Reference, class Node, class Compare>
	class MapIterator
	{

	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Compare key_compare;

		/* ------------------------------- CONSTRUCTOR:  ------------------------------- */

		MapIterator(Node *node = 0) : _node(node) {} // default

		MapIterator(MapIterator<T, T*, T&, Node, key_compare> const &my_it) : _node(my_it.get_node()) {}

		MapIterator &operator=(MapIterator<T, T*, T&, Node, key_compare> const &rhs)
		{
			this->_node = rhs.get_node();
			this->_comp = rhs._comp;
			return (*this);
		}

		/* ------------------------------- DESTRUCTOR: ------------------------------- */

		virtual ~MapIterator(){};


		/*------------------------------- INCREMENTS: -------------------------------*/

		/*------------------------------- (++a) -------------------------------*/
		MapIterator &operator++()
		{
			Node *tmp = _node;
			// _last_node->right == _first  and  _first->left == NULL
			// _last->right == _last_node   and  _last_node->left  == _last
			if (_node->right)
			{
				tmp = _node->right;
				while (tmp->left && tmp->left != _node)
					tmp = tmp->left;
			}
			else if (_node->parent)
			{
				tmp = _node->parent;
				while (tmp->parent && _comp(tmp->val.first, _node->val.first)) // tmp->val.first < _node->val.first
					tmp = tmp->parent;
			}
			_node = tmp;
			return (*this);
		}

		/*------------------------------- (a++) -------------------------------*/
		MapIterator operator++(int)
		{
			MapIterator copy(*this);
			operator++();
			return (copy);
		}

		/*------------------------------- DECREMENT: -------------------------------*/

		/*------------------------------- (--a) -------------------------------*/

		MapIterator &operator--()
		{
			Node *tmp = _node;
			// _last_node->left == _last  and  _last->right == _last_node
			// _last->left == tmp    and  tmp->right   == NULL
			if (_node->left)
			{
				tmp = _node->left;
				while (tmp->right && tmp->right != _node)
					tmp = tmp->right;
			}
			else if (_node->parent)
			{
				tmp = _node->parent;
				while (tmp->parent && _comp(_node->val.first, tmp->val.first)) // _node->val.first < tmp->val.first
					tmp = tmp->parent;
			}
			_node = tmp;
			return (*this);
		}

		/*------------------------------- (a--) -------------------------------*/

		MapIterator operator--(int)
		{
			MapIterator copy(*this);
			operator--();
			return (copy);
		}

		/*-------------------------------DEREFERENCE: -------------------------------*/

		reference operator*()
		{
			return (this->_node->val);
		}

		pointer operator->(void)
		{

			return &(this->_node->val);
		}

		/*------------------------------- EQUALITY / INEQUALITY COMPARISONS: -------------------------------*/

		bool operator==(const MapIterator &rhs)
		{
			return this->_node == rhs._node;
		}

		bool operator!=(const MapIterator &rhs)
		{
			return this->_node != rhs._node;
		}

		/*------------------------------- GETTER: ------------------------------- */

		Node *get_node() const
		{
			return this->_node;
		}

			
		private:
			Node *_node;
			key_compare _comp;
	};
}

#endif
