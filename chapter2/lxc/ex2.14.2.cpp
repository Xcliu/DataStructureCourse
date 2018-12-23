#include"link_node.h"
#include<iostream>
using namespace std;



//定位从表头开始的第i个数
template<class T>
void List<T>::Find_max(List<T>& x)const{
	LinkNode<T> *current_link=x.getHead()->link;
	T max=current_link->data;
        while(current_link!=NULL){
		if(current_link->data>max){
			max=current_link->data;

		}
		current_link=current_link->link;
	}
	cout << "The max is :" << max << endl;

}

int main(){
	List<int> L;
	L.inputRear(0);
	cout << "Dispaly the LinkNode:" << endl;
	L.output();
	L.Find_max(L);
	return 0;
 }
