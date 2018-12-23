#include<iostream>
#include"link_stack.h"
using namespace std;
int main(){
    int N=150;int tag=8;int tmp=N;
    if(N<0){cout << "input error" << endl;return 0;}
    LinkedStack<int> lk_st;
    while(N>=tag){
        tmp=N;N=N/tag;lk_st.Push(tmp%tag);
    }
    lk_st.Push(N);
    cout << lk_st;
    return 0;
}