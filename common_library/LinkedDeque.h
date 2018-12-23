#ifndef LINKEDDEQUE_H_
#define LINKEDDEQUE_H_
#include "Deque.h"
#include "LinkedQueue.h"
namespace DS {


template<typename T>
class LinkedDeque: public Deque<T>,  public LinkedQueue<T>
{
public:
    typedef LinkedQueue<T> super_type;
    typedef typename super_type::size_type size_type;
    typedef typename super_type::diff_type diff_type;
    typedef typename super_type::value_type value_type;
    typedef typename super_type::ptr_type ptr_type;
    typedef typename super_type::node_type node_type;
    typedef typename super_type::alloc_type alloc_type;

    LinkedDeque(){}
    LinkedDeque(const std::initializer_list<value_type> & lst):super_type(lst){}
    virtual ~LinkedDeque(){}
    bool EnQueueHead(const value_type &) override;
    bool DeQueueHead(value_type & x) override{ return DeQueue(x); }
    bool DeQueueHead() override{ return DeQueue(); }
    bool getHead(value_type & x) override{ return getFront(x); }
    value_type & refHead() override{ return refFront(); }
    const value_type & refHead()const override{ return refFront(); }

    bool EnQueueTail(const value_type & x) override{ return EnQueue(x); }
    bool DeQueueTail(value_type &) override;
    bool DeQueueTail() override;
    bool getTail(value_type &) override;
    value_type & refTail() override{ return rear->data; }
    const value_type & refTail()const override{ return rear->data; }

    bool EnQueue(const value_type & x) override{ return super_type::EnQueue(x); }
    bool DeQueue(value_type & x) override{ return super_type::DeQueue(x); }
    bool DeQueue() override{ return super_type::DeQueue(); }
    bool getFront(value_type & x)const override{ return super_type::getFront(x); }
    value_type & refFront() override{ return super_type::refFront(); }
    const value_type & refFront()const override{ return super_type::refFront(); }

    bool IsEmpty()const override{ return super_type::IsEmpty(); }
    bool IsFull()const override{ return super_type::IsFull(); }
    size_type getSize()const override{ return super_type::getSize(); }
    void makeEmpty()override{ super_type::makeEmpty(); }
    ostream & output(ostream & os = cout)const override{ return super_type::output(os); }
protected:
    using super_type::front;
    using super_type::rear;
    using super_type::allocator;
};

template<typename T>
bool LinkedDeque<T>::EnQueueHead(const value_type & x){
    front = allocator.alloc( __func__, x, front );
    if( !rear ){ rear = front; }
    return true;
}

template<typename T>
bool LinkedDeque<T>::DeQueueTail(value_type & x){
    if( IsEmpty() ){ return false; }
    if( front == rear ){
        x = front->data;
        allocator.deAlloc( front );
        front = rear = nullptr;
    }else{
        auto ptr = front;
        while( ptr->link != rear ){ ptr = ptr->link; }
        x = rear->data;
        allocator.deAlloc( rear );
        rear = ptr; rear->link = nullptr;
    }
    return true;
}

template<typename T>
bool LinkedDeque<T>::DeQueueTail(){
    if( IsEmpty() ){ return false; }
    if( front == rear ){
        allocator.deAlloc( front );
        front = rear = nullptr;
    }else{
        auto ptr = front;
        while( ptr->link != rear ){ ptr = ptr->link; }
        allocator.deAlloc( rear );
        rear = ptr; rear->link = nullptr;
    }
    return true;
}
template<typename T>
bool LinkedDeque<T>::getTail(value_type & x){
    if( IsEmpty() ){ return false; }
    x = rear->data;
    return true;
}





} // DS
#endif
