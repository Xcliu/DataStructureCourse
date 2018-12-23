#include "mystd.h"
#include <cstdlib>


namespace MYSTD
{

namespace MYFILE
{



void checkInFile(ifstream & fin, const string str1, const string str2)
{
    if( !fin.is_open() ){
        cout << "In function " << str2 << ": " << " input file " << str1 << " cannot open!" << endl;
        exit(EXIT_FAILURE);
    }
}

void checkOutFile(ofstream & fout, const string str1, const string str2)
{
    if( !fout.is_open() ){
        cout << "In function " << str2 << ": " << " output file " << str1 << " cannot open!" << endl;
        exit(EXIT_FAILURE);
    }
}



}// name space MYFILE


namespace MYTIME
{

void delaySec(const int delayAmount )
{
    if( delayAmount < 0 ){
        cout << __func__ << ": cannot delay negative " << delayAmount << " seconds!" << endl;
        exit(EXIT_FAILURE);
    }

    time_t t_end = time(NULL) + delayAmount;

    while( time(NULL) < t_end ){ ; }
}




}// end of namespace MYTIME



my_memoryController::my_memoryController()
{}

my_memoryController::~my_memoryController()
{
    free();
}

void my_memoryController::check_input(unsigned long num, const string & info)
{
    if( num == 0 ){
        cout << info << ": input " << num << " should > 0!" << endl;
        exit(EXIT_FAILURE);
    }
}

void my_memoryController::check_alloc(void * pt, const string & info)
{
    if( pt == NULL ){
        cout << info << ": allocation failed!" << endl;
        exit(EXIT_FAILURE);
    }
}

void * my_memoryController::externalloc(void * pt, unsigned long sizeBuff)
{
    _rec.emplace( _totCt++, pair_t(pt, sizeBuff) );

    _totMem += sizeBuff;

    return pt;
}

void my_memoryController::free( unsigned long id, const string info )
{
    auto it = _rec.find( id );
    if( it == _rec.end() ){
        cout << __func__ << ":" << info << ": can not free because input is not in the record list!" << endl;
    }

    std::free( it->second.first );
    _totMem -= it->second.second;

    _rec.erase( it );
}

void my_memoryController::free()
{
    for( auto & i: _rec ){
        std::free(i.second.first);
        _totMem -= i.second.second;
    }

    if( _totMem != 0 ){
        cout << __func__ << ": free failed! Remain " << _totMem << " bytes!" << endl;
    }

    _rec.clear();
}

unsigned long my_memoryController::get_lastRecId()const
{
    if( _totCt == 0 ){
        cout << __func__ << ": empty memory holder!" << endl;
        exit(EXIT_FAILURE);
    }
    return _totCt - 1;
}

ostream & my_memoryController::show_info(ostream & os, const int tag)const
{
    os << "------class my_memoryController------" << endl;
    os  << "Total memory allocated: " << _totMem << endl
        << "Total number of records: " << _totCt << ", remain: " << _rec.size() << endl;

    if( tag == 1 ){
        os << "Records list:" << endl;

        if( _rec.size() == 0 ){ os << "\tEmpty" << endl; }

        unsigned long ct = 0;
        for( const auto & i: _rec){
            os << "<" << ct++ << ">\t" << i.first << "\t" << i.second.first << "\t" << i.second.second << endl;
        }
    }

    return os;
}



}//namespace MYSTD
