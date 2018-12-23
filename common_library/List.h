#ifndef LIST_H_
#define LIST_H_
#include "LinearList.h"
#include "SeqStack.h" // for reverse
namespace DS {

template<typename T>class List;

template<typename T>
struct LinkNode{
    T data;
    LinkNode * link;
    LinkNode( LinkNode * ptr = nullptr ): link(ptr){}
    LinkNode( const T & item, LinkNode * ptr = nullptr ): data(item), link(ptr){}
};



template<typename T>
T & max( const List<T> &);

template<typename T>
std::size_t number( const List<T> &, const T &);

template<typename T>
List<T> creat( T arr[], size_t n);

template<typename T>
void tidyup( List<T>& );

template<typename T>
class List : public LinearList<T>
{
public:
    typedef LinearList<T> super_type;
    typedef typename super_type::size_type size_type;
    typedef typename super_type::diff_type diff_type;
    typedef typename super_type::value_type value_type;
    typedef LinkNode<T> node_type;
    typedef node_type * ptr_type;

    List();
    List( const T & );
    List( const List & );
    List( List && );
    List( const std::initializer_list<value_type> & );
    virtual ~List();

    void makeEmpty();
    size_type Size()const override;
    size_type Length()const override;
    ptr_type Search(const value_type &)const;
    ptr_type Locate(diff_type i)const;
    bool getData( size_type, value_type &)const override;
    bool setData( size_type, const value_type & ) override;
    bool Insert( size_type, const value_type & ) override;
    bool _Insert( ptr_type, const value_type & );
    bool Remove( size_type, value_type &) override;
    bool _Remove( ptr_type, value_type & );

    bool IsEmpty()const override;
    bool IsFull()const override;
    void Sort() override {}
    istream & input(istream & is = cin) override;
    ostream & output(ostream & os = cout)const override;
    List & operator=( const List & );
    List & operator=( List && );
    const value_type& operator[](size_type i)const override;
    value_type& operator[](size_type i)override;

    ptr_type getHead()const;


    friend value_type & max<T>( const List &);
    friend std::size_t number<T>( const List &, const T &);
    friend List creat<T>( T arr[], size_t n);
    friend void tidyup<T>( List<T>& );

