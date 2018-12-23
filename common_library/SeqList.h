#ifndef SEQLIST_H_
#define SEQLIST_H_
#include "LinearList.h"
namespace DS {


template<typename T>
class SeqList: public LinearList<T>
{
public:
    typedef LinearList<T> super_type;
    typedef typename super_type::size_type size_type;
    typedef typename super_type::diff_type diff_type;
    typedef typename super_type::value_type value_type;
    typedef T * ptr_type;
    static const size_type defaultSize = 100;

    SeqList(size_type sz = defaultSize):maxSize(sz),last(0){ data = my_alloc<value_type>(sz, __func__); }
    SeqList(const SeqList & lst):maxSize(lst.maxSize),last(lst.last){ data = my_alloc<value_type>(maxSize, __func__); _copy(lst.data, last, data); }
    SeqList(const std::initializer_list<value_type> & );
    virtual ~SeqList(){ my_deAllocArr(data); }

    virtual size_type Size()const{ return maxSize; }
    virtual size_type Length()const{ return last; }
    virtual ptr_type Search(const value_type &)const;
    virtual ptr_type Locate(size_type)const;
    virtual bool getData(size_type, value_type &)const;
    virtual bool setData(size_type, const value_type &);
    virtual bool Insert(size_type, const value_type &);
    virtual bool Remove(size_type, value_type &);
    virtual bool IsEmpty()const{ return last == 0; }
    virtual bool IsFull()const{ return last == maxSize; }
    virtual void Sort(){}
    virtual istream & input( istream & is = cin );
    virtual ostream & output( ostream & = cout )const;
    virtual const value_type & operator[](size_type i) const{ return data[i]; }
    virtual value_type & operator[](size_type i){ return data[i]; }

    SeqList & operator=(const SeqList & lst){ if( lst.Length() > Size() ){ my_deAllocArr(data); data = my_alloc<value_type>( lst.Size(), __func__ ); copy(lst.data,  lst.Length(), data); } }
protected:
    size_type maxSize, last;
    value_type * data;
    void _reSize(size_type sz);
    void _copy(const value_type * source, size_type n, value_type * target);
    void _inverse_copy(const value_type * source, size_type n, value_type * target);
};


template<typename T>
SeqList<T>::SeqList( const std::initializer_list<value_type> & lst ){
    maxSize =  lst.size() > defaultSize? lst.size() : defaultSize,
        last = lst.size();
    data = my_alloc<value_type>( maxSize , __func__);
    size_type id = 0;
    for( const auto & val : lst ){
        data[id++] = val;
    }
}


template<typename T>
typename SeqList<T>::ptr_type SeqList<T>::Search(const value_type & x)const{
    for( size_type i = 0; i< last; ++i ){
        if( data[i] == x ){ return data+i; }
    }
    return nullptr;
}
template<typename T>
typename SeqList<T>::ptr_type SeqList<T>::Locate(size_type i)const{
    if( i > last ){ return nullptr; }
    return data + i;
}

template<typename T>
bool SeqList<T>::getData(size_type i, value_type & x)const{
    if( i >= last ){ return false; }
    x = data[i]; return true;
}
template<typename T>
bool SeqList<T>::setData(size_type i, const value_type & x){
    if( i >= last ){ return false; }
    data[i] = x; return true;
}
template<typename T>
bool SeqList<T>::Insert(size_type i, const value_type & x){
    if( IsFull() ){ _reSize( 2*maxSize < 1 ? 1 : 2*maxSize ); }
    auto ins_loc = Locate(i); if( !ins_loc ){ return false; }
    _inverse_copy( ins_loc, last - i, ins_loc+1 );
    *ins_loc = x;
    ++last;
    return true;
}
template<typename T>
bool SeqList<T>::Remove(size_type i, value_type & x){
    if( i >= last ){ return false; }
    auto rem_loc = Locate(i);
    x = *rem_loc;
    _copy( rem_loc+1, last - i - 1, rem_loc );
    --last;
    return true;
}

template<typename T>
istream & SeqList<T>::input( istream & is ){
    value_type v_tmp;
    last = 0;
    while( is >> v_tmp ){
        if( IsFull() ){ _reSize( 2*maxSize < 1 ? 1 : 2*maxSize ); }
        data[last++] = v_tmp;
    }
    return is;
}
template<typename T>
ostream & SeqList<T>::output( ostream & os)const{
    for (size_type i = 0; i < last; ++i){
        os << data[i] << '\t';
    }
    return os;
}

template<typename T>
void SeqList<T>::_reSize(size_type sz){
    if( sz < last ){ CMYFPOS << ": can not resize from " << last << " to " << sz << endl; exit(EXIT_FAILURE); }
    auto new_data = my_alloc<value_type>(sz, __func__);
    _copy( data, last, new_data );
    my_deAllocArr(data);
    data = new_data;
    maxSize = sz;
}


template<typename T>
void SeqList<T>::_copy(const value_type * source, size_type n, value_type * target){
    for(size_type i = 0; i < n; --i){
        target[i] = source[i];
    }
}
template<typename T>
void SeqList<T>::_inverse_copy(const value_type * source, size_type n, value_type * target){
    for(diff_type i = n-1; i >= 0; --i){
        target[i] = source[i];
    }
}





} // DS


#endif
