#ifndef MERGE_H_
#define MERGE_H_
#include "mystd.h"
#define _MERGE_COMPARE_T(T) std::function< bool(const T &, const T &) >
namespace DS {
using namespace MYSTD;

template<typename T>
inline void _merge(T *b1, T *e1, T *b2, T *e2, T *target, _MERGE_COMPARE_T(T) compare_f = std::less<T>() ){
    vector<T> v1(b1, e1), v2(b2, e2);
    auto it1 = v1.data(), it_e1 = it1 + v1.size(),
        it2 = v2.data(), it_e2 = it2 + v2.size();

    while( it1 != it_e1 && it2 != it_e2 ){
        if( compare_f( *it1, *it2 ) ){
            *target++ = *it1++;
        }else{
            *target++ = *it2++;
        }
    }

    if( it1 == it_e1 ){
        std::copy( it2, it_e2, target );
    }else{
        std::copy( it1, it_e1, target );
    }
}

template<typename T>
inline void _merge_memAvailable(
    T *b1, T *e1, T *b2, T *e2, T *target,
    T *memAvail, _MERGE_COMPARE_T(T) compare_f = std::less<T>()
){
    std::size_t sz1 = e1-b1, sz2 = e2-b2;
    std::copy(b1,e1,memAvail);
    std::copy(b2,e2,memAvail+sz1);

    auto it1 = memAvail, it_e1 = it1 + sz1,
        it2 = it_e1, it_e2 = it2 + sz2;
    while( it1 != it_e1 && it2 != it_e2 ){
        if( compare_f( *it1, *it2 ) ){ *target++ = *it1++;}
        else{ *target++ = *it2++; }
    }
    if( it1 == it_e1 ){ std::copy( it2, it_e2, target ); }
    else{ std::copy( it1, it_e1, target ); }
}


} // DS
#endif
