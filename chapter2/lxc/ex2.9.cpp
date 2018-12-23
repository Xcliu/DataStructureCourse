#include<iostream>
using namespace std;

void exch_array(int m,int n,int *A){
	const int k=m+n;
	int B[k];
	for(int i=0;i<m+n;i++){
	   if(i<m){B[n+i]=A[i];}
	   B[i-m]=A[i];
	}
        for(int i=0;i<m+n;i++){cout << B[i] << ";";}


}

int main(){
   int m=5;int n=5;
   int *A=new int[m+n];
   for(int i=0;i<m+n;i++){A[i]=i;}
   exch_array(m,n,A);	



   return 0;	
}
