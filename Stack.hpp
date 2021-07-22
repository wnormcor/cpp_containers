#ifndef STACK_HPP
#define STACK_HPP

#include "List.hpp"
#include <deque>

namespace ft
{
	template <class T, class Container = std::deque<T> >
	class stack
	{

		public:
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;

		private:
			container_type cont;

		public:
			
			explicit stack (const container_type& ctnr = container_type()) : cont(ctnr) {}
			
			bool empty() const
			{
				return cont.empty();
			}

			size_type size() const
			{
				return cont.size();
			}

			value_type& top()
			{
				return cont.back();
			}
			
			const value_type& top() const
			{
				return cont.back();
			}

			void push (const value_type& val)
			{
				return cont.push_back(val);
			}

			void pop()
			{
				return cont.pop_back();
			}

			template<class T_, class Container_>
					friend bool
					operator==(const stack<T_, Container_> &lhs, const stack<T_, Container_> &rhs);

				template<class T_, class Container_>
					friend bool
					operator!=(const stack<T_, Container_> &lhs, const stack<T_, Container_> &rhs);

				template<class T_, class Container_>
					friend bool
					operator<(const stack<T_, Container_> &lhs, const stack<T_, Container_> &rhs);

				template<class T_, class Container_>
					friend bool
					operator<=(const stack<T_, Container_> &lhs, const stack<T_, Container_> &rhs);

				template<class T_, class Container_>
					friend bool
					operator>(const stack<T_, Container_> &lhs, const stack<T_, Container_> &rhs);

				template<class T_, class Container_>
					friend bool
					operator>=(const stack<T_, Container_> &lhs, const stack<T_, Container_> &rhs);
	};

	 /*================================ NON-MEMBER OVERLOADS: ================================*/

	 
	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.cont == rhs.cont);
	}

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.cont != rhs.cont);
	}

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.cont < rhs.cont);
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.cont <= rhs.cont);
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.cont > rhs.cont);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.cont >= rhs.cont);
	}
}

#endif