#ifndef MERGESORT_H_
#define MERGESORT_H_
#include "Merge.h"
namespace DS {


template<typename T>
void merger_sort(T *b, T *e, _MERGE_COMPARE_T(T) compare_f = std::less<T>()){
    if( e - b <= 1 ){ return; }     // # elements <= 1; Needn't sort

    T * memAvail = my_alloc<T>(e-b, __func__);
    for(std::size_t k = 1, sz = e-b; k < sz; k*=2 ) {
        T *iter_end = b + (sz-sz%(2*k));
        T *p1 = b, *p2 = p1 + k;
        while( p1 != iter_end ){
            p2 = p1 + k;
            _merge_memAvailable( p1, p2, p2, p2+k, p1, memAvail, compare_f );
            p1 = p2+k;
            p2 = p1+k;
        }
        if( e - p1 > std::ptrdiff_t(k) ){ _merge_memAvailable( p1, p2, p2, e, p1, memAvail, compare_f ); }
    }
    my_deAllocArr(memAvail);
}










} // DS
#endif
