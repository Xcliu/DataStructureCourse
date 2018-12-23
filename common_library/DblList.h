#ifndef DBLLIST_H_
#define DBLLIST_H_
#include "LinearList.h"
namespace DS {

template<typename T>
struct DblNode{
    T data;
    DblNode * lLink, * rLink;
    DblNode( DblNode * lptr = nullptr, DblNode * rptr = nullptr ): lLink(lptr), rLink(rptr){}
    DblNode( const T & item, DblNode * lptr = nullptr, DblNode * rptr = nullptr ): data(item), lLink(lptr), rLink(rptr){}
};


template<typename T>
class DblList : public LinearList<T>
{
public:
    using size_type = typename LinearList<T>::size_type;
    typedef std::ptrdiff_t  diff_type;
    using value_type = typename LinearList<T>::value_type;
    typedef DblNode<T> * pointer_type;
    typedef DblNode<T> node_type;

    DblList();
    DblList( const T & );
    DblList( const DblList & );
    virtual ~DblList();

    void makeEmpty();
    size_type Size()const;
    size_type Length()const;
    pointer_type Search(const value_type &)const;
    pointer_type Locate(diff_type i)const;
    pointer_type lLocate(diff_type i)const;
    pointer_type Locate(diff_type i, diff_type direc)const;
    bool getData( size_type, value_type &)const;
    bool lgetData( size_type, value_type & )const;
    bool getData( size_type, value_type &, diff_type direc )const;
    bool setData( size_type, const value_type & );
    bool lsetData( size_type, const value_type & );
    bool setData( size_type, const value_type &, diff_type direc );
    bool Insert( size_type, const value_type & );
    bool lInsert( size_type, const value_type & );
    bool Insert( size_type, const value_type &, diff_type direc );
    bool _Insert( pointer_type, const value_type & );
    bool Remove( size_type, value_type &);
    bool lRemove( size_type, value_type & );
    bool Remove( size_type, value_type &, diff_type direc );
    bool _Remove( pointer_type, value_type & );

    bool IsEmpty()const;
    bool IsFull()const;
    void Sort(){}
    void input(istream & is = cin);
    void output(ostream & os = cout)const;
    void loutput(ostream & os = cout)const;
    DblList & operator=( const DblList & );

