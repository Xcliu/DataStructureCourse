#include<iostream>
#include<stdlib.h>
using namespace std;

template<class T>
struct DblNode{
	T data;int fk;int freq;
	DblNode<T> *lLink,*rLink;
	DblNode(DblNode<T> *left=NULL,DblNode<T> *right=NULL)
		:lLink(left),rLink(right){}
	DblNode(T value,int fk_1=1,int freq_1=0,DblNode<T> *left=NULL,DblNode<T> *right=NULL)
		:data(value),fk(fk_1),freq(freq_1),lLink(left),rLink(right){}
};

template<class T>
class DblList{
	public:
	DblList(T uniqueVal);
	~DblList(){};
	int Length()const;
	bool IsEmpty(){return first->rLink==first;}
	DblNode<T> *getHead()const{return first;}
	void setHead(DblNode<T> *ptr){first=ptr;}
	DblNode<T> *Search(const T& x);
	DblNode<T> *Locate(int i,int d);
	bool Insert(int i,const T& x,int d);
	bool Remove(int i,T& x,int d);
	void inputRear(T endTag);
	void r_output();
	void l_output();
	void fuck();
	void Locate_manage(T& x);
	private:
	DblNode<T> *first;
};

template<class T>
DblList<T>::DblList(T uniqueVal){
	first=new DblNode<T>(uniqueVal);
	if(first==NULL){cerr << "storage asking is defused " << endl;exit(1);}
	first->rLink=first->lLink;
};

template<class T>
int DblList<T>::Length()const{
	DblNode<T> *current =first->rLink;int count=0;
	while(current!=first){current=current->rLink;count++;}
	return count;
}

template<class T>
DblNode<T> *DblList<T>::Search(const T& x){
	DblNode<T> *current=first->rLink;
	while(current!=first&&current->data!=x){
		current=current->rLink;
	}
	if(current!=first){return current;}
	else{return NULL;}
}

template<class T>
DblNode<T> *DblList<T>::Locate(int i,int d){
	if(first->rLink==first||i==0){return first;}
	DblNode<T> *current;
	if(d==0){current =first->lLink;}
	else{current=first->rLink;}
	for(int j=1;j<i;j++){
		if(current==first){break;}
		else {
		if(d==0){current=current->lLink;}
		else{current=current->rLink;}
		}
	}
	if(current!=first){return current;}
	else{return NULL;}
}

template<class T>
bool DblList<T>::Insert(int i,const T& x,int d){
	DblNode<T> *current=Locate(i,d);
	if(current==NULL){return false;}
	DblNode<T> *newNode=new DblNode<T>(x);
	if(newNode==NULL){cerr << "storage asking is refused" << endl;exit(1);}
	if(d==0){
		newNode->lLink=current->lLink;
		current->lLink=newNode;
		newNode->lLink->rLink=newNode;
		newNode->rLink=current;
	}
	else{
		newNode->rLink=current->rLink;
		current->rLink=newNode;
		newNode->rLink->lLink=newNode;
		newNode->lLink=current;
	}
	return true;
}


template<class T>
bool DblList<T>::Remove(int i,T& x,int d){
	DblNode<T> *current=Locate(i,d);
	if(current==NULL){return false;}
	current->rLink->lLink=current->lLink;
	current->lLink->rLink=current->rLink;
	x=current->data;delete current;
	return true;
}
//输入构造函数和输出显示函数
template<class T>
void DblList<T>::inputRear(T endTag){
	DblNode<T> *newNode,*last;T val;
	cout << "Please input the first val of the DblList #0: " << endl;
	cin >> val;last=first;int index=0;
	while(val!=endTag){
		index++;
		newNode =new DblNode<T>(val);
		if(newNode==NULL){cerr << "storage asking is refused" << endl;exit(1);}
		last->rLink=newNode;newNode->rLink=first;
		first->lLink=newNode;newNode->lLink=last;
		last=newNode;
		cout << "Please input the #" << index << endl;
		cin >> val;
	}
}

template<class T>
void DblList<T>::r_output(){
	DblNode<T> *current=first->rLink;
	while(current!=first){
		cout << current->data << ";" << endl;
		current=current->rLink;
	}
}


template<class T>
void DblList<T>::l_output(){
	DblNode<T> *current=first->lLink;
	while(current!=first){
		cout << current->data << ";" << endl;
		current=current->lLink;
	}
}





