#include "../Map.hpp"
#include <map>
#include <memory>
#include <unistd.h>
#include <cmath>
#include <iterator>

#define red "\x1b[31m"
#define green "\x1b[32m"
#define yellow "\x1b[33m"
#define blue "\x1b[34m"
#define cend "\x1b[0m"

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

template <class Key, class T>
void print_map(ft::map<Key, T> &map)
{
	typename ft::map<Key, T>::iterator it = map.begin();
	typename ft::map<Key, T>::iterator ite = map.end();
	while (it != ite)
	{
		std::cout << it->first << " ," << it->second << " | ";
		++it;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

template <class Key, class T>
void print_map_const(ft::map<Key, T> &map)
{
	typename ft::map<Key, T>::const_iterator cit = map.begin();
	typename ft::map<Key, T>::const_iterator cite = map.end();
	while (cit != cite)
	{
		std::cout << cit->first << " ," << cit->second << " | ";
		++cit;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void constructor_test()
{
	std::cout << blue << "***************[ Default constructor test ]***************" << cend << std::endl;

	std::cout << green << "Testing empty map int: " << cend << std::endl;
	ft::map<int, int> mymap;

	std::cout << green << "Testing map <char, int> with some values added: " << cend << std::endl;

	ft::map<char,int> first;

 	first['a']=10;
  	first['b']=30;
  	first['c']=50;
  	first['d']=70;

	std::cout << green << "Map contents: " << cend << std::endl;
	print_map(first);
	std::cout << green << "Testing range constructor: " << cend << std::endl;
  	ft::map<char,int> second (first.begin(),first.end());
	std::cout << green << "Map contents: " << cend << std::endl;
	print_map(second);
	std::cout << green << "Testing copy constructor: " << cend << std::endl;
  	ft::map<char,int> third (second);
	std::cout << green << "Map contents (third): " << cend << std::endl;
	print_map(third);
	third = first;
	std::cout << green << "Testing operator = : " << cend << std::endl;
	std::cout << green << "Map contents (third): " << cend << std::endl;
	print_map(third);
  	ft::map<char,int,classcomp> fourth; // class as Compare
  	bool(*fn_pt)(char,char) = fncomp;
  	ft::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
}

void iterator_test()
{
	std::cout << blue << "***************[ Iterators test (int) ]***************" << cend << std::endl;

	ft::map<int, int> map;
	map[1] = 1;
	map[2] = 2;
	map[3] = 3;
	map[4] = 4;
	map[5] = 5;
	map[6] = 6;
	std::cout << green << "map contents, using iterator: " << cend << std::endl;
	print_map(map);
	std::cout << green << "map contents in reverse, using the reverse iterator: " << cend << std::endl;

	ft::map<int, int>::reverse_iterator rit = map.rbegin();
	ft::map<int, int>::reverse_iterator rite = map.rend();

	while (rit != rite)
	{
		std::cout << rit->first << " " << rit->second << " | ";
		rit++;
	}
	std::cout << std::endl;
	std::cout << green << "Testing arithmetic operations on iterator: " << cend << std::endl;
	ft::map<int, int>::iterator it = map.begin();
	ft::map<int, int>::iterator ite = map.end();
	std::cout << "it value: " << it->first << std::endl;
	it++;
	std::cout << "it++ value: " << it->first << std::endl;
	it--;
	std::cout << "it-- value: " << it->first << std::endl;
	++it;
	std::cout << "++it value: " << it->first << std::endl;
	--it;
	std::cout << "--it value: " << it->first << std::endl;

	std::cout << green << "Testing arithmetic operations on reverse iterator: " << cend << std::endl;
	ft::map<int, int>::reverse_iterator itr = map.rbegin();
	std::cout << "itr value: " << itr->first << std::endl;
	itr++;
	std::cout << "itr++ value: " << itr->first << std::endl;
	itr--;
	std::cout << "itr-- value: " << itr->first << std::endl;
	++itr;
	std::cout << "++itr value: " << itr->first << std::endl;
	--itr;
	std::cout << "--itr value: " << itr->first << std::endl;

	std::cout << green << "Testing iterator comparison: " << cend << std::endl;
	bool b = it == ite;
	std::cout << "it == ite: " << b << std::endl;
	b = it == it;
	std::cout << "it == it: " << b << std::endl;
	b = it != ite;
	std::cout << "it != ite: " << b << std::endl;
	b = ite != ite;
	std::cout << "ite != ite: " << b << std::endl;

	std::cout << green << "Testing reverse iterator comparison: " << cend << std::endl;
	bool r = rit == rite;
	std::cout << "rit == rite: " << r << std::endl;
	r = rit == rit;
	std::cout << "rit == rit: " << r << std::endl;
	r = rit != rite;
	std::cout << "rit != rite: " << r << std::endl;
	r = rite != rite;
	std::cout << "rite != rite: " << r << std::endl;
	std::cout << std::endl;
}

void const_iterator_test()
{
	std::cout << blue << "***************[ Const iterators test (char) ]***************" << cend << std::endl;
	
	ft::map<int, int> map;
	map[1] = 1;
	map[2] = 2;
	map[3] = 3;
	map[4] = 4;
	map[5] = 5;
	map[6] = 6;
	std::cout << green << "map contents, using iterator: " << cend << std::endl;
	print_map_const(map);
	//map.treeprint();

	std::cout << green << "Testing iterator comparison: " << cend << std::endl;
	ft::map<int, int>::const_iterator cit = map.begin();
	ft::map<int, int>::const_iterator cite = map.end();

	bool b = cit == cite;
	std::cout << "cit == cite: " << b << std::endl;
	b = cit == cit;
	std::cout << "it == it: " << b << std::endl;
	b = cit != cite;
	std::cout << "cit != cite: " << b << std::endl;
	b = cite != cite;
	std::cout << "cite != cite: " << b << std::endl;

	std::cout << blue << "***************[ Const reverse iterators test (char) ]***************" << cend << std::endl;

	ft::map<int, int>::const_reverse_iterator crit = map.rbegin();
	ft::map<int, int>::const_reverse_iterator crite = map.rend();

	b = crit == crite;
	std::cout << "crit == crite: " << b << std::endl;
	b = crit == crit;
	std::cout << "crit == crit: " << b << std::endl;
	b = crit != crite;
	std::cout << "crit != crite: " << b << std::endl;
	b = crite != crite;
	std::cout << "crite != crite: " << b << std::endl;
}

void capasity_test()
{
	std::cout << blue << "***************[ Empty test (char, int) ]***************" << cend << std::endl;

	ft::map<char,int> mymap;

  	mymap['a']=10;
  	mymap['b']=20;
  	mymap['c']=30;

  	while (!mymap.empty())
  	{
		std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
		mymap.erase(mymap.begin());
  	}

	std::cout << blue << "***************[ Size test (char, int) ]***************" << cend << std::endl;
	std::cout << "mymap.size() is " << mymap.size() << '\n';
	mymap['d']=340;
	mymap['d']=30;
	mymap['e']=60;
	std::cout << "mymap.size() is " << mymap.size() << '\n';
	mymap['f']=50;
	std::cout << "mymap.size() is " << mymap.size() << '\n';
	mymap.erase('b');
	std::cout << "mymap.size() is " << mymap.size() << '\n';
	
	std::cout << blue << "***************[ Max size test (int, int) ]***************" << cend << std::endl;

	std::cout << mymap.max_size() << std::endl;
	int i;
	ft::map<int,int> mymap1;

  	if (mymap1.max_size()>1000)
 	{
		for (i=0; i<1000; i++) mymap1[i]=0;
		std::cout << "The map contains 1000 elements.\n";
  	}
  	else std::cout << "The map could not hold 1000 elements.\n";

}
	void insert_test()
	{
		ft::map<int, int> mymap;
		ft::map<int, int>::iterator it;
		ft::map<int, int>:: iterator ite;

	
	std::cout << "**************************MY FUNCS********************************" << std::endl;

	mymap[1] = 200;
	mymap[3] = 500;
	mymap.insert(std::pair<int, int>(5, 200));
	mymap.insert(std::pair<int, int>(4, 400));
	std::pair<ft::map<int, int>::iterator, bool> ret;

	ret = mymap.insert(std::pair<int, int>(6, 100));
	std::cout << "return value is (6): " << ret.first->first << '\n';
	std::cout << " with a value of " << ret.first->second << '\n';
	std::cout << "bool value is (1): " << ret.second << '\n';
	mymap.insert(std::pair<int, int>(3, 400));
	mymap.insert(std::pair<int, int>(2, 400));
	mymap.insert(std::pair<int, int>(1, 400));
	mymap.insert(std::pair<int, int>(8, 100));
	std::cout << "return value is (8): " << ret.first->first << '\n';
	std::cout << " with a value of " << ret.first->second << '\n';
	std::cout << "bool value is (1): " << ret.second << '\n';
	ret = mymap.insert(std::pair<int, int>(8, 100));
	std::cout << "return value is (8): " << ret.first->first << '\n';
	std::cout << " with a value of " << ret.first->second << '\n';
	std::cout << "bool value is (0): " << ret.second << '\n';
	ret = mymap.insert(std::pair<int, int>(10, 100));
	std::cout << "return value is (10): " << ret.first->first << '\n';
	std::cout << " with a value of " << ret.first->second << '\n';
	std::cout << "bool value is (1): " << ret.second << '\n';
	ret = mymap.insert(std::pair<int, int>(6, 100));
	std::cout << "return value is (6): " << ret.first->first << '\n';
	std::cout << " with a value of " << ret.first->second << '\n';
	std::cout << "bool value is (0): " << ret.second << '\n';
	mymap.insert(std::pair<int, int>(7, 100));
	ret = mymap.insert(std::pair<int, int>(7, 100));
	std::cout << "return value is (7): " << ret.first->first << '\n';
	std::cout << " with a value of " << ret.first->second << '\n';
	std::cout << "bool value is (0): " << ret.second << '\n';
	mymap.insert(std::pair<int, int>(9, 100));
	it = mymap.begin();
	it++;
	it++;
	it = mymap.insert(it, std::pair<int, int>(17, 89));
	std::cout << "ITER VALUE IS: " << it->first << std::endl;
	ft::map<int, int> anothermap;
	ft::map<int, int> anothermap1;
	anothermap.insert(mymap.begin(), mymap.end());

	anothermap1 = anothermap;

	std::cout << "begin is: " << mymap.begin()->first << std::endl;
	print_map(mymap);
	std::cout << "size is : " << mymap.size() << std::endl;
	it = mymap.begin();
	ite = mymap.end();
	while (it != ite)
	{
		std::cout << "contents of my map: " << it->first << ", " << it->second << std::endl;
		++it;
	}
	ft::map<int, int>::iterator it2;
	ft::map<int, int>::iterator ite2;
	it2 = anothermap.begin();
	ite2 = anothermap.end();
	while (it2 != ite2)
	{
		std::cout << "contents of another map: " << it2->first << ", " << it2->second << std::endl;
		++it2;
	}
	it = anothermap.begin();
	std::cout << "map begin: " << it->first << std::endl;
	std::cout << "IT value is: " << it->first << std::endl;
	anothermap.erase(1); // 1
	std::cout << "________________1_______________" << std::endl;
	std::cout << "IT value is: " << it->first << std::endl;
	print_map(mymap);
	anothermap.erase(2); // 2
		std::cout << "______________2__________________" << std::endl;
	print_map(mymap);
	anothermap.erase(3); //3
			std::cout << "______________3__________________" << std::endl;
	print_map(mymap);
	anothermap.erase(4); //4
			std::cout << "______________4__________________" << std::endl;
	print_map(mymap);
	anothermap.erase(5);//5
			std::cout << "______________5__________________" << std::endl;
	print_map(mymap);
	anothermap.erase(6);//6
			std::cout << "______________6__________________" << std::endl;
	print_map(mymap);
	anothermap.erase(7); //7
			std::cout << "______________7__________________" << std::endl;
	print_map(mymap);
	anothermap.erase(8); //8
			std::cout << "______________8__________________" << std::endl;
	print_map(mymap);
	anothermap.erase(9); //9
			std::cout << "______________9__________________" << std::endl;
	print_map(mymap);
	anothermap.erase(10); //10
			std::cout << "______________10__________________" << std::endl;
	print_map(mymap);
	anothermap.erase(17);
	std::cout << "______________17__________________" << std::endl;

	mymap.insert(std::pair<int, int>(3, 400));
	mymap.insert(std::pair<int, int>(2, 400));
	mymap.insert(std::pair<int, int>(1, 400));
	mymap.insert(std::pair<int, int>(8, 100));
	std::cout << "Contents of mymap: " << std::endl;
	print_map(mymap);
	anothermap.clear();
	std::cout << "mymap size is: " << anothermap.size() << std::endl;
	std::cout << "Inserting new elements : " << std::endl;
	mymap.insert(std::pair<int, int>(3, 400));
	mymap.insert(std::pair<int, int>(2, 400));
	mymap.insert(std::pair<int, int>(1, 400));
	mymap.insert(std::pair<int, int>(8, 100));
	std::cout << "Contents of mymap: " << std::endl;
	anothermap.erase(anothermap.begin(), anothermap.end());
	std::cout << "mymap size is: " << anothermap.size() << std::endl;
}

void erase_range_test()
{
			ft::map<char,int> mymap;
  	ft::map<char,int>::iterator it;
ft::map<char,int>::iterator ite;

  	mymap['a']=50;
  	mymap['b']=100;
  	mymap['c']=150;
  	mymap['d']=200;
	mymap['t']=600;
	mymap['o']=800;
	mymap['l']=100; 
	mymap['i']=500;
	it = mymap.begin();
	ite = mymap.end();

print_map(mymap);
it++;
it++;
ite--;
ite--;
	mymap.erase(it, ite);
	print_map(mymap);


}

void erase_and_clear_func_test()
{
	std::cout << blue << "***************[ Erase func test ]***************" << cend << std::endl;
	
	erase_range_test();

	ft::map<int, int> mymap;
	ft::map<int, int>::iterator it;
	ft::map<int, int>::iterator ite;

	// insert some values:
	mymap[1] = 10;
	mymap[2] = 20;
	mymap[3] = 30;
	mymap[4] = 40;
	mymap[5] = 50;
	mymap[6] = 60;
	mymap[7] = 70;
	mymap[8] = 80;
	mymap[9] = 90;
	mymap[10] = 100;

	std::cout << "SIZE SHOULD BE 10: " << mymap.size() << std::endl;


	it = mymap.begin();
	it++;
	std::cout << "it value is: " << it->first << std::endl;

	print_map(mymap);
	mymap.erase(3); // erasing by key
	std::cout << "__________after erase 3_________________________" << std::endl << std::endl;
	print_map(mymap);

	std::cout << "__________after erase 2_________________________" << std::endl << std::endl;
	mymap.erase(it); // erasing by iterator
	print_map(mymap);
	mymap.erase(4); // erasing by key
	std::cout << "__________after erase 4________________________" << std::endl << std::endl;
	print_map(mymap);
	std::cout << "__________after erase 6____________" << std::endl << std::endl;
	mymap.erase(6); // erasing by key
	print_map(mymap);
}

void 	swap_func_test()
{
	std::cout << blue << "***************[ swap func test]***************" << cend << std::endl;	
	ft::map<char,int> foo,bar;

  foo['x']=100;
  foo['y']=200;

  bar['a']=11;
  bar['b']=22;
  bar['c']=33;

  foo.swap(bar);

  std::cout << "foo contains:\n";
  for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
	std::cout << it->first << " => " << it->second << '\n';

  std::cout << "bar contains:\n";
  for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
	std::cout << it->first << " => " << it->second << '\n';
}

void modifiers_test()
{
	insert_test();
	erase_and_clear_func_test();
	swap_func_test();
}
void value_comparison_test()
{
		std::cout << blue << "***************[ value_comp func test]***************" << cend << std::endl;
	 ft::map<char,int> mymap;

  mymap['x']=1001;
  mymap['y']=2002;
  mymap['z']=3003;

  std::cout << "mymap contains:\n";

  std::pair<char,int> highest = *mymap.rbegin();          // last element

  ft::map<char,int>::iterator it = mymap.begin();
  do {
	std::cout << it->first << " => " << it->second << '\n';
  } while ( mymap.value_comp()(*it++, highest) );
}

void key_comparison_test()
{
	std::cout << blue << "***************[ key_comp func test]***************" << cend << std::endl;

	ft::map<char,int> mymap;

  ft::map<char,int>::key_compare mycomp = mymap.key_comp();

  mymap['a']=100;
  mymap['b']=200;
  mymap['c']=300;

  std::cout << "mymap contains:\n";

  char highest = mymap.rbegin()->first;     // key value of last element

  ft::map<char,int>::iterator it = mymap.begin();
  do {
	std::cout << it->first << " => " << it->second << '\n';
  } while ( mycomp((*it++).first, highest) );

  std::cout << '\n';

}
void observers_test()
{
	key_comparison_test();
	value_comparison_test();
}

void find_func()
{
	std::cout << blue << "***************[ FIND && REVERSE_ITERATOR func test FT]***************" << cend << std::endl;	
	ft::map<char,int> mymap;
  	ft::map<char,int>::iterator it;
	ft::map<char, int>::reverse_iterator rit;
	ft::map<char, int>:: reverse_iterator rite;

  	mymap['a']=50;
  	mymap['b']=100;
  	mymap['c']=150;
  	mymap['d']=200;
	mymap['t']=600;
	mymap['o']=800;
	mymap['i']=500;
	mymap['l']=100; 


  	it = mymap.find('b');
  	if (it != mymap.end())
		mymap.erase (it);

  // print content:
  std::cout << "elements in mymap:" << '\n';
  std::cout << "a => " << mymap.find('a')->second << '\n';
  std::cout << "c => " << mymap.find('c')->second << '\n';
  std::cout << "d => " << mymap.find('d')->second << '\n';

  std::cout << "reverse iterator test: " << std::endl;
  rit = mymap.rbegin();
  rite = mymap.rend();
  rite--;
  std::cout << rite->first << std::endl;
 
  
  rit++;
  std::cout << "reverse iterator: " << std::endl;
  std::cout << rite->first << std::endl;
  std::cout << rit->first << std::endl;
  while (rit != rite)
	{
		std::cout << rit->first << " | ";
		rit++;
	}
}

void count_func()
{
	std::cout << blue << "***************[ count func test]***************" << cend << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	  ft::map<char,int> mymap;
  char c;

  mymap ['a']=101;
  mymap ['c']=202;
  mymap ['f']=303;

  for (c='a'; c<'h'; c++)
  {
	std::cout << c;
	if (mymap.count(c)>0)
	  std::cout << " is an element of mymap.\n";
	else 
	  std::cout << " is not an element of mymap.\n";
  }
}

void lower_bound_test()
{
	ft::map<char,int> mymap;
  	ft::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;

  itlow=mymap.lower_bound ('b');  // itlow points to b
  itup=mymap.upper_bound ('d');   // itup points to e (not d!)

  	std::cout << "UPPER: itlow val: " << itlow->first << std::endl;
	std::cout << "UPPER: itupval: " << itup->first << std::endl;

}

void upper_bound_test()
{
	ft::map<char,int> mymap;
  	ft::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;

  itlow=mymap.lower_bound ('b');  // itlow points to b
  itup=mymap.upper_bound ('d');   // itup points to e (not d!)
}

void equal_range()
{
	 ft::map<char,int> mymap;

  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;

  std::pair< ft::map <char,int>::iterator, ft::map <char,int>::iterator> ret;
  ret = mymap.equal_range('b');

  std::cout << "lower bound points to: ";
  std::cout << ret.first->first << " => " << ret.first->second << '\n';

  std::cout << "upper bound points to: ";
  std::cout << ret.second->first << " => " << ret.second->second << '\n';
}

void operations_test()
{
	find_func();
	count_func();
	lower_bound_test();
	upper_bound_test();
	equal_range();
}




int main()
{
	constructor_test();
	iterator_test();
	const_iterator_test();
	capasity_test();
	modifiers_test();
	observers_test();
	operations_test();
	//sleep(50);


	return 0;
}