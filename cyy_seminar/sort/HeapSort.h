#ifndef HEAPSORT_H_
#define HEAPSORT_H_
#include "Heap.h"
namespace DS {

#define _HEAP_COMPARE_T(T) typename Heap<T>::comp_type

template<typename T>
void heap_sorted(T *b, T *e, T *t, _HEAP_COMPARE_T(T) compare_f = std::less<T>() ){
    Heap<T> heap(b,e,compare_f);
    heap.sorted(t);
}

template<typename T>
void heap_sort(T *b, T *e, _HEAP_COMPARE_T(T) compare_f = std::less<T>() ){
    Heap<T> heap(b,e,compare_f);
    heap.sort();
}


} // DS
#endif
