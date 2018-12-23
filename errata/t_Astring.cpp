#include "Astring.h"


int main(int argc, char const *argv[])
{
    AString str("Tsinghua University");
    AString temp_str = std::move(str(5,5));
    std::cout << temp_str << std::endl;     // Output shoud be "hua U";


    /*
AString str("Tsinghua University");
AString * pstr = str(5,5);
std::cout << *pstr << std::endl;        // Output shoud be "hua U";
delete pstr;                            // DO NOT forget to release memory;
    */

    /*
AString str("Tsinghua University");
AString temp_str;                       // An external container is always needed;
str(5,5,temp_str);
std::cout << temp_str << std::endl;     // Output shoud be "hua U";
    */

    return 0;
}


