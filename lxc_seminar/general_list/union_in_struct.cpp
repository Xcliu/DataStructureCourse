/*#include <iostream>
using namespace std;

struct fuck{
    int a;
    union {
        int b;
        char c;        
    }info;
    fuck():a(0){info.b=0;}
    fuck(fuck & x){a=x.a;info=x.info;}
};

int main(){
    fuck f;
    f.info.b=3;
    fuck h(f);
    cout << f.info.b << endl;
    return 0;
}

#include <iostream>  
using namespace std;  

class base{  
public:  
  base(){cout << "base()" <<endl;}  
  ~base(){cout << "~base()" << endl;}  
};

union tu{  
    base* b;  
    tu(){cout << "tu()" << endl;}  
    ~tu(){cout << "~tu()" << endl;b->~base();}  
};  

int main()  
{  
    tu t;  
    return 0;  
} */

#include <iostream>
using namespace std;

template<typename T>//两个结构的前后顺序问题
struct GenListNode{
    //private:
    int utype;int mark;
    GenListNode<T> *tlink;
    union{
        int ref;T value;GenListNode<T> *hlink;
    }info;

    public:
    GenListNode():utype(0),mark(0),tlink(NULL){info.ref=0;}//???
    GenListNode(GenListNode<T> & RL){
        utype=RL.utype;mark=RL.mark;tlink=RL.tlink;info=RL.info;
    }

};

template<typename T>
struct Items{
    int utype;int mark;
    union{
        int ref;
        T value;
        GenListNode<T> *hlink;
    }info;
    int judge_type(int a){return 0;}
    int judge_type(T a){return 1;}
    int judge_type(GenListNode<T>* a){return 2;}
    Items(int a):utype(),mark(0){info.ref=a;}
    Items(Items<T>& RL){utype=RL.utype;mark=RL.mark;info=RL.info;}
};

template<typename T>
class GenList{
    public:
    GenList(){
        Items<T> c;
    }
    ~GenList(){

    }
    Items<T> c;
    GenListNode<T> b;
};


int main(){  
    Items<char> gen(2);
    cout << gen.judge_type(gen.info) << endl;
    //cannot judge the type of union in this way
    return 0;  
}
