# timeit-cpp
A C++ version of IPython's timeit magic.

## Usage
Measure time for anything "callable" for example a lambda or an struct with operator(). `timeit::timeit` prints results similar to IPython's timeit magic. It automatically guesses number of repeats and iterations.

```c++
      #include <iostream>
      #include <vector>
      #include "timeit.h"
      using namespace std;
      int main(){
        vector<float> A(10000,1.0);
        auto find_sum = [&](){
          float s=0.0;
          for(float x:A)
            s += x;
        };

        timeit::timeit(find_sum);
      }
```
```
      97.5 μs ± 93.3 ns per loop (mean ± std. dev. of 3 runs, 100000 loops each)
```
    
`timeit::timeit` can also take other arguments.
```c++
    long repeat=5, number=100;
    timeit::timeit(find_sum, repeat, number);
```
```
    0.101 ms ± 3.06 μs per loop (mean ± std. dev. of 5 runs, 100 loops each)
```
  
`timeit::repeat` returns a vector of results
```c++
    long repeat=5, number=100;
    vector<double> timings = timeit::repeat(find_sum, repeat, number);
```

`timeit::autorange` returns the number of loops and time taken so that total time >= 1.0.
```c++
    cout << timeit::autorange(find_sum) << endl;
```
```
    20000
```

## Examples

Comparing different algorithms to solve the [Sliding Window Maximum (Maximum of all subarrays of size k)](https://www.geeksforgeeks.org/sliding-window-maximum-maximum-of-all-subarrays-of-size-k/) problem. See complete [source](https://github.com/impopular-guy/timeit-cpp/blob/master/examples/example_sliding_window.cpp).

```c++
    cout<<"Approach 1(deque):\n";
    timeit::timeit(sliding_deque);
    cout<<"Approach 2(cache):\n";
    timeit::timeit(sliding_cache);
    cout<<"Approach 3(naive):\n";
    timeit::timeit(sliding_naive);
```
```
    Approach 1(deque):
    95.6 μs ± 53.5 ns per loop (mean ± std. dev. of 3 runs, 100000 loops each)
    Approach 2(cache):
    7.6 μs ± 5.2 ns per loop (mean ± std. dev. of 3 runs, 1000000 loops each)
    Approach 3(naive):
    0.246 ms ± 2.07 μs per loop (mean ± std. dev. of 7 runs, 10000 loops each)
```

## Future Work
- Compare best and worst timing results and show the same.
