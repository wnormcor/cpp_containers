#ifndef MAP_HPP
#define MAP_HPP

#include "MapIterator.hpp"
#include "ReverseIterator.hpp"
#include "Utils.hpp"
#include <iomanip>
#include <math.h>

namespace ft
{
	template <class Key, class T,
			  class Compare = less<Key>,
			  class Alloc = std::allocator<std::pair<Key, T> > >
	class map
	{

	private:
		struct Node
		{
			std::pair<Key, T> val;
			Node *left;
			Node *right;
			Node *parent;
			int height;
		};

	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef std::pair<key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;

		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

		typedef typename ft::MapIterator<value_type, value_type*, value_type&, Node, key_compare> iterator;
		typedef typename ft::MapIterator<value_type, const value_type*, const value_type&, Node, key_compare> const_iterator;
		typedef typename ft::ReverseIterator<iterator> reverse_iterator;
		typedef typename ft::ReverseIterator<const_iterator> const_reverse_iterator;

		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map;

		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}

		public:
			bool
			operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

		/*------------------------------- CONSTRUCTORS: -------------------------------*/

		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type()) : _node(NULL), _comp(comp), _allocator_type(alloc)
		{
			this->_tail = allocate_tree_node();
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value> * = NULL,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : _node(NULL), _comp(comp), _allocator_type(alloc)
		{
			this->_tail = allocate_tree_node();
			this->insert(first, last);
		}

		map(const map &x) : _node(x._node), _comp(x._comp), _allocator_type(x._allocator_type)
		{
			this->_tail = allocate_tree_node();
			_node = _alloc_node.allocate(1);
			*this = x;
		}

		/*------------------------------- DESTRUCTOR: -------------------------------*/

		virtual ~map()
		{
			clear();
			_alloc_node.deallocate(_tail, 1);
		}

		/*------------------------------- OPERATOR=: -------------------------------*/

		map &operator=(const map &x)
		{
			if (&x != this)
			{
				clear();
				insert(x.begin(), x.end());
			}
			return (*this);
		}

		/*------------------------------- ITERATORS: -------------------------------*/

		iterator begin()
		{
			if (!_tail->right) // в последней ноде всегда меняем минимальное значение после вставки
				return (iterator(_node));
			return (iterator(_tail->right));
		}

		const_iterator begin() const
		{
			if (!_tail->right)
				return (const_iterator(_node));
			return (const_iterator(_tail->right));
		}

		iterator end()
		{
			return (iterator(_tail));
		}

		const_iterator end() const
		{
			return (const_iterator(_tail));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(end()));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(end()));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(begin()));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(begin()));
		}

		/*-------------------------------  CAPACITY: -------------------------------*/

		bool empty() const
		{
			if (!_node)
				return true;
			else
				return false;
		}

		size_type size() const
		{
			if (!_node)
				return (0);
			return (tree_size(_node) + 1);
		}

		size_type max_size() const
		{
			return this->_alloc_node.max_size();
		}

		/*-------------------------------  ELEMENT ACCESS: -------------------------------*/

		mapped_type &operator[](const key_type &k)
		{
			return (*((this->insert(std::make_pair(k, mapped_type()))).first)).second;
		}

		/*-------------------------------  MODIFIERS: ------------------------------- */

		std::pair<iterator, bool>
		insert(const value_type &val)
		{
			if (_tail->left)
				unlink_end();

			Node *current = _node;
			Node *tmp;

			while (current)
			{
				if (current->val.first == val.first)
				{
					link_end();
					return std::make_pair(iterator(current), false);
				}
				if (_comp(val.first, current->val.first)) // val.first < current->val.first
				{
					current = current->left;
				}
				else
				{
					current = current->right;
				}
			}
			_node = insert_node(_node, val);
			current = _node;
			while (current)
			{
				tmp = current;
				if (_comp(val.first, current->val.first)) // val.first < current->val.first
				{
					current = current->left;
				}
				else
				{
					current = current->right;
				}
			}
			link_end();
			return std::make_pair(iterator(tmp), true);
		}

		iterator
		insert(iterator position, const value_type &val)
		{
			Node *current;
			Node *tmp;

			(void)position;
			if (_tail->left)
				unlink_end();
			_node = insert_node(_node, val);
			current = _node;
			while (current)
			{
				tmp = current;
				if (_comp(val.first, current->val.first)) // val.first < current->val.first
				{
					current = current->left;
				}
				else
				{
					current = current->right;
				}
			}
			link_end();
			return (iterator(tmp));
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type isIterator = InputIterator())
		{
			(void)isIterator;
			while (first != last)
				insert(*(first++));
		}

		/* ERASE */

		void erase(iterator position)
		{
			erase((*position).first);
		}

		size_type erase(const key_type &k)
		{
			if (_tail->right == _tail->left)
			{
				unlink_end();
				_alloc_node.destroy(_node);
				_alloc_node.deallocate(_node, 1);
				_node = NULL;
				return 1;
			}
			unlink_end();
			_node = deleteNode(_node, k);
			link_end();
			return 1;
		}

		void erase(iterator first, iterator last)
		{
			if (first == this->begin() && last == this->end())
			{
				while (first != last && _node != NULL)
					erase((*(first++)).first);
			}
			else
			{
				difference_type n = calculate_diff(first, last);
				while (n--)
					erase((*(first++)).first);
			}
		}

		/* SWAP */

		void swap(map &x)
		{
			if (this == &x)
				return;
			ft::swap(this->_node, x._node);
			ft::swap(this->_allocator_type, x._allocator_type);
			ft::swap(this->_alloc_node, x._alloc_node);
			ft::swap(this->_comp, x._comp);
			ft::swap(this->_tail, x._tail);
		}

		/* CLEAR */

		void clear()
		{
			erase(begin(), end());
		}

		/*================================ OBSERVERS: ================================*/

		key_compare key_comp() const
		{
			return key_compare();
		}

		value_compare value_comp() const
		{
			return value_compare(key_compare());
		}

		/*================================ OPERATIONS: ================================*/

		iterator find(const key_type &k)
		{
			Node *current = _node;
			unlink_end();
			while (current)
			{
				if (current->val.first == k)
				{
					link_end();
					return (iterator(current));
				}
				if (_comp(k, current->val.first)) // k < current->val.first
				{
					current = current->left;
				}
				else
				{
					current = current->right;
				}
			}
			link_end();
			return end();
		}

		const_iterator find(const key_type &k) const
		{
			const_iterator(find(k));
		}

		size_type count(const key_type &k) const
		{
			Node *current = _node;
			size_type count = 0;
			while (current)
			{
				if (current->val.first == k)
				{
					count++;
				}
				if (_comp(k, current->val.first)) // k < current->val.first
				{
					current = current->left;
				}
				else
				{
					current = current->right;
				}
			}
			return count;
		}

		iterator lower_bound(const key_type &k)
		{
			iterator start = this->begin();
			iterator end = this->end();

			while (start != end)
			{
				if (_comp((*start).first, k) == false)
					break;
				start++;
			}
			return (start);
		}

		const_iterator lower_bound(const key_type &k) const
		{
			return const_iterator(lower_bound(k));
		}

		iterator upper_bound(const key_type &k)
		{
			iterator start = this->begin();
			iterator end = this->end();

			while (start != end)
			{
				if (_comp(k, (*start).first))
					break;
				start++;
			}
			return (start);
		}

		const_iterator upper_bound(const key_type &k) const
		{
			return const_iterator(upper_bound(k));
		}

		std::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return std::make_pair(lower_bound(k), upper_bound(k));
		}

		std::pair<iterator, iterator> equal_range(const key_type &k)
		{
			return std::make_pair(lower_bound(k), upper_bound(k));
		}

		/*================================ HELPING FUNCTIONS : ================================*/

	private:

		Node *allocate_tree_node()
		{
			Node *node;

			node = this->_alloc_node.allocate(1);
			node->right = NULL;
			node->left = NULL;
			node->parent = NULL;
			std::memset(&node->val, 0, sizeof(node->val));
			return node;
		}

		// Получить максимум из двух чисел
		int max(int a, int b)
		{
			return (a > b) ? a : b;
		}

		// высчитываем высоту поддерева (рекурсивная функция)
		size_type _height(Node *tmp, int i = 1)
		{
			int x;
			int y;
			if (tmp && tmp != _tail)
			{
				if (tmp->left && tmp->right && tmp->right != _tail)
				{
					x = _height(tmp->left, i + 1);
					y = _height(tmp->right, i + 1);
					i = (x > y) ? x : y;
				}
				else if (tmp->left)
					i = _height(tmp->left, i + 1);
				else if (tmp->right && tmp->right != _tail)
					i = _height(tmp->right, i + 1);
			}
			else
				return (0);

			return (i);
		}

		// Вспомогательная функция, которая выделяет новую ноду с заданным ключом и NULL левым и правым указателями
		Node *newNode(const value_type &val, Node *parent = NULL)
		{
			Node *node;
			node = _alloc_node.allocate(1);
			_allocator_type.construct(&node->val, val);
			node->right = NULL;
			node->left = NULL;
			node->parent = parent;

			return (node);
		}

		// правый поворот - у которой корень - это y
		Node *rightRotate(Node *y)
		{
			Node *x = y->left;
			Node *T2 = x->right;

			// делаем поворот
			x->right = y;
			y->left = T2;

			// обновляем значения родителей у меняемых узлов
			x->parent = y->parent;
			y->parent = x;
			if (T2)
				T2->parent = y;

			// возвращаем новый корень
			return x;
		}

		// левый поворот
		Node *leftRotate(Node *x)
		{
			Node *y = x->right;
			Node *T2 = y->left;

			// делаем поворот
			y->left = x;
			x->right = T2;

			// обновляем родителей у x/y
			y->parent = x->parent;
			x->parent = y;
			if (T2)
				T2->parent = x;

			// возвращаем новый рут
			return y;
		}

		// посчитаем баланс ноды (баланс фактор) -> вызывает рекурсивный хайт
		int getBalance(Node *N)
		{
			if (N == NULL)
				return 0;
			return _height(N->left) - _height(N->right);
		}

		// рекурсивная функция, чтобы вставить ноду в зависимости от функции сравнения
		Node *insert_node(Node *node, const value_type &val, Node *parent = NULL)
		{
			if (node == NULL)
				return (newNode(val, parent));						// крайний случай (первая нода - первая вставка)

			// вставляем ноду без балансировки 
			if (_comp(val.first, node->val.first))					// val.first < node->val.first
			{
				node->left = insert_node(node->left, val, node);	// сюда вставляем если меньше верхнего узла
			}
			else													// val.first > node->val.first
			{
				node->right = insert_node(node->right, val, node);	// вставляем вправо (если больше)
			}

			// считаем баланс фактор (уходим в рекурсию для данного узла)
			int balance = getBalance(node);

			// если данный узел не сбалансирован - то возможно 4 варианта поворотов:

			// Левый поворот
			if (balance > 1 && _comp(val.first, node->left->val.first)) //val.first < node->left->val.first
				return rightRotate(node);

			// Правый поворот
			if (balance < -1 && _comp(node->right->val.first, val.first)) // val.first > node->right->val.first
				return leftRotate(node);

			// Левый правый поворот
			if (balance > 1 && _comp(node->left->val.first, val.first)) // val.first > node->left->val.first
			{
				node->left = leftRotate(node->left);
				return rightRotate(node);
			}

			// Правый левый поворот
			if (balance < -1 && _comp(val.first, node->right->val.first)) // val.first < node->right->val.first
			{
				node->right = rightRotate(node->right);
				return leftRotate(node);
			}
			
			// возвращаем указатель на ноду
			return node;
		}

		// удаление ноды
		Node *deleteNode(Node *root, const key_type &key)
		{

			// если нет элементов - то отдаем указатель (крайний случай)
			if (root == NULL)
				return root;

			// если меньше узла - то идем налево
			if (_comp(key, root->val.first))				// key < root->val.first
				root->left = deleteNode(root->left, key);

			// если больше - то идем на право
			else if (_comp(root->val.first, key))			// key > root->val.first
				root->right = deleteNode(root->right, key);

			// если равно данному узлу - то удаляем ноду
			else
			{
				// нода только с одним потомком или без "детей"
				if ((root->left == NULL) ||
					(root->right == NULL))
				{
					Node *temp = root->left ? root->left : root->right;

					// Без "детей"
					if (temp == NULL)
					{
						temp = root;
						root = NULL;
					}
					else
					{
						temp->parent = root->parent;
						*root = *temp;
					} // Если только один "ребенок" то копируем контент на родительский узел (передвигаем указатель)
					_alloc_node.destroy(temp);
					_alloc_node.deallocate(temp, 1);
				}
				else
				{
					// нода с двумя детьми - нужно найти минимальное от нее значение справа
					Node *temp = min_node(root->right);

					// скопировать данные этой ноды из темпа в рут
					root->val = temp->val;

					// удалить искомую ноду
					root->right = deleteNode(root->right,
											 temp->val.first);
				}
			}

			// если в дереве только одна нода - возвращаем ее
			if (root == NULL)
				return root;

			// считаем баланс фактор
			int balance = getBalance(root);

			// есть 4 кейса как и прежде

			// Левый левый поворот
			if (balance > 1 &&
				getBalance(root->left) >= 0)
				return rightRotate(root);

			// Левый правый поворот
			if (balance > 1 &&
				getBalance(root->left) < 0)
			{
				root->left = leftRotate(root->left);
				return rightRotate(root);
			}

			// Правый поворот
			if (balance < -1 &&
				getBalance(root->right) <= 0)
				return leftRotate(root);

			// Правый левый поворот
			if (balance < -1 &&
				getBalance(root->right) > 0)
			{
				root->right = rightRotate(root->right);
				return leftRotate(root);
			}

			return root;
		}

		Node *min_node(Node *node)
		{
			if (node)
			{
				while (node->left)
					node = node->left;
			}
			return (node);
		}

		Node *max_node(Node *node)
		{
			if (node)
			{
				while (node->right)
					node = node->right;
			}
			return (node);
		}

		size_type tree_size(Node *node) const
		{
			if (node == NULL || node->right == _tail)
				return 0;
			return (tree_size(node->left) + 1 + tree_size(node->right));
		}

		void unlink_end()
		{
			if (_tail->left)
				_tail->left->right = NULL;
		}

		void link_end()
		{
			Node *max = max_node(_node);

			_node->parent = NULL;
			max->right = _tail;
			_tail->left = max;
			_tail->right = min_node(_node);
			_tail->parent = max;
		}

		template<class iterator>
		difference_type calculate_diff(iterator first, iterator last)
		{
			difference_type diff = 0;
			for (; first != last; first++)
				diff++;
			return diff;
		}


	private:
		Node *_node;
		Node *_tail;
		Compare _comp;
		allocator_type _allocator_type;
		std::allocator<Node> _alloc_node;
	};
}

#endif