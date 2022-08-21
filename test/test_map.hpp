#ifndef TEST_MAP_HPP
#define TEST_MAP_HPP

#if !defined(USE_STD)  // if this is not specified
#include "map.hpp"     // then use self-implemented version
#define TEST_NS ft
#else
#include <map>  // use compiler's version
#define TEST_NS std
#endif

#include <iostream>

template <class Key, class T>
void print_map(TEST_NS::map<Key, T> const &vct) {
    std::cout << "size: " << vct.size() << std::endl;
    typename TEST_NS::map<Key, T>::const_iterator first = vct.begin();
    typename TEST_NS::map<Key, T>::const_iterator last = vct.end();
    std::cout << std::endl << "Content is:" << std::endl;
    while (first != last) {
        std::cout << " - " << first->first << " : " << first->second
                  << std::endl;
        ++first;
    }
    std::cout << "----------------------------------------" << std::endl;
}

#endif
