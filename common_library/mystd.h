// std library by Yangyao
/*
Yangyao...1226/2017...
Update:
 - write my_deAllocArr, my_deAlloc, my_readList

Yangyao...0115/2018...
New:
 - write my_memoryController;
 - write MYFILE{ delaySec, measureSec};

Yangyao...0201/2018...
 - Refine the include list and using list.
*/

#ifndef MYSTD_H_
#define MYSTD_H_

#define MYLPOS "File: " << __FILE__ << ", Func: " << __FUNCTION__ << ", Line: " << __LINE__
#define MYFPOS "File: " << __FILE__ << ", Func: " << __FUNCTION__
#define CMYLPOS cout << "File: " << __FILE__ << ", Func: " << __FUNCTION__ << ", Line: " << __LINE__
#define CMYFPOS cout << "File: " << __FILE__ << ", Func: " << __FUNCTION__


// Streams
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>


// Containers
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <initializer_list>

// sort ...
#include <algorithm>
// function-object: less<T>, greater<T> ...
#include <functional>

// Memory
// bad_alloc
#include <new>
// swap, pair, move, forward
#include <utility>
// allocator
#include <memory>


// C libraries
#include <cstdlib>
// size_t, ptrdiff_t
#include <cstddef>
// time(), clock(), clock_t, time_t
#include <ctime>
// mathematical functions
#include <cmath>
#include <stdexcept>
// macro assert for debug
#include <cassert>


