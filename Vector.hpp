#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "VectorIterator.hpp"
#include "ReverseIterator.hpp"
#include "Utils.hpp"

#include "stddef.h"

namespace ft
{

	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

		typedef ft::VectorIterator<T, T *, T &> iterator;
		typedef ft::VectorIterator<T, const T *, const T &> const_iterator;
		typedef ft::ReverseIterator<iterator> reverse_iterator;
		typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;

		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

		/*------------------------------- CONSTRUCTORS: -------------------------------*/

		explicit vector(const allocator_type &alloc = allocator_type()) : _allocator_type(alloc), _begin_ptr(NULL), _end_ptr(NULL), _end_capacity(NULL) {}

		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type()) : _allocator_type(alloc),_begin_ptr(NULL), _end_ptr(NULL), _end_capacity(NULL)
		{
			if (n)
				assign(n, val);
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value> * = NULL, const allocator_type &alloc = allocator_type()) : _allocator_type(alloc), _begin_ptr(NULL), _end_ptr(NULL), _end_capacity(NULL) 
		{
			assign(first, last);
		}

		vector(const vector &src) : _allocator_type(src._allocator_type), _begin_ptr(NULL), _end_ptr(NULL), _end_capacity(NULL)
		{
			*this = src;
		}

		/*------------------------------- DESTRUCTOR: -------------------------------*/

		virtual ~vector()
		{
			if (_begin_ptr)
			{
				clear();

				_allocator_type.deallocate(this->_begin_ptr, capacity());
				_end_capacity = NULL;
				_begin_ptr = NULL;
				_end_ptr = NULL;

				
			}
		}

		/*------------------------------- OPERATOR=: -------------------------------*/

		vector &operator=(vector const &rhs)
		{
			if (*this != rhs)
			{
				assign(rhs.begin(), rhs.end());
			}
			return (*this);
		}

		/*------------------------------- ITERATORS: -------------------------------*/

		iterator begin()
		{
			return _begin_ptr;
		}

		iterator end()
		{
			return _end_ptr;
		}

		const_iterator begin() const
		{
			return _begin_ptr;
		}

		const_iterator end() const
		{
			return _end_ptr;
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		/*-------------------------------  CAPACITY: -------------------------------*/

		size_type size() const
		{
			return static_cast<size_type>(_end_ptr - _begin_ptr);
		}

		size_t max_size(void) const
		{
			return _allocator_type.max_size();
		}

		void resize(size_type n, value_type val = value_type())
		{
			size_type v_size = size();
			if (n < v_size)
			{
				erase(begin() + n, end());
			}
			else if (v_size < n)
			{
				size_type offset;
				offset = n - v_size;
				insert(end(), offset, val);
			}
		}

		size_type capacity() const
		{
			return static_cast<size_type>(_end_capacity - _begin_ptr);
		}

		bool empty() const
		{
			if (size() == 0)
				return true;
			else
				return false;
		}

		void reserve(size_type n)
		{
			if (n <= capacity())
				return;
			if (n > capacity())
			{
				pointer old_begin = _begin_ptr;
				pointer old_end = _end_ptr;
				size_type old_end_capacity = capacity();

				pointer array = _allocator_type.allocate(n); // выделить память для n объектов
				_end_ptr = array;
				while (_begin_ptr != old_end) // склпировать все в новый массив
				{
					_allocator_type.construct(_end_ptr, *(_begin_ptr)); // создать объект
					_end_ptr++;
					_begin_ptr++;
				}
				_allocator_type.deallocate(old_begin, old_end_capacity);
				_begin_ptr = array;
				_end_capacity = _begin_ptr + n; // увеличить capacity
			}
		}

		/*-------------------------------  ELEMENT ACCESS: -------------------------------*/

		reference operator[](size_type n)
		{
			return _begin_ptr[n];
		}

		const_reference operator[](size_type n) const
		{
			return _begin_ptr[n];
		}

		reference at(size_type n)
		{
			if (n < 0 || n > size())
				throw(std::out_of_range("error: out of range"));
			return (_begin_ptr[n]);
		}

		const_reference at(size_type n) const
		{
			if (n < 0 || n > size())
				throw(std::out_of_range("error: out of range"));
			return _begin_ptr[n];
		}

		reference front()
		{
			return *(_begin_ptr);
		}

		const_reference front() const
		{
			return *(_begin_ptr);
		}

		reference back()
		{
			return *(_end_ptr - 1);
		}

		const_reference back() const { return *(_end_ptr - 1); }

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

		void push_back(const value_type &val)
		{
			this->insert(this->end(), val);
		}

		void pop_back()
		{
			_allocator_type.destroy(&back());
			_end_ptr--;
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			size_type len = (&(*position)) - _begin_ptr;

			if (capacity() > n + size() - 1)
			{
				for (size_type i = 0; i < this->size() - len; i++) // size - len так мы узнаем кол-во элементов после n, которые надо переместить
					_allocator_type.construct(_end_ptr - i + (n - 1), *(_end_ptr - i - 1));
				_end_ptr += n;
				while (n != 0)
				{
					_allocator_type.construct(&(*position) + (n - 1), val); // заполняем с конца 
					n--;
				}
			}
			else
			{
				reserve(size() * 2 + n);
				for (size_type i = 0; i < this->size() - len; i++)
					_allocator_type.construct(_end_ptr - i + (n - 1), *(_end_ptr - i - 1)); // заполняем элементами, которые идут после тех, которые нужно вставить
				_end_ptr += n;
				size_type i = len;
				for (size_type j = 0; j < n; j++, i++)
				{
					_allocator_type.construct(_begin_ptr + i, val); // заполняем элементами, которые нужно вставить
				}
			}
		}

		iterator insert(iterator position, const value_type &val)
		{
			difference_type diff = position - begin();
			insert(position, 1, val);
			return (iterator(begin() + diff));
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first,
					InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type isIterator = InputIterator())
		{
			(void)isIterator;
			size_type len = (&(*position)) - _begin_ptr;

			difference_type diff = calculate_diff(first, last); // считаем кол-во элементов, которые нужно вставить
			if (capacity() >= diff + size())
			{
				for (size_type i = 0; i < size() - len; i++)
					_allocator_type.construct(_end_ptr - i + (diff - 1), *(_end_ptr - i - 1)); // перемещаем оставшиеся элементы после 'n' на новые позиции
				_end_ptr += diff;
				for (int i = 0; i < diff; ++i)
				{
					_allocator_type.construct(&(*position) + i, *first);
					first++;
				}
			}
			else
			{
				reserve(size() * 2 + diff);
				for (size_type i = 0; i < this->size() - len; i++)
					_allocator_type.construct(_end_ptr - i + (diff - 1), *(_end_ptr - i - 1)); // заполняем элементами, которые идут после тех, которые нужно вставить
				_end_ptr += diff;
				size_type i = len;
				for (int j = 0; j < diff; j++, i++, first++)
				{
					_allocator_type.construct(_begin_ptr + i, *first); // заполняем элементами, которые нужно вставить
				}
			}
		}

		iterator erase(iterator position)
		{
			pointer ptr_pos = &(*position);
			_allocator_type.destroy(&(*position));
			for (int i = 0; i < _end_ptr - ptr_pos - 1; i++)
			{
				_allocator_type.construct(ptr_pos + i, *(ptr_pos + i + 1)); // скопировать правую часть массива на место, куда указывает удаляемый элемент
				_allocator_type.destroy(ptr_pos + i + 1);					// уничтожить дубликаты (ранее скопированный элемент)
			}
			_end_ptr--;
			return (iterator(ptr_pos));
		}

		iterator erase(iterator first, iterator last)
		{
			pointer ptr_first = &(*first);
			pointer ptr_last = &(*last);

			while (first != last)
			{
				_allocator_type.destroy(&(*first)); // удалить range элементов
				first++;
			}
			for (int i = 0; i < _end_ptr - ptr_last; i++)
			{
				_allocator_type.construct(ptr_first + i, *(ptr_last + i)); // скопировать правую часть массива на место, куда указывает удаляемый элементs
				_allocator_type.destroy(ptr_last + i);					   //  уничтожить дубликаты (ранее скопированный элемент)
			}
			_end_ptr -= ptr_last - ptr_first;
			return (iterator(ptr_first));
		}

		void swap(vector &x)
		{
			if (*this == x)
				return;
			std::swap(_begin_ptr, x._begin_ptr);
			std::swap(_end_ptr, x._end_ptr);
			std::swap(_end_capacity, x._end_capacity);
		}

		void clear()
		{
			size_type v_size = size();
			for (size_type i = 0; i < v_size; i++)
			{
				_allocator_type.destroy(_end_ptr--);
			}
		}

	private:

		template<class iterator>
		difference_type calculate_diff(iterator first, iterator last)
		{
			difference_type diff = 0;
			for (; first != last; first++)
				diff++;
			return diff;
		}

	private:
		allocator_type _allocator_type;
		pointer _begin_ptr;
		pointer _end_ptr;
		pointer _end_capacity;
		
	};

	/*------------------------------- NON-MEMBER FUNCITON OVERLOADS: -------------------------------*/

	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}
}

#endif