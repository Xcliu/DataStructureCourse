#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <seq_stack.h>
using namespace std;
/**/
template<typename T>
bool compare(T a,T b);

template<typename T>
void quick_sort_rec(T *A,int p,int r,function<bool(T a,T b)>f);

template<typename T>
void quick_sort_nrec(T *A,int p,int r,function<bool(T a,T b)>f);

template<typename T>
int partition(T *A,int p,int r,function<bool(T a,T b)>f);

template<typename T>
void random_pivot(T *A,int p,int r);

/**/
template<typename T>
bool compare(T a,T b){
    return (a>=b)?true:false;
}

template<typename T>
int partition(T *A,int p,int r,function<bool(T a,T b)>f){
    T temp;
    random_pivot(A,p,r);//这样的随机化方式为什么会出错？
    T x=A[r];
    int i=p-1;
    for (int j=p;j<r;j++){
        if(f(x,A[j])){
            i++;
            temp=A[i];A[i]=A[j];A[j]=temp;
        }
    }
    temp=A[i+1];A[i+1]=A[r];A[r]=temp;
    return i+1;
}

template<typename T>
void random_pivot(T *A,int p,int r){
    int i=rand()%(r-p+1)+p;
    T temp;
    temp=A[r];A[r]=A[i];A[i]=temp;
}

template<typename T>
void quick_sort_rec(T *A,int p,int r,function<bool(T a,T b)>f){
    while(p<r){
        int q=partition(A,p,r,f);
        quick_sort_rec(A,p,q-1,f);//怎样写成完全非递归？
        p=q+1;
    }
}

template<typename T>
void quick_sort_nrec(T *A,int p,int r,function<bool(T a,T b)>f){
    int q=partition(A,p,r,f);
    SeqStack<int> beg;
    SeqStack<int> end;
    beg.Push(p);end.Push(q-1);
    int beg_index=q+1;int end_index=r;
    while(!(beg.IsEmpty() && end.IsEmpty() )|| end_index>beg_index){
        if(end_index>beg_index){
            q=partition(A,beg_index,end_index,f);
            if((q-1)>beg_index){
                beg.Push(beg_index);end.Push(q-1);
                }
            beg_index=q+1;
        }else{
            beg.Pop(beg_index);end.Pop(end_index);
        }
    }
}


int main(){
    clock_t start=clock();
    const int size=100;int i;//递归和用栈实现的非递归耗时区别不大
    int* A=new int[size];
    for(i=0;i<size;i++){
        A[i]=rand()%size+1;
    }


    quick_sort_nrec<int>(A,0,size-1,compare<int>);
    for(i=0;i<size;i++){cout << A[i] << ";";}
    cout << endl;


    delete []A;
    clock_t ends=clock();
    cout << "Runing time : " <<(double)(ends-start)/CLOCKS_PER_SEC << endl;
    return 0;
}

