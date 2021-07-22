#include "../Stack.hpp"
#include "../Vector.hpp"
#include "../List.hpp"
#include <deque>
#include <list>
#include <vector>
#include <iostream>
#include <iterator>
#include <stack>
#include <unistd.h>

#define red "\x1b[31m"
#define green "\x1b[32m"
#define yellow "\x1b[33m"
#define blue "\x1b[34m"
#define cend "\x1b[0m"

void contstructor_test()
{
	std::cout << blue << "***************[ Constructors test ]***************" << cend << std::endl;

	std::deque<char> mydeque(9, 'a'); // deque with 9 elements
	ft::vector<int> myvector(2, 200); // vector with 2 elements

	ft::stack<int> first;          // empty stack
	ft::stack<int, std::list <int> >mylist; // stack initialized to copy of deque

	ft::stack<int, std::list <int> > second(mylist); // stack initialized to copy of list

	ft::stack<int, ft::vector<int> > third; // empty stack using vector
	ft::stack<int, ft::vector<int> > fourth(myvector);

	std::cout << "size of first: " << first.size() << std::endl;
	std::cout << "size of second: " << second.size() << std::endl;
	std::cout << "size of third: " << third.size() << std::endl;
	std::cout << "size of fourth: " << fourth.size() << std::endl;
}

void empty_test()
{
	std::cout << blue << "***************[ empty() test ]***************" << cend << std::endl;

	ft::stack<int> mystack_e;
	int sum(0);

	for (int i = 1; i <= 10; i++)
		mystack_e.push(i);

	while (!mystack_e.empty())
	{
		sum += mystack_e.top();
		mystack_e.pop();
	}

	std::cout << "total: " << sum << std::endl;
}

void size_test()
{
	std::cout << blue << "***************[ size() test ]***************" << cend << std::endl;

	ft::stack<int> myints;
	std::cout << "0. size: " << myints.size() << std::endl;

	for (int i = 0; i < 5; i++)
		myints.push(i);
	std::cout << "1. size: " << myints.size() << std::endl;

	myints.pop();
	std::cout << "2. size: " << myints.size() << std::endl;
}

void top_push_test()
{
	std::cout << blue << "***************[ top & push test ]***************" << cend << std::endl;
	ft::stack<int> mystack;

	mystack.push(10);
	mystack.push(20);

	mystack.top() -= 5;

	std::cout << "mystack.top() is now " << mystack.top() << std::endl;
}

void pop_test()
{
	std::cout << blue << "***************[ pop() test ]***************" << cend << std::endl;
	ft::stack<int> mystack;

	for (int i = 0; i < 5; ++i)
		mystack.push(i);

	std::cout << "Popping out elements...";
	while (!mystack.empty())
	{
		std::cout << ' ' << mystack.top();
		mystack.pop();
	}
	std::cout << std::endl;
}

void relational_operators_test()
{
	ft::stack<int> mystack;
	for (int i = 0; i < 10; ++i)
		mystack.push(i);
	ft::stack<int> mystack1(mystack);

	bool b = mystack == mystack1;
	std::cout << "mystack == mystack1(true) : " << b << std::endl;
	b = mystack != mystack1;
	std::cout << "mystack != mystack1(false) : " << b << std::endl;
	mystack.pop();
	b = mystack < mystack1;
	std::cout << "mystack < mystack1(true) : " << b << std::endl;
	b = mystack > mystack1;
	std::cout << "mystack > mystack1(false) : " << b << std::endl;
	b = mystack <= mystack1;
	std::cout << "mystack <= mystack1(true) : " << b << std::endl;
	b = mystack >= mystack1;
	std::cout << "mystack >= mystack1(false) : " << b << std::endl;  
}

int main()
{
	contstructor_test();
	empty_test();
	size_test();
	top_push_test();
	pop_test();
	relational_operators_test();
  //  sleep(50);
	return 0;
}