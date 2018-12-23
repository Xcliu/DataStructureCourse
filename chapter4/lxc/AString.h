#ifndef ASTRING_H
#define ASTRING_H
#include <string>
#include <iostream>
#include <assert.h>
# define defaultSize 128
using namespace std;

class AString{
    public:
    AString(int sz=defaultSize);
    AString(const char* init);
    AString(const AString& ob);
    ~AString(){delete []ch;}
    int Length()const{return curLength;}
    AString operator()(int pos,int len);
    int operator==(AString& ob)const{return strcmp(ch,ob.ch)==0;}
    int operator!=(AString& ob)const{return strcmp(ch,ob.ch)!=0;}
    int operator!()const{return curLength==0;}
    AString& operator=(const AString& ob);
    AString& operator+=(const AString& ob);
    char& operator[](int i);
    int Find(AString& pat)const;
    void getNext();
    void replace(AString& s,AString& t,AString& v);
    int *next;
    int fastFind(AString& pat,int k,int *next);
    private:
    char *ch;
    int curLength;
    int maxSize;
};

AString::AString(int sz){
     maxSize=sz;
     ch=new char[maxSize];
     curLength=0;ch[0]='\0';
 };

AString::AString(const char* init){
    int len=strlen(init);
    maxSize=(len>maxSize)?len:defaultSize;
    ch=new char[maxSize+1];
    curLength=len;
    strcpy(ch,init);
};

AString::AString(const AString& ob){
    maxSize=ob.maxSize;
    ch=new char[maxSize+1];
    curLength=ob.curLength;
    strcpy(ch,ob.ch);
};

AString AString::operator()(int pos,int len){
    AString temp;
    if(pos<0||pos+len-1>=maxSize||len<0){
        temp.curLength=0;temp.ch[0]='\0';
    }
    else{
        if(pos+len-1>=curLength)
        {len=curLength-pos;}
        temp.curLength=len;
        for(int i=0,j=pos;i<len;i++,j++){temp.ch[i]=ch[j];}
        temp.ch[len]='\0';
    }
    return temp;
};

AString& AString::operator=(const AString& ob){
    if(&ob!=this){
        delete []ch;
        ch =new char[ob.maxSize];
        curLength=ob.curLength;
        strcpy(ch,ob.ch);
    }
    else {cout << " 字符串自身赋值出错！ \n";}
    return *this;
};

AString& AString::operator+=(const AString& ob){
    char* temp =ch;
    int n=curLength+ob.curLength;
    int m=(maxSize>n)?maxSize:n;
    ch=new char[m];
    maxSize=m;curLength=n;
    strcpy(ch,temp);
    strcat(ch,ob.ch);
    delete []temp;
    return *this; 
};


char& AString::operator[](int i){
    if(i<0||i>=curLength){
        cout << "the index is out of range";
        exit(1);
    }
    return ch[i];
}

void AString::getNext(){
    int j=0,k=-1,lengthP=curLength;
    next=new int[curLength];
    next[0]=-1;
    while(j<lengthP){
        if(k==-1||ch[j]==ch[k]){
        j++;k++;
        next[j]=k;
        }
        else{k=next[k];}
    }
};

int AString::fastFind(AString& pat,int k,int *next){
    int posP=0,posT=k;
    int lengthP=pat.curLength;
    int lengthT=curLength;
    while(posP<lengthP && posT<lengthT){
        if(posP==-1||pat.ch[posP]==ch[posT]){
            posP++;posT++;
        }
        else posP=next[posP];
    }
    if(posP<lengthP){return -1;}
    else{return posT-lengthP;}
};



 #endif
