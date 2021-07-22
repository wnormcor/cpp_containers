#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include "ListIterator.hpp"
#include "Utils.hpp"
#include "ReverseIterator.hpp"

/* почитать про двусвязные кольцевые списки: 
https://www.geeksforgeeks.org/doubly-circular-linked-list-set-1-introduction-and-insertion/  

то, на основе чего сделан merge sort: https://www.tutorialspoint.com/merge-sort-for-doubly-linked-list-using-cplusplus 
https://www.geeksforgeeks.org/sorted-merge-of-two-sorted-doubly-circular-linked-lists/ 
*/

namespace ft
{

	template <class T, class Alloc = std::allocator<T> >
	class list
	{
	private:
		struct Node
		{
			T data;
			Node *next;
			Node *prev;
		};

	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename Alloc::reference reference;
		typedef typename Alloc::const_reference const_reference;
		typedef typename Alloc::pointer pointer;
		typedef typename Alloc::const_pointer const_pointer;

		typedef typename ft::ListIterator<T, T*, T&, Node> iterator;
		typedef typename ft::ListIterator<T, const T*, const T&, Node> const_iterator;
		typedef typename ft::ReverseIterator<iterator> reverse_iterator;
		typedef typename ft::ReverseIterator<const_iterator> const_reverse_iterator;


		typedef ptrdiff_t difference_type;
		typedef size_t size_type;


		/*------------------------------- CONSTRUCTORS: -------------------------------*/

		explicit list(const allocator_type &alloc = allocator_type()) :
		 _allocator_type(alloc), _size(0)
		{
			_tail = allocate_node();
		}

		explicit list(size_type n, const value_type &val = value_type(),
					  const allocator_type &alloc = allocator_type()) : 
					  _allocator_type(alloc), _size(0)
		{
			_tail = allocate_node();
			for (int i = 0; i < n; ++i)
			{
				push_back(val);
			}
		}

		template <class InputIterator>
		list(InputIterator first, InputIterator last, 
		typename ft::enable_if<!is_integral<InputIterator>::value> * = NULL,
		const allocator_type &alloc = allocator_type()) : _allocator_type(alloc), _size(0)
		{
			_tail = allocate_node();
			assign(first, last);
		}

		list(const list &x)
		{
			_tail = allocate_node();
			assign(x.begin(), x.end());
		}

		/*------------------------------- DESTRUCTOR: -------------------------------*/

		virtual ~list()
		{
			erase(begin(), end());
			deallocate_node(_tail);
		}

		/*------------------------------- OPERATOR=: -------------------------------*/

		list &operator=(const list &x)
		{
			if (this != &x)
			{
				assign(x.begin(), x.end());
			}

			return (*this);
		}

		/*------------------------------- ITERATORS: -------------------------------*/

		iterator begin()
		{
			return iterator(_tail->next);
		}

		const_iterator begin() const
		{
			return const_iterator(_tail->next);
		}

		iterator end()
		{
			return iterator(_tail);
		}

		const_iterator end() const
		{
			return const_iterator(_tail);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		/*-------------------------------  CAPACITY: -------------------------------*/

		bool empty() const
		{
			return _size == 0;
		}

		size_type size() const
		{
			return _size;
		}

		size_type max_size() const
		{
			return _node_alloc.max_size();
		}

		/*-------------------------------  ELEMENT ACCESS: -------------------------------*/

		reference front()
		{
			return _tail->next->data;
		}

		const_reference front() const
		{
			return _tail->next->data;
		}

		reference back()
		{
			return _tail->prev->data;
		}

		const_reference back() const
		{
			return _tail->prev->data;
		}

		/*-------------------------------  MODIFIERS: ------------------------------- */

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last, 
		typename ft::enable_if<!is_integral<InputIterator>::value, 
		InputIterator>::type isIterator = InputIterator())
		{
			(void)isIterator;
			clear();
			insert(begin(), first, last);
		}

		void assign(size_type n, const value_type &val)
		{
			clear();
			insert(begin(), n, val);
		}

		void push_front(const value_type &val)
		{
			insert(begin(), val);
		}

		void pop_front()
		{
			erase(begin());
		}

		void push_back(const value_type &val)
		{
			insert_to_the_end(val);
		}

		void pop_back()
		{
			erase(--end());
			// --end потому что end() указывает на элемент после конца
		}

