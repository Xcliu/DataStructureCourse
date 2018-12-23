#include"link_node.h"
#include<iostream>
using namespace std;

template<class T>
void List<T>::create(T array_x[],int size){
	LinkNode<T>* current_link=first;
	first->data=T(size);
	for(int i=0;i<size;i++){
		current_link->link=new LinkNode<T>(array_x[i]);
		current_link=current_link->link;
	}
	current_link=NULL;
}

int main(){
	const int size=3;
	int array_x[size]={2,3,6};
	List<int> L;
	L.create(array_x,3);
	L.output();
}
