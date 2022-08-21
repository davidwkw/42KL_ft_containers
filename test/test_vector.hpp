#ifndef TEST_VECTOR_HPP
#define TEST_VECTOR_HPP

#if !defined(USE_STD)  // if this is not specified
#include "vector.hpp"  // then use self-implemented version
#define TEST_NS ft
#else
#include <vector>  // use compiler's version
#define TEST_NS std
#endif

#include <iostream>

template <typename T>
void print_vector(TEST_NS::vector<T> const &vct) {
    std::cout << "size: " << vct.size() << std::endl;
    typename TEST_NS::vector<T>::const_iterator first = vct.begin();
    typename TEST_NS::vector<T>::const_iterator last = vct.end();
    std::cout << std::endl << "Content is:" << std::endl;
    while (first != last) {
        std::cout << " - " << *first++ << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
}

#endif
