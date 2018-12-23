#include <iostream>
using namespace std;

template<typename T>
bool compare(T a, T b);

template<typename T>
void insert_sort(T *&arr,int size,function<bool(T a,T b)>f);

template<typename T>
void bucket_sort(T *&arr,int size, T max,T min,function<bool(T a,T b)>f);


template<typename T>
void bucket_sort(T *&arr,int size, T arr_max,T arr_min,function<bool(T a,T b)>f){
    int bucket_num=size/(5)+1;
    
    struct bucket_node{
        int node_index;
        int bucket_size;
        int current_size=0;
        T *bucket;
        bucket_node(int n,int size,int bucket_num){
            bucket_size=size/bucket_num;
            node_index=n;
            bucket=new T[bucket_size];
        }
        ~bucket_node(){
            delete []bucket;
        }
        void add(T element){
            if(current_size<bucket_size){
                current_size++;
                bucket[current_size-1]=element; 
            }else{
                T *temp=new T[bucket_size*2];
                for(int i=0;i<bucket_size;i++){
                    temp[i]=bucket[i];
                }
                temp[bucket_size]=element;
                delete []bucket;
                bucket=temp;
                current_size=bucket_size+1;
                bucket_size=bucket_size*2;             
            }
        }
    };
    bucket_node **total=new bucket_node*[bucket_num];
    
    for(int i=0;i<bucket_num;i++){
        total[i]=new bucket_node(i,size,bucket_num);
    }
    
    /*注意不要让整数越界*/
    //cout << bucket_num << endl;
    for(int i=0;i<size;i++){ //会出现负数奇怪！！
        //cout << (bucket_num-1)*(arr[i]-arr_min)/(arr_max-arr_min)<<endl;
        //cout << (arr[i]-min)*(bucket_num-1)/(max-min) << endl;
        total[(arr[i]-arr_min)*(bucket_num-1)/(arr_max-arr_min)]->add(arr[i]);
    }
   
    for(int i=0;i<bucket_num;i++){
        insert_sort(total[i]->bucket,total[i]->current_size,f);
    }
    int k=0;
    for(int i=0;i<bucket_num;i++){
        for(int j=0;j<total[i]->current_size;j++){
            arr[k]=total[i]->bucket[j];
            k++;
        }
    }
    delete []total;
}



/*have been tested*/
template<typename T>
void insert_sort(T *&arr,int size,function<bool(T a,T b)>f){
int pre,current,j;
for (pre=0,current=1;current<size;pre++,current++){
for(j=pre;j>=0;j--){
    if(f(arr[current],arr[j])){
        T temp=arr[current];
        for(int k=pre;k>j;k--){
            arr[k+1]=arr[k];
        }
        arr[j+1]=temp;break;
    }
    if(j==0){
        T temp=arr[current];
        for(int k=current-1;k>=j;k--){
            arr[k+1]=arr[k];
        }
    arr[j]=temp;
    }
}
}
}

template<typename T>
bool compare(T a, T b){
    return a>=b?true:false;
}


int main(){
    int size=1000000;
    int *arr=new int[size];
    for(int i=0;i<size;i++){
        arr[i]=rand()%10000+1;
    }
    /*for(int i=0;i<size;i++){
        cout << arr[i] << ";";
    }
    cout << endl;
    cout << "the fucking dividig line"<<endl;*/
    clock_t start=clock();
    //insert_sort<int>(arr,size,compare<int>);
    bucket_sort<int>(arr,size,size,1,compare<int>);
    clock_t ends=clock();
    cout << "Runing time : " <<(double)(ends-start)/CLOCKS_PER_SEC << endl;
    /*for(int i=0;i<size;i++){
        cout << arr[i] << ";";
    }*/
    cout << endl;
    delete []arr;

    return 0;
}