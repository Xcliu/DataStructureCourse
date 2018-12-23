#ifndef DUAL_STACK_H
#define DUAL_STACK_H

#include<iostream>
#include<assert.h>
const int default_size=50;
template<typename T>
class DualStack{
    private:
    T* elements;
    int top_1,top_2;
    int MaxSize;
    public:
    DualStack();
    ~DualStack(){delete[] elements;}
    bool IsEmpty(int tag)const;
    bool IsFull()const;
    bool Push(const T& x,int tag);
    bool Pop(T& x,int tag);
};

template<typename T>
DualStack<T>::DualStack():top_1(-1),top_2(default_size),MaxSize(default_size){
    elements=new T[default_size];
    assert(elements!=NULL);
}
template<typename T>
bool DualStack<T>::IsEmpty(int tag)const{
    if(tag==1){
        if(top_1==-1){return true;}
    }
    else{
        if(top_2==default_size){return true;}
    }
    return false;
}

template<typename T>
bool DualStack<T>::IsFull()const{
    if(top_1+1==top_2){return true;}
    return false;
}
template<typename T>
bool DualStack<T>::Push(const T& x,int tag){
    if(IsFull()==true){return false;}
    if(tag==1){
        elements[++top_1]=x;
    }
    if(tag==2){
        elements[--top_2]=x;
    }
    return false;
}

template<typename T>
bool DualStack<T>::Pop(T& x,int tag){
    if(IsEmpty(tag)==true){return false;}
    if(tag==1){
        x=elements[top_1--];
    }
    else{x=elements[top_2++];}
    return true;
}

#endif