#ifndef SEQPQUEUE_H_
#define SEQPQUEUE_H_
#include "PQueue.h"
namespace DS {

template<typename T, typename CompareT = std::less<T> >
class SeqPQueue: public PQueue<T, CompareT>
{
public:
    typedef PQueue<T, CompareT> super_type;
    typedef typename super_type::size_type size_type;
    typedef typename super_type::diff_type diff_type;
    typedef typename super_type::value_type value_type;
    typedef typename super_type::compr_type compr_type;
    typedef value_type * ptr_type;
    static const size_type defaultSize = 50;

    SeqPQueue( size_type sz = defaultSize ):last(0),maxSize(sz){ elements = my_alloc<value_type>(sz, __func__); }
    SeqPQueue( const std::initializer_list<value_type>& );
    ~SeqPQueue() override { my_deAllocArr(elements); }
    bool Insert(const value_type &) override;
    bool RemoveMin(value_type &) override;
    bool RemoveMin() override;
    bool getFront(value_type &)const override;
    value_type & refFront() override{ return elements[last - 1]; }
    const value_type & refFront()const override{ return elements[last - 1]; }
    void makeEmpty() override{ last = 0; }
    bool IsEmpty()const override{ return last == 0; }
    bool IsFull()const override{ return last == maxSize; }
    size_type getSize()const override{ return last; }
    ostream & output( ostream & os = cout )const override;
protected:
    ptr_type elements;
    size_type last;
    size_type maxSize;
    compr_type compr;
    void adjust();
    void overflowProcess();
};


template<typename T, typename CompareT>
SeqPQueue<T, CompareT>::SeqPQueue( const std::initializer_list<value_type>& lst)
:SeqPQueue( lst.size() > defaultSize ? ( lst.size() + defaultSize ) : (defaultSize) )
{
    for( const auto & val: lst ){
        Insert( val );
    }
}

template<typename T, typename CompareT>
bool SeqPQueue<T, CompareT>::Insert(const value_type & x){
    if( IsFull() ){ overflowProcess(); }
    elements[last++] = x;
    adjust();
    return true;
}

template<typename T, typename CompareT>
bool SeqPQueue<T, CompareT>::RemoveMin(value_type & x){
    if( IsEmpty() ){ return false; }
    x = elements[ --last ];
    return true;
}
template<typename T, typename CompareT>
bool SeqPQueue<T, CompareT>::RemoveMin(){
    if( IsEmpty() ){ return false; }
    --last;
    return true;
}

template<typename T, typename CompareT>
bool SeqPQueue<T, CompareT>::getFront(value_type & x)const{
    if( IsEmpty() ){ return false; }
    x = elements[ last - 1 ];
    return true;
}

template<typename T, typename CompareT>
void SeqPQueue<T, CompareT>::adjust(){
    value_type temp = elements[last - 1];
    diff_type id = last - 2;
    while( id >= 0 && compr( elements[id], temp ) ){
        elements[id + 1] = elements[id];
        --id;
    }
    elements[id+1] = temp;
}
template<typename T, typename CompareT>
void SeqPQueue<T, CompareT>::overflowProcess(){
    size_type new_size = maxSize == 0 ? ( defaultSize ) : ( 2*maxSize );
    auto new_elements = my_alloc<value_type>( new_size, __func__ );
    for(size_type i = 0; i < last; ++i) {
        new_elements[i] = elements[i];
    }
    my_deAllocArr( elements );

    elements = new_elements;
    maxSize = new_size;
}

template<typename T, typename CompareT>
ostream & SeqPQueue<T, CompareT>::output( ostream & os )const{
    for( size_type i = last; i > 0;){
        os << elements[--i] << '\t';
    }
    return os;
}


} // DS
#endif
