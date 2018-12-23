#ifndef LINEARLIST_H_
#define LINEARLIST_H_
#include "mystd.h"
namespace DS {
using namespace MYSTD;


template<typename T>
class LinearList
{
public:
    typedef std::size_t size_type;
    typedef std::ptrdiff_t diff_type;
    typedef T value_type;
    //typedef T *ptr_type;

    LinearList(){}
    virtual ~LinearList(){}
    virtual size_type Size()const = 0;
    virtual size_type Length()const = 0;
    //virtual ptr_type Search(const value_type &)const = 0;
    //virtual ptr_type Locate(size_type)const = 0;
    virtual bool getData(size_type, value_type &)const = 0;
    virtual bool setData(size_type, const value_type &) = 0;
    virtual bool Insert(size_type, const value_type &) = 0;
    virtual bool Remove(size_type, value_type &) = 0;
    virtual bool IsEmpty()const = 0;
    virtual bool IsFull()const = 0;
    virtual void Sort() = 0;
    virtual istream & input( istream & ) = 0;
    virtual ostream & output( ostream & )const = 0;
    virtual const value_type & operator[](size_type) const = 0;
    virtual value_type & operator[](size_type) = 0;
};





} // DS


#endif
