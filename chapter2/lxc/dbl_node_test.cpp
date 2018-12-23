#include"dbl_node.h"
#include<iostream>

using namespace std;

int main(){
	//DblList<int>(-1);
	DblList<int> dbl(-1);
	dbl.inputRear(0);
	cout << "the input list:" << endl;
	dbl.r_output();
      	cout << "Inverse:" << endl;
	dbl.l_output();
	return 0;
}

