#include<iostream>
#include"link_node.h"
int get_max(List<int>& ls,int n);
int get_szie(List<int>& ls,int i=1);
int get_average(List<int>& ls,int i=1);

using namespace std;
int sum=0;
int get_sum(List<int>& ls, int i=1){
    int x;
    if(ls.Locate(i)==NULL){return sum;}
    ls.getData(i,x);
    sum=x+get_sum(ls,i+1);
    return sum;       
}


int get_size(List<int>& ls,int i=1){
    if(ls.Locate(i)->link==NULL){return i;}
    return get_size(ls,i+1);
}


int get_max(List<int>& ls,int n){
    int x;
    if(n==1){ls.getData(1,x);return x;}
    int tmp=get_max(ls,n-1);
    ls.getData(n,x);
    if(x>tmp){return x;}
    else{return get_max(ls,n-1);}
}

int main(){
    List<int> ls;
    const int size=5;
    int A[size]={3,4,11,4,5}; 
    ls.create(A,size);
    double av=double(get_sum(ls))/double(get_size(ls));
    cout << av ;
    return 0;
}
