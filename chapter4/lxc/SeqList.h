
//enum bool{false,true};
#ifndef LINEARLIST_H 
#define LINEARLIST_H 
template<class T>
class LinearList{
public:
	//LinearList();
	//~LinearList();
        virtual int Size()const=0;
        virtual int Length()const=0;
        virtual int Search(T& x)const=0;
        virtual T Locate(int i)const=0;
        virtual bool getData(int i ,T& x)const=0;
        virtual void setData(int i,T& x)=0;
        virtual bool Insert(int i,T& x)=0;
	virtual bool Remove(int i,T& x)=0;
        /*virtual bool IsEmpty()const=0;
        virtual bool IsFull()const=0;
        virtual void Sort()=0;*/
        virtual void input()=0;
        virtual void output()=0;
        //virtual LinearList<T> operator=(LinearList<T>& L)=0;	
}; 





#include<iostream>
#include<stdlib.h>
//#include"LinearList.h"
using namespace std;
const int DefaultSize=100;
template<class T>
class SeqList:public LinearList<T>{
	public:
		T *data;
		int maxSize;
		int last;
		void reSize(int newSize);
		SeqList(int sz=DefaultSize);
		SeqList(SeqList<T>& L);
		~SeqList(){delete[] data;}
		int Size()const{return maxSize;}
		int Length()const{return last+1;}
	        int Search(T& x)const;
	        T Locate(int i)const;
	        bool getData(int i,T& x)const 
		{if(i>1 && i<=last+1){x=data[i-1];return true;}else return false;}	
		void setData(int i,T& x )
		{if(i>0 && i<=last+1)data[i-1]=x;}
		bool Insert(int i,T& x);
		bool Remove(int i,T& x);
		bool IsEmpty()
		{return (last ==-1)?true : false;}
		bool IsFull()
		{return (last==maxSize-1)?true:false;}
		void input();
		void output();
		SeqList<T> operator=(SeqList<T>& L);
                
		//add for homework
		T del_min();
                void del_special_range(T& x,T& y);
                void del_special_number(T& x);
                void del_rep();
                void combine_order(int m,T A[m],int n,T B[n]);
};               

template<class T>
SeqList<T>::SeqList(int sz){
	if(sz>0){
		maxSize=sz;last=-1;
		data=new T[maxSize];
		if(data==NULL){
		cerr << "动态存储分配错误!" << endl;
		exit(1);
		
		}

	
	}
}


template<class T>
SeqList<T>::SeqList(SeqList<T>& L){
	maxSize=L.Size();last=L.Length()-1;T value;
        data=new T[maxSize];
        if(data==NULL){
	cerr << "动态存储分配错误!" << endl;
        }
	for(int i=1;i<=last+1;i++){
	L.getData(i,value);data[i-1]=value;
	}
}

template<class T>
void SeqList<T>::reSize(int newSize){
	if(newSize<=0){cerr << "the size of array is wrong!" << endl;return;}
	if(newSize !=maxSize){
		T *newarray=new T[newSize];
		if(newarray==NULL){
			cerr << "storage request is refused!" << endl;exit(1);
		}
		int n=last+1;
		T* srcptr=data;
		T* destptr=newarray;
		while(n--){*destptr++=*srcptr++;}
		delete []data;
		data=newarray;maxSize=newSize;
	}

}


template<class T>
int SeqList<T>::Search(T& x)const{
       for(int i=0;i<=last;i++){
	       if(data[i]==x)return i+1;}
       return 0;

}

template<class T>
T SeqList<T>::Locate(int i)const{
	if(i>=1&&i<=last+1){return data[i];}
	else {return 0;}
   
}


template<class T>
bool SeqList<T>::Insert(int i,T& x){
	if(last==maxSize-1){return false;}
	if(i<0||i>last+1){return false;}
	for(int j=last;j>=i;j--){
		data[j+1]=data[j];}
	data[i]=x;
	last++;
	return true;

}

template<class T>
bool SeqList<T>::Remove(int i,T& x){
	if(last==-1){return false;}
	x=data[i-1];
	for(int j=i;j<=last;j++){data[j-1]=data[j];}
	last--;
	return true;
 
}

template<class T>
void SeqList<T>::input(){
     cout << "Begin to creat the seqlist,please input the last index of the list:" << endl;
     while(1){
        cin >> last;
	if(last<=maxSize-1){break;}
	cout <<"The number is error,can't beyond:" << maxSize-1 << ";";
     
     }
     //cout << "input:" << endl;
     for(int i=0;i<=last;i++){
         cout << "input # " << i << endl ;
         //cin >> data[i];//cout << i+1 << endl;
     }
}

template<class T>
void SeqList<T>::output(){
    cout << "The last index of the SeqList is :" << last << endl;
    for(int i=0;i<=last;i++){
       cout << "#" << i+1 << ";" << data[i] << endl;
    }

}
/*
template<class T>
SeqList<T> SeqList<T>::operator=(SeqList<T>& L){
          maxSize=L.Size();last=L.Length()-1;T value;
	  for(int i=0;i<=last;i++){
	  L.getData(i,value);data[i-1]=value;
	  }

}

*/

#endif