		iterator insert(iterator position, const value_type &val)
		{
			Node *tmp = construct_node(val);

			// установить prev и next of новой ноды
			tmp->next = position.get_node();
			tmp->prev = position.get_node()->prev;

			// Обновить next и previous указатели у предыдущей ноды
			position.get_node()->prev->next = tmp;
			position.get_node()->prev = tmp;

			++_size;
			return iterator(tmp);
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			for (size_type i = 0; i < n; ++i)
			{
				insert(position, val);
			}
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, 
		InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, 
		InputIterator>::type isIterator = InputIterator())
		{
			(void)isIterator;
			while (first != last)
			{
				position = insert(position, *first);
				++position;
				++first;
			}
		}

		iterator erase(iterator position)
		{
			Node *next;

			next = position.get_node()->next;
			destroy_and_deallocate_node(position.get_node());
			return iterator(next);
		}

		iterator erase(iterator first, iterator last)
		{
			while (first != last)
			{
				destroy_and_deallocate_node(first.get_node());
				first++;
			}

			return (last);
		}

		void swap(list &x)
		{
			if (this == &x)
				return;
			ft::swap(_tail, x._tail);
			ft::swap(_size, x._size);
			ft::swap(_allocator_type, x._allocator_type);
			ft::swap(_node_alloc, x._node_alloc);
		}

		void resize(size_type n, value_type val = value_type())
		{
			iterator pos = begin();
			size_type n_copy = n;
			while (n_copy--)
				pos++;
			if (n < this->_size)
				erase(pos, end());
			else if (this->_size < n)
			{
				size_type offset;
				offset = n - this->_size;
				insert(end(), offset, val);
			}
		}

		void clear()
		{
			erase(begin(), end());
		}

		/*------------------------------- OPERATIONS: -------------------------------*/

		void splice(iterator position, list &x)
		{
			iterator it = x.begin();
			size_type i = 0;
			while (i < x.size())
			{
				insert(position, it.get_node()->data);
				i++;
				it++;
			}
			x.clear();
		}

		void splice(iterator position, list &x, iterator i)
		{
			iterator tmp = x.begin();
			while (tmp != i)
				tmp++; // получить итератор на элемент в x, который нужно удалить
			insert(position, i.get_node()->data);
			x.erase(tmp);
		}

		void splice(iterator position, list &x, iterator first, iterator last)
		{
			iterator x_first = first; // сохранить позицию итератора для x
			while (first != last)
			{
				insert(position, first.get_node()->data);
				first++;
				x.erase(x_first);
				x_first++;
			}
		}

		void remove(const value_type &val)
		{
			Node *save;
			save = _tail->next; // 1й элемент

			size_type i = 0;
			size_type save_size = this->_size;
			while (i < save_size)
			{
				save = save->next;
				if (save->prev->data == val)
				{
					destroy_and_deallocate_node(save->prev);
				}
				--save_size;
			}
		}

		template <class Predicate>
		void remove_if(Predicate pred)
		{
			Node *save;
			save = _tail->next; // 1й элемент

			size_type i = 0;
			size_type save_size = this->_size;
			while (i < save_size)
			{
				save = save->next;
				if (pred(save->prev->data))
				{
					destroy_and_deallocate_node(save->prev);
				}
				--save_size;
			}
		}

		void unique()
		{
			Node *save;
			save = _tail->next->next; // 2й элемент
			size_type i = 0;
			size_type save_size = this->_size;
			while (i < save_size)
			{
				if (save->prev->data == save->data)
				{
					save = save->next;
					destroy_and_deallocate_node(save->prev);
				}
				else
					save = save->next;
				--save_size;
			}
		}

		template <class BinaryPredicate>
		void unique(BinaryPredicate binary_pred)
		{
			Node *save;
			save = _tail->next->next; // 2й элемент
			size_type i = 0;
			size_type save_size = this->_size;
			while (i < save_size)
			{
				if (binary_pred(save->prev->data, save->data))
				{
					save = save->next;
					destroy_and_deallocate_node(save->prev);
				}
				else
					save = save->next;
				--save_size;
			}
		}

		void merge(list &x)
		{
			merge(x, ft::less<value_type>());
		}