namespace MYSTD
{

// Streams
// standard IO
using std::cout; using std::cin; using std::endl;
using std::ios_base;
// IO stream
using std::ostream; using std::istream;
using std::ifstream; using std::ofstream;
using std::istringstream; using std::ostringstream;

// Container
using std::string;
using std::vector;

//
using namespace std::placeholders;

// Memory
// exceptions
using std::bad_alloc;
using std::swap;  // always use swap(...);
// Caution: Do not 'using std::move', always call std::move(...);


namespace MYFILE
{
void checkInFile(ifstream & fin, const string str1, const string str2 = "");
void checkOutFile(ofstream & fout,const string str1, const string str2 = "");

template<typename T>
ostream & width_prt(ostream & os, size_t width, const T & x){
    os << std::setw( width ) << x;
    return os;
}


template<typename T>
ostream & width_prt(ostream & os, size_t width, char separator, const T & x){
    os << std::setw( width ) << x;
    return os;
}
template<typename T, typename... Args>
ostream & width_prt(ostream & os, size_t width, char separator ,const T & x, const Args &... args){
    os << std::setw( width ) << x << separator;
    return width_prt(os, width, separator, args...);
}


template<typename T>
ostream & width_prt(ostream & os, std::initializer_list<size_t>::iterator it_width, char separator, const T & x){
    os << std::setw( *it_width++ ) << x;
    return os;
}
template<typename T, typename... Args>
ostream & width_prt(ostream & os, std::initializer_list<size_t>::iterator it_width, char separator, const T & x, const Args &... args){
    os << std::setw( *it_width++ ) << x <<  separator;
    return width_prt(os, it_width, separator, args...);
}
template<typename T, typename... Args>
ostream & width_prt(ostream & os, const std::initializer_list<size_t> &widths, char separator,
    const T & x, const Args &...args){
    return width_prt(os, widths.begin(), separator, args...);
}


template<typename T>
ostream & array_prt(ostream & os, const T * ptr, size_t n, char separator = '\t', size_t ncols = 10){
    for( size_t i = 0; i < n-1; ++i ){
        os << ptr[i] << ( (i%ncols == ncols - 1)?'\n':separator );
    }
    return os << ptr[n-1];
}





}

namespace MYTIME
{
// Yangyao, 0114/2018
// Delay (delayAmount) seconds.
// in -- time to be delayed in [sec]
void delaySec(const int delayAmount );

// Yangyao, 0114/2018
// Test the time consuming for a function;
// For the non-void-input function, use (bind) in <functional> or (lambda) as test function;
// in -- void-input function (func) to be test;
// out-- time consumed in [sec];
/*
// Yangyao, 0418/2018
// This is no longer used, since the new version can replace it.
template <typename T>
double measureSec( T callable ){
    auto t1 = clock();
    callable();
    auto t2 = clock();
    return double(t2-t1)/double(CLOCKS_PER_SEC);
}*/

// Yangyao, 0418/2018
// Test the time consuming for a function, with any number of passed arguments;
// in --callable: function to be test;
//      args: arguments to be passed to callable
// out--time consumed in [sec];
template<typename T, typename... Args>
double measureSec( T callable, Args&&... args ){
    auto t1 = std::clock();
    callable( std::forward<Args>(args)... );
    auto t2 = std::clock();
    return double(t2-t1)/double(CLOCKS_PER_SEC);
}

// Yangyao, 0418/2018
// Similar to measureSec, but calling the callable n times repeatedly.
template<typename T, typename... Args>
double measureSec_repeated( T callable, size_t n ,Args&&... args ){
    auto t1 = std::clock();
    for( size_t i = 0; i < n; ++i ){
        callable( std::forward<Args>(args)... );
    }
    auto t2 = std::clock();
    return double(t2-t1)/double(CLOCKS_PER_SEC);
}


}//end of namespace MYTIME


// these are two functions for allocating memories
// Allocate memory for array
template <typename T>
T * my_alloc(const int size, const string str = "")
{
    if( size <= 0 ){
        cout << __func__  << ":" << str << ": cannot alloc memory for size = " << size << "!" << endl;
        exit(EXIT_FAILURE);
    }
    T * pt;
    try{
        pt = new T [size];
    }catch( bad_alloc & ba ){
        cout << __func__ << ":" << str << ": bad alloc when alloc size = " << size  << "!" << endl;
        exit(EXIT_FAILURE);
    }
    return pt;
}

// Allocate memory for single variable
template <typename T>
T * my_alloc(const string str = "")
{
    T * pt;
    try{
        pt = new T;
    }catch( bad_alloc & ba ){
        cout << __func__ << ":" << str << ": bad alloc when alloc memory!" << endl;
        exit(EXIT_FAILURE);
    }
    return pt;
}

// Deallocate memory for array
// Repair: 0321/2018
//  - a huge bug when set NULL;
template <typename T>
void my_deAllocArr(T * &pt)
{
    if( pt ){
        delete [] pt;
        pt = NULL;
    }
}

// Deallote memory for single variable
// Repair: 0321/2018
//  - a huge bug when set NULL;
template <typename T>
void my_deAlloc(T * &pt)
{
    if( pt ){
        delete pt;
        pt = NULL;
    }
}

// Add: Yangyao 0321/2018
//  - For handling valued-initialization.
template <typename T>
class my_allocator
{
public:
    // Alloc a type T variable
    //  - buff : the buffer for error print.
    //  - args : direct initialization parameters.
    //  - return : pointer to the data
    template<typename... Args>
    static T * alloc(const char * buff, Args &&... args){
        T * ptr = nullptr;
        try{ ptr = new T( std::forward<Args>(args)... ); }
        catch( bad_alloc ){
            CMYFPOS << buff << ": alloc failed!" << endl; exit(EXIT_FAILURE);
        }
        return ptr;
    }
    // Deallocatoe a type T variable
    //  - Should be coorporated with alloc.
    static void deAlloc(T * &ptr){
        if( ptr ){ delete ptr; ptr = nullptr; }
    }
};




// Yangyao, 0114/2018
// class: Control the memory allocation.
// Description:
//  1> Allocate memory when asked;
//  2> Automatically deallocate when destroying the instance;
//  3> Keep all the memory allocation record (pointer location, size of memory);
class my_memoryController
{
private:
    void check_input(unsigned long num, const string & info);
    void check_alloc(void * pt, const string & info);
public:
    typedef std::pair<void *, unsigned long> pair_t;
    typedef std::unordered_map<unsigned long, pair_t> map_t;

    map_t _rec;
    unsigned long _totMem = 0;
    unsigned long _totCt = 0;
public:
    my_memoryController();
    ~my_memoryController();

