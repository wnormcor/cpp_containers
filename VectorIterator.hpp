#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

namespace ft
{
	template <class T, class Pointer, class Reference>
	class VectorIterator
	{
   
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef std::random_access_iterator_tag     iterator_category;

		typedef VectorIterator<T, Pointer, Reference> iterator_type;

	   /* ----------------------------- CONSTRUCTORS:  ------------------------------- */

		VectorIterator(pointer ptr = 0) : _ptr(ptr) {}

		VectorIterator(VectorIterator<T, T*, T&> const &my_it) : _ptr(my_it.base()) {} 

		VectorIterator &operator=(VectorIterator<T, T*, T&> const &rhs) 
		{
			if (this != &rhs)
				_ptr = rhs.base();
			return (*this);
		}

	   /* ------------------------------- DESTRUCTOR: ------------------------------- */

	   virtual ~VectorIterator() {}


		/*------------------------------- INCREMENTS: -------------------------------*/

		/*------------------------------- (++a) -------------------------------*/
		VectorIterator &operator++()
		{
			_ptr++;
			return (*this);
		}
	
		/*------------------------------- (a++) -------------------------------*/ 
		VectorIterator operator++(int)
		{
			VectorIterator copy(*this);
			operator++();
			return (copy);
		}

		/*------------------------------- DECREMENT: -------------------------------*/

		/*------------------------------- (--a) -------------------------------*/
		VectorIterator &operator--()
		{
			_ptr--;
			return (*this);
		}
		
		/*------------------------------- (a--) -------------------------------*/
		VectorIterator operator--(int)
		{
			VectorIterator copy(*this);
			operator--();
			return (copy);
		}

		/*------------------------------- += && -= : -------------------------------*/
		VectorIterator &operator+=(size_t n)
		{
			_ptr += n;
			return (*this);
		}

		VectorIterator &operator-=(size_t n)
		{
			_ptr -= n;
			return (*this);
		}

	   /*------------------------------- ARITHMETIC OPERATIONS : -------------------------------*/

		VectorIterator operator+(difference_type n) const
		{
			return (VectorIterator<T, T*, T&>(_ptr + n));
		}

		VectorIterator operator-(difference_type n) const
		{
			return (VectorIterator<T, T*, T&>(_ptr - n));
		}

		/*-------------------------------DEREFERENCE: -------------------------------*/

		reference operator*() const
		{
			return *_ptr;
		}

		pointer operator->() const
		{
			return _ptr;
		}

		reference operator[](difference_type n) const
		{
			return _ptr[n];
		}

		/*------------------------------- GETTER: ------------------------------- */
		pointer base() const
		{
			return (_ptr);
		}

		private:
			pointer _ptr;
	};

   /*------------------------------- RELATIONAL OPERATORS: ------------------------------- */

	template <class T, class Pointer, class Reference>
	VectorIterator<T, Pointer, Reference> operator+(
		typename VectorIterator<T, Pointer, Reference>::difference_type n,
		const VectorIterator<T, Pointer, Reference> &m_it)
	{
		return (VectorIterator<T, Pointer, Reference>(m_it.base() + n));
	}

	template <class T, class Pointer, class Reference>
	typename VectorIterator<T, Pointer, Reference>::difference_type operator-(
		const VectorIterator<T, Pointer, Reference> &lhs,
			  const VectorIterator<T, Pointer, Reference> &rhs)
	{
		return lhs.base() - rhs.base();
	}

	template <class Tl, class Pl, class Rl, class Tr, class Pr, class Rr>
	bool operator==(const VectorIterator<Tl, Pl, Rl> &lhs,
					const VectorIterator<Tr, Pr, Rr> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class Tl, class Pl, class Rl, class Tr, class Pr, class Rr>
	bool operator!=(const VectorIterator<Tl, Pl, Rl> &lhs,
					const VectorIterator<Tr, Pr, Rr> &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <class Tl, class Pl, class Rl, class Tr, class Pr, class Rr>
	bool operator<(const VectorIterator<Tl, Pl, Rl> &lhs,
				   const VectorIterator<Tr, Pr, Rr> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Tl, class Pl, class Rl, class Tr, class Pr, class Rr>
	bool operator<=(const VectorIterator<Tl, Pl, Rl> &lhs,
					const VectorIterator<Tr, Pr, Rr> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Tl, class Pl, class Rl, class Tr, class Pr, class Rr>
	bool operator>(const VectorIterator<Tl, Pl, Rl> &lhs,
				   const VectorIterator<Tr, Pr, Rr> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Tl, class Pl, class Rl, class Tr, class Pr, class Rr>
	bool operator>=(const VectorIterator<Tl, Pl, Rl> &lhs,
					const VectorIterator<Tr, Pr, Rr> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}
}

#endif