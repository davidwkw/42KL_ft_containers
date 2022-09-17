#include "test_vector.hpp"
#include <stdexcept>
#include <list>

#define TEST_TYPE int

TEST_NAMESPACE::vector<TEST_TYPE> construct_vector(){
	std::list<TEST_TYPE> lst;
	std::list<TEST_TYPE>::iterator lst_it;
	for (int i = 1; i < 42; ++i)
		lst.push_back(i * 42);
	TEST_NAMESPACE::vector<TEST_TYPE> vct(lst.begin(), lst.end());
	return vct;
}

void test_copy_construct(){
	try
	{
		TEST_NAMESPACE::vector<TEST_TYPE> vct1 = construct_vector();
		TEST_NAMESPACE::vector<TEST_TYPE> vct2(vct1);
		
		printContent(vct1);
		printContent(vct2);

		TEST_NAMESPACE::vector<TEST_TYPE> vct3;
		vct3 = vct2;
		printContent(vct3);
	}
	catch(const std::exception& e){
		std::cout << "Copy construct exception" << std::endl;
		std::cerr << e.what() << std::endl;
	}
}

void test_assign(){
	try
	{
		std::list<TEST_TYPE> lst;
		std::list<TEST_TYPE>::iterator lst_it;
		for (int i = 1; i < 5; ++i)
			lst.push_back(i * 20);

		TEST_NAMESPACE::vector<TEST_TYPE> vct1;
		vct1.assign(7,100);
		printContent(vct1);

		TEST_NAMESPACE::vector<TEST_TYPE> vct2;
		vct2.assign(lst.begin(), lst.end());
		printContent(vct2);
	}
	catch(const std::exception& e){
		std::cout << "Assign exception" << std::endl;
		std::cerr << e.what() << std::endl;
	}
}

