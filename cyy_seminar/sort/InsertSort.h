#ifndef INSERT_H_
#define INSERT_H_

#include "mystd.h"
#define _INSERTSORT_COMPARE_T(T) std::function< bool(const T &, const T &) >

namespace DS {
using namespace MYSTD;

namespace _insert_sort_helper {
template<typename T>
T *_bisearch(T *b, T *e, T val, _INSERTSORT_COMPARE_T(T) compare_f = std::less<T>() ){
    T *cen = nullptr;
    while( e - b > 1 ){
        cen = b + (e-b)/2;
        if( compare_f( val, *cen ) ){ e = cen; }
        else{ b = cen; }
    }
    return compare_f(val, *b)?(b-1):b;
}

template<typename T>
void _move_ahead(T *bi_tar, T *e ){
    for( --e; e > bi_tar; --e ){
        *(e+1) = *e;
    }
}
} // _insert_sort_helper


template<typename T>
void insert_sort( T *b, T *e, _INSERTSORT_COMPARE_T(T) compare_f = std::less<T>() ){
    T * tar = nullptr;
    T val;
    for( T *p = b+1; p < e; ++p ){
        val = *p;
        tar = p - 1;
        while( (tar >= b) && compare_f(val, *tar) ){
            *(tar+1) = *tar;
            --tar;
        }
        *(tar+1) = val;
    }
}

template<typename T>
void insert_sort_bisearch(T *b, T *e, _INSERTSORT_COMPARE_T(T) compare_f = std::less<T>() ){
    T *bi_tar = nullptr;
    T val;
    for( T *p = b+1; p < e; ++p ){
        val = *p;
        bi_tar = _insert_sort_helper::_bisearch( b, p, val, compare_f );
        cout << val << " " << *bi_tar << endl;
        _insert_sort_helper::_move_ahead( bi_tar, p );
        *(bi_tar + 1) = val;
    }
}


} // DS
#endif
