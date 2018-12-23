#ifndef GENERALIST_H
#define GENERALIST_H
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <string>//不能用string.h
#include <mystd.h>
#include "/Users/liuxingchen/work/DataStructureCourse/DataStructureHomework/chapter3/lxc/seq_stack.h"
//目前存在两个问题1.没有实现复杂结构union的析构 
//2.引用头表会报错Segmentation fault: 11，A(e,A);
//不能自引用的原因可能是自引用的析构会出问题
using namespace MYSTD;

template<typename T>
class GenList;

template<typename T>//两个结构的前后顺序问题
struct GenListNode{
    //private:
    int utype;int mark;
    GenListNode<T> *tlink;
    
    union{
        int ref;T value;GenListNode<T> *hlink;
    }info;

    public:
    GenListNode():utype(0),mark(0),tlink(NULL){
        info.ref=0;
    }
    GenListNode(GenListNode<T> & RL){
        utype=RL.utype;mark=RL.mark;tlink=RL.tlink;info=RL.info;
    }
    //~GenListNode(){if(utype==2){info.value.~T();}}

};

template<typename T>
struct Items{
    int utype;int mark;
    union{
        int ref;
        T value;
        GenListNode<T> *hlink;
    }info;
    Items():utype(0),mark(0){info.ref=0;}
    Items(Items<T>& RL){utype=RL.utype;mark=RL.mark;info=RL.info;} 
    //~Items(){if(utype==2)info.value.~T();}
};

template<typename T>
class GenList{
    public:
    GenList(istream& in);
    GenList(string fname);
    ~GenList();
    bool Head(Items<T>& x);
    bool Tail(GenList<T>& lt);
    GenListNode<T> *First();
    GenListNode<T> *Next(GenListNode<T> *elem);
    void Copy(const GenList<T>& R);
    void delvalue(GenListNode<T> *ls,T x);
    int Length();
    int depth();

    //private:
    GenListNode<T> *first;
    GenListNode<T> *Copy(GenListNode<T> *ls);
    int Length(GenListNode<T> *ls);
    int depth(GenListNode<T> *ls);
    bool equal(GenListNode<T> *s,GenListNode<T> *t);
    void Remove(GenListNode<T> *ls);
};


template<typename T>
GenList<T>::GenList(istream& in){
    SeqStack<GenListNode<T>* > node_stack;
    GenListNode<T>* ls=NULL;
    GenListNode<T> *p=NULL;
    int size;
    cout << "Please input the number of elements in the general list:";
    in >> size;
    T *Ls1=new T[size+1];
    GenListNode<T>** Ls2=new GenListNode<T>*[size];
    for(int i=0;i<size;i++){
        Ls1[i]='$';Ls2[i]=NULL;
    }Ls1[size]='$';

    T chr;in >>chr;
    if(isalpha(chr)&&isupper(chr)){
        first=new GenListNode<T>;
        first->utype=0;
        Ls1[0]=chr;Ls2[0]=first;
    }else{cout << "Input error!";exit(1);}

    GenListNode<T> *pre_out_node=first;

while(1){
    in >>chr;
    if(isalpha(chr)&&isupper(chr)){
        ls=new GenListNode<T>;
        pre_out_node->tlink=ls;
        ls->utype=2;
        int n=0;
        while(Ls1[n]!='$'){n++;}
        int m=-1;
        for(int i=0;i<n;i++){
            if(Ls1[i]==chr){m=i;break;}
        }
        if(m!=-1){
            p=Ls2[m];
            p->info.ref++;
            ls->info.hlink=p;
            pre_out_node=ls;
        }
        else{
            node_stack.Push(ls);
            ls->info.hlink=new GenListNode<T>;
            ls->info.hlink->utype=0;ls->info.hlink->info.ref=1;
            pre_out_node=ls->info.hlink;
            Ls1[n]=chr;Ls2[n]=ls->info.hlink;
        }
    }
    else if(isalpha(chr)&&islower(chr)){
        ls=new GenListNode<T>;ls->utype=1;
        pre_out_node->tlink=ls;
        ls->info.value=chr;
        pre_out_node=ls;
    }
    else if(chr==')'){pre_out_node=NULL;}
    else if(chr==','){
        if(pre_out_node==NULL){
            node_stack.Pop(pre_out_node);
        }
    }
    else if(chr=='#'){ls=NULL;break;}// 这里#作为输入结束符号
}
    /*for(int i=0;i<n;i++){
        cout << Ls1[i] << ";" << Ls2[i] << endl;
    }*/

    delete []Ls1;delete []Ls2;
}


