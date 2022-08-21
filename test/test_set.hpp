#ifndef TEST_SET_HPP
#define TEST_SET_HPP

#if !defined(USE_STD)  // if this is not specified
#include "set.hpp"     // then use self-implemented version
#define TEST_NS ft
#else
#include <set>  // use compiler's version
#define TEST_NS std
#endif

#include <iostream>

template <class T>
void print_set(TEST_NS::set<T> const &st) {
    std::cout << "size: " << st.size() << std::endl;
    typename TEST_NS::set<T>::const_iterator first = st.begin();
    typename TEST_NS::set<T>::const_iterator last = st.end();
    std::cout << std::endl << "Content is:" << std::endl;
    while (first != last) {
        std::cout << " - " << *first++ << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
}

#endif
