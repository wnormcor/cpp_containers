#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

/* @reference : 
http://cplusplus.com/reference/iterator/reverse_iterator/?kw=reverse_iterator */

namespace ft
{
	template <class Iterator>
	class ReverseIterator
	{
	public:
		typedef Iterator iterator_type;
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;

		/* ------------------------------- CONSTRUCTORS:  ------------------------------- */
		ReverseIterator() {}

		explicit ReverseIterator(iterator_type type) : _type(type) {}

		template<class Iter>
		ReverseIterator(const ReverseIterator<Iter> &rev_type) : _type(rev_type.base()) {}

		/* ------------------------------- DESTRUCTOR:  ------------------------------- */

		virtual ~ReverseIterator() {}

		/* ------------------------------- OPERATIONS:  ------------------------------- */

		iterator_type base() const
		{
			return (_type);
		}

		reference operator*() const
		{
			iterator_type base_copy = this->_type;
			return *(--base_copy);
		}

		ReverseIterator operator+(difference_type n) const
		{
			return ReverseIterator(this->_type - n);
		}

		ReverseIterator &operator++()
		{
			this->_type--;
			return (*this);
		}

		ReverseIterator operator++(int)
		{
			ReverseIterator base_copy(*this);
			this->_type--;
			return (base_copy);
		}

		ReverseIterator &operator+=(difference_type n)
		{
			this->_type -= n;
			return (*this);
		}

		ReverseIterator operator-(difference_type n) const
		{
			return ReverseIterator(this->_type + n);
		}

		ReverseIterator &operator--()
		{
			this->_type++;
			return (*this);
		}

		ReverseIterator operator--(int)
		{
			ReverseIterator base_copy(*this);
			this->_type++;
			return (base_copy);
		}

		ReverseIterator &operator-=(difference_type n)
		{
			this->_type += n;
			return (*this);
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		reference operator[](difference_type n) const
		{
			return base()[-n - 1];
		}

	private:
		iterator_type _type;
	};

	/* ------------------------------- RELATIONAL OPERATIONS:  ------------------------------- */

	template <class Iterator>
	bool operator==(const ReverseIterator<Iterator> &lhs,
					const ReverseIterator<Iterator> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class Iterator>
	bool operator!=(const ReverseIterator<Iterator> &lhs,
					const ReverseIterator<Iterator> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class Iterator>
	bool operator<(const ReverseIterator<Iterator> &lhs,
				   const ReverseIterator<Iterator> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <class Iterator>
	bool operator<=(const ReverseIterator<Iterator> &lhs,
					const ReverseIterator<Iterator> &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <class Iterator>
	bool operator>(const ReverseIterator<Iterator> &lhs,
				   const ReverseIterator<Iterator> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <class Iterator>
	bool operator>=(const ReverseIterator<Iterator> &lhs,
					const ReverseIterator<Iterator> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <class Iterator>
	ReverseIterator<Iterator> operator+(
		typename ReverseIterator<Iterator>::difference_type n,
		const ReverseIterator<Iterator> &rev_it)
	{
		return (ReverseIterator<Iterator>(rev_it.base() - n));
	}

	template <class Iterator>
	typename ReverseIterator<Iterator>::difference_type operator-(
		const ReverseIterator<Iterator> &lhs,
		const ReverseIterator<Iterator> &rhs)
	{
		return rhs.base() - lhs.base();
	}
}

#endif