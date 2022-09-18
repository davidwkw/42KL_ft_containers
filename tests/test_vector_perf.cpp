#include <ctime>
#include <iostream>
#include <cstdlib>
#include "vector.hpp"
#include <vector>

#define NUMBERS 1000000
#define RUNS 10

double compare_performance(){
	std::srand(time(NULL));
	const int seed = rand();

	std::vector<int> std_vct;
	ft::vector<int> ft_vct;

	clock_t start, end;
	double std_time, ft_time, perf_ratio;

	std::srand(seed);
	start = clock();
	for (int i = 0; i < NUMBERS; ++i){
		std_vct.push_back(rand());
	}
	end = clock();
	std_time = double(end - start) / CLOCKS_PER_SEC;
	
	std::srand(seed);
	start = clock();
	for (int i = 0; i < NUMBERS; ++i){
		ft_vct.push_back(rand());
	}
	end = clock();
	ft_time = double(end - start) / CLOCKS_PER_SEC;
	perf_ratio = ft_time / std_time;
	std::cout << "Performance ratio: " << perf_ratio << std::endl;
	return perf_ratio;
}

int main(void){
	double ratios = 0;
	
	for (int i = 0; i < RUNS; ++i){
		ratios += compare_performance();
	}
	
	std::cout << "Average performance: " << (ratios / RUNS) << std::endl;
	return 0;
}
