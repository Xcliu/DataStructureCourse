#include "Merge.h"
#include "MergeSort.h"
#include <random>
using namespace MYSTD;

template<typename T>
void output(T * arr, int sz, ostream & os = cout){
    for(int i = 0; i < sz; ++i) {
        os << arr[i] << '\t';
    }
    os << endl;
}

template<typename T>
void fill_random_int(T * arr, int sz){
    std::default_random_engine e;
    std::uniform_int_distribution<T> u;
    for (int i = 0; i < sz; ++i){
        arr[i] = u(e);
    }
}


void t_merge(){
    const int Nd = 8;
    int arr[Nd] = {1,3,5,7,2,4,6,10};
    DS::_merge( arr, arr+4, arr+4, arr+8, arr );

    for( const auto & val : arr ){
        cout << val << '\t';
    }
    cout << endl;
}

void t_merge_sort(){
    int arr[] = {1,3,5,7,2,4,6,10,0,11,5,101};
    constexpr int sz = sizeof(arr)/sizeof(int);
    DS::merger_sort<int>( arr, arr + sz, std::greater<int>());
    output( arr, sz );
}

void t_merge_sort_time(){
    const int Nd = 10000000;
    int *arr = my_alloc<int>( Nd, __func__ );
    fill_random_int( arr, Nd );
    cout << Nd << " ints" << endl;

    clock_t t1,t2;
    t1 = clock();
    DS::merger_sort<int>( arr, arr + Nd, std::greater<int>() );
    t2 = clock();
    cout << "Time: " << double(t2-t1)/CLOCKS_PER_SEC << endl;

    my_deAllocArr( arr );
}


int main(int argc, char const *argv[])
{
    //t_merge();
    t_merge_sort();
    t_merge_sort_time();
    return 0;
}
