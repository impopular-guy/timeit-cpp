#include <iostream>
#include <vector>
#include <cstdlib>
#include "timeit.h"

using namespace std;

int main(){
	int N=100000;

	vector<int> arr;
	auto pb = [&](){
		arr.clear();
		for(int i=0; i<N; i++)
			arr.push_back(rand()%1000);
	};

	auto eb = [&](){
		arr.clear();
		for(int i=0; i<N; i++)
			arr.emplace_back(rand()%1000);
	};

	cout<< "Using push_back\n";
	timeit::timeit(pb);
	cout<< "Using emplace_back\n";
	timeit::timeit(eb);

	return 0;
}