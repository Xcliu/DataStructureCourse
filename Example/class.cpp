#include <iostream>
using namespace std;


class Vec
{
public:// private 是外部不能访问的数据类型
    double pos[3];
public:
    Vec(double a, double b, double c){
        pos[0] = a;
        pos[1] = b;
        pos[2] = c;
    }

    Vec add( Vec v ){
        Vec new_v( pos[0] + v.pos[0], pos[1] + v.pos[1], pos[2] + v.pos[2] );
        return new_v;
    }

    virtual void prt(){ //c++虚函数
        cout << pos[0] << ", " << pos[1] << ", " << pos[2] << endl;
        cout << "Dad!" << endl;
    }

    // v1+v2 ~= v1.operator+(v2)
    Vec operator+(Vec v){
        Vec new_v( pos[0] + v.pos[0], pos[1] + v.pos[1], pos[2] + v.pos[2] );
        return new_v;
    }
};// 类结束最后需要加分号

class EVec: public Vec
{
public:
    EVec(double a, double b, double c):Vec(a,b,c){
        cout << "EVec" << endl;
    }
    double norm(){
        return pos[0]*pos[0] + pos[1]*pos[1] + pos[2]*pos[2];
    }

    virtual void prt(){
        cout << pos[0] << ", " << pos[1] << ", " << pos[2] << endl;
        cout << "Son!" << endl;
    }

};

/*
void prt_info( Vec & v){//& 表示C++中的引用
    v.prt();

}
*/
void prt_info(Vec & v){
     v.prt();
}




int main(int argc, char const *argv[])
{
    Vec v(1.,2.,3.), v2(2.,3.,4.);

    cout << v.pos[0] << ", " << v.pos[1] << ", " << v.pos[2] << endl;

    Vec new_v = v.add(v2);

    cout << new_v.pos[0] << "," << endl;

    Vec new_v2 = v + v2;//得益于类中关于运算符的定义
    cout << new_v2.pos[0] << ", " << endl;



    EVec ve(1.,2.,3.);
    cout << ve.norm() << endl;


    v.prt();

    ve.prt();

    prt_info( v );
    prt_info( ve );

    return 0;
}













