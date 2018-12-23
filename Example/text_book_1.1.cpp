#include<iostream>

#define DataSize 100

using namespace std;

typedef int DataType;

typedef struct{ //结构体数据类型 与class 很类似
       DataType data[DataSize];
       int length;



}DataList;


int main(int argc, char const *argv[]){
    DataList D;
   // D.data;
    for(int i=0;i<100;++i){
	    D.data[i]=i;
	    cout << D.data[i] <<";";
    }
    return 0;
    

}
