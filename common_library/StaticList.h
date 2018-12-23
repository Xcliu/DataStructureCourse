#ifndef STATICLIST_H_
#define STATICLIST_H_
#include "mystd.h"
namespace DS {
using namespace MYSTD;

template<typename T>
struct SLinkNode{
    typedef std::ptrdiff_t diff_type;
    T data;
    diff_type link;
    SLinkNode(const T & x, diff_type id = -1):data(x),link(id){}
    SLinkNode(diff_type id = -1):link(id){}
};

template<typename T>
class StaticList: public LinearList<T>
{
public:
    typedef LinearList<T> super_type;
    typedef typename super_type::size_type size_type;
    typedef typename super_type::diff_type diff_type;
    typedef typename super_type::value_type value_type;
    typedef SLinkNode<T> node_type;
    typedef node_type * ptr_type;

    StaticList(const StaticList & lst);
    StaticList(size_type);
    StaticList(size_type, const std::initializer_list<value_type> &);
    virtual ~StaticList();

    virtual void makeEmpty();
    virtual size_type Size()const override;
    virtual size_type Length()const override;
    virtual ptr_type Search(const value_type &)const;
    virtual ptr_type Locate(diff_type)const;
    virtual bool getData(size_type, value_type &)const override;
    virtual bool setData(size_type, const value_type &) override;
    virtual bool Insert(size_type, const value_type &) override;
    virtual bool Remove(size_type, value_type &) override;
    virtual bool IsEmpty()const override{ return last == 0;}
    virtual bool IsFull()const override{ return avail == -1; }
    virtual void Sort() override{}
    virtual istream & input( istream & = cin ) override;
    virtual ostream & output( ostream & = cout )const override;
    virtual const value_type & operator[](size_type) const override;
    virtual value_type & operator[](size_type) override;
protected:
    diff_type last;
    diff_type avail;
    ptr_type data;
    size_type maxSize;
};


template<typename T>
StaticList<T>::StaticList(const StaticList & lst){
    maxSize = lst.maxSize;
    data = my_alloc<node_type>( maxSize, __func__ );
    avail = lst.avail;
    last = lst.last;
    for( size_type i = 0; i < maxSize; ++i  ){
        data[i] = lst.data[i];
    }
}
template<typename T>
StaticList<T>::StaticList(size_type n){
    maxSize = n + 1;
    data = my_alloc<node_type>( maxSize, __func__ );

    makeEmpty();
}

template<typename T>
StaticList<T>::StaticList(size_type n, const std::initializer_list<value_type> & lst){
    if( lst.size() > n ){ CMYFPOS << ": can not initialize list with size " << n << " containing " << lst.size() << " elements!" << endl; exit(EXIT_FAILURE); }
    maxSize = n+1;
    data = my_alloc<node_type>( maxSize, __func__ );
    last = 0;

    for( const auto & val : lst ){
        data[last].link = last + 1;
        data[++last].data = val;
    }
    avail = data[last].link;
    data[last].link = -1;

    for( size_type i = last + 1; i < n; ++i ){
        data[i].link = i+1;
    }
    data[n] = -1;
}

template<typename T>
void StaticList<T>::makeEmpty(){
    last = 0; avail = 1;
    data[0].link = -1;
    for (size_type i = 1; i < maxSize - 1; ++i){
        data[i].link = i+1;
    }
    data[maxSize - 1].link = -1;
}

template<typename T>
StaticList<T>::~StaticList(){
    my_deAllocArr(data);
}

template<typename T>
typename StaticList<T>::size_type StaticList<T>::Size()const{
    return maxSize - 1;
}
template<typename T>
typename StaticList<T>::size_type StaticList<T>::Length()const{
    size_type sz = 0, id = 0;
    while( data[id].link != -1 ){
        id = data[id].link;
        ++sz;
    }
    return sz;
}

template<typename T>
typename StaticList<T>::ptr_type StaticList<T>::Search(const value_type & x)const{
    diff_type id = data[0].link;
    while( id != -1 && data[id].data != x ){
        id = data[id].link;
    }
    if( id == -1 ){ return nullptr; }
    return data + id;
}
template<typename T>
typename StaticList<T>::ptr_type StaticList<T>::Locate(diff_type i)const{
    diff_type id = 0, ct = 0;
    while( id != -1 && ct <= i ){
        id = data[id].link;
        ++ct;
    }
    if( id == -1 ){ return nullptr; }
    return data+id;
}

template<typename T>
bool StaticList<T>::getData(size_type i, value_type & x)const{
    auto ptr = Locate(i);
    if( ptr ){ x = ptr->data; return true; }
    return false;
}
template<typename T>
bool StaticList<T>::setData(size_type i, const value_type & x){
    auto ptr = Locate(i);
    if( ptr ){ ptr->data = x; return true; }
    return false;
}
template<typename T>
bool StaticList<T>::Insert(size_type i, const value_type & x){
    if( IsFull() ){ return false; }
    auto pre = Locate(diff_type(i)-1);
    if( pre ){
        auto new_id = avail;
        avail = data[avail].link;

        data[new_id].link = pre->link;
        pre->link = new_id;

        if( data[new_id].link == -1 ){ last = new_id; }
        return true;
    }else{
        return false;
    }
}
template<typename T>
bool StaticList<T>::Remove(size_type i, value_type & x){
    auto pre = Locate( diff_type(i) - 1 );
    if( pre && pre->link != -1 ){
        auto del = pre->link;
        if( del == last ){ last = pre - data;  }
        pre->link = data[del].link;
        data[del].link = avail;
        avail = del;
        return true;
    }else{
        return false;
    }
}
template<typename T>
istream & StaticList<T>::input( istream & is){
    makeEmpty();
    value_type tmp;
    while( !IsFull() && is>>tmp ){
        data[last].link = avail;
        last = avail;
        data[last].data = tmp;
        avail = data[avail].link;
        data[last].link = -1;
    }
    return is;
}
template<typename T>
ostream & StaticList<T>::output( ostream & os)const{
    diff_type id = 0;
    while( data[id].link != -1 ){
        id = data[id].link;
        os << data[id].data << '\t';
    }
    return os;
}
template<typename T>
const typename StaticList<T>::value_type & StaticList<T>::operator[](size_type i) const{
    auto ptr = Locate(i);
    return ptr->data;
}
template<typename T>
typename StaticList<T>::value_type & StaticList<T>::operator[](size_type i){
    auto ptr = Locate(i);
    return ptr->data;
}





} // DS


#endif
