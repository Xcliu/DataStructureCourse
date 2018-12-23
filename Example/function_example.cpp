#include <mystd.h>
using namespace MYSTD;


/*将函数和类作为函数形参传入函数的方式*/
/*#include <iostream>
using namespace std;
*/
template<typename T>
bool compare( const T & a, const T & b){
    return a < b;
}


template<typename T>
void print(const T & a, const T & b, bool (*f)(const T &, const T &) ){
/*
C++中数组名是通过内部处理成为指针，而函数名自然就是一个指针，但是类名并不是。
*/

    if( f( a, b ) ){
        cout << "a<b" << endl;
    }else{
        cout << "a>=b" << endl;
    }
}



template<typename T>
void print2(const T & a, const T & b, std::function< bool( const T &, const T & ) > f ){
/*
lambda 表达式的写法
*/
    if( f( a, b ) ){
        cout << "a<b" << endl;
    }else{
        cout << "a>=b" << endl;
    }
}

template<typename T>
class Compare3
{
public:
    bool operator()( const T & a, const T & b ){
        return a < b;
    }
};


int main(int argc, char const *argv[]){
    int a = 5,b=2;
    /*
    print(a,b, compare<int> );
    
    // 1 function pointer
    print2<int>(a,b, &compare<int> );//这里取指针的地址？用*compare<int>也可以？
    // 2 lambda expression
    */
    auto compare2 = [](const int & a, const int & b)->bool{ return a < b; };
    print2<int>(a,b,compare2 );
    // 3 callable class
    Compare3<int> comp3;
    print2<int>(a,b,comp3);//将类作为参数传给函数

    /*数组名并不是指针的证据
    int c[3] = {1,2,3};
    int * d = new int [3];

    cout << sizeof(c) << endl;
    cout << sizeof(d) << endl;

    delete [] d;
    */

    return 0;
}
