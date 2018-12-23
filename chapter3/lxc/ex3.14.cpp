#include<iostream>
using namespace std;

const int size=5;
int A[size]={1,2,80,9,19};

int fuck_add(int n);
int fuck_max(int n);

int fuck_add(int n){
    if(n==0){return A[0];}
    return A[n]+fuck_add(n-1);
};
/*
int tmp=0;
int fuck_max(int n){
    if(n==0){return A[0];}
    if(A[n]>A[n-1]){tmp=A[n-1];A[n-1]=A[n];A[n]=tmp;}
    return fuck_max(n-1);
} 
*/

int fuck_max(int n){
	if(n==1){return A[0];}
	int tmp=fuck_max(n-1);
	if(tmp>A[n-1]){return tmp;}
	else{return A[n-1];}
}



int main(){
    cout << fuck_max(size) << ";";
    return 0;
}
