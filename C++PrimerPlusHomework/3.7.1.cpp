
#include<iostream>
using namespace std;


void Height_display(int origin_inch){
    const int ratio=12;
    int inch =origin_inch % 12;
    int foot =(origin_inch - inch)/ratio;
    cout << "Your heght is  " << foot << " foot " << inch  <<" inch "<< endl;
    
}

int main(){
    cout << "please input your height in inch (int number):___________\b\b\b\b\b\b\b" ;
    int input_height;
    cin >> input_height;
    Height_display(input_height );
    
    return 0;
}






