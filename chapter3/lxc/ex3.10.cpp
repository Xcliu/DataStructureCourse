#include<iostream>
#include"link_stack.h"
#include"link_node.h"
const int size=5;
int main(){
    List<int> lk_ls;
    int a[size]={2,5,7,4,9};
    lk_ls.create(a,size);
    LinkedStack<int> lk_st;
    int x;
    for(int i=0;i<size;i++){
	lk_ls.getData(i+1,x);
        lk_st.Push(x);
    }
    lk_ls.makeEmpty();
    for(int i=0;i<size;i++){
    	lk_st.Pop(x);
	lk_ls.Insert(i,x);

    }
    lk_ls.output();
    return 0;
}
