#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
/*Declare function*/
template<typename T>
void merger_sort(T* &A,int front,int rear);

template<typename T> 
bool compare(T num_a,T num_b);

template<typename T>
void combine_sort(T* A,int beg_i,int end_i,int beg_j,int end_j,function< bool( T num_a , T num_b ) > f);

template<typename T>
void merger_any(T* A,int front,int rear);


/*In order to realize any number*/
template<typename T>
void merger_any(T* A,int front,int rear){
   int tot=rear-front+1;int up_num;int i;
   int beg_num=0;int fuck_impro;int flag=0;
   while(tot>=2){//开始这里没有等于2 在n=10,18类似这种数的时候出错！！!
        fuck_impro=log(tot)/log(2);
        up_num=pow(2,fuck_impro);
        T *temp=new T[up_num];
        for(i=0;i<up_num;i++){temp[i]=A[beg_num+i];}
        merger_sort<T>(temp,0,up_num-1);
        for(i=0;i<up_num;i++){A[beg_num+i]=temp[i];}
        delete []temp;
        beg_num=beg_num+up_num;
        tot=tot-up_num;
        if(flag==1){
            combine_sort<T>(A,0,beg_num-up_num-1,beg_num-up_num,beg_num-1,compare<T>);
        }
        flag=1;
   }
   if(tot==1){
       combine_sort<T>(A,0,rear-1,rear,rear,compare<T>);
   }
}


/*Merger sort function*/
template<typename T>
void merger_sort(T* &A,int front,int rear){
    int tot=rear-front+1;
    int circ_num=log(tot)/log(2);
    int i;int j;
    /*This part is only valid for the total number equal 2^n */
    for(i=0;i<circ_num;i++){
        int k=0;
        for(j=0;j<tot/pow(2,i+1);j++){
            combine_sort<T>(A,k,k+pow(2,i)-1,k+pow(2,i),k+2*pow(2,i)-1,compare<T>);
            k=k+pow(2,i+1);
        } 
    }
    /*Attention to the limitation!*/ 
}

/*Have been tested!*/
template<typename T>
void combine_sort(T* A,int beg_i,int end_i,int beg_j,int end_j,function< bool( T num_a , T num_b ) > f){//ensure beg_i<beg_j
    int size=end_i+end_j-beg_i-beg_j+2;
    T* temp=new T[size];//
    int k;
    int temp_beg=beg_i;
    for(k=0;k<size;k++){
        if(beg_i>end_i){temp[k]=A[beg_j];beg_j++;}
        else if(beg_j>end_j){temp[k]=A[beg_i];beg_i++;}
        else{
            if(f(A[beg_i],A[beg_j])==true){
            temp[k]=A[beg_j];beg_j++;
            }
            else{temp[k]=A[beg_i];beg_i++;}
        }
    }
    for(k=0;k<size;k++){A[temp_beg+k]=temp[k];}
    delete []temp;
}
/*Have been tested*/
template<typename T> 
bool compare(T num_a,T num_b){
    if(num_a<num_b){return true;}
    else{return false;}
}


/*Main function*/
int main(){
    clock_t start=clock();
    const int array_size=10;//pow(1,1);
    /*when the magnitude of total number is 10^9*,it takes 476.945 seconds */
    int i;
    int* A=new int[array_size];
    for(i=0;i<array_size;i++){
        A[i]=rand()%40+1;//generate random number from 1 to 40
    }
    /*   */
    merger_any<int>(A,0,array_size-1);
    
    
    for(i=0;i<array_size;i++){cout << A[i] << ";";}
    cout << endl;
    delete []A;
    clock_t ends=clock();
    cout << "Runing time : " <<(double)(ends-start)/CLOCKS_PER_SEC << endl;
    return 0;
}
