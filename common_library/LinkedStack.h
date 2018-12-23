#ifndef LINKEDSTACK_H_
#define LINKEDSTACK_H_
#include "Stack.h"
#include "List.h"
namespace DS {
using namespace MYSTD;

template<typename T>
class LinkedStack: public Stack<T>
{
public:
    typedef Stack<T> super_type;
    typedef typename super_type::size_type size_type;
    typedef typename super_type::diff_type diff_type;
    typedef typename super_type::value_type value_type;
    typedef LinkNode<T>  node_type;
    typedef node_type * ptr_type;
    typedef my_allocator<LinkNode<T> > alloc_type;

    LinkedStack():top(nullptr){}
    LinkedStack(const std::initializer_list<value_type> &);
    virtual ~LinkedStack() override { makeEmpty(); }
    virtual void Push(const value_type &) override;
    virtual bool Pop(value_type &) override;
    virtual bool Pop() override;
    virtual bool getTop(value_type &)const override;
    virtual const value_type & refTop()const override{ return top->data; }
    virtual value_type & refTop() override{ return top->data; }
    virtual bool IsEmpty()const override { return top == nullptr; }
    virtual bool IsFull()const override { return false; }
    virtual size_type getSize()const override;
    virtual ostream & output(ostream & os = cout)const override;
    virtual void makeEmpty() override;
protected:
    ptr_type top;
    alloc_type allocator;
};

template<typename T>
LinkedStack<T>::LinkedStack(const std::initializer_list<value_type> & lst):LinkedStack(){
    for( const auto & val : lst ){ Push(val); }
}

template<typename T>
inline void LinkedStack<T>::Push(const value_type & x){
    top = allocator.alloc(__func__, x, top);
}
template<typename T>
inline bool LinkedStack<T>::Pop(value_type & x){
    if( IsEmpty() ){ return false; }
    x = top->data;
    auto del = top; top = top->link;
    allocator.deAlloc( del );
    return true;
}
template<typename T>
inline bool LinkedStack<T>::Pop(){
    if( IsEmpty() ){ return false; }
    auto del = top; top = top->link;
    allocator.deAlloc( del );
    return true;
}
template<typename T>
inline bool LinkedStack<T>::getTop(value_type & x)const{
    if( IsEmpty() ){ return false; }
    x = top->data;
    return true;
}

template<typename T>
typename LinkedStack<T>::size_type LinkedStack<T>::getSize()const{
    auto ptr = top; size_type ct = 0;
    while( ptr ){
        ++ct;
        ptr = ptr->link;
    }
    return ct;
}

template<typename T>
ostream & LinkedStack<T>::output(ostream & os)const{
    auto ptr = top;
    while(ptr) {
        os << ptr->data << '\t';
        ptr = ptr->link;
    }
    return os;
}

template<typename T>
void LinkedStack<T>::makeEmpty(){
    auto ptr = top, del = top;
    while( ptr ){
        del = ptr;
        ptr = ptr->link;
        allocator.deAlloc( del );
    }
}







} // DS



#endif