template<typename T>
GenList<T>::~GenList(){
    Remove(first);
}

template<typename T>
bool GenList<T>::Head(Items<T>& x){
    if(first->tlink==NULL){return false;}
    else{
        x.utype=first->tlink->utype;
        //x.info=first->tlink->info;
        return true;
    }
}

template<typename T>
bool GenList<T>::Tail(GenList<T>& lt){
    if(first->tlink==NULL){return false;}
    else{
        lt.first->utype=0;
        lt.first->info.ref=0;
        lt.first->tlink=Copy(first->tlink->tlink);
        return true;
    }
}

template<typename T>
GenListNode<T> *GenList<T>::First(){
    if(first->tlink==NULL){return NULL;}
    else{return first->tlink;}
}

template<typename T>
GenListNode<T> *GenList<T>::Next(GenListNode<T> *elem){
    if(elem->tlink==NULL){return NULL;}
    else{return elem->tlink;}
}

template<typename T>
void GenList<T>::Copy(const GenList<T>& R){
    first=Copy(R.first);
}

template<typename T>
GenListNode<T> *GenList<T>::Copy(GenListNode<T> *ls){
    GenListNode<T> *q=NULL;
    if(ls!=NULL){
        q=new GenListNode<T>;
        q->utype=ls->utype;
        switch(ls->utype){
            case 0:q->info.ref=ls->info.ref;break;
            case 1:q->info.value=ls->info.value;break;
            case 2:q->info.hlink=Copy(ls->info.hlink);break;
        }
        q->tlink=Copy(ls->tlink);
    }
    return q;
}

template<typename T>
int GenList<T>::Length(){
    return Length(first);
}

template<typename T>
int GenList<T>::Length(GenListNode<T> *ls){
    if(ls!=NULL){return 1+Length(ls->tlink);}
    else{return 0;}
}

template<typename T>
int GenList<T>::depth(){
    return depth(first);
}

template<typename T>
int GenList<T>::depth(GenListNode<T> *ls){
    if(ls->tlink==NULL){return 1;}
    GenListNode<T> *temp=ls->tlink;int m=0;int n;
    while(temp!=NULL){
        if(temp->utype==2){
            n=depth(temp->info.hlink);
            if(m<n){m=n;}
        }
        temp=temp->tlink;
    }
    return m+1;
}

template<typename T>
bool GenList<T>::equal(GenListNode<T> *s,GenListNode<T> *t){
    int x;
    if(s->tlink==NULL&&t->tlink==NULL){return true;}
    if(s->tlink!=NULL&&t->tlink!=NULL&&
        s->tlink->utype==t->tlink->utype){
        if(s->tlink->utype==1){
            x=(s->tlink->info.value==t->tlink->info.value)?1:0;
        }else if(s->tlink->utype==2){
            x=equal(s->tlink->info.hlink,t->tlink->info.hlink);
        }
        if(x==1){return equal(s->tlink,t->tlink);}
    }
    return false;
}

template<typename T>
void GenList<T>::delvalue(GenListNode<T> *ls,T x){
    if(ls->tlink!=NULL){
        GenListNode<T> *p=ls->tlink;
        while(p!=NULL&&(p->utype==1&&p->info.value==x)){
            ls->tlink=p->tlink;delete p;p=ls->tlink;
        }
        if(p!=NULL){
            if(p->utype==2){
                delvalue(p->info.hlink);
            }
            delete(p,x);
        }
    }
}

template<typename T>
void GenList<T>::Remove(GenListNode<T> *ls){
    ls->info.ref--;//这种递归删去，对于存在引用的节点会出错。
    if(ls->info.ref<=0){
        GenListNode<T> *q;
        while(ls->tlink!=NULL){
            q=ls->tlink;
            if(q->utype==2){
                Remove(q->info.hlink);
                if(q->info.hlink->info.ref<=0){
                    delete q->info.hlink;
                }
            }
            ls->tlink=q->tlink;delete q;
        }
    }
}



#endif
