#include "QuickSort.h"
#include <random>
using namespace MYSTD;

template<typename T>
void fill_random_int(T * arr, int sz){
    std::default_random_engine e;
    std::uniform_int_distribution<T> u;
    for (int i = 0; i < sz; ++i){
        arr[i] = u(e);
    }
}
template<typename T>
void output(T * arr, int sz, ostream & os = cout){
    for(int i = 0; i < sz; ++i) {
        os << arr[i] << '\t';
    }
    os << endl;
}
