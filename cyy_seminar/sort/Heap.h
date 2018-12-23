#ifndef HEAP_H_
#define HEAP_H_
#include "mystd.h"

#define HEAP_LEFT(i) ( 2*(i)+1 )
#define HEAP_RIGHT(i) ( 2*(i)+2 )
#define HEAP_PARENT(i) ( ((i)-1)/2 )

namespace DS {
using namespace MYSTD;


template<typename T>
class Heap{
public:
    typedef std::size_t size_type;
    typedef std::ptrdiff_t diff_type;
    typedef T value_type;
    typedef value_type *ptr_type;
    typedef std::function< bool(const value_type&, const value_type&) > comp_type;

    Heap(ptr_type b, ptr_type e, comp_type f = std::less<value_type>());
    virtual ~Heap(){}

    void max_heapify(diff_type i);
    void build_max_heap();
    ptr_type sorted(ptr_type);
    void sort();
private:
    ptr_type pb;
    diff_type sz;
    comp_type less;
};

template<typename T>
Heap<T>::Heap(ptr_type b, ptr_type e, comp_type f)
:pb(b), sz(e-b), less(f){
    if( sz < 0 ){ cout << __func__ << ": Pointer order is wrong: " << (void*)(b) << ", " << (void*)(e) << endl; exit(EXIT_FAILURE); }
    build_max_heap();
}


// old version
// not efficient enough
/*
template<typename T>
void Heap<T>::max_heapify(diff_type i){
    diff_type l, r, max_id = i;
    do{
        l = HEAP_LEFT(i), r = HEAP_RIGHT(i);
        if( l < sz && less( pb[max_id], pb[l] ) ) max_id = l;
        if( r < sz && less( pb[max_id], pb[r] ) ) max_id = r;
        if( max_id != i ){ swap( pb[max_id], pb[i] ); i = max_id; }
        else{ break; }
    }while( true );
}
*/


template<typename T>
void Heap<T>::max_heapify(diff_type i){
    value_type elem = pb[i];
    diff_type j = HEAP_LEFT(i);
    while( j < sz ){
        if( j + 1 < sz && less( pb[j], pb[j+1] ) ){ ++j; }
        if( less( pb[j], elem ) ){ break; }
        pb[i] = pb[j];
        i = j; j = HEAP_LEFT(i);
    }
    pb[i] = elem;
}


template<typename T>
void Heap<T>::build_max_heap(){
    if( sz <= 1 ){ return; }
    for( diff_type i = HEAP_PARENT(sz-1); i >= 0; --i ){
        max_heapify( i );
    }
}

template<typename T>
typename Heap<T>::ptr_type Heap<T>::sorted(ptr_type t){
    t += sz;
    while( sz > 1 ){
        *--t = *pb;
        *pb = pb[--sz];
        max_heapify(0);
    }
    *--t = *pb; --sz;
    return t;
}

template<typename T>
void Heap<T>::sort(){
    auto pe = pb + sz;
    while( (sz--) > 0 ){
        swap( *--pe, *pb );
        max_heapify(0);
    }
}




} // DS
#endif
