#include<iostream>
#include"link_stack.h"
using namespace std;
int re_akm(int m,int n);
int nonre_akm(int m,int n);

int re_akm(int m,int n){
    if(m==0){return n+1;}
    if(m!=0&&n==0){return re_akm(m-1,1);}
    if(m!=0&&n!=0){return re_akm(m-1,re_akm(m,n-1));}
    return -1;
}

struct Fucking_node{
    int m;int n;
};

int nonre_akm(int m,int n){
    LinkedStack<Fucking_node> lk_st;
    Fucking_node pir;
    pir.m=m;pir.n=n;
    lk_st.Push(pir);
    while(1){
        lk_st.Pop(pir);
        if(pir.m==0){
            int k=pir.n+1;
            if(lk_st.IsEmpty()==false){
                lk_st.Pop(pir);pir.n=k;lk_st.Push(pir);
            }
            else{ return k;}
        }
        else if(pir.n==0){
            pir.m=pir.m-1;pir.n=1;
            lk_st.Push(pir);
        }
        else{
            pir.m=pir.m-1;lk_st.Push(pir);
            pir.m=pir.m+1,pir.n=pir.n-1;lk_st.Push(pir);
        }
    }
}


int main(){
    cout << re_akm(3,2) << endl;
    return 0;
}
