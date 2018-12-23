#include <iostream>
using namespace std;



template<typename T>
class Vec
{
public:
    T pos[3];
    Vec(T a, T b, T c){
        pos[0] =a;
        pos[1] =b;
        pos[2] =c;
    }
    void prt(){
        cout << pos[0] << ", " << pos[1] << ", " << pos[2] << endl;
        cout << "Dad!" << endl;
    }
};




int main(int argc, char const *argv[])
{
    Vec<double> d_vec(1.5,2.5,3.5);
    d_vec.prt();

    Vec<int> i_vec(1,2,3);
    i_vec.prt();




    return 0;
}
