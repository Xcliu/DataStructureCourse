#include <iostream>
#include <string>
using namespace std; 
bool test_pali(string tag_str,int size);


bool test_pali(string tag_str,int size){
    int i,j;
    for(i=0,j=size-1;i<size&&j>=0;i++,j--){
        if(tag_str[i]!=tag_str[j]){cout << "N" <<endl;return false;}
    }
    cout << "Y" << endl;
    return true; 
}

int main(){
    cout << "please input the tested strings: "<< endl;
    string tag_str;
    cin >> tag_str;
    int size=tag_str.size();
    test_pali(tag_str,size);
    return 0;
}