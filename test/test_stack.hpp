#ifndef TEST_STACK_HPP
#define TEST_STACK_HPP

#if !defined(USE_STD)  // if this is not specified
#include "stack.hpp"   // then use self-implemented version
#include "vector.hpp"
#define TEST_NS ft
#else
#include <stack>  // use compiler's version
#include <vector>
#define TEST_NS std
#endif

#include <iostream>

template <typename T>
void print_stack(TEST_NS::stack<T> stk) {
    std::cout << "size: " << stk.size() << std::endl;
    TEST_NS::vector<T> vct;

    while (stk.size() > 0) {
        vct.insert(vct.begin(), stk.top());
        stk.pop();
    }

    typename TEST_NS::vector<T>::const_reverse_iterator first = vct.rbegin();
    typename TEST_NS::vector<T>::const_reverse_iterator last = vct.rend();
    std::cout << std::endl << "Content is:" << std::endl;
    while (first != last) {
        std::cout << " - " << *first++ << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
}

#endif
