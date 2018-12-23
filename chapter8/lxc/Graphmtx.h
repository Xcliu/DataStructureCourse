//failed untill now
#ifndef GRAPHMTX_H_
#define GRAPHMTX_H_

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Graph.h"
using namespace std;
extern const int DefaultVertices;

template<typename T,typename E>
class Graphmtx;

template<typename T,typename E>
ostream& operator << (ostream& out,Graphmtx<T,E>& G);


template<typename T,typename E>
class Graphmtx:public Graph<T,E>{
    public:
        Graphmtx(int size=DefaultVertices);
        Graphmtx(char *filename,int size=DefaultVertices);
        ~Graphmtx(){delete []VerticesList;delete []Edge;}
        T getValue(int i){
            return i>=0&&i<=this->numVertices?VerticesList[i]:NULL;
        }
        E getWeight(int v1,int v2){
            return v1!=-1&&v2!=-1?Edge[v1][v2]:0;
        }
        int getFirstNeighbor(int v);
        int getNextNeighbor(int v,int w);
        bool insertVertex(const T& vertex);
        bool insertEdge(int v1,int v2,E cost);
        bool removeVertex(int v);
        bool removeEdge(int v1,int v2);
        friend ostream& operator << <T,E>(ostream& out,Graphmtx<T,E>& G);
    private:
        //int test=2;
        T *VerticesList;
        E **Edge;      
        int getVertexPos(T vertex){
            for(int i=0;i<this->numVertices;i++){
                if(VerticesList[i]==vertex){return i;}
                
            }
            return -1;
        }
};

template<typename T,typename E>
Graphmtx<T,E>::Graphmtx(int size){
    //cout << "fuck" << endl;
    this->maxVertices=size;this->numVertices=0;this->numEdges=0;
    int i,j;
    //test=1; 
    VerticesList=new T[this->maxVertices];
    VerticesList[0]='A';
    //cout << VerticesList[0] <<endl;
    Edge=new E*[this->maxVertices];
    for(i=0;i<this->maxVertices;i++){
        Edge[i]=new E[this->maxVertices];
    }
    for(j=0;j<this->maxVertices;j++){
        for(i=0;i<this->maxVertices;i++){
            Edge[i][j]=(i==j)?0:this->maxWeight;
        }
    }
}

template<typename T,typename E>
Graphmtx<T,E>::Graphmtx(char *filename,int size){
    this->maxVertices=size;this->numVertices=0;this->numEdges=0;
    int i,j;
    //test=1; 
    VerticesList=new T[this->maxVertices];
    VerticesList[0]='A';
    //cout << VerticesList[0] <<endl;
    Edge=new E*[this->maxVertices];
    for(i=0;i<this->maxVertices;i++){
        Edge[i]=new E[this->maxVertices];
    }
    for(j=0;j<this->maxVertices;j++){
        for(i=0;i<this->maxVertices;i++){
            Edge[i][j]=(i==j)?0:this->maxWeight;
        }
    }

   ifstream inFile;
   inFile.open(filename);
   if(!inFile.is_open()){
       cout<<"Couldn't open the file: "<<filename <<endl;
        exit(EXIT_FAILURE);
   }
   T v_value;E w_value;
   inFile >> v_value;
 
   insertVertex(v_value);
   //cout << "fuck " <<endl;
   while(v_value!=';'&&!inFile.eof()){
       inFile>>v_value;
       if(v_value!=','&&v_value!=';'){
           insertVertex(v_value);
           //cout << v_value << this->numVertices <<endl;
       }
   }
   int l,k;
    /*
   for(int i=0;i<this->maxVertices;i++){
       cout << VerticesList[i] << endl;
   }*/
  
   while(!inFile.eof()){
       for(int i=0;i<6;i++){
            if(i<4){
                inFile >> v_value;
                if(i==0&&v_value!=','){
                    //cout << v_value <<endl;
                    l=getVertexPos(v_value);
                    //cout << l <<endl;
                }
                if(i==2&&v_value!=','){
                    //cout << "hah:"<< v_value <<endl;
                    k=getVertexPos(v_value);
                    //cout << k << endl;
                }
            }else if(i==4){
                inFile >> w_value;
                if(l==-1||k==-1){
                    cout << "input error!" <<endl;
                }else{
                    insertEdge(l,k,w_value);
                }
            }else if(i==5){
              char temp;
               inFile >>temp;
               if(temp!=';'){
                   cout << "input error!"<< endl;
               }   
            }
        }       
    }
}


template<typename T,typename E>
int Graphmtx<T,E>::getFirstNeighbor(int v){
    if(v!=-1){
        for(int col=0;col<this->numVertices;col++){
            if(Edge[v][col]>0&&Edge[v][col]<this->maxWeight){
                return col;
            }
        }
    }else{return -1;}
}

template<typename T,typename E>
int Graphmtx<T,E>::getNextNeighbor(int v,int w){
    if(v!=-1&&w!=-1){
        for(int col=w+1;col<this->numVertices;col++){
            if(Edge[v][col]>0&&Edge[v][col]<this->maxWeight){
                return col;
            }
        }
    }else{return -1;}
}

template<typename T,typename E>
bool Graphmtx<T,E>::insertVertex(const T& vertex){
    if(this->numVertices==this->maxVertices){return false;}
    this->numVertices++;
    int temp=this->numVertices-1;
    VerticesList[temp]=vertex;
    //cout << temp <<endl;
    return true;
}

template<typename T,typename E>
bool Graphmtx<T,E>::removeVertex(int v){
    if(v<0||v>=this->numVertices){return false;}
    if(this->numVertices==1){return false;}
    int i,j;
    VerticesList[v]=VerticesList[this->numVertices-1];
    for(i=0;i<this->numVertices;i++){
        if(Edge[i][v]>0&&Edge[i][v]<this->maxWeight){this->numEdges--;}
    }
    for(i=0;i<this->numVertices;i++){
        Edge[i][v]=Edge[i][this->numVertices-1];
    }
    for(j=0;j<this->numVertices;j++){
        Edge[v][j]=Edge[this->numVertices-1][j];
    }
    this->numVertices--;
    return true;
}

template<typename T,typename E>
bool Graphmtx<T,E>::insertEdge(int v1,int v2,E cost){
    if(v1>-1&&v1<this->numVertices&&v2>-1&&v2<this->numVertices
            &&Edge[v1][v2]==this->maxWeight){
        Edge[v1][v2]=Edge[v2][v1]=cost;
        this->numEdges++;
        return true;
    }else{
        return false;
    }
}

template<typename T,typename E>
bool Graphmtx<T,E>::removeEdge(int v1,int v2){
    if(v1>-1&&v1<this->numVertices&&v2>-1&&v2<this->numVertices
            &&Edge[v1][v2]>0&&Edge[v1][v2]<this->maxWeight){
        Edge[v1][v2]=Edge[v2][v1]=this->maxWeight;
        this->numEdges--;
        return true;
    }else{
        return false;
    }
}

template<typename T,typename E>
ostream& operator <<(ostream& out,Graphmtx<T,E>& G){
    int i,j,n,m;T e1,e2;E w;
    n=G.NumberOfVertices();m=G.NumberOfEDges();
    out<< n << ","<<m<<endl;
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            w=G.getWeight(i,j);
            if(w>0 &&w<G.maxWeight){
                e1=G.getValue(i);e2=G.getValue(j);
                out << "(" << e1 << ","<<e2 <<":" << w << ")"<<endl;
            }
        }
    }
    return out;
}




#endif