#include <ctime>
#include <iostream>
#include <cstdlib>
#include "map.hpp"
#include <map>

#define NUMBERS 1000000
#define RUNS 10
#define T1 int
#define T2 int
typedef std::map<T1, T2>::value_type STD_T3;
typedef ft::map<T1, T2>::value_type FT_T3;

double compare_performance(){
	std::srand(time(NULL));
	const int seed = rand();

	std::map<T1, T2> std_mp;
	ft::map<T1, T2> ft_mp;

	clock_t start, end;
	double std_time, ft_time, perf_ratio;

	std::srand(seed);
	start = clock();
	for (int i = 0; i < NUMBERS; ++i){
		std_mp.insert(STD_T3(rand(), rand()));
	}
	end = clock();
	std_time = double(end - start) / CLOCKS_PER_SEC;
	
	std::srand(seed);
	start = clock();
	for (int i = 0; i < NUMBERS; ++i){
		ft_mp.insert(FT_T3(rand(), rand()));
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
