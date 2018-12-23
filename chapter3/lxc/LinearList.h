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
        virtual int Locate(int i)const=0;
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
#endif
