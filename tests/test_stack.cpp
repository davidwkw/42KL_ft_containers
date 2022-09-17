#include "test_stack.hpp"

#define TEST_TYPE int

TEST_NAMESPACE::stack<TEST_TYPE> construct_stack(){
	TEST_NAMESPACE::vector<TEST_TYPE> vct;
	TEST_NAMESPACE::vector<TEST_TYPE>::iterator vct_it;
	for (int i = 0; i < 42; ++i)
		vct.push_back(i);
	return TEST_NAMESPACE::stack<TEST_TYPE>(vct);
}

void test_copy_construct(){
	try
	{
		TEST_NAMESPACE::stack<TEST_TYPE> stck1 = construct_stack();
		TEST_NAMESPACE::stack<TEST_TYPE> stck2(stck1);
		
		printContent(stck1);
		printContent(stck2);

		TEST_NAMESPACE::stack<TEST_TYPE> stck3;
		stck3 = stck2;
		printContent(stck3);
	}
	catch(const std::exception& e){
		std::cout << "Copy construct exception" << std::endl;
		std::cerr << e.what() << std::endl;
	}
}

void test_empty(){
	try
	{
		TEST_NAMESPACE::stack<TEST_TYPE> stck = construct_stack();
		std::cout << std::boolalpha << stck.empty() << std::endl;
		printContent(stck);
		while (stck.size() != 0) {
			stck.pop();
		}
		std::cout << std::boolalpha << stck.empty() << std::endl;
		printContent(stck);
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
		TEST_NAMESPACE::stack<TEST_TYPE> stck;

		printContent(stck);
		stck.push(42);
		stck.push(500);
		stck.pop();
		printContent(stck);
		stck.pop();
		printContent(stck);
	}
	catch(const std::exception& e)
	{
		std::cout << "Push pop exception" << std::endl;
		std::cerr << e.what() << '\n';
	}
}

int main(void){

	test_copy_construct();
	test_empty();
	test_push_pop();
	return 0;
}
