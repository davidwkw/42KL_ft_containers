
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>

#include "map.hpp"

#define COUNT 131072
#define RUNS 10

double compare() {
    std::srand(time(NULL));

    const int seed = rand();  // initialise a seed
    ft::map<int, int> ft_map;
    std::map<int, int> std_map;
    clock_t begin, end;

    // insert COUNT number of items into ft map
    std::srand(seed);
    begin = clock();
    for (int i = 0; i < COUNT; i++) {
        ft_map.insert(ft::make_pair(rand(), rand()));
    }
    end = clock();
    double ft_time = double(end - begin) / CLOCKS_PER_SEC;

    // insert COUNT number of items into standard map
    std::srand(seed);  // set seed to insert same values as before
    begin = clock();
    for (int i = 0; i < COUNT; i++) {
        std_map.insert(std::make_pair(rand(), rand()));
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
