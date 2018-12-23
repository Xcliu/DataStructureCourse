/*have been tested*/
template<typename T>
void insert_sort(T *arr,int size,function<bool(T a,T b)>f){
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