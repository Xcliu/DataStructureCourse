#ifndef LINKEDQUEUE_H_
#define LINKEDQUEUE_H_
#include "Queue.h"
#include "List.h"
namespace DS {

template<typename T>
class LinkedQueue: public Queue<T>
{
public:
    typedef Queue<T> super_type;
    typedef typename super_type::size_type size_type;
    typedef typename super_type::diff_type diff_type;
    typedef typename super_type::value_type value_type;
    typedef LinkNode<T>  node_type;
    typedef node_type * ptr_type;
    typedef my_allocator<LinkNode<T> > alloc_type;

    LinkedQueue();
    LinkedQueue(const std::initializer_list<value_type> &);
    virtual ~LinkedQueue()override{ makeEmpty(); }
    bool EnQueue(const value_type &) override;
    bool DeQueue(value_type &) override;
    bool DeQueue() override;
    bool getFront(value_type &)const override;
    value_type & refFront() override{ return front->data; }
    const value_type & refFront()const override{ return front->data; }
    bool IsEmpty()const override{ return front == nullptr; }
    bool IsFull()const override{ return false; }
    size_type getSize()const override;
    void makeEmpty() override;
    ostream & output(ostream & os = cout)const override;
protected:
    ptr_type front, rear;
    alloc_type allocator;
};

template<typename T>
LinkedQueue<T>::LinkedQueue():front(nullptr),rear(nullptr){}

template<typename T>
LinkedQueue<T>::LinkedQueue(const std::initializer_list<value_type> & lst):LinkedQueue(){
    for( const auto & val : lst ){
        EnQueue( val );
    }
}

template<typename T>
bool LinkedQueue<T>::EnQueue(const value_type & x){
    if( IsEmpty() ){
        front = rear = allocator.alloc(__func__, x, nullptr );
    }else{
        rear->link = allocator.alloc(__func__, x, nullptr );
        rear = rear->link;
    }
    return true;
}

template<typename T>
bool LinkedQueue<T>::DeQueue(value_type & x){
    if( IsEmpty() ){ return false; }
    x = front->data;
    auto del = front; front = front->link;
    if( front == nullptr ){ rear = nullptr; }
    allocator.deAlloc( del );
    return true;
}

template<typename T>
bool LinkedQueue<T>::DeQueue(){
    if( IsEmpty() ){ return false; }
    auto del = front; front = front->link;
    if( front == nullptr ){ rear = nullptr; }
    allocator.deAlloc( del );
    return true;
}

template<typename T>
bool LinkedQueue<T>::getFront(value_type & x)const{
    if( IsEmpty() ){ return false; }
    x = front->data;
    return true;
}

template<typename T>
typename LinkedQueue<T>::size_type LinkedQueue<T>::getSize()const{
    auto ptr = front;
    size_type ct = 0;
    while( ptr ){
        ++ct;
        ptr = ptr->link;
    }
    return ct;
}

template<typename T>
void LinkedQueue<T>::makeEmpty(){
    ptr_type del;
    while( front ){
        del = front;
        front = front->link;
        allocator.deAlloc( del );
    }
    rear = nullptr;
}

template<typename T>
ostream & LinkedQueue<T>::output(ostream & os)const{
    auto ptr = front;
    while( ptr ){
        os << ptr->data << '\t';
        ptr = ptr->link;
    }
    return os;
}

} // DS
#endif
