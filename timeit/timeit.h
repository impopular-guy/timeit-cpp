#pragma once
#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
typedef long long ll;

namespace timeit{
	using namespace std;
	using namespace chrono;

	string format_time(double t, int precision){
		ostringstream out;
		out << setprecision(precision);

		if(t>=60.0){
			int parts[] = {60*60*24, 60*60, 60, 1};
			char suffix[4][4] = {"d", "h", "min", "s"};
			double tmp = t;
			for(int i=0; i<4; i++){
				int value = int(tmp/parts[i]);
				if(value>0){
					tmp = fmod(tmp, parts[i]);
					out << value << suffix[i] <<" "; 
				}
				if(tmp<1)
					break;
			}
			return out.str();
		}

		char units[4][8] = {"s", "ms", "\u03BCs", "ns"};
		double scaling[] = {1, 1e3, 1e6, 1e9};
		int order = min(-int((floor(log10(t))-1)/3), 3);
		if(t<=0.0) order=3;
		if(order<0) order=0;
		if(order>3) order=3;
		
		out	<< t*scaling[order] <<" "<< units[order];
		return out.str();
	}

	template<class T>
	bool check(T code){
		bool tmp = false;
		try{
			code();
			tmp = true;
		}catch(const exception &exc){
			cout << exc.what() <<endl;
		}
		return tmp;
	}

	template<class T>
	double inner(T code, ll number){
		ll i;
		auto t0 = high_resolution_clock::now();
		for(i=0; i<number; i++)
			code();
		auto t1 = high_resolution_clock::now();
		time_t t = duration_cast<nanoseconds>(t1-t0).count();
		return double(t)/1e9;
	}

	template<class T>
	vector<double> repeat(T code, long runs, ll number){
		vector<double> all_runs(runs,0);
		for(ll i=0; i<runs; i++){
			all_runs[i] = inner(code, number);
		}
		return all_runs;
	}

	template<class T>
	ll autorange(T code){
		ll i=1, number;
		int jarr[] = {1,2,5};
		while(true){
			for(int j:jarr){
				number = i*j;
				time_t time_taken = inner(code, number);
				if(time_taken >= 1)
					return number;
			}
			i *= 10;
		}
	}

	template<class T>
	void timeit(T code, long runs=0, ll number=0, int precision=3){
		if(!check(code)){
			cout<< "Error: Faulty code. Couldn\'t compute time.\n";
			return;
		}
		time_t time_number;
		if(number<=0){
			number = 1;
			for(int index=0; index<15; index++){
				time_number = inner(code, number);
				if(time_number >= 1)
					break;
				number *= 10;
			}
		}
		else
			time_number =inner(code, number);

		if(runs<=0){
			runs = 7;
			if(time_number > 3) runs = 5;
			if(time_number > 6) runs = 3;
			if(time_number > 10) runs = 1;
		}

		vector<double> all_runs;
		if(runs==1)
			all_runs.push_back(time_number);
		else
			all_runs = repeat(code, runs, number);

		double mean=0, sd = 0;
		for(double&x: all_runs){
			x /= number;
			mean += x;
			sd += x*x;
		}
		mean /= runs;
		sd = sqrt(sd/runs - mean*mean);

		char runs_plural = (runs>1)?'s':'\0';
		char number_plural = (number>1)?'s':'\0';
		cout<< format_time(mean, precision)
			<< " \u00B1 "
			<< format_time(sd, precision)
			<< " per loop (mean \u00B1 std. dev. of " << runs
			<< " run" << runs_plural << ", " << number << " loop"
			<< number_plural << " each)";
	}
}