    // By using SeqStack<ptr_type>;
    void reverse();
protected:
    ptr_type first;
    ptr_type allocNode(const value_type &, ptr_type ptr = nullptr, const char * buff = "");
    ptr_type allocNode(ptr_type ptr = nullptr, const char * buff = "");
};






template<typename T>
List<T>::List(){
    first = allocNode(nullptr, __func__);
    first->link = first;
}
template<typename T>
List<T>::List( const T & x){
    first = allocNode(x, nullptr, __func__);
    first->link = first;
}
template<typename T>
List<T>::List( const List & that):List(that.first->data){
    ptr_type pthat = that.first->link, pthis = first;
    while(pthat != that.first) {
        pthis->link = allocNode( pthat->data, nullptr, __func__ );
        pthis = pthis->link;
        pthat = pthat->link;
    }
    pthis->link = first;
}

template<typename T>
List<T>::List( List && that ){
    first = that.first;
    that.first = allocNode( nullptr, __func__ );
    that.first->link = that.first;
}

template<typename T>
List<T>::List( const std::initializer_list<value_type> & lst):List(){
    auto rear = first;
    for( const auto & val : lst ){
        rear->link = allocNode(val,first,__func__);
        rear = rear->link;
    }
}

template<typename T>
List<T>::~List(){ makeEmpty(); }

template<typename T>
void List<T>::makeEmpty(){
    ptr_type pre = first->link, ptr = pre;
    while( pre != first ){
        ptr = ptr->link;
        delete pre; pre = ptr;
    }
    first->link = first;
}

template<typename T>
typename List<T>::size_type List<T>::Size()const{
    return Length() + 1;
}

template<typename T>
typename List<T>::size_type List<T>::Length()const{
    size_type count = 0;
    ptr_type ptr = first->link;
    while( ptr != first ){
        ++count;
        ptr = ptr->link;
    }
    return count;
}
template<typename T>
typename List<T>::ptr_type List<T>::Search(const value_type & x)const{
    ptr_type ptr = first->link;
    while( ptr != first ){
        if( ptr->data == x ){ break; }
        ptr = ptr->link;
    }
    return ptr == first ? nullptr : ptr;
}
template<typename T>
typename List<T>::ptr_type List<T>::Locate(diff_type pos)const{

    if( pos < -1 ){ return nullptr; }
    if( pos == -1 ){ return first; }

    ptr_type ptr = first;
    for (diff_type i = 0; i <= pos; ++i){
        ptr = ptr->link;
        if( ptr == first ){ return nullptr; }
    }
    return ptr;
}
template<typename T>
bool List<T>::getData( size_type pos, value_type & x)const{
    ptr_type ptr = Locate(pos);
    if( ptr == nullptr ){ return false; }

    x = ptr->data;
    return true;
}

template<typename T>
bool List<T>::setData( size_type pos, const value_type & x){
    ptr_type ptr = Locate(pos);
    if( ptr == nullptr ){ return false; }

    ptr->data = x;
    return true;
}

template<typename T>
bool List<T>::Insert( size_type i, const value_type & x){
    ptr_type ptr = Locate(i - 1);

    if( ptr == nullptr ){ return false; }

    ptr_type new_node;
    new_node = allocNode(x, ptr->link, __func__);
    ptr->link = new_node;
    return true;
}

template<typename T>
bool List<T>::_Insert( ptr_type ptr, const value_type & x ){
    auto new_node = allocNode( x, ptr, __func__ );
    auto pre = ptr;
    while(pre->link != ptr) {
        pre = pre->link;
    }
    pre->link = new_node;
    return true;
}

template<typename T>
bool List<T>::Remove( size_type i, value_type & x){
    ptr_type ptr = Locate(i-1);
    if( ptr == nullptr || ptr->link == first ){ return false; }

    ptr_type del = ptr->link;
    x = del->data;
    ptr->link = del->link;
    delete del;
    return true;
}

template<typename T>
bool List<T>::_Remove( ptr_type ptr, value_type & x ){
    if( ptr == first || ptr == nullptr ){ return false; }
    ptr_type pre = ptr;
    while( pre->link != ptr ){
        pre = pre->link;
    }

    pre->link = ptr->link;
    x = ptr->data;
    delete ptr;
    return true;
}

template<typename T>
bool List<T>::IsEmpty()const{
    return first->link == first ? true : false;
}
template<typename T>
bool List<T>::IsFull()const{
    return true;
}


template<typename T>
istream & List<T>::input(istream & is){
    makeEmpty();
    ptr_type rear = first;
    value_type tmp;
    while( is >> tmp ){
        rear->link = allocNode( tmp, first, __func__ );
        rear = rear->link;
    }
    return is;
}

template<typename T>
ostream & List<T>::output(ostream & os)const{
    ptr_type ptr = first->link;
    while( ptr != first ){
        os << ptr->data << '\t';
        ptr = ptr->link;
    }
    return os;
}

template<typename T>
List<T> & List<T>::operator=( const List & that){
    makeEmpty();
    first->data = that.first;
    ptr_type pthis = first, pthat = that.first->link;
    while( pthat != that.first ){
        pthis->link = allocNode( pthat->data, nullptr, __func__ );
        pthis = pthis->link;
        pthat = pthat->link;
    }
    pthis->link = first;
    return *this;
}

template<typename T>
List<T> & List<T>::operator=( List && that){
    swap( first, that.first );
    return *this;
}

template<typename T>
const typename List<T>::value_type& List<T>::operator[](size_type i)const{
    return Locate(i)->data;
}

template<typename T>
typename List<T>::value_type& List<T>::operator[](size_type i){
    return Locate(i)->data;
}


template<typename T>
typename List<T>::ptr_type List<T>::getHead()const{
    return first;
}

template<typename T>
typename List<T>::ptr_type List<T>::allocNode(const value_type & x, ptr_type ptr, const char * buff){
    ptr_type new_node;
    try{ new_node = new node_type( x, ptr );  }
    catch( bad_alloc & ba){ cout << buff << ": alloc wrong!\n"; exit(EXIT_FAILURE); }
    return new_node;
}

template<typename T>
typename List<T>::ptr_type List<T>::allocNode(ptr_type ptr, const char * buff){
    ptr_type new_node;
    try{ new_node = new node_type( ptr );  }
    catch( bad_alloc & ba){ cout << buff << ": alloc wrong!\n"; exit(EXIT_FAILURE); }
    return new_node;
}

template<typename T>
T & max( const List<T> & lst){
    if( lst.IsEmpty() ){
        cout << __func__ << ": Empty list can not call max!" << endl;
        exit(EXIT_FAILURE);
    }
    auto ptr = lst.first->link, max_ptr = ptr;
    while( ptr != lst.first ) {
        if( ptr->data > max_ptr->data ){ max_ptr = ptr; }
        ptr = ptr->link;
    }
    return max_ptr->data;
}

template<typename T>
std::size_t number( const List<T> & lst, const T & x){
    std::size_t n = 0;
    auto ptr = lst.first->link;
    while( ptr != lst.first ){
        if( ptr->data == x ){ ++n; }
        ptr = ptr->link;
    }
    return n;
}

template<typename T>
List<T> creat( T arr[], size_t n){
    List<T> lst;
    auto rear = lst.first;
    for (size_t i = 0; i < n; ++i){
        rear->link = lst.allocNode( arr[i], lst.first, __func__ );
        rear = rear->link;
    }
    return lst;
}

template<typename T>
void tidyup( List<T>& lst){
    typename List<T>::ptr_type pre = lst.first->link,
        post = nullptr, del = nullptr;
    while( pre != lst.first ){
        post = pre->link;
        while( post != lst.first && post->data == pre->data ){
            del = post; post = post->link; pre->link = post;
            delete del;
        }
        pre = post;
    }
}

template<typename T>
void List<T>::reverse(){
    SeqStack<ptr_type> stk;
    auto ptr = first->link;
    while( ptr !=  first ){
        stk.Push( ptr );
        ptr = ptr->link;
    }
    auto last = first;
    while( stk.Pop( ptr ) ) {
        last->link = ptr; last = ptr;
    }
    last->link = first;
}


} // DS
#endif
