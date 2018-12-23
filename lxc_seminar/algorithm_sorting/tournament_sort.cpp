#include <iostream>
using namespace std;
template<typename T>
class WinnerTree{
    private:
        int maxSize;
        int n;
        int lowExt;
        int offset;
        void Play(int k,int lc,int rc,function<bool(T a,T b)>f);
    public:
        int *t;
        T *e;
        T maxValue;
        WinnerTree(int Treesize,T max):maxSize(Treesize),n(0){
            maxValue=max;
            t=new int[Treesize];
        }
        ~WinnerTree(){delete []t;}
        bool Initial(T *a,int size,function<bool(T a,T b)>f);
        bool rePlay(int i,function<bool(T a,T b)>f);
        void Update(){e[t[1]]=maxValue;}
        int Winner()const{return (n!=0)?t[1]:0;}
        int Winner(int i)const{return (i<n)?t[i]:0;}
        int Winner(int a,int b,function<bool(T a,T b)>f){return f(e[a],e[b])?b:a;}
};

/*have been tested*/
template<typename T>
bool WinnerTree<T>::Initial(T *a,int size,function<bool(T a,T b)>f){
    if(size>maxSize||size<2){return false;}
    n=size;e=a;
    //for(int i=1;i<=size;i++){cout<< e[i]<< endl;}
    int i,s;
    for(s=1;2*s<=n-1;s+=s);
    lowExt=2*(n-s);offset=2*s-1;
    for(i=2;i<=lowExt;i+=2){
        Play((offset+i)/2,i-1,i,f);
    }
    if(n%2==0){i=lowExt+2;}
    else{
        Play(n/2,t[n-1],lowExt+1,f);
        i=lowExt+3;
    }
    for(;i<=n;i+=2){
        Play((i-lowExt+n-1)/2,i-1,i,f);
    }
    return true;
}

template<typename T>
void WinnerTree<T>::Play(int k,int lc,int rc,function<bool(T a,T b)>f){
    t[k]=Winner(lc,rc,f);
    while(k>1&&k%2!=0){
        t[k/2]=Winner(t[k-1],t[k],f);
        k/=2;
    }

}
template<typename T>
bool WinnerTree<T>::rePlay(int i,function<bool(T a,T b)>f){
    if(i<=0||i>n){return false;}
    int k,lc,rc;
    if(i<=lowExt){
        k=(offset+i)/2;
        lc=2*k-offset;rc=lc+1;
    }else{
        k=(i-lowExt+n-1)/2;
        if(2*k==n-1){lc=t[2*k];rc=i;}
        else{lc=2*k-n+1+lowExt;rc=lc+1;}
    }
    t[k]=Winner(lc,rc,f);
    k/=2;
    for(;k>=1;k/=2){
        t[k]=Winner(t[2*k],t[2*k+1],f);
    }
    return true;
}

template<typename T>
void Tournament_sort(T *arr,T max,const int left,const int right,function<bool(T a,T b)>f){
    int size=right-left+1;
    WinnerTree<T> WT(size,max+1);
    T *data=new T[size+1];
    int i;
    for(i=1;i<=size;i++){data[i]=arr[i-1+left];}
    WT.Initial(data,size,f);

    //WT.Update();
    //cout << WT.maxValue << endl;
    //cout << WT.e[WT.t[1]] << endl;
    //WT.rePlay(WT.t[1],f);

    /*for(int i=1;i<=size;i++){
        cout << WT.Winner(i) <<"f"<<endl;
    }*/
    for(i=1;i<=size;i++){
        arr[i+left-1]=data[WT.Winner()];
        WT.Update();
        WT.rePlay(WT.t[1],f);
        if(data[WT.Winner()]==WT.maxValue){break;}
    }
}


template<typename T>
bool compare(T a, T b){
    return a>=b?true:false;
}


int main(){
    //cout << getDigit<int>(100,2) << ";";
    int size=10000000;int max=1000;//一千万个数耗时5.6秒
    int *arr=new int[size];
    for(int i=0;i<size;i++){
        arr[i]=rand()%max;
    }
    /*for(int i=0;i<size;i++){
        cout << arr[i] << ";";
    }*/
    cout << endl;
    cout << "the fucking dividig line"<<endl;
    clock_t start=clock();
    Tournament_sort<int>(arr,max,0,size-1,compare<int>);
    
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