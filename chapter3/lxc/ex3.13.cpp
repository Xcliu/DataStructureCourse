#include<fstream>
#include<iostream>
#include"link_stack.h"
using namespace std;

bool check_bra(){
    char data='f';char x;
    ifstream infile;infile.open("fucking_test.txt");
    LinkedStack<char> lk_st;
    while(data!='/'){//自己设置“/” 为文件结束标志符
        infile >> data;
        if(data=='('||data=='['||data=='{'){
            lk_st.Push(data);
        }
        if(data==')'||data==']'||data=='}'){
            lk_st.getTop(x);
            if(data==')'){
                if(lk_st.IsEmpty()==true){return false;}
                else{if(x=='('){lk_st.Pop(x);}}
            }
            if(data==']'){
                if(lk_st.IsEmpty()==true){return false;}
                else{if(x=='['){lk_st.Pop(x);}}
            }
            if(data=='}'){
                if(lk_st.IsEmpty()==true){return false;}
                else{if(x=='{'){lk_st.Pop(x);}}
            }
        }
    }
    infile.close();
    return  (lk_st.IsEmpty())?true:false;
}

int main(){
    if(check_bra()==true){
        cout << "right" << endl;
    }
    else{cout << "wrong" << endl; }
    return 0;
}
