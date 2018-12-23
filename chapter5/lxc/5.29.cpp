#include "TwoLinkBinaryTree.h"

//外部函数没有权限访问结构体，
//这里常用的解决方式是通过将结构体放在public中
//另外一中需要尝试的方式是将visit声明成友元函数
//但是这样没有成功？？？

//具体在oid BinaryTree<T>::levelOrder()函数中
int main(){
    BinaryTree<char> bintree('#');
    bintree.CreateBinTree();
    bintree.levelOrder();
    return 0;
}