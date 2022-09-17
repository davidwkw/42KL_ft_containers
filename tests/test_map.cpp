#include "test_map.hpp"

#define T1 int
#define T2 int
typedef TEST_NAMESPACE::map<T1, T2>::value_type T3;
typedef TEST_NAMESPACE::map<T1, T2>::iterator ft_iterator;
typedef TEST_NAMESPACE::map<T1, T2>::const_iterator ft_const_iterator;

TEST_NAMESPACE::map<T1,T2> construct_map(){
	std::list<T3> lst;
	std::list<T3>::iterator lst_it;
	for (int i = 1; i < 42; ++i)
		lst.push_back(T3(i, i+5));
	TEST_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	return mp;
}

void test_copy_construct(){
	try
	{
		TEST_NAMESPACE::map<T1, T2> mp = construct_map();
		TEST_NAMESPACE::map<T1, T2> mp2(mp);

		printContent(mp);
		printContent(mp2);

		TEST_NAMESPACE::map<T1, T2> mp3;
		mp3 = mp2;
		printContent(mp3);
	}
	catch(const std::exception& e){
		std::cout << "Copy construct exception" << std::endl;
		std::cerr << e.what() << std::endl;
	}
}

void test_clear_empty(){
	try
	{
		TEST_NAMESPACE::map<T1,T2> mp = construct_map();
		std::cout << std::boolalpha << mp.empty() << std::endl;
		printContent(mp);
		mp.clear();
		std::cout << std::boolalpha << mp.empty() << std::endl;
		printContent(mp);
	}
	catch(const std::exception& e)
	{
		std::cout << "Erase exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

void test_insert(){
	try
	{
		TEST_NAMESPACE::map<T1,T2> mp;
		TEST_NAMESPACE::pair<TEST_NAMESPACE::map<T1,T2>::iterator, bool> ret;
		TEST_NAMESPACE::map<T1,T2>::iterator it;

		ret = mp.insert(T3(0, 42));
		printContent(mp);
		std::cout << "Key: " << ret.first->first << " | Unique: " << std::boolalpha << ret.second << std::endl;
		ret = mp.insert(T3(0, 42));
		printContent(mp);
		std::cout << "Key: " << ret.first->first << " | Unique: " << std::boolalpha << ret.second << std::endl;

		it = mp.insert(mp.begin(), T3(43, 42));
		printContent(mp);
		std::cout << "Key: " << it->first << " | Unique: " << std::boolalpha << it->second << std::endl;

		it = mp.insert(mp.begin(), T3(43, 42));
		printContent(mp);
		std::cout << "Key: " << it->first << " | Unique: " << std::boolalpha << it->second << std::endl;

		TEST_NAMESPACE::map<T1,T2> mp2;
		mp2.insert(mp.begin(), mp.end());
		printContent(mp2);
	}
	catch(const std::exception& e)
	{
		std::cout << "Insert exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

void test_subscript(){
	try
	{
		TEST_NAMESPACE::map<T1, T2> mp = construct_map();
		
		printContent(mp);
		int &pr = mp[2];
		std::cout << pr << std::endl;
		pr = 50;
		printContent(mp);
	}
	catch(const std::exception& e)
	{
		std::cout << "Subscript exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

void test_swap(){
	try
	{
		TEST_NAMESPACE::map<T1, T2> mp = construct_map();
		TEST_NAMESPACE::map<T1, T2> mp2;
		mp2.insert(T3(2,4));

		printContent(mp);
		printContent(mp2);
		
		mp.swap(mp2);
		printContent(mp);
		printContent(mp2);

		TEST_NAMESPACE::swap(mp, mp2);
		printContent(mp);
		printContent(mp2);
	}
	catch(const std::exception& e)
	{
		std::cout << "Swap exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

void test_find(){
	try
	{
		TEST_NAMESPACE::map<T1, T2> mp = construct_map();
		TEST_NAMESPACE::map<T1, T2>::iterator it;
		TEST_NAMESPACE::map<T1, T2>::iterator cit;

		printContent(mp);
		it = mp.find(2);
		std::cout << it->first <<std::endl;

		cit = mp.find(3);
		std::cout << cit->first <<std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Find exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

void test_count(){
	try
	{
		TEST_NAMESPACE::map<T1, T2> mp = construct_map();
		TEST_NAMESPACE::map<T1, T2>::size_type num;

		printContent(mp);
		num = mp.count(1);
		std::cout << num << std::endl;
		num = mp.count(0);
		std::cout << num << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Count exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

int main(void){
	test_copy_construct();
	test_clear_empty();
	test_insert();
	test_clear_empty();
	test_subscript();
	test_swap();
	test_find();
	test_count();

	return 0;
}
