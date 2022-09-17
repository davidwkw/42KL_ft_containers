#ifndef TEST_STACK_HPP
#define TEST_STACK_HPP

#include <list>
#include <iostream>
#if !defined(STD) 
#include "stack.hpp"
#define TEST_NAMESPACE ft
#else
#include <stack>
#define TEST_NAMESPACE std
#endif

template <typename T>
void printContent(TEST_NAMESPACE::stack<T> stck){

	std::cout << "Stack size: " << stck.size() << std::endl;
	std::cout << "Stack content: " << std::endl;
	while (stck.size() != 0) {
		std::cout << stck.top() << std::endl;
		stck.pop();
	}
	std::cout << "=============================="<< std::endl;
}

#endif
