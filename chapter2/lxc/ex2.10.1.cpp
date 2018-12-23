
#include<iostream>

//#include"LinearList.h"
#include"SeqList.h"


using namespace std;
//template class SeqList<int>;

template<class T>
T SeqList<T>::del_min(){
  T a=data[0];
  for(int i=0;i<=last;i++){
     if(data[i]<a){a=data[i];}
  }
  T content_max;
  T last_data=data[last];
  int index_min=Search(a);
  Remove(index_min,content_max);
  Insert(index_min,last_data);
  return content_max;  
}




int main(){
    SeqList<int> SL;
    SL.input();
    SL.output();
    cout << "The min num: " << SL.del_min() << endl;
    SL.output();
    return 0;
}
