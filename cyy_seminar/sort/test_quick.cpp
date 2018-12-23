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

void check_quick(){
    int Nd = 10;
    int *data = my_alloc<int>(Nd, __func__);

    fill_random_int(data, Nd);
    cout << MYTIME::measureSec( DS::quick_sort<int>, data, data+Nd, std::less<int>() ) << endl;
    output(data, Nd);

    fill_random_int(data, Nd);
    cout << MYTIME::measureSec( DS::quick_sort<int>, data, data+Nd, std::less<int>()) << endl;
    output(data, Nd);

    my_deAllocArr( data );
}


void test_quick(){
    int Nd = 10000000;
    int *data = my_alloc<int>(Nd, __func__);

    fill_random_int(data, Nd);
    cout << MYTIME::measureSec( DS::quick_sort<int>, data, data+Nd, std::less<int>() ) << endl;

    fill_random_int(data, Nd);
    cout << MYTIME::measureSec( DS::quick_sort<int>, data, data+Nd, std::less<int>()) << endl;


    my_deAllocArr( data );
}




int main(int argc, char const *argv[])
{
    check_quick();
    test_quick();
    return 0;
}
