#ifndef TWOLINKBINARYTREE_H_
#define TWOLINKBINARYTREE_H_

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <fstream>
#include <seq_stack.h>
#include <seq_deque.h>

using namespace std;

template<typename T>
class BinaryTree;
/*template<typename T>
istream& operator >> (istream& in ,BinaryTree<T> &Tree);*/
template<typename T>
ostream& operator << (ostream &out,BinaryTree<T> &Tree);
//template<typename T>
//void visit (BinaryTree<T>::BinTreeNode* p);

template<typename T>
class BinaryTree{
        protected:
        struct BinTreeNode{
            T data;
            BinTreeNode *leftChild,*rightChild;
            BinTreeNode():leftChild(NULL),rightChild(NULL){}
            BinTreeNode(T x,BinTreeNode *l=NULL,BinTreeNode *r=NULL):
                data(x),leftChild(l),rightChild(r){}

        };
  
        BinTreeNode *root;
        T RefValue;
        bool Insert(BinTreeNode *& subTree,const T& X);
        void destory(BinTreeNode *& subTree);
        bool Find(BinTreeNode *subTree,const T&x)const;
        BinTreeNode *Copy(BinTreeNode *orignnode);
        int Height(BinTreeNode *subTree);
        
        BinTreeNode *Parent(BinTreeNode *subTree,BinTreeNode *current);
        BinTreeNode *Find(const T&x)const;
        void Traverse(BinTreeNode *sunTree,ostream& out);
        void preOrder(BinTreeNode * subTree,void(*visit)(BinTreeNode *p));
        void inOrder(BinTreeNode * subTree,void(*visit)(BinTreeNode *p));
        void postOrder(BinTreeNode * subTree,void(*visit)(BinTreeNode *p));
        /*friend istream& operator >> <T>(istream & in ,BinaryTree<T> &Tree);*/
        friend ostream& operator << <T>(ostream & out,BinaryTree<T> &Tree);
        //friend void visit <T>(BinaryTree<T>::BinTreeNode *p);
    public:   
        BinaryTree():root(NULL){}
        BinaryTree(T value):root(NULL),RefValue(value){}
        //BinaryTree(BinaryTree<T> &s);
        ~BinaryTree(){destory(root);}
        int Size(BinTreeNode *subTree);

        void CreateBinTree();//different from the function in the textbook

        bool IsEmpty(){return (root==NULL)?true:false;}
        BinTreeNode *Parent(BinTreeNode* current){
            return (root==NULL||root==current)?
                NULL:Parent(root,current);
        }
        BinTreeNode *LeftChild(BinTreeNode* current){
            return (current!=NULL)?current->leftChild:NULL;
        }
        BinTreeNode *rightChild(BinTreeNode* current){
            return (current!=NULL)?current->rightChild:NULL;
        }
        int Height(){return Height(root);}
        int Size(){return Size(root);}
        BinTreeNode *getRoot()const{return root;}
        void preOrder(void(*visit)(BinTreeNode *p)){
            preOrder(root,visit);
        }
        void inOrder(void(*visit)(BinTreeNode *p)){
            inOrder(root,visit);
        }
        void postOrder(void(*visit)(BinTreeNode *p)){
            postOrder(root,visit);
        }
        void levelOrder();
        int  Insert(const T& item);
        BinTreeNode Find(T& item)const;
        /*left for homeeork function*/
        /*5.23(1)*/
        void get_num_leaf(BinTreeNode *subTree,int &i)const;
        /*5.23(2)*/
        void exchange_lr(BinaryTree &BT);
        /*5.24*/
        bool array_complete_bt(T *&array,int size);

        void preOrder(BinTreeNode* subTree);

        bool find_someone_allancestor(T tag);
        
        void get_num_d1(BinTreeNode *t,int &k)const;
        void get_num_d2(BinTreeNode *t,int &k)const;
        void get_num_d0(BinTreeNode *t,int &k)const;
    
        int get_height(BinTreeNode *t)const;
        int get_width(BinTreeNode *t)const;
        
        static void visit(BinTreeNode *p);
        void double_order_traversal(BinTreeNode *p);

        bool Is_binary_search_tree(); 
};

template<typename T>
void BinaryTree<T>::destory(BinTreeNode *& subTree){
    if(subTree!=NULL){
        destory(subTree->leftChild);
        destory(subTree->rightChild);
        delete subTree;
    }
};

template<typename T>
typename BinaryTree<T>::BinTreeNode *BinaryTree<T>::Parent(BinTreeNode *subTree,BinTreeNode *current){
    if(subTree==NULL){return NULL;}
    if(subTree->leftChild==current||subTree->rightChild==current){
        return subTree;
    }
    BinTreeNode *p;
    if((p=Parent(subTree->leftChild,current))!=NULL){return p;}
    else{return Parent(subTree->rightChild,current);}
};

