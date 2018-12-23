#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<time.h>
using namespace std;

template<typename T>
void max_heap(T* A,int front,int rear,function< bool( T a, T b) > f);

template<typename T>
void heap_sort(T* A,int front,int rear,function< bool( T a, T b) > f);

template<typename T>
void updata_maxhep(T* A,int front,int rear,function< bool( T a, T b) > f);

template<typename T>
bool compare(T a,T b);

/*compare*/
template<typename T>
bool compare(T a,T b){
    return (a>=b)?true:false;
}

/*Have been tested;used creat a totally new max hep*/
template<typename T>
void max_heap(T* A,int front,int rear,function< bool( T a, T b) > f){
    int fuck=(rear-1)/2;
    int s_nd;
    for(s_nd=fuck;s_nd>=0;s_nd--){
        int max_index;T temp;
        int last_index=s_nd;
        while((last_index+1)*2-1<=rear){
            if((last_index+1)*2>rear){max_index=(last_index+1)*2-1;}
            else{
                if(f(A[(last_index+1)*2],A[(last_index+1)*2-1])){max_index=(last_index+1)*2;}
                else{max_index=(last_index+1)*2-1;} 
            }
            if(f(A[max_index],A[last_index])){
                temp= A[last_index];A[last_index]=A[max_index];A[max_index]=temp;
                last_index=max_index;//attention
            }
            else{last_index=rear+1;}//直接退出while循环
        }
    }
}

template<typename T>
void updata_maxhep(T* A,int front,int rear,function< bool( T a, T b) > f){
    int last=0;
    int max_index;
    T temp;
    while((last+1)*2-1<=rear){
        if((last+1)*2>rear){max_index=(last+1)*2-1;}
        else{
            if(f(A[(last+1)*2-1],A[(last+1)*2])){
                max_index=(last+1)*2-1;
            }else{max_index=(last+1)*2;}
        }
        if(f(A[max_index],A[last])){
            temp=A[max_index];A[max_index]=A[last];A[last]=temp;
            last=max_index;
        }else{last=rear+1;}
    }
}


template<typename T>
void heap_sort(T* A,int front,int rear,function< bool( T a, T b) > f){
    int i;int last=rear;T temp;
    int size=rear-front+1;
    max_heap(A,0,last,f);
    temp=A[last];
    A[last]=A[0];
    A[0]=temp;
    for(i=0;i<size-1;i++){
        updata_maxhep(A,0,last-1,f);
        temp=A[last-1];
        A[last-1]=A[0];
        A[0]=temp;
        last--;
    }
    
}




int main(){
    clock_t start=clock();
    const int size=pow(10,7);int i;
    /*when the magnitude of total number is 10^7,it takes 2.93 seconds 
    */
    int* A=new int[size];
    for(i=0;i<size;i++){
        A[i]=rand()%40+1;//generate random number from 1 to 40
    }
    heap_sort<int>(A,0,size-1,compare<int>);
    //for(i=0;i<size;i++){cout << A[i] << ";";}
    //cout << endl;
    delete []A;
    clock_t ends=clock();
    cout << "Runing time : " <<(double)(ends-start)/CLOCKS_PER_SEC << endl;
    return 0;

}