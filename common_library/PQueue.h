#ifndef PQUEUE_H_
#define PQUEUE_H_
#include "mystd.h"
namespace DS {
using namespace MYSTD;

template<typename T, typename CompareT = std::less<T> >
class PQueue
{
public:
    typedef std::size_t size_type;
    typedef std::ptrdiff_t diff_type;
    typedef T value_type;
    typedef CompareT compr_type;

    PQueue(){}
    virtual ~PQueue(){}
    virtual bool Insert(const value_type &) = 0;
    virtual bool RemoveMin(value_type &) =0;
    virtual bool RemoveMin() =0;
    virtual bool getFront(value_type &)const =0;
    virtual value_type & refFront() =0;
    virtual const value_type & refFront()const =0;
    virtual void makeEmpty() =0;
    virtual bool IsEmpty()const =0;
    virtual bool IsFull()const =0;
    virtual size_type getSize()const =0;
    virtual ostream & output( ostream & os )const =0;
};


} // DS
#endif
