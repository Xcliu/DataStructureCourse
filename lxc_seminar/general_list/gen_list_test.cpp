#include "GeneralList.h"
#include <iostream>
#include <mystd.h>
#include <string>
using namespace MYSTD;

/*
void test(){
    cout << 111 << endl;
    int *i = my_alloc<int>(100, __func__);
    my_deAllocArr(i);

    int *j = new int [100];
    delete [] j;
}

 struct test{
        int *a;
        test(){
            a=new int[3];
            for(int i=0;i<3;i++){
                a[i]=3;
            }
        }
        ~test(){delete []a;}
    };
*/
int main(){
    GenList<char> gl(cin);
    cout << gl.first->info.ref<<endl;
    //cout << "fucking dividing line" <<endl;
    //GenList<char> gl1(cin);
    //cout <<gl.equal(gl.first,gl1.first)<<endl;
    cout <<"length:" <<gl.Length() <<endl;
    cout <<"depth:" <<gl.depth() <<endl;
    return 0;
}