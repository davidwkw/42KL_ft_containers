
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>

#include "stack.hpp"

#define COUNT 1048576
#define RUNS 10

double compare() {
    std::srand(time(NULL));

    const int seed = rand();  // initialise a seed
    ft::stack<int> ft_stk;
    std::stack<int> std_stk;
    clock_t begin, end;

    // insert COUNT number of items into ft stack
    std::srand(seed);
    begin = clock();
    for (int i = 0; i < COUNT; i++) {
        ft_stk.push(rand());
    }
    end = clock();
    double ft_time = double(end - begin) / CLOCKS_PER_SEC;

    // insert COUNT number of items into standard stack
    std::srand(seed);  // set seed to insert same values as before
    begin = clock();
    for (int i = 0; i < COUNT; i++) {
        std_stk.push(rand());
    }
    end = clock();
    double std_time = double(end - begin) / CLOCKS_PER_SEC;

    // calculate relative performance
    double ratio = ft_time / std_time;
    std::cout << "Performance ratio = " << ratio << std::endl;
    return ratio;
}

int main() {
    double d = 0;

    for (int i = 0; i < RUNS; ++i) {
        d += compare();
    }
    std::cout << "Average Performance ratio = " << (d / RUNS) << std::endl;
    return 0;
}
