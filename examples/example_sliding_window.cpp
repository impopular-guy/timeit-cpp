#include <iostream>
#include <algorithm>
#include <deque>
#include <cstdlib>
#include <vector>
#include "timeit.h"
using namespace std;

int main(){

    int N = 1000, x = 100; // x is the window size
    int A[N];
    for(int i=0; i<N; i++)
        A[i] = rand()%1000;

    deque<int> Qi;
    // sliding window max using deque
    auto sliding_deque = [&](){
        Qi.clear();
        int i; 
        for (i = 0; i < x; ++i) { 
            while ((!Qi.empty()) && A[i] >= A[Qi.back()]) 
                Qi.pop_back(); 
            Qi.push_back(i); 
        } 
        //cout<< A[Qi.front()] <<" ";
        for (; i < N; ++i) { 
            while ((!Qi.empty()) && Qi.front() <= i - x) 
                Qi.pop_front(); // Remove from front of queue 
            while ((!Qi.empty()) && A[i] >= A[Qi.back()]) 
                Qi.pop_back(); 
      
            Qi.push_back(i);
            //cout<< A[Qi.front()] <<" ";
        }
    };
    
    // using O(1) space, worst case O(n*x)
    auto sliding_cache = [&](){
        int rmax = A[0], count=0;
        for(int i=1; i<x; i++)
            if(A[i] > rmax){
                rmax = A[i];
                count=1;
            }else if(A[i] == rmax)
                count++;
        //cout<< rmax <<" ";
        for(int i=x; i<N; i++){
            if(A[i-x]==rmax && count>0)
                count--;
            if(A[i] > rmax){
                rmax = A[i]; count=1;
            }else if(A[i]==rmax)
                count++;

            if(count == 0){
                rmax = *max_element(A+(i-x+1), A+i);
                count=1;
            }
            //cout<< rmax <<" "; 
        }
    };

    auto sliding_naive = [&](){
        int nmax;  
        for (int i=0; i<=N-x; i++){  
            nmax = A[i];
            for (int j=1; j<x; j++){  
                if (A[i + j] > nmax)  
                    nmax = A[i + j];  
            }  
            // cout << nmax << " ";  
        }
    };

    cout<<"Approach 1(deque):\n";
    timeit::timeit(sliding_deque);
    cout<<"Approach 2(cache):\n";
    timeit::timeit(sliding_cache);
    cout<<"Approach 3(naive):\n";
    timeit::timeit(sliding_naive);
    cout<< endl;
    return 0;
} 