#include <iostream>

using namespace std;

void test_c(){
    int a = 1;
    if( a > 0 ){
        cout <<  a << endl ;
    }else if( a == -1 ){
        cout << -1 << endl;
    }else{
        cout << -2 << endl;
    }


    for (int i = 0; i < 5; ++i)
    {
        cout << i << endl;
    }

    int i = 0;
    while( i <5){
        cout << i << endl;
        ++i;
    }

    int j = 0;
    do{
        cout << j << endl;
        ++j;
    }while( j<5 );


}



int main(int argc, char const *argv[])
{
    test_c();
    return 0;
}
