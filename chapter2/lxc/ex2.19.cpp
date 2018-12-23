#include"dbl_node.h"
#include<iostream>

using namespace std;

template<class T>
void DblList<T>::fuck(){
	DblNode<T> *current,*index,*tmp,*last;
	last=first;
	current=first->rLink;
	T max,min;
	max=current->data;
	index=current;
	while(current!=first){
		if(current->data>max){
			max=current->data;
		}
		current=current->rLink;
	}
	//cout << max << endl ;
	while(index!=first){
		min=max;
		current=first->rLink;
		while(current!=first){
			if(current->data<=min&&current->fk!=0){
				min=current->data;
				tmp=current;
			}
		current=current->rLink;
		}
		//cout << tmp->data << ":";
		tmp->fk=0;
		tmp->lLink=last;
		last=tmp;
		index=index->rLink;
		//cout << tmp->data << ":";
	}
	first->lLink=tmp;
	//cout << tmp->data << ";";
	while(tmp!=first){
		cout << tmp->data << ";";
		tmp=tmp->lLink;
	}
}

int main(){
	//DblList<int>(-1);
	DblList<int> dbl(-1);
	dbl.inputRear(0);
	cout << "the input list:" << endl;
	dbl.r_output();
	dbl.fuck();
	//dbl.l_output();
	return 0;
}

