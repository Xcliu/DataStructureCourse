#include <iostream>
#include <cstdlib>
#include<ctime>
#include "Binary_search_tree.h"

using namespace std;

template<typename E,typename K>
bool BST<E,K>::Remove(const K x,BSTNode<E,K>*& ptr){
    BSTNode<E,K>* temp;
    if(ptr!=NULL){
        if(x<ptr->data){Remove(x,ptr->left);}
        else if(x>ptr->data){Remove(x,ptr->right);}
        else if(ptr->left!=NULL&&ptr->right!=NULL){
            srand((unsigned)time(NULL));
            int k=rand()%2;
            if(k==1){
                temp=ptr->right;
                while(temp->left!=NULL){temp=temp->left;}
                ptr->data=temp->data;
                Remove(ptr->data,ptr->right);
            }else{
                temp=ptr->left;
                while(temp->right!=NULL){temp=temp->right;}
                ptr->data=temp->data;
                Remove(ptr->data,ptr->right);
            }
        }else{
            temp=ptr;
            if(ptr->left==NULL){ptr=ptr->right;}
            else{
                ptr=ptr->left;
            }
            delete temp;
            return true;
        }
    }
    else return false;
};

int main(){
    char* filename=new char[30];
    cout << "please input the filename (less than 30 signals) " << endl;
    cin.getline(filename,30);
    BST<int,int> bst(0,filename);
    bst.PrintTree();
    cout << endl;
    bst.Remove(99);
    bst.PrintTree();
    cout << endl;
    return 0;
}

