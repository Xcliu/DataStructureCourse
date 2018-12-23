#include<iostream>
#include<math.h>
using namespace std;
int main(){
    int tot;
    cin >> tot;
    int f=log(tot)/log(2);
    int circ_num=pow(2,f);
    cout << circ_num << endl;
    return 0;
}