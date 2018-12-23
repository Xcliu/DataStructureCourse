#include "InsertSort.h"
#include "RandomSequence.h"

void test_insert(){
    const int Nd = 12;
    int arr[Nd] = {5,6,7,8,4,3,1,2,2,9,2,110};
    output(arr, Nd);

    DS::insert_sort( arr, arr+Nd );
    output(arr, Nd);
}

void test_insert_bisearch(){
    const int Nd = 12;
    int arr[Nd] = {5,6,7,8,4,3,1,2,2,9,2,110};
    output(arr, Nd);

    DS::insert_sort_bisearch( arr, arr+Nd );
    output(arr, Nd);
}

void test_time(){
    for(unsigned i = 0; i < 100; ++i) {
        int Nd = 1 + i *100;
        int *arr = my_alloc<int>( Nd, __func__ );
        fill_random_int(arr, Nd);

        cout << "rank for " << Nd << endl;


        cout << MYTIME::measureSec( DS::insert_sort<int>, arr, arr+Nd, std::less<int>() ) << endl;


        my_deAllocArr(arr);
    }
}

int main(int argc, char const *argv[])
{
    test_insert();
    //test_time();
    test_insert_bisearch();
    return 0;
}
