#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;

template<typename T>
void RadixSort(T *arr,int left,int right,int d,function<bool(T a,T b)>f);

template<typename T>
void insert_sort(T *arr,int left,int right ,function<bool(T a,T b)>f);

template<typename T>
bool compare(T a, T b){
    return a>=b?true:false;
}

/*have been tested*/
template<typename T>
int getDigit(T temp,int d){
    int count=1;
    while(temp-pow(10,count)>=0){
        count++;
    }
    //cout << count << "f";
    int dig[count];
    for(int i=count;i>=1;i--){
        dig[i-1]=temp/pow(10,i-1);
        temp=temp-dig[i-1]*pow(10,i-1);
    }
    if(d>count){return 0;}
    else{return dig[d-1];}
}

template<typename T>
void RadixSort(T *arr,int left,int right,int d,function<bool(T a,T b)>f){
    const int radix=10,M=100;
    int i,j,count[radix],p1,p2;
    T *temp=new T[right-left+1];
    if(d<=0){return;}
    if(right-left+1<=M){
        insert_sort(arr,left,right,f);
        return ;
    }
    for(j=0;j<radix;j++){count[j]=0;}
    for(i=left;i<=right;i++){
        count[getDigit(arr[i],d)]++;
    }
    for(j=1;j<radix;j++){
        count[j]=count[j]+count[j-1];
    }
    for(i=left;i<=right;i++){
        j=getDigit(arr[i],d);
        temp[count[j]-1]=arr[i];
        count[j]--;
    }
    for(i=left,j=0;i<=right;i++,j++){
        arr[i]=temp[j];
    }
    delete []temp; 
    /*for(j=0;j<radix;j++){
        cout<< count[j]<< "f;";
    }*/
    for(j=0;j<radix-1;j++){
        p1=count[j];
        p2=count[j+1]-1;
        //cout << p1+left<<"f"<<p2+left << endl;
        if(p2>p1)RadixSort(arr,p1+left,p2+left,d-1,f);
    }
    if(right>count[radix-1])RadixSort(arr,count[radix-1]+left,right,d-1,f);
    //cout << count[radix-1]+left<<"f"<< right<< endl;
}


template<typename T>
void insert_sort(T *arr,int left,int right,function<bool(T a,T b)>f){
int pre,current,j;
for (pre=left,current=left+1;current<=right;pre++,current++){
for(j=pre;j>=left;j--){
    if(f(arr[current],arr[j])){
        T temp=arr[current];
        for(int k=pre;k>j;k--){
            arr[k+1]=arr[k];
        }
        arr[j+1]=temp;break;
    }
    if(j==left){
        T temp=arr[current];
        for(int k=current-1;k>=j;k--){
            arr[k+1]=arr[k];
        }
    arr[j]=temp;
    }
}
}
}

int main(){
    //cout << getDigit<int>(100,2) << ";";
    int size=1000;//百位以内数字，一亿个数耗时40秒
    int *arr=new int[size];
    for(int i=0;i<size;i++){
        arr[i]=rand()%10000;
    }
    /*for(int i=0;i<size;i++){
        cout << arr[i] << ";";
    }*/
    cout << endl;
    cout << "the fucking dividig line"<<endl;
    clock_t start=clock();
    RadixSort<int>(arr,0,size-1,4,compare<int>);

    bool test=true;
    for(int i=0;i<size-1;i++){
        if(arr[i]>arr[i+1]){test=false;}
    }
    cout << "the results: " << test<< endl;

    clock_t ends=clock();
    cout << "Runing time : " <<(double)(ends-start)/CLOCKS_PER_SEC << endl;
    /*for(int i=0;i<size;i++){
        cout << arr[i] << ";";
    }*/
    cout << endl;
    delete []arr;
    return 0;
}