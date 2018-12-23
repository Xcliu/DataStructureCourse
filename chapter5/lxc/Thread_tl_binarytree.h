#ifndef THREAD_TL__BINARYTREE_H_
#define THREAD_TL__BINARYTREE_H_
#include <iostream>
#include <fstream>
#include <seq_stack.h>

using namespace std;

template<typename T>
struct ThreadNode{
    int ltag,rtag;
    ThreadNode<T> *leftChild,*rightChild;
    T data;
    ThreadNode(const T item)://初始化顺序与声明顺序最好一致
        ltag(0),rtag(0),leftChild(NULL),rightChild(NULL),data(item){}
};


template<typename T>
class ThreadTree{
    protected:
        
        void createInThread(ThreadNode<T>* current,ThreadNode<T>* &pre);
        ThreadNode<T> *parent(ThreadNode<T> *);
        void destory(ThreadNode<T> *& subTree);

    public:
        ThreadNode<T> *root;
        ThreadTree();
        ~ThreadTree(){destory(root);}
        void createInThread();
        ThreadNode<T> *First(ThreadNode<T> *current);
        ThreadNode<T> *Last(ThreadNode<T> *current);
        ThreadNode<T> *Next(ThreadNode<T> *current);
        ThreadNode<T> *Prior(ThreadNode<T> *current);
        void Inorder();//void (*visit)(ThreadNode<T> *p)
        void preorder(void (*visit)(ThreadNode<T> *p));
        void postorder(void (*visit)(ThreadNode<T> *p));
        void Traverse(ThreadNode<T> *subTree);
        void InserRight(ThreadNode<T> *s,ThreadNode<T> *r);
        void InserLeft(ThreadNode<T> *s,ThreadNode<T> *l);//5.31
        /*reserveed for homework function*/
        void add_as_lchild(ThreadNode<T> *s,ThreadNode<T> *l);
};

template<typename T>/*have been tested*/
ThreadTree<T>::ThreadTree():root(NULL){
    SeqStack<ThreadNode<char> * > s;
    ThreadNode<char> *p,*t;int k;
    char filename[50];
    cout << "Please input the filename:" << endl;
    cin >> filename;
    char ch;
    ifstream inFile;
    inFile.open(filename);
    if(!inFile.is_open()){
        cout << "Could not open the file :" << filename << endl;
        cout << "Program terminating \n";
        exit(EXIT_FAILURE);
    }

    inFile >> ch;
    while(ch!='#'){
        switch(ch){
            case'(':{s.Push(p);k=1;break;}
            case')':{s.Pop(t);break;}
            case',':{k=2;break;}
            default:{p=new ThreadNode<char>(ch);}
            if(root==NULL){root=p;}
            else if(k==1){
                s.getTop(t);t->leftChild=p;
            }else{
                s.getTop(t);t->rightChild=p;
            }
        }
        inFile >> ch;
    }
    
    createInThread();

}


template<typename T>
void ThreadTree<T>::destory(ThreadNode<T> *& subTree){
    if(subTree!=NULL){
        if(subTree->ltag==0){
            destory(subTree->leftChild);
            }
        if(subTree->rtag==0){
            destory(subTree->rightChild);
            }
        delete subTree;
    }
};



template<typename T>
ThreadNode<T> *ThreadTree<T>::First(ThreadNode<T> *current){
    ThreadNode<T> *p=current;
    while(p->ltag==0){
        p=p->leftChild;
    }
    return p;
}

template<typename T>
ThreadNode<T> *ThreadTree<T>::Next(ThreadNode<T> *current){
    ThreadNode<T> *p=current->rightChild;
    if(current->rtag==0){return First(p);}
    else{return p;}
}
template<typename T>
ThreadNode<T> *ThreadTree<T>::Last(ThreadNode<T> *current){
    ThreadNode<T> *p=current;
    while(p->rtag==0){
        p=p->rightChild;
    }
    return p;
}
template<typename T>
ThreadNode<T> *ThreadTree<T>::Prior(ThreadNode<T> *current){
    ThreadNode<T> *p=current->leftChild;
    if(p->ltag==0){
        return Last(p);   
    }
    return p;
}

template<typename T>//void (*visit)(ThreadNode<T> *p)
void ThreadTree<T>::Inorder(){
    ThreadNode<T> *p;
    for(p=First(root);p!=NULL;p=Next(p)){cout << p->data << endl;}
}

template<typename T>
void ThreadTree<T>::createInThread(){
    ThreadNode<T> *pre=NULL;
    if(root!=NULL){
        createInThread(root,pre);
        pre->rightChild=NULL;pre->rtag=1;
    }
}

template<typename T>
void ThreadTree<T>::createInThread(ThreadNode<T>* current,ThreadNode<T>* &pre){
    if(current==NULL){return ;}
    createInThread(current->leftChild,pre);
    if(current->leftChild==NULL){
        current->leftChild=pre;current->ltag=1;
    }
    if(pre!=NULL&&pre->rightChild==NULL){
        pre->rightChild=current;pre->rtag=1;
    }
    pre=current;
    createInThread(current->rightChild,pre);
}

template<typename T>
void ThreadTree<T>::Traverse(ThreadNode<T> *subTree){
    if(subTree!=NULL){
        cout << subTree->data << ";";
        cout << subTree->ltag<< ";";
        cout << subTree->rtag<< endl;
        if(subTree->ltag==0)Traverse(subTree->leftChild);
        if(subTree->rtag==0)Traverse(subTree->rightChild);
    }
};

template<typename T>
void ThreadTree<T>::InserRight(ThreadNode<T> *s,ThreadNode<T> *r){
    r->rightChild=s->rightChild;
    r->rtag=s->rtag;
    r->leftChild=s;r->ltag=1;
    s->rightChild=r;s->rtag=0;
    if(r->rtag==0){
        ThreadNode<T> *temp;
        temp=First(r->rightChild);
        temp->leftChild=r;
    }
}


template<typename T>
void ThreadTree<T>::InserLeft(ThreadNode<T> *s,ThreadNode<T> *l){
    l->leftChild=s->leftChild;
    l->ltag=s->ltag;
    l->rightChild=s;l->rtag=1;
    s->leftChild=l;s->ltag=0;
    if(l->ltag==0){
        ThreadNode<T> *temp;
        temp=Last(l->leftChild);
        temp->rightChild=l;
    }
}







#endif