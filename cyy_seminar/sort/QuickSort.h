#ifndef QUICKSORT_H_
#define QUICKSORT_H_
#include "mystd.h"
#include "SeqStack.h"


#define _QUICKSORT_COMPARE_T(T) std::function< bool(const T &, const T &) >
namespace DS {

using namespace MYSTD;
namespace _quick_sort_helper {
template<typename T>
T * _partition( T *beg, T *tail, _QUICKSORT_COMPARE_T(T) compare_f = std::less<T>() ){
    T *last = tail - 1;
    T *q = beg;
    while( beg < last ){
        if( compare_f( *beg, *last ) ){
            swap( *beg, *q++ );
        }
        ++beg;
    }
    swap( *last, *q );
    return q;
}
template<typename T>
void _quick_sort( T *beg, T *tail, _QUICKSORT_COMPARE_T(T) compare_f = std::less<T>() ){
    if( tail - beg > 1 ){
        auto q = _partition( beg, tail, compare_f );
        _quick_sort( beg, q, compare_f );
        _quick_sort( q + 1, tail, compare_f );
    }
}

template<typename T>
void _quick_sort_stk( T *beg, T *tail, _QUICKSORT_COMPARE_T(T) compare_f = std::less<T>() ){
    SeqStack<T*> stk_b, stk_e;
    stk_b.Push( beg ); stk_e.Push(tail);
    T *b,*e,*q;
    while( stk_b.Pop(b) ){
        stk_e.Pop_noCheck(e);
        if( e - b > 1 ){
            q = _partition(b,e,compare_f);
            if( q - b > 1 ){ stk_b.Push(b); stk_e.Push(q); }
            if( e - q > 2 ){ stk_b.Push(q+1); stk_e.Push(e); }
        }
    }
}

} // _quick_sort_helper

template<typename T>
void quick_sort( T *beg, T *tail, _QUICKSORT_COMPARE_T(T) compare_f = std::less<T>() ){
    std::random_shuffle( beg, tail );
    //_quick_sort_helper::_quick_sort(beg, tail, compare_f);
    // Non-recursive method is a little bit quicker.
    _quick_sort_helper::_quick_sort_stk(beg, tail, compare_f);
}


} // DS
#endif