		template <class Compare>
		void merge(list &x, Compare comp)
		{
			if (&x == this)
				return;
			Node *first = _tail->next;
			Node *second = x._tail->next;
			iterator position = this->begin();
			while (first != _tail && second != x._tail)
			{
				if (comp(second->data, first->data))
				{
					insert(position, second->data);
					second = second->next;
				}
				else
				{
					first = first->next;
				}
				position++;
			}
			while (second != x._tail)
			{
				this->push_back(second->data);
				second = second->next;
			}
			x.clear();
		}

		void sort()
		{
		  sort(ft::less<value_type>());
		}

		template <class Compare>
		void sort(Compare comp)
		{
			Node *last_node = NULL;
			_tail->next = mergeSort(_tail->next, comp, &last_node);

			Node *head = _tail->next;

			// получить указатель на ноду, которая будет последней в листе
			Node *last;

			while (head != _tail)
			{
				last = head;
				head = head->next;
			}

			_tail->prev = last;
		}

		void reverse()
		{
			Node *tmp_first = _tail->next;
			Node *tmp_last = _tail->prev;

			while (tmp_first != tmp_last)
			{
				ft::swap(tmp_first->data, tmp_last->data);
				tmp_first = tmp_first->next;
				tmp_last = tmp_last->prev;
			}
		}

		/*------------------------------- PRIVATE HELPER FUNCS: -------------------------------*/

	private:
	
		Node *allocate_node()
		{
			Node *node;

			node = _node_alloc.allocate(1);
			node->next = node;
			node->prev = node;
			return node;
		}

		Node *construct_node(const_reference val)
		{
			Node *node;
			node = allocate_node();
			_allocator_type.construct(&node->data, val);
			return (node);
		}

		void deallocate_node(Node *node)
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
			_node_alloc.deallocate(node, 1);
		}

		void insert_to_the_end(const_reference val)
		{
			Node *last = _tail->prev;

			Node *new_node;
			new_node = construct_node(val);

			new_node->next = _tail;
			_tail->prev = new_node;
			new_node->prev = last;
			last->next = new_node;
			++_size;
		}

		void destroy_and_deallocate_node(Node *node)
		{
			_node_alloc.destroy(node);
			node->prev->next = node->next;
			node->next->prev = node->prev;
			_node_alloc.deallocate(node, 1);
			_size -= 1;
		}

		Node *splitList(Node *src)
		{
			Node *fast = src->next;
			Node *slow = src;

			while (fast != _tail)
			{
				fast = fast->next;
				if (fast != _tail)
				{
					fast = fast->next;
					slow = slow->next;
				}
			}

			Node *splitted = slow->next;
			slow->next = _tail;
			return (splitted);
		}

		template <class Compare>
		Node *mergeSortedLists(Node *first, Node *second, Compare comp, Node **last_node)
		{
			if (first == _tail) // если первый лист пустой
				return (second);
			if (second == _tail) //если второй лист пустой
				return (first);

			// Взять наименьшее значение 
			if (comp(first->data, second->data)) // if first < second
			{
				*last_node = second;
				first->next = mergeSortedLists(first->next, second, comp, last_node);
				first->next->prev = first;
				first->prev = _tail;
				return (first);
			}
			else
			{
				second->next = mergeSortedLists(first, second->next, comp, last_node);
				second->next->prev = second;
				second->prev = _tail;
				return (second);
			}
		}

		template <class Compare>
		Node *mergeSort(Node *first, Compare comp, Node **last_node)
		{
			if (first == _tail || first->next == _tail)
				return (first); // в случае если один элемент в листе

			Node *second = splitList(first); // возвращает указатель на вторую часть разделенной части

			first = mergeSort(first, comp, last_node);
			second = mergeSort(second, comp, last_node);

			return (mergeSortedLists(first, second, comp, last_node));
		}

		allocator_type _allocator_type;
		std::allocator<Node> _node_alloc;
		size_type _size;
		Node *_tail;
	};

	/*------------------------------- NON-MEMBER FUNCITON OVERLOADS: -------------------------------*/

	template <class T, class Alloc>
	bool operator==(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		return (lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	// a<=b	equivalent !(b<a)
	template <class T, class Alloc>
	bool operator<=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	// a>b	equivalent to b<a
	template <class T, class Alloc>
	bool operator>(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	// a>=b	equivalent !(a<b)
	template <class T, class Alloc>
	bool operator>=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	/* SWAP */
	template <class T, class Alloc>
	void swap(list<T, Alloc> &x, list<T, Alloc> &y)
	{
		x.swap(y);
	}
}

#endif
