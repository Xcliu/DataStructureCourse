#include <iostream>
#include "AString.h"
using namespace std;

int main(){
    const int size1=10;
    const int size2=10;
    char str1[size1]="abaabcac";
    char str2[size2]="abc";
    AString astr1(str1);
    AString astr2(str2);
    astr2.getNext();
    int x=astr1.fastFind(astr2,0,astr2.next);
    cout << x << endl;
    return 0;
}