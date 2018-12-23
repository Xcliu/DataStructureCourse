#include <iostream>
#include <math.h>
using namespace std;

template<typename T>
bool compare(T a, T b);

template<typename T>
void usual_insert(T *&arr,int pre,int current,function<bool(T a,T b)> f);

template<typename T>
void binary_insert(T *&arr,int pre,int current,function<bool(T a,T b)> f);

template<typename T>
void binary_insert_sort(T *& arr,int size,function<bool(T a,T b)> f);


template<typename T>
bool compare(T a, T b){
    return a>=b?true:false;
}

template<typename T>
void binary_insert_sort(T *& arr,int size,function<bool(T a,T b)> f){
    int pre,current;
    for(pre=0,current =1;current<size;pre++,current++){
        binary_insert<T>(arr,pre,current,f);
    }
}

template<typename T>
void usual_insert(T *&arr,int pre,int current,function<bool(T a,T b)> f){
    for(int i=0;i<=pre;i++){
        if(f(arr[i],arr[current])){
            T temp=arr[current];
            for(int j=current-1;j>=i;j--){
                arr[j+1]=arr[j];    
            }
            arr[i]=temp;
            break;
        }
    }
}

template<typename T>
void binary_insert(T *&arr,int pre,int current,function<bool(T a,T b)> f){
    int low,high,middle;
    low=0;high=pre;
    while(low<=high){
        middle=(low+high)/2;
        if(compare(arr[current],arr[middle])){
            low=middle+1;
        }else{
            high=middle-1;
        }
    }
    T temp=arr[current];
    for(int j=current-1;j>=low;j--){
        arr[j+1]=arr[j];    
    }
    arr[low]=temp;
}


int main(){
    int size=100;
    int *arr=new int[size];

    for(int i=0;i<size;i++){
        arr[i]=rand()%size+1;
    }
    for(int i=0;i<size;i++){
        cout << arr[i] << ";";
    }
    cout << endl;
    cout << "the fucking dividig line"<<endl;
    binary_insert_sort<int>(arr,size,compare<int>);

    for(int i=0;i<size;i++){
        cout << arr[i] << ";";
    }
    cout << endl;
    delete []arr;
    return 0;
}
