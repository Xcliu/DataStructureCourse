#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;

template<typename T>
bool compare(T a, T b);

template<typename T>
void shell_sort(T * arr,int size,function<bool(T a,T b)> f);

template<typename T>
bool compare(T a, T b){
    return a>=b?true:false;
}

template<typename T>
void shell_sort(T * arr,int size,function<bool(T a,T b)> f){
    int gap=size/3+1;
    while(1){
        for(int i=0;i<gap;i++){
            int pre,current;
            for(pre=i,current=pre+gap;current<size;pre+=gap,current+=gap){
                for(int j=pre;j>=i;j-=gap){
                    if(f(arr[current],arr[j])){//这里插入算法（从大到小）一定要从后面插入否则会越来越慢
                        T temp=arr[current];//一般的插入算法没有上面的要求（已经排好时复杂度最大（从前面插入））
                        for(int k=pre;k>j;k-=gap){
                            arr[k+gap]=arr[k];
                        }
                        arr[j+gap]=temp;break;
                    }
                    if(j==i){
                        T temp=arr[current];
                        for(int k=current-gap;k>=j;k-=gap){
                            arr[k+gap]=arr[k];
                        }
                        arr[j]=temp;
                   }
                }
            }
        }
        if(gap==1){break;}
        gap=gap/3+1;    
    }
}
int main(){
    int size=1000000;
    int *arr=new int[size];
    for(int i=0;i<size;i++){
        arr[i]=rand()%size+1;
    }
    /*for(int i=0;i<size;i++){
        cout << arr[i] << ";";
    }
    cout << endl;*/
    cout << "the fucking dividig line"<<endl;
    clock_t start=clock();
    shell_sort<int>(arr,size,compare<int>);
    clock_t ends=clock();
    cout << "Runing time : " <<(double)(ends-start)/CLOCKS_PER_SEC << endl;
    /*for(int i=0;i<size;i++){
        cout << arr[i] << ";";
    }
    cout << endl;*/
    delete []arr;
    return 0;
}
