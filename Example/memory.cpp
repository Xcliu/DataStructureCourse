#include <iostream>
using namespace std;




void array(){

    int arr[5];//C++中内置数组的长度必须在声明时确定，只能通过动态内存分配的方式实现长度可变的数组

/*
    int size = 5;
    int arr[size]; //size作为变量不能表示数组长度
    const size =5
    int arr[size]//这样的语法才是内置C++数组所允许的
*/

    for (int i = 0; i < 5; ++i){//for(循环参量初始值;循环进行的条件;参量直增)
        arr[i] = i;
    }

    for (int i = 0; i < 5; ++i)
    {
        cout << arr[i] << endl;
    }
}


void dynamic_mem(int size){      //动态内存分配的具体实现函数
    int *p = new int [size];
/*
1. new() 分配这种类型的一个大小的内存空间,并以括号中的值来初始化这个变量;

2. new[] 分配这种类型的n个大小的内存空间,并用默认构造函数来初始化这些变量;  
*/
    for (int i = 0; i < size; ++i)
    {
        p[i] = i;
    }

    for (int i = 0; i < size; ++i)
    {
        cout << p[i] << endl;
    }

    delete [] p;
}


int main(int argc, char const *argv[])
{
    //array();
    int size;
    cin >> size;
    dynamic_mem( size );
    return 0;
}