void test_at(){
	try
	{
		TEST_NAMESPACE::vector<TEST_TYPE> vct(10);
		for (unsigned int i=0; i<vct.size(); i++)
   			vct.at(i)=i;
		printContent(vct);
	}
	catch(const std::exception& e)
	{
		std::cout << "At exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

void test_front_back(){
	try
	{
		TEST_NAMESPACE::vector<TEST_TYPE> vct = construct_vector();

		std::cout << vct.front() << std::endl;
		std::cout << vct.back() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Back exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

void test_insert(){
	try
	{
		TEST_NAMESPACE::vector<TEST_TYPE> vct(3, 100);
		TEST_NAMESPACE::vector<TEST_TYPE>::iterator it;
		vct.insert(vct.begin(), 200);
		printContent(vct);

		TEST_NAMESPACE::vector<TEST_TYPE> vct2(5);
		vct2.insert(vct2.begin(), 5, 300);
		printContent(vct2);

		TEST_NAMESPACE::vector<TEST_TYPE> vct3(5);
		vct3.insert(vct3.begin(), vct.begin(), vct.end());
		printContent(vct3);
	}
	catch(const std::exception& e)
	{
		std::cout << "Insert exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

void test_erase(){
	try
	{
		TEST_NAMESPACE::vector<TEST_TYPE> vct = construct_vector();
		vct.erase(vct.begin());
		printContent(vct);
		vct.erase(vct.begin(), vct.end());
		printContent(vct);
	}
	catch(const std::exception& e)
	{
		std::cout << "Erase exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

void test_clear_empty(){
	try
	{
		TEST_NAMESPACE::vector<TEST_TYPE> vct = construct_vector();
		std::cout << std::boolalpha << vct.empty() << std::endl;
		printContent(vct);
		vct.clear();
		std::cout << std::boolalpha << vct.empty() << std::endl;
		printContent(vct);
	}
	catch(const std::exception& e)
	{
		std::cout << "Erase exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

void test_push_pop(){
	try
	{
		TEST_NAMESPACE::vector<TEST_TYPE> vct(42);
		TEST_NAMESPACE::vector<TEST_TYPE> vct2;

		printContent(vct);

		vct.push_back(42);
		vct2.push_back(420);

		printContent(vct);
		printContent(vct2);

		vct.pop_back();
		vct2.pop_back();

		printContent(vct);
		printContent(vct2);
	}
	catch(const std::exception& e)
	{
		std::cout << "Push pop exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

void test_iterator(){
	try
	{
		TEST_NAMESPACE::vector<TEST_TYPE> vct = construct_vector();
		TEST_NAMESPACE::vector<TEST_TYPE>::iterator it = vct.begin();
		TEST_NAMESPACE::vector<TEST_TYPE>::iterator it2;
		TEST_NAMESPACE::vector<TEST_TYPE>::const_iterator cit = vct.begin();

		std::cout << std::boolalpha << (it == vct.begin()) << std::endl;
		std::cout << std::boolalpha << (it != vct.begin()) << std::endl;
		std::cout << std::boolalpha << (cit == vct.begin()) << std::endl;
		std::cout << std::boolalpha << (cit != vct.begin()) << std::endl;
		std::cout << std::boolalpha << (it == cit) << std::endl;
		std::cout << std::boolalpha << (it != cit) << std::endl;

		std::cout << *it << std::endl;
		std::cout << *cit << std::endl;

		*it = 42;
		std::cout << *it << std::endl;

		it++;
		std::cout << *it << std::endl;
		++it;
		std::cout << *it << std::endl;
		std::cout << *it++ << std::endl;

		it--;
		std::cout << *it << std::endl;
		--it;
		std::cout << *it << std::endl;
		std::cout << *it-- << std::endl;

		it2 = it + 12;
		it2 = 12 + it;
		it2 = it - 12;
		std::cout << (it2 - it) << std::endl;
		std::cout << *(it += 2) << std::endl;
		std::cout << *(it -= 2) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Iterator exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

void test_iterator_relational_operator(){
	try{
		TEST_NAMESPACE::vector<TEST_TYPE> vct = construct_vector();
		TEST_NAMESPACE::vector<TEST_TYPE>::const_iterator it, it2;
		
		it = vct.begin();
		it2 = vct.begin();
		std::cout << "== " << std::boolalpha << (it == it2) << std::endl;
		++it2;
		std::cout << "!= " <<std::boolalpha << (it != it2) << std::endl;
		std::cout << "< " <<std::boolalpha << (it < it2) << std::endl;
		std::cout << "<= " << std::boolalpha << (it <= it2) << std::endl;
		std::cout << "> " <<std::boolalpha << (it > it2) << std::endl;
		std::cout << ">= " << std::boolalpha << (it >= it2) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Iterator relational operator exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

void test_reverse_iterator() {
	try
	{
		TEST_NAMESPACE::vector<TEST_TYPE> vct = construct_vector();
		TEST_NAMESPACE::vector<TEST_TYPE>::reverse_iterator rit(vct.begin());
		TEST_NAMESPACE::vector<TEST_TYPE>::reverse_iterator rit2;
		TEST_NAMESPACE::vector<TEST_TYPE>::const_reverse_iterator crit(vct.begin());

		std::cout << "segfault here?" << std::endl;
		std::cout << std::boolalpha << (*--rit == *(vct.begin())) << std::endl;
		std::cout << std::boolalpha << (*--rit != *(vct.begin())) << std::endl;
		std::cout << std::boolalpha << (*--crit == *(vct.begin())) << std::endl;
		std::cout << std::boolalpha << (*--crit != *(vct.begin())) << std::endl;
		std::cout << std::boolalpha << (rit == crit) << std::endl;
		std::cout << std::boolalpha << (rit != crit) << std::endl;

		std::cout << *rit << std::endl;
		std::cout << *crit << std::endl;

		*rit = 42;
		std::cout << *rit << std::endl;

		rit++;
		++rit;

		rit--;
		std::cout << *rit << std::endl;
		--rit;
		std::cout << *rit << std::endl;
		std::cout << *rit-- << std::endl;

		rit2 = rit + 12;
		rit2 = 12 + rit;
		rit2 = rit - 12;
		std::cout << (rit2 - rit) << std::endl;
		std::cout << *(rit += 2) << std::endl;
		std::cout << *(rit -= 2) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Iterator exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

void test_reverse_iterator_relational_operator(){
	try{
		TEST_NAMESPACE::vector<TEST_TYPE> vct = construct_vector();
		TEST_NAMESPACE::vector<TEST_TYPE>::const_iterator it, it2;
		
		it = vct.begin();
		it2 = vct.begin();
		std::cout << "== " << std::boolalpha << (it == it2) << std::endl;
		++it2;
		std::cout << "!= " <<std::boolalpha << (it != it2) << std::endl;
		std::cout << "< " <<std::boolalpha << (it < it2) << std::endl;
		std::cout << "<= " << std::boolalpha << (it <= it2) << std::endl;
		std::cout << "> " <<std::boolalpha << (it > it2) << std::endl;
		std::cout << ">= " << std::boolalpha << (it >= it2) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Iterator relational operator exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

void test_resize(){
	try
	{
		TEST_NAMESPACE::vector<TEST_TYPE> vct = construct_vector();

		vct.resize(75, 100);
		printContent(vct);
	}
	catch(const std::exception& e)
	{
		std::cout << "Resize exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

void test_reserve(){
	try
	{
		TEST_NAMESPACE::vector<TEST_TYPE> vct;

		vct.reserve(42);
		std::cout << vct.capacity() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Reserve exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

void test_subscript(){
	try
	{
		TEST_NAMESPACE::vector<TEST_TYPE> vct = construct_vector();

		std::cout << vct[2] << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Subscript exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

void test_relational_operators(){
	try
	{
		TEST_NAMESPACE::vector<TEST_TYPE> vct = construct_vector();
		TEST_NAMESPACE::vector<TEST_TYPE> vct2 = construct_vector();

		std::cout << "== " << std::boolalpha << (vct == vct2) << std::endl;
		vct2.insert(vct2.end(), 1);
		std::cout << "!= " << std::boolalpha << (vct != vct2) << std::endl;
		std::cout << "< " << std::boolalpha << (vct < vct2) << std::endl;
		std::cout << "<= " << std::boolalpha << (vct <= vct2) << std::endl;
		std::cout << "> " << std::boolalpha << (vct > vct2) << std::endl;
		std::cout << "> " << std::boolalpha << (vct >= vct2) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Relational operators exception" << std::endl;
		std::cerr << e.what() << '\n';
	}	
}

void test_swap(){
	try
	{
		TEST_NAMESPACE::vector<TEST_TYPE> vct = construct_vector();
		TEST_NAMESPACE::vector<TEST_TYPE> vct2(20, 100);

		printContent(vct);
		printContent(vct2);
		
		vct.swap(vct2);
		printContent(vct);
		printContent(vct2);

		TEST_NAMESPACE::swap(vct, vct2);
		printContent(vct);
		printContent(vct2);
	}
	catch(const std::exception& e)
	{
		std::cout << "Swap exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

int main(void){
	test_copy_construct();
	test_assign();
	test_at();
	test_front_back();
	test_insert();
	test_erase();
	test_clear_empty();
	test_push_pop();
	test_iterator();
	test_iterator_relational_operator();
	test_reverse_iterator();
	test_reverse_iterator_relational_operator();
	test_resize();
	test_reserve();
	test_subscript();
	test_relational_operators();
	test_swap();

	return 0;
}
