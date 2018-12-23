#include<iostream>

//#include"LinearList.h"
#include"SeqList.h"


using namespace std;
//template class SeqList<int>;

int main(){
    SeqList<int> SL;
    SL.input();
    SL.output();
    int a=3;
    cout << SL.Search(a) << endl;
    return 0;
}
