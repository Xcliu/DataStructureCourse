#include"link_node.h"
#include<iostream>
using namespace std;

template<class T>
void List<T>::tidyup(){
	LinkNode<T>* current_link=first->link;
	while(current_link->link!=NULL){
		if(current_link->link->data==current_link->data){
			LinkNode<T> *del=current_link->link;
			current_link->link=del->link;
			cout << "the del :" << del->data << endl;
			delete del;
			//cout << current_link->data << ":" << endl;
		}
		else{current_link=current_link->link;}
		//cout << current_link->data << ";" << endl;
	}
}

int main(){
	const int size=10;
	int array_x[size]={1,1,6,6,6,7,8,8,8,9};
	List<int> L;
	L.create(array_x,size);
	L.output();
	L.tidyup();
	cout << "changed:" << endl;
	L.output();
}
