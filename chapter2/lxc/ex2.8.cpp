#include<iostream>
#include<cmath>
using namespace std;

void divide(int array_size,int *A){ //怎样把数组作为函数的输入
     int *C=new int [array_size];
     int *B=new int [array_size];
     int index_B=0;
     int index_C=0;
     for(int i=0;i<array_size;i++){
        //cout << A[i] << ";";
	if(A[i]>0){B[index_B]=A[i];index_B++;}
	if(A[i]<0){C[index_C]=A[i];index_C++;}
     }
    
     for(int i=0;i<index_B;i++){cout << B[i] << ","; }
     for(int i=0;i<index_C;i++){cout << C[i] << ";"; }


}

int main(){
  
  int array_size=90;	
  int *A=new int [array_size];//初始化动态数组有没有更直接的方式
  for(int i=0;i<=array_size;i++){A[i]=pow(-1,i+1)*(i+1);}
  divide(array_size,A);

	
  return 0;
}
