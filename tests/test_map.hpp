#ifndef TEST_MAP_HPP
#define TEST_MAP_HPP

#include <iostream>
#include <list>
#if !defined(STD) 
#include "map.hpp"
#define TEST_NAMESPACE ft
#else
#include <map>
#define TEST_NAMESPACE std
#endif

template <typename T, typename U>
void printContent(const TEST_NAMESPACE::map<T, U> &mp){
	typedef typename TEST_NAMESPACE::map<T, U>::size_type size_type;
	typedef typename TEST_NAMESPACE::map<T, U>::const_iterator const_iterator;

	const_iterator it = mp.begin();
	const_iterator ite = mp.end();
	const size_type size = mp.size();

	std::cout << "Map size: " << size << std::endl;
	std::cout << "Map content: " << std::endl;
	while (it != ite){
		std::cout << "Key: " << it->first << " | Value : " << it->second << std::endl;
		++it;
	}
	std::cout << "=============================="<< std::endl;
}

#endif
