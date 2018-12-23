#include "Graphmtx.h"
#include <iostream>

using namespace std;

int main(){
    char* filename=new char[30];
    cout << "please input the filename (less than 30 signals) " << endl;
    cin.getline(filename,30); 
    Graphmtx<char,int> g_mtx(filename,50);
    cout << g_mtx <<endl;
    return 0;
}