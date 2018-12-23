#include <iostream>
using namespace std;


//creat your own namespace 
namespace LXC {

void prt(){
    cout << "lxc" << endl;
}

} // LXC


namespace CYY{
void prt(){
    cout << "cyy" << endl;
}
}


void io_test(){
    int a, b;// the self variable 
    (cin >> a) >> b; //cin >> can be seen as a function 
    //  ~= cin >> a; cin >> b;
    // cin >> a will return cin;

    cout << a << ", " << b << endl;
}


int main(int argc, char const *argv[])// if we input "./a.out 5 6 "in the  commandline
//argc refer the words number of the input (int argc =3)
//argv 是指针数组，argv[0]="./a.out"  argv[1]="5" argv[2]="6"   argc argv 可以在下面的函数中访问 
{
    //io_test();
    LXC::prt();

    using namespace CYY;

    prt();
    cout << argc << endl;
    for(int a= 0; a < 3;++a){
        cout << *argv[a] << endl;
    }
    //cout << *argv[0] << endl;

    return 0;
}
