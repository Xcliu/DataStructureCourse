#include "Heap.h"
#include "HeapSort.h"
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

int compare_f( const void * a, const void *b ){
    if( *(int *)a < *(int *)b ) return -1;
    else if( *(int *)a == *(int *)b ) return 0;
    else return 1;
}

void make_heap();
void sort_time();


int main(int argc, char const *argv[])
{
    make_heap();
    sort_time();
    return 0;
}


void make_heap(){
    int p[] = {5,3,1,2,4,8,6,9,1,3,1000,99};
    constexpr int Nd = sizeof(p)/sizeof(int);

    //std::sort(p,p+Nd);
    //std::qsort( p, Nd, sizeof(int), compare_f );
    DS::heap_sort(p, p+Nd);
    output(p, Nd);
}


void sort_time(){
    const int Nd = 10000000;
    int *arr = my_alloc<int>( Nd, __func__ );
    fill_random_int( arr, Nd );
    cout << Nd << " ints" << endl;

    clock_t t1,t2;
    t1 = clock();
    //std::qsort( arr, Nd, sizeof(int), compare_f );
    //std::sort( arr, arr+Nd );
    DS::heap_sort<int>( arr, arr + Nd);
    t2 = clock();
    cout << "Time: " << double(t2-t1)/CLOCKS_PER_SEC << endl;


    my_deAllocArr( arr );
}

