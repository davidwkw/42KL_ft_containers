#ifndef TEST_VECTOR_HPP
#define TEST_VECTOR_HPP

#include <iostream>
#if !defined(STD) 
#include "vector.hpp"
#define TEST_NAMESPACE ft
#else
#include <vector>
#define TEST_NAMESPACE std
#endif

template <typename T>
void printContent(const TEST_NAMESPACE::vector<T> &vct){
	typedef typename TEST_NAMESPACE::vector<T>::size_type size_type;
	typedef typename TEST_NAMESPACE::vector<T>::const_iterator const_iterator;

	const_iterator it = vct.begin();
	const_iterator ite = vct.end();
	const size_type size = vct.size();
	const size_type capacity = vct.capacity();

	std::cout << "Vector size: " << size << std::endl;
	std::cout << "Vector capacity: " << capacity << std::endl;
	std::cout << "Vector content: " << std::endl;
	while (it != ite){
		std::cout << *it << std::endl;
		++it;
	}
	std::cout << "=============================="<< std::endl;
}

#endif
