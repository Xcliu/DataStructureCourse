#include "mystd.h"
using namespace MYSTD;



double add(double a, double b){
    double c = 0;
    for(unsigned i = 0; i < 10000000; ++i) {
        c += a+b;
    }
    cout << c << endl;
    return c;
}

void test_time(){
    cout << MYTIME::measureSec(add, 1., 2.) << endl;
    cout << MYTIME::measureSec_repeated(add, 10 ,1., 2.) << endl;
}


int main(int argc, char const *argv[]){
    test_time();
    return 0;
}
