#ifndef SEQQUEUE_H_
#define SEQQUEUE_H_
#include "Queue.h"
namespace DS {

template<typename T>
class SeqQueue: public Queue<T>
{
public:
    typedef Queue<T> super_type;
    typedef typename super_type::size_type size_type;
    typedef typename super_type::diff_type diff_type;
    typedef typename super_type::value_type value_type;
    typedef value_type * ptr_type;

    static const size_type defaultSize = 50;

    SeqQueue(size_type sz = defaultSize);
    SeqQueue(const std::initializer_list<value_type> &);
    virtual ~SeqQueue()override{ my_deAllocArr( elements ); }
    bool EnQueue(const value_type &) override;
    bool DeQueue(value_type &) override;
    bool DeQueue() override;
    bool getFront(value_type &)const override;
    value_type & refFront() override;
    const value_type & refFront()const override;
    bool IsEmpty()const override{ return rear == front; }
    bool IsFull()const override{ return (rear + 1) % maxSize == front; }
    size_type getSize()const override{ return ((maxSize + rear) - front) % maxSize; }
    void makeEmpty() override{ rear = front; }
    ostream & output(ostream & os = cout)const override;
protected:
    size_type front, rear;
    ptr_type elements;
    size_type maxSize;
    void overflowProcess();
    size_type next(size_type & i)const{ size_type temp = i; i = (i+1)%maxSize; return temp; }
};


template<typename T>
SeqQueue<T>::SeqQueue(size_type sz):front(0),rear(0),maxSize(sz){
    elements = my_alloc<value_type>( maxSize, __func__ );
}
template<typename T>
SeqQueue<T>::SeqQueue(const std::initializer_list<value_type> & lst):front(0),rear(0){
    maxSize = lst.size() > defaultSize ? ( lst.size() + defaultSize ):( defaultSize );
    elements = my_alloc<value_type>( maxSize, __func__ );
    for( const auto & val : lst ){
        EnQueue(val);
    }
}
template<typename T>
bool SeqQueue<T>::EnQueue(const value_type & x){
    if( IsFull() ){ overflowProcess(); }
    elements[ next(rear) ] = x;
    return true;
}
template<typename T>
bool SeqQueue<T>::DeQueue(value_type & x){
    if( IsEmpty() ){ return false; }
    x = elements[ next(front) ];
    return true;
}
template<typename T>
bool SeqQueue<T>::DeQueue(){
    if( IsEmpty() ){ return false; }
    next(front);
    return true;
}
template<typename T>
bool SeqQueue<T>::getFront(value_type & x)const{
    if( IsEmpty() ){ return false; }
    x = elements[front];
    return true;
}
template<typename T>
typename SeqQueue<T>::value_type & SeqQueue<T>::refFront(){
    return elements[front];
}
template<typename T>
const typename SeqQueue<T>::value_type & SeqQueue<T>::refFront()const{
    return elements[front];
}
template<typename T>
ostream & SeqQueue<T>::output(ostream & os)const{
    auto id = front;
    while( id != rear ){
        os << elements[ next(id) ] << '\t';
    }
    return os;
}
template<typename T>
void SeqQueue<T>::overflowProcess(){
    size_type newSize = maxSize == 0 ?( defaultSize ):( 2*maxSize );
    ptr_type new_elements = my_alloc<value_type>( newSize, __func__ );

    size_type id = front, newid = 0;
    while( id != rear ){
        new_elements[newid++] = elements[ next(id) ];
    }
    my_deAllocArr(elements);
    elements = new_elements;

    maxSize = newSize;
    front = 0; rear = newid;
}





} // DS
#endif
