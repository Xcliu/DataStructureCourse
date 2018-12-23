#ifndef DEQUE_H_
#define DEQUE_H_
#include "Queue.h"
namespace DS {


template<typename T>
class Deque: public Queue<T>
{
public:
    typedef Queue<T> super_type;
    typedef typename super_type::size_type size_type;
    typedef typename super_type::diff_type diff_type;
    typedef typename super_type::value_type value_type;

    Deque(){}
    virtual ~Deque(){}
    virtual bool EnQueueHead(const value_type &) =0;
    virtual bool DeQueueHead(value_type &) =0;
    virtual bool DeQueueHead() =0;
    virtual bool getHead(value_type &) =0;
    virtual value_type & refHead() =0;
    virtual const value_type & refHead()const =0;
    virtual bool EnQueueTail(const value_type &) =0;
    virtual bool DeQueueTail(value_type &) =0;
    virtual bool DeQueueTail() =0;
    virtual bool getTail(value_type &) =0;
    virtual value_type & refTail() =0;
    virtual const value_type & refTail()const =0;
};



} // DS
#endif
