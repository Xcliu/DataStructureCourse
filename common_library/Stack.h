#ifndef STACK_H_
#define STACK_H_
#include "mystd.h"
namespace DS {
using namespace MYSTD;

template<typename T>
class Stack
{
public:
    typedef std::size_t size_type;
    typedef std::ptrdiff_t diff_type;
    typedef T value_type;

    Stack(){}
    virtual ~Stack(){}
    virtual void Push(const value_type &) = 0;
    virtual bool Pop(value_type &) = 0;
    virtual bool Pop() = 0;
    virtual bool getTop(value_type &)const = 0;
    virtual const value_type & refTop()const = 0;
    virtual value_type & refTop() = 0;
    virtual bool IsEmpty()const = 0;
    virtual bool IsFull()const = 0;
    virtual size_type getSize()const = 0;
    virtual ostream & output(ostream & os)const = 0;
    virtual void makeEmpty() = 0;
};

} // DS
#endif