template<typename T>
void BinaryTree<T>::Traverse(BinTreeNode *subTree,ostream &out){
    if(subTree!=NULL){
        out << subTree->data << ";";
        Traverse(subTree->leftChild,out);
        Traverse(subTree->rightChild,out);
    }
};
/*
template<typename T>
istream& operator >> (istream& in,BinaryTree<T> & Tree){
    CreateBinTree();
    return in;
};
*/
template<typename T>
ostream& operator << (ostream& out,BinaryTree<T> & Tree){
    out << "the preorder of the binary tree \n";
    Tree.Traverse(Tree.root,out);
    out <<endl;
    return out;
};

template<typename T>
void BinaryTree<T>::CreateBinTree(){
    SeqStack<BinaryTree<char>::BinTreeNode * > s;
    root=NULL;
    BinaryTree<char>::BinTreeNode *p,*t;int k;
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
    while(ch!=RefValue){
        switch(ch){
            case'(':{s.Push(p);k=1;break;}
            case')':{s.Pop(t);break;}
            case',':{k=2;break;}
            default:{p=new BinTreeNode(ch);}
            if(root==NULL){root=p;}
            else if(k==1){
                s.getTop(t);t->leftChild=p;
            }else{
                s.getTop(t);t->rightChild=p;
            }
        }
        inFile >> ch;
    }

}

/*left for homeeork function*/
/*5.23(1)*/

template<typename T>
void BinaryTree<T>::get_num_leaf(BinTreeNode *subTree,int &i)const{
    if(subTree!=NULL){
        if(subTree->leftChild==NULL&&subTree->rightChild==NULL){
            i++;
        }
        get_num_leaf(subTree->leftChild,i);
        get_num_leaf(subTree->rightChild,i);
    }
}

/*5.23(2)*/
template<typename T>
void BinaryTree<T>::exchange_lr(BinaryTree &BT){
    SeqStack<BinaryTree<T>::BinTreeNode * > s;
    BinaryTree<T>::BinTreeNode * temp;
    BinaryTree<T>::BinTreeNode *k=BT.getRoot();
    while(k->leftChild!=NULL||k->rightChild!=NULL){
        s.Push(k->rightChild);
        temp=k->rightChild;k->rightChild=k->leftChild;
        k->leftChild=temp;
        k=k->rightChild;
    }
    while(!s.IsEmpty()){
        s.Pop(k);
        if(k->leftChild!=NULL||k->rightChild!=NULL){
            temp=k->rightChild;k->rightChild=k->leftChild;
            k->leftChild=temp;
        }
    }
}

/*5.24,怎么实现析构？*/
template<typename T>
bool BinaryTree<T>::array_complete_bt(T *&array,int size){
    if(size==0){return false;}
    BinaryTree<T>::BinTreeNode **temp=new BinaryTree<T>::BinTreeNode *[size];
    for(int i=0;i<size;i++){
        temp[i]=new BinaryTree<T>::BinTreeNode(array[i]);
    }
    root=temp[0];
    int k=0;BinaryTree<T>::BinTreeNode * current=temp[k];
    while((2*k+1)<size){
        current->leftChild=temp[2*k+1];
        if(2*k+1<size-1){
            current->rightChild=temp[2*k+2];
        }else{current->rightChild=NULL;}
        k++;current=temp[k];
    }
    return true;
}
//void (*visit)(BinTreeNode *p)
template<typename T>
void BinaryTree<T>::levelOrder(){//由于队列头文件中的一些问题引发的警告可以直接忽略
    SeqDeque<BinTreeNode* > Q(BinaryTree<T>::Size(root));
    BinTreeNode *p=root;
    Q.EnQueue(p);
    T *store_array=new T[BinaryTree<T>::Size(root)];
    int k=0;
    while(!Q.IsEmpty()){
        Q.DeQueue(p);
        store_array[k]=p->data;k++;
        //cout << p->data <<endl;
        //visit(p);
        if(p->leftChild!=NULL){Q.EnQueue(p->leftChild);}
        if(p->rightChild!=NULL){Q.EnQueue(p->rightChild);}
    }
    for(int i=0;i<BinaryTree<T>::Size(root);i++){
        cout << store_array[i] << endl;
    }
    delete []store_array;
}

template<typename T>
int BinaryTree<T>::Size(BinTreeNode *subTree){
    if(subTree==NULL){return 0;}
    else{
        int i=Size(subTree->leftChild);
        int j=Size(subTree->rightChild);
        return i+j+1;
    }
}



template<typename T>
void BinaryTree<T>::visit(BinTreeNode *p){
    ofstream outFile("7.26.txt",ios::app);
    outFile << p->data <<endl;
    outFile.close();
}



template<typename T>
void BinaryTree<T>::inOrder(BinTreeNode * subTree,void(*visit)(BinTreeNode *p)){
   if(subTree!=NULL){
       inOrder(subTree->leftChild,visit);
       visit(subTree);
       inOrder(subTree->rightChild,visit);
   } 
}



#endif 