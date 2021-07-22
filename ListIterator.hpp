#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP

namespace ft
{
	template <class T, class Pointer, class Reference, class Node>
	class ListIterator
	{
	private:
		Node *_node;

	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef Pointer pointer;
		typedef Reference reference;

		/* ------------------------------- CONSTRUCTOR:  ------------------------------- */

		ListIterator(Node *node = 0) : _node(node) {}

		ListIterator(ListIterator<T, T*, T&, Node> const &my_it) : _node(my_it.get_node()) {}

		ListIterator &operator=(ListIterator<T, T*, T&, Node> const &rhs)
		{
			if (this != &rhs)
				_node = rhs.get_node();
			return (*this);
		}

		/* ------------------------------- DESTRUCTOR: ------------------------------- */

		virtual ~ListIterator(){};


		/*------------------------------- INCREMENTS: -------------------------------*/

		/*------------------------------- (++a) -------------------------------*/ 
		ListIterator &operator++() 
		{
			_node = _node->next;
			return (*this);
		}

		/*------------------------------- (a++) -------------------------------*/ 
		ListIterator operator++(int) 
		{
			ListIterator copy(*this);
			operator++();
			return (copy);
		}

		/*------------------------------- DECREMENT: -------------------------------*/

		/*------------------------------- (--a) -------------------------------*/
		ListIterator &operator--()
		{
			_node = _node->prev;
			return (*this);
		}

		 /*------------------------------- (a--) -------------------------------*/
		ListIterator operator--(int)
		{
			ListIterator copy(*this);
			operator--();
			return (copy);
		}

		/*-------------------------------DEREFERENCE: -------------------------------*/

		reference operator*()
		{
			return (_node->data);
		}

		pointer operator->(void)
		{

			return &(_node->data);
		}

		/*------------------------------- EQUALITY / INEQUALITY COMPARISONS: -------------------------------*/

		bool operator==(const ListIterator &rhs)
		{
			return _node == rhs._node;
		}

		bool operator!=(const ListIterator &rhs)
		{
			return _node != rhs._node;
		}

		/*------------------------------- GETTER: ------------------------------- */

		Node *get_node() const
		{
			return _node;
		}

	};
}

#endif