    pointer_type getHead()const;
    pointer_type nextNode(pointer_type ptr)const;
    pointer_type lnextNode(pointer_type ptr)const;
    pointer_type nextNode(pointer_type ptr, diff_type direc)const;
protected:
    pointer_type first;
    pointer_type allocNode(const value_type &, pointer_type lptr = nullptr, pointer_type rptr = nullptr ,const char * buff = "");
    pointer_type allocNode(pointer_type ptr = nullptr, pointer_type rptr = nullptr, const char * buff = "");
};






template<typename T>
DblList<T>::DblList(){
    first = allocNode(nullptr, nullptr, __func__);
    first->lLink = first->rLink = first;
}
template<typename T>
DblList<T>::DblList( const T & x){
    first = allocNode(x, nullptr, nullptr, __func__);
    first->lLink = first->rLink = first;
}
template<typename T>
DblList<T>::DblList( const DblList & that):DblList(that.first->data){
    pointer_type pthat = that.first->rLink, pthis = first;
    while(pthat != that.first) {
        pthis->rLink = allocNode( pthat->data, pthis, nullptr, __func__ );
        pthis = pthis->rLink;
        pthat = pthat->rLink;
    }
    pthis->rLink = first;
    first->lLink = pthis;
}
template<typename T>
DblList<T>::~DblList(){ makeEmpty(); }

template<typename T>
void DblList<T>::makeEmpty(){
    pointer_type pre = first->rLink, ptr = pre;
    while( pre != first ){
        ptr = ptr->rLink;
        delete pre; pre = ptr;
    }
    first->rLink = first->lLink = first;
}

template<typename T>
typename DblList<T>::size_type DblList<T>::Size()const{
    return Length() + 1;
}

template<typename T>
typename DblList<T>::size_type DblList<T>::Length()const{
    size_type count = 0;
    pointer_type ptr = first->rLink;
    while( ptr != first ){
        ++count;
        ptr = ptr->rLink;
    }
    return count;
}
template<typename T>
typename DblList<T>::pointer_type DblList<T>::Search(const value_type & x)const{
    pointer_type ptr = first->rLink;
    while( ptr != first ){
        if( ptr->data == x ){ break; }
        ptr = ptr->rLink;
    }
    return ptr == first ? nullptr : ptr;
}
template<typename T>
typename DblList<T>::pointer_type DblList<T>::Locate(diff_type pos)const{
    pointer_type ptr = first;
    for (diff_type i = 0; i <= pos; ++i){
        ptr = nextNode(ptr);
    }
    return ptr;
}
template<typename T>
typename DblList<T>::pointer_type DblList<T>::lLocate(diff_type pos)const{
    pointer_type ptr = first;
    for (diff_type i = 0; i <= pos; ++i){
        ptr = lnextNode(ptr);
    }
    return ptr;
}
template<typename T>
typename DblList<T>::pointer_type DblList<T>::Locate(diff_type pos, diff_type direc)const{
    return direc == 0 ? lLocate( pos ) : Locate( pos );
}

template<typename T>
bool DblList<T>::getData( size_type pos, value_type & x)const{
    pointer_type ptr = Locate(pos);
    if( ptr == first ){ return false; }
    x = ptr->data;
    return true;
}


template<typename T>
bool DblList<T>::lgetData( size_type pos, value_type & x)const{
    pointer_type ptr = lLocate(pos);
    if( ptr == first ){ return false; }
    x = ptr->data;
    return true;
}

template<typename T>
bool DblList<T>::getData( size_type pos, value_type & x, diff_type direc)const{
    return direc == 0? lgetData(pos, x): getData(pos, x);
}

template<typename T>
bool DblList<T>::setData( size_type pos, const value_type & x){
    pointer_type ptr = Locate(pos);
    if( ptr == first ){ return false; }

    ptr->data = x;
    return true;
}


template<typename T>
bool DblList<T>::lsetData( size_type pos, const value_type & x){
    pointer_type ptr = lLocate(pos);
    if( ptr == first ){ return false; }

    ptr->data = x;
    return true;
}

template<typename T>
bool DblList<T>::setData( size_type pos, const value_type & x, diff_type direc){
    return direc == 0? lsetData(pos,x) : setData(pos,x);
}

template<typename T>
bool DblList<T>::Insert( size_type i, const value_type & x){
    pointer_type ptr = Locate(i);
    return _Insert( ptr, x );

}
template<typename T>
bool DblList<T>::lInsert( size_type i, const value_type & x){
    pointer_type ptr = lLocate(i);
    return _Insert( ptr, x );
}

template<typename T>
bool DblList<T>::Insert( size_type i, const value_type & x, diff_type direc){
    return direc == 0? lInsert(i,x) : Insert(i,x);
}

template<typename T>
bool DblList<T>::_Insert( pointer_type ptr, const value_type & x ){
    auto pre = ptr->lLink;
    auto new_node = allocNode( x, pre ,ptr, __func__ );
    pre->rLink = new_node;
    new_node->rLink->lLink = new_node;
    return true;
}

template<typename T>
bool DblList<T>::Remove( size_type i, value_type & x){
    pointer_type ptr = Locate(i);
    return _Remove( ptr, x );
}

template<typename T>
bool DblList<T>::lRemove( size_type i, value_type & x){
    pointer_type ptr = lLocate(i);
    return _Remove( ptr, x );
}

template<typename T>
bool DblList<T>::Remove( size_type i, value_type & x, diff_type direc){
    return direc == 0 ? lRemove(i,x) : Remove(i,x);
}

template<typename T>
bool DblList<T>::_Remove( pointer_type ptr, value_type & x ){
    if( ptr == first ){ return false; }
    auto pre = ptr->lLink;
    pre->rLink = ptr->rLink;
    ptr->rLink->lLink = pre;
    x = ptr->data;
    delete ptr;
    return true;
}

template<typename T>
bool DblList<T>::IsEmpty()const{
    return first->rLink == first ? true : false;
}
template<typename T>
bool DblList<T>::IsFull()const{
    return true;
}


template<typename T>
void DblList<T>::input(istream & is){
    makeEmpty();
    pointer_type rear = first;
    value_type tmp;
    while( is >> tmp ){
        rear->rLink = allocNode( tmp,rear, first, __func__ );
        rear = rear->rLink;
    }
    first->lLink = rear;
}

template<typename T>
void DblList<T>::output(ostream & os)const{
    pointer_type ptr = first->rLink;
    while( ptr != first ){
        os << ptr->data << '\t';
        ptr = ptr->rLink;
    }
}

template<typename T>
void DblList<T>::loutput(ostream & os)const{
    pointer_type ptr = first->lLink;
    while( ptr != first ){
        os << ptr->data << '\t';
        ptr = ptr->lLink;
    }
}

template<typename T>
DblList<T> & DblList<T>::operator=( const DblList & that){
    makeEmpty();
    first->data = that.first->data;
    first->rLink = first;

    pointer_type pthis = first, pthat = that.first->rLink;
    while( pthat != that.first ){
        pthis->rLink = allocNode( pthat->data, pthis, first, __func__ );
        pthis = pthis->rLink;
        pthat = pthat->rLink;
    }
    first->lLink = pthis;
    return *this;
}

template<typename T>
typename DblList<T>::pointer_type DblList<T>::getHead()const{
    return first;
}

template<typename T>
typename DblList<T>::pointer_type DblList<T>::nextNode(pointer_type ptr)const{
    auto post = ptr->rLink;
    if( post == getHead() ){
        post = post->rLink;
    }
    return post;
}


template<typename T>
typename DblList<T>::pointer_type DblList<T>::lnextNode(pointer_type ptr)const{
    auto post = ptr->lLink;
    if( post == getHead() ){
        post = post->lLink;
    }
    return post;
}


template<typename T>
typename DblList<T>::pointer_type DblList<T>::nextNode(pointer_type ptr, diff_type direc)const{
    return direc == 0? lnextNode( ptr ) : nextNode( ptr );
}

template<typename T>
typename DblList<T>::pointer_type DblList<T>::allocNode(const value_type & x, pointer_type lptr , pointer_type rptr, const char * buff){
    pointer_type new_node;
    try{ new_node = new node_type( x, lptr, rptr );  }
    catch( bad_alloc & ba){ cout << buff << ": alloc wrong!\n"; exit(EXIT_FAILURE); }
    return new_node;
}

template<typename T>
typename DblList<T>::pointer_type DblList<T>::allocNode(pointer_type lptr, pointer_type rptr ,const char * buff){
    pointer_type new_node;
    try{ new_node = new node_type( lptr, rptr );  }
    catch( bad_alloc & ba){ cout << buff << ": alloc wrong!\n"; exit(EXIT_FAILURE); }
    return new_node;
}






} // DS
#endif
