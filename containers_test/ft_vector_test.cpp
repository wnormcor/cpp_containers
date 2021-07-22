#include "../Vector.hpp"
#include <iostream>
#include <unistd.h>
#include <vector>

#define red "\x1b[31m"
#define green "\x1b[32m"
#define yellow "\x1b[33m"
#define blue "\x1b[34m"
#define cend "\x1b[0m"

void print_int_array(ft::vector<int> &vec)
{
	ft::vector<int>::iterator it = vec.begin();
	ft::vector<int>::iterator ite = vec.end();
	while (it != ite)
	{
		std::cout << *it << " | ";
		it++;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void print_float_array(ft::vector<float> &vec)
{
	ft::vector<float>::iterator it = vec.begin();
	ft::vector<float>::iterator ite = vec.end();
	while (it != ite)
	{
		std::cout << *it << " | ";
		it++;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void print_double_array(ft::vector<double> &vec)
{
	ft::vector<double>::iterator it = vec.begin();
	ft::vector<double>::iterator ite = vec.end();
	while (it != ite)
	{
		std::cout << *it << " | ";
		it++;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void print_char_array(ft::vector<char> &vec)
{
	ft::vector<char>::iterator it = vec.begin();
	ft::vector<char>::iterator ite = vec.end();
	while (it != ite)
	{
		std::cout << *it << " | ";
		it++;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void print_string_array(ft::vector<std::string> &vec)
{
	ft::vector<std::string>::iterator it = vec.begin();
	ft::vector<std::string>::iterator ite = vec.end();
	while (it != ite)
	{
		std::cout << *it << " | ";
		it++;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void constructor_test()
{
	std::cout << blue << "***************[ Default constructor test ]***************" << cend << std::endl;

	std::cout << green << "Testing empty vector int: " << cend << std::endl;
	ft::vector<int> vec;
	std::cout << "vector size is: " << vec.size() << std::endl
			  << std::endl;

	std::cout << blue << "***************[ Fill constructor test ]***************" << cend << std::endl;
	std::cout << green << "Testing vector<int> vec1(10, 42): " << cend << std::endl;
	ft::vector<int> vec1(10, 42);
	print_int_array(vec1);
	std::cout << std::endl;

	std::cout << blue << "***************[ Range constructor test ]***************" << cend << std::endl;
	ft::vector<int> vec2;
	for (int i = 0; i < 10; ++i)
	{
		vec2.push_back(i);
	}
	ft::vector<int>::iterator it = vec2.begin();
	ft::vector<int> vec3(it, it + 2);
	print_int_array(vec3);
	std::cout << std::endl;

	std::cout << blue << "***************[ Copy constructor test ]***************" << cend << std::endl;
	std::cout << green << "Making copy vector<int> vec4(vec1): " << cend << std::endl;
	ft::vector<int>				vec4(vec1);
	print_int_array(vec4);

	std::cout << blue << "***************[ Operator = test ]***************" << cend << std::endl;
	std::cout << green << "Making vector<int> vec5 = vec1: " << cend << std::endl;
	ft::vector<int>				vec5(10, 4);
	vec1 = vec5;
	print_int_array(vec1);
	std::cout << std::endl;
}


void iterator_test()
{
	std::cout << blue << "***************[ Iterators test (char) ]***************" << cend << std::endl;

	ft::vector<int> vec;
	for (int i = 0; i < 10; ++i)
	{
		vec.push_back(i);
	}
	std::cout << green << "vector contents, using iterator: " << cend << std::endl;
	print_int_array(vec);
	std::cout << green << "vector contents in reverse, using the reverse iterator: " << cend << std::endl;

	ft::vector<int>::reverse_iterator rit = vec.rbegin();
	ft::vector<int>::reverse_iterator rite = vec.rend();

	while (rit != rite)
	{
		std::cout << *rit << " ";
		rit++;
	}
	std::cout << std::endl;

	std::cout << green << "Testing arithmetic operations on iterator: " << cend << std::endl;
	ft::vector<int>::iterator it = vec.begin();
	std::cout << "it value: " << *it << std::endl;
	it++;
	std::cout << "it++ value: " << *it << std::endl;
	it--;
	std::cout << "it-- value: " << *it << std::endl;
	++it;
	std::cout << "++it value: " << *it << std::endl;
	--it;
	std::cout << "--it value: " << *it << std::endl;
	it = it + 5;
	std::cout << "it = it + 5: " << *it << std::endl;
	it = it - 2;
	std::cout << "it = it - 2: " << *it << std::endl;
	it += 3;
	std::cout << "it += 3: " << *it << std::endl;
	it -= 3;
	std::cout << "it -= 3: " << *it << std::endl;
	bool b = (it == it + 1);
	std::cout << "it == it + 1: " << b << std::endl;
	b = (it != it + 1);
	std::cout << "it != it + 1: " << b << std::endl;
	b = (it > it + 1);
	std::cout << "it > it + 1: " << b << std::endl;
	b = (it >= it);
	std::cout << "it >= it: " << b << std::endl;
	b = (it < it);
	std::cout << "it < it: " << b << std::endl;
	b = (it <= it + 1);
	std::cout << "it <= it + 1: " << b << std::endl;
	std::cout << "it[0]: " << it[0] << std::endl;

	std::cout << green << "Testing arithmetic operations on reverse iterator: " << cend << std::endl;
	ft::vector<int>::reverse_iterator itr = vec.rbegin();
	std::cout << "itr value: " << *itr << std::endl;
	itr++;
	std::cout << "itr++ value: " << *itr << std::endl;
	itr--;
	std::cout << "itr-- value: " << *itr << std::endl;
	++itr;
	std::cout << "++itr value: " << *itr << std::endl;
	--itr;
	std::cout << "--itr value: " << *itr << std::endl;
	itr = itr + 5;
	std::cout << "itr = itr + 5: " << *itr << std::endl;
	itr = itr - 2;
	std::cout << "itr = itr - 2: " << *itr << std::endl;
	itr += 3;
	std::cout << "itr += 3: " << *itr << std::endl;
	itr -= 3;
	std::cout << "itr -= 3: " << *itr << std::endl;
	std::cout << "itr[0]: " << itr[0] << std::endl;
}

void const_iterator_test()
{
	std::cout << blue << "***************[ Const iterators test (int) ]***************" << cend << std::endl;

	ft::vector<int> vec;
	for (int i = 0; i < 10; ++i)
	{
		vec.push_back(i);
	}
	std::cout << green << "vector contents, using const iterator: " << cend << std::endl;
	ft::vector<int>::const_iterator cit = vec.begin();
	ft::vector<int>::const_iterator cite = vec.end();
	while (cit != cite)
	{
		std::cout << *cit << std::endl;
		cit++;
	}
	std::cout << green << "Testing iterator comparison: " << cend << std::endl;
	bool b = cit == cite;
	std::cout << "it == ite: " << b << std::endl;
	b = cit == cit;
	std::cout << "it == it: " << b << std::endl;
	b = cit != cite;
	std::cout << "it != ite: " << b << std::endl;
	b = cite != cite;
	std::cout << "ite != ite: " << b << std::endl;
}

void capacity_tests()
{
	std::cout << blue << "***************[ size() test (int) ]***************" << cend << std::endl;
	ft::vector<int> myints;
	std::cout << green << "Empty vector: " << cend << std::endl;
	std::cout << "0. size: " << myints.size() << std::endl;

	for (int i = 0; i < 10; i++)
		myints.push_back(i);
	std::cout << green << "After push_back 10 elements: " << cend << std::endl;
	std::cout << "1. size: " << myints.size() << std::endl;

	myints.insert(myints.end(), 10, 100);
	std::cout << green << "After inserting 10 elements: " << cend << std::endl;
	std::cout << "2. size: " << myints.size() << std::endl;

	myints.pop_back();
	std::cout << green << "After popback(): " << cend << std::endl;
	std::cout << "3. size: " << myints.size() << std::endl
			  << std::endl;

	std::cout << blue << "***************[ max_size() test (int) ]***************" << cend << std::endl;
	std::cout << green << "Taking the same vector: " << cend << std::endl;
	std::cout << "size: " << myints.size() << std::endl;
	std::cout << "max_size: " << myints.max_size() << std::endl
			  << std::endl;

	std::cout << blue << "***************[ resize() test (int) ]***************" << cend << std::endl;
	myints.resize(5);
	std::cout << green << "myints.resize(5): " << cend << std::endl;
	print_int_array(myints);
	std::cout << green << "myints.resize(8, 100): " << cend << std::endl;
	myints.resize(8, 100);
	print_int_array(myints);
	myints.resize(12);
	std::cout << green << "myints.resize(12): " << cend << std::endl;
	print_int_array(myints);
	std::cout << std::endl;

	std::cout << blue << "***************[ reserve() test (int) ]***************" << cend << std::endl;
	ft::vector<int>::size_type sz;
	ft::vector<int>::size_type n_sz;

	ft::vector<int> foo;
	sz = foo.capacity();
	std::cout << green << "making foo grow: " << cend << std::endl;
	for (int i = 0; i < 100; ++i)
	{
		foo.push_back(i);
		if (sz != foo.capacity())
		{
			n_sz = foo.capacity();
		if (n_sz < sz)
			std::cout << "capacity has changed" << n_sz << std::endl;
		}
	}
	ft::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);
	std::cout << green << "making bar grow: " << cend << std::endl;
	for (int i = 0; i < 100; ++i)
	{
		bar.push_back(i);
		if (sz != bar.capacity())
		{
			n_sz = bar.capacity();
			if (n_sz > sz)
				std::cout << "capacity has changed: " << n_sz << std::endl
					  << std::endl;
		}
	}

	std::cout << blue << "***************[ empty() test (char) ]***************" << cend << std::endl;
	ft::vector<char> vec;
	std::cout << "empty vector: " << vec.empty() << std::endl;
	vec.push_back(5);
	std::cout << "vec not empty: " << vec.empty() << std::endl
			  << std::endl;
}

void element_access_test()
{
	std::cout << blue << "***************[ operator[] test (string) ]***************" << cend << std::endl;
	ft::vector<std::string> myvector(10); // 10 zero-initialized elements

	myvector.push_back("have");
	myvector.push_back("a");
	myvector.push_back("good");
	myvector.push_back("day");
	myvector.push_back("!");

	ft::vector<std::string>::size_type sz = myvector.size();
	std::cout << green << "reverse vector using operator[]: " << cend << std::endl;
	for (unsigned i = 0; i < sz / 2; i++)
	{
		std::string temp;
		temp = myvector[sz - 1 - i];
		myvector[sz - 1 - i] = myvector[i];
		myvector[i] = temp;
	}

	std::cout << "myvector contains:";
	for (unsigned i = 0; i < sz; i++)
		std::cout << ' ' << myvector[i];
	std::cout << std::endl
			  << std::endl;

	std::cout << blue << "***************[ at function test (double) ]***************" << cend << std::endl;
	ft::vector<double> dvec;

	dvec.push_back(6.025);
	dvec.push_back(42.0);
	dvec.push_back(6.669096);
	dvec.push_back(9.5);
	dvec.push_back(34.42);

	std::cout << "Initial array contents: " << std::endl;
	print_double_array(dvec);

	std::cout << green << "using at func, at(3): " << cend << std::endl;
	std::cout << dvec.at(3) << std::endl;

	std::cout << blue << "***************[ front() and back() function test (double) ]***************" << cend << std::endl;
	std::cout << "front: " << dvec.front() << " | end: " << dvec.back() << std::endl;

	std::cout << std::endl;
}

void modifiers_test()
{
	std::cout << blue << "***************[ assign() test (int) ]***************" << cend << std::endl;
	ft::vector<int> first;
	ft::vector<int> second;
	ft::vector<int> third;

	std::cout << green << "assign 7 ints with the value of 100 " << cend << std::endl;
	first.assign(7, 100); // 7 ints with a value of 100
	std::cout << "vector contents: " << std::endl;
	print_int_array(first);

	ft::vector<int>::iterator it;
	it = first.begin() + 1;
	std::cout << green << "assign 5 central values of first" << cend << std::endl;
	second.assign(it, first.end() - 1); // the 5 central values of first
	std::cout << "vector contents: " << std::endl;
	print_int_array(second);

	std::cout << green << "creating array of ints {1776, 7, 4} and assigning from it: " << cend << std::endl;
	int myints[] = {1776, 7, 4};
	third.assign(myints, myints + 3); // assigning from array.
	std::cout << "vector contents: " << std::endl;
	print_int_array(third);

	std::cout << "Size of first: " << int(first.size()) << std::endl;
	std::cout << "Size of second: " << int(second.size()) << std::endl;
	std::cout << "Size of third: " << int(third.size()) << std::endl
			  << std::endl;

	std::cout << blue << "***************[ push_back() and pop_back() test (float) ]***************" << cend << std::endl;
	ft::vector<float> vf;
	vf.push_back(1.23f);
	vf.push_back(2.34f);
	vf.push_back(3.45f);
	vf.push_back(4.55f);
	vf.push_back(5.56f);
	std::cout << "vector contents: " << std::endl;
	print_float_array(vf);

	std::cout << green << "calling pop_back() 2 times: " << cend << std::endl;
	vf.pop_back();
	vf.pop_back();

	std::cout << "vector contents: " << std::endl;
	print_float_array(vf);

	std::cout << blue << "***************[ insert test (int) ]***************" << cend << std::endl;
	ft::vector<int> vi;
	for (int i = 0; i < 10; ++i)
		vi.push_back(i);
	std::cout << "vector contents: " << std::endl;
	print_int_array(vi);
	std::cout << green << "insert 1 element at 2nd position with the value of 666 " << cend << std::endl;
	it = vi.begin();
	vi.insert(it + 2, 666);
	std::cout << "vector contents: " << std::endl;
	print_int_array(vi);
	std::cout << "vector size: " << vi.size();
	//std::cout << " | vector capacity: " << vi.capacity() << std::endl;
	std::cout << std::endl;

	std::cout << green << "insert 5 element at 5th position with the value of 55 " << cend << std::endl;

	vi.insert(it + 5, 5, 55);
	std::cout << "vector contents: " << std::endl;
	print_int_array(vi);
	std::cout << "vector size: " << vi.size();
	//std::cout << " | vector capacity: " << vi.capacity() << std::endl;
	std::cout << std::endl;

	std::cout << green << "insert range of elements int arr[] = {501,502,503} at the begin() + 1" << cend << std::endl;
	int myarray[] = {501, 502, 503};
	vi.insert(vi.begin() + 1, myarray, myarray + 3);
	print_int_array(vi);
	std::cout << "vector size: " << vi.size();
	//std::cout << " | vector capacity: " << vi.capacity() << std::endl;
	std::cout << std::endl;

	std::cout << blue << "***************[ erase test (int) ]***************" << cend << std::endl;
	std::cout << green << "erase the 6th element: " << cend << std::endl;
	vi.erase(vi.begin() + 5);
	print_int_array(vi);
	std::cout << "vector size: " << vi.size();
	//std::cout << " | vector capacity: " << vi.capacity() << std::endl;
	std::cout << std::endl;
	std::cout << green << "erase the first 3 elements: " << cend << std::endl;
	vi.erase(vi.begin(), vi.begin() + 3);
	print_int_array(vi);
	std::cout << "vector size: " << vi.size();
	//std::cout << " | vector capacity: " << vi.capacity() << std::endl;
	std::cout << std::endl;

	std::cout << blue << "***************[ swap() test (string) ]***************" << cend << std::endl;
	ft::vector<std::string> vs1;
	ft::vector<std::string> vs2;
	vs1.push_back("chto");
	vs1.push_back("kak");
	vs1.push_back("sunshine");
	vs1.push_back("?");

	vs2.push_back("prosto");
	vs2.push_back("sdelai");
	vs2.push_back("it");

	std::cout << "vector vs1 contents: " << std::endl;
	print_string_array(vs1);
	std::cout << "vector vs2 contents: " << std::endl;
	print_string_array(vs2);
	
	std::cout << green << "after swapping values : " << cend << std::endl;
	
	vs1.swap(vs2);
	
	std::cout << "vector vs1 contents: " << std::endl;
	print_string_array(vs1);
	std::cout << "vector vs2 contents: " << std::endl;
	print_string_array(vs2);

	std::cout << blue << "***************[ clear() test (string) ]***************" << cend << std::endl;
	std::cout << green << "Initial vector contents : " << cend << std::endl;
	print_string_array(vs1);
	std::cout << "vector size: " << vs1.size();
	//std::cout << " | vector capacity: " << vs1.capacity() << std::endl;
	std::cout << std::endl;

	std::cout << green << "vector contents after clear() : " << cend << std::endl;
	vs1.clear();
	print_string_array(vs1);
	std::cout << "vector size: " << vs1.size();
	//std::cout << " | vector capacity: " << vs1.capacity() << std::endl;
	std::cout << std::endl;
}

	void non_member_functions()
{
	std::cout << blue << "***************[ creating 3 vectors to test non-member functions overloads: ]***************" << cend << std::endl;
	ft::vector<int>		v0(6, 42);
	ft::vector<int>		v1(9, 21);
	ft::vector<int>		v2(9, 21);
	//ft::vector<int>		v2(v1);

	std::cout << "1st array contents: " << std::endl;
	print_int_array(v0);
	std::cout << "2nd array contents: " << std::endl;
	print_int_array(v1);
	std::cout << "3rd array contents: " << std::endl;
	print_int_array(v2);

	std::cout << blue << "***************[ operator == ]***************" << cend << std::endl;
	bool i = v0 == v1;
	bool j = v1 == v2;
	std::cout << "v0 == v1 : " << std::boolalpha << i << std::endl;
	std::cout << "v1 == v2 : " << std::boolalpha << j << std::endl;

	std::cout << blue << "***************[ operator != ]***************" << cend << std::endl;
	i = v0 != v1;
	j = v1 != v2;
	std::cout << "v0 != v1 : " << i << std::endl;
	std::cout << "v1 != v2 : " << j << std::endl;

	std::cout << blue << "***************[ operator < ]***************" << cend << std::endl;
	i =  v0 < v1;
	j = v1 < v2;
	std::cout << "v0 < v1 : " << i << std::endl;
	std::cout << "v1 < v2 : " << j << std::endl;

	std::cout << blue << "***************[ operator <= ]***************" << cend << std::endl;
	i = v0 <= v1;
	j = v1 <= v2;
	std::cout << "v0 <= v1 : " << i << std::endl;
	std::cout << "v1 <= v2 : " << j << std::endl;

	std::cout << blue << "***************[ operator > ]***************" << cend << std::endl;
	i = v0 > v1;
	j = v1 > v2;
	std::cout << "v0 > v1 : " << i << std::endl;
	std::cout << "v1 > v2 : " << j << std::endl;

	std::cout << blue << "***************[ operator >= ]***************" << cend << std::endl;
	i = v0 >= v1;
	j = v1 >= v2;
	std::cout << "v0 >= v1 : " << i << std::endl;
	std::cout << "v1 >= v2 : " << j << std::endl;

	std::cout << blue << "***************[ swap function ]***************" << cend << std::endl;

	std::cout << "vector v0 contents before swap: " << std::endl;
	print_int_array(v0);
	std::cout << "vector v1 contents before swap: " << std::endl;
	print_int_array(v1);
	
	std::cout << green << "after swapping values : " << cend << std::endl;
	swap(v0, v1);
	std::cout << "vector v0 contents: " << std::endl;
	print_int_array(v0);
	std::cout << "vector v1 contents: " << std::endl;
	print_int_array(v1);

}

int main()
{
	constructor_test();
	iterator_test();
	const_iterator_test();
	capacity_tests();
	element_access_test();
	modifiers_test();
	non_member_functions();

	return 0;
}