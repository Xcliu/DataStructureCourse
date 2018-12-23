#include <iostream>
using namespace std;


// overload function: can have same name, but input should be different

// returnT, name, inT
// body
int add(int a, int b){
    return a+b;
}

double add(double a, double b){
    return a+b;
}
//模版函数的写法
template<typename T>
T add( T a, T b ){
    T res = a+b;
    return res;
}



int main(int argc, char const *argv[])
{
    int a = 2, b=3;
    double c = 2., d = 3.1;
    //cout << add(a,b) << endl;
    //coresout << add(c,d) << endl;
    cout << add<int>(a,d) << endl;
    cout << add<double>( a,d ) << endl;//模版函数的调用方式
    return 0;
}