    template<typename T>
    T * malloc(unsigned long num, const string info = ""){

        check_input( num, info );
        T * pt = (T*)std::malloc( sizeof(T)*num );
        check_alloc( pt, info );

        _rec.emplace( _totCt++, pair_t(pt, sizeof(T)*num) );
        _totMem += sizeof(T) * num;

        return pt;
    }

    template<typename T>
    T * calloc(unsigned long num, const string info = ""){

        check_input(num, info);
        T * pt = (T*)std::calloc( num, sizeof(T) );
        check_alloc(pt, info);

        _rec.emplace( _totCt++, pair_t( pt, sizeof(T)*num ) );
        _totMem += sizeof(T)*num;

        return pt;
    }

    template<typename T>
    T * realloc(unsigned long id, unsigned long num, const string info = ""){
        auto it = _rec.find( id );
        if( it == _rec.end() ){
            cout << __func__ << ":" << info << ": can not realloc because input is not in the record list!" << endl;
        }

        check_input(num, info);
        T * pt = (T*)std::realloc( it->second.first, sizeof(T)*num );
        check_alloc(pt,info);

        _totMem += sizeof(T)*num - it->second.second;
        it->second.first = pt;
        it->second.second = sizeof(T)*num;

        return pt;
    }

    void * externalloc(void * pt, unsigned long sizeBuff = 0);

    void free(unsigned long id, const string info);
    void free();

    unsigned long get_lastRecId()const;
    ostream & show_info(ostream & os = cout, const int tag = 0)const;
};




template <typename T>
void
my_readList(const string fname, T * arr, const int size)
{
    if( size < 1 ){
        cout << __func__ << ": input size " << size << " should >= 1!" << endl;
        exit(EXIT_FAILURE);
    }

    ifstream fin( fname.c_str() );
    MYFILE::checkInFile( fin, __func__, fname );

    for (int i = 0; i < size; ++i)
    {
        fin >> arr[i];
    }

    if( !fin ){
        cout << __func__ << ": file " << fname << " does not have enough data item, expect " << size << " items!" << endl;
        exit(EXIT_FAILURE);
    }

    T tmp;
    if( fin >> tmp ){
        cout << __func__ << ": file " << fname << " has data item more than expect " << size << '!' << endl;
        exit(EXIT_FAILURE);
    }

    fin.close();
}

template <typename T>
void my_readList(ifstream & fin, T * arr, const int size)
{
    if( size < 1 ){
        cout << __func__ << ": input size " << size << " should >= 1!" << endl;
        exit(EXIT_FAILURE);
    }

    if( !fin ){
        cout << __func__ << ": input ifstream err!" << endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; ++i)
    {
        fin >> arr[i];
    }

    if( !fin ){
        cout << __func__ << ": input ifstream does not have enough data term!" << endl;
        exit(EXIT_FAILURE);
    }

}



template <typename T>
bool writeBlk(ofstream & fout, const T * data, const int size)
{
    if( size <= 0 ){
        cout << __func__ << ": Error! can not write " << size << " data items!" << endl;
        exit(EXIT_FAILURE);
    }


    fout.write( (char*)&size, sizeof(int) );
    fout.write( (char*) data, sizeof(T)*size );
    fout.write( (char*)&size, sizeof(int) );

    return bool(fout);
}


template <typename T>
bool readBlk(ifstream & fin, T * data, int & size, const int max_size)
{
    if( size <= 0 ){
        cout << __func__ << ": Error! can not read " << size << " data items!" << endl;
        exit(EXIT_FAILURE);
    }

    int tmp1, tmp2;

    fin.read( (char *)&tmp1, sizeof(int) );
    if( tmp1 > max_size ){
        if( data != NULL ){
            delete [] data;
        }

        data = my_alloc<T>(tmp1, __func__);
    }
    fin.read( (char *)data, sizeof(T)*tmp1 );
    fin.read( (char *)&tmp2, sizeof(int) );

    if( tmp1 != tmp2 ){
        cout << __func__ << ": blksize " << tmp1 << "/ " << tmp2 << " don't match?" << endl;
        exit(EXIT_FAILURE);
    }

    size = tmp1;

    return bool(fin);
}





}

#endif
