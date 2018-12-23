#ifndef ASTRING_H_
#define ASTRING_H_

#include <iostream>
#include <cstring>

#define defaultSize 128
class AString
{
public:
    AString(int sz = defaultSize);
    AString(const char *init);
    AString(const AString &ob);

    //AString* operator()( int pos, int len );
    //void operator()( int pos, int len, AString &ob );
    AString operator()( int pos, int len );
    AString(AString &&ob)noexcept;
    AString &operator=(AString &&ob)noexcept;
    ~AString(){ if( ch ){ delete [] ch;} }

    void reserve( int sz );
    int Length()const{ return curLength; }
    bool operator==(const AString& ob)const{ return strcmp(ch, ob.ch) == 0; }
    bool operator!=(const AString& ob)const{ return !(*this == ob); }
    bool operator!()const{ return Length() == 0; }
    friend std::ostream &operator<<(std::ostream &os, const AString & ob);
//    AString &operator=(const AString &ob);
//    AString &operator+=(const AString &ob);
//    char &operator[](int i);
//    const char &operator[](int i)const;
//    int Find( const AString & pat )const;
private:
    char *ch;
    int curLength;
    int maxSize;
};


AString::AString(int sz ):curLength(0),maxSize(sz){
    try{ ch = new char[maxSize + 1]; }
    catch( const std::bad_alloc & ba ){ std::cout << __func__ << ": " << ba.what() << std::endl; exit(EXIT_FAILURE); }
    ch[0] = '\0';
}

AString::AString(const char * init ):curLength(std::strlen(init)){
    maxSize = ( curLength > defaultSize ) ? curLength : defaultSize;
    try{ ch = new char[maxSize + 1]; }
    catch( const std::bad_alloc & ba ){ std::cout << __func__ << ": " << ba.what() << std::endl; exit(EXIT_FAILURE); }
    std::strcpy( ch, init );
}
AString::AString(const AString &ob)
    :curLength(ob.curLength),maxSize(ob.maxSize){
    try{ ch = new char[maxSize + 1]; }
    catch( const std::bad_alloc & ba ){ std::cout << __func__ << ": " << ba.what() << std::endl; exit(EXIT_FAILURE); }
    std::strcpy( ch, ob.ch );
}

std::ostream &operator<<(std::ostream &os, const AString & ob){
    os << ob.ch;
    return os;
}

void AString::reserve( int sz ){
    if( maxSize >= sz ){ return; }
    // Alloc more memory, and copy original characters to it
    maxSize = sz;
    char * new_ch = new char[maxSize + 1];
    if( !new_ch ){ std::cerr << __func__ << ": Failed to alloc memory\n"; exit(EXIT_FAILURE); }
    strcpy( new_ch, ch );
    // Destroy original data
    delete [] ch;
    ch = new_ch;
}

/*
// Method 1
AString * AString::operator()( int pos, int len ){
    // <1> To ensure sufficient memory
    AString *temp = new AString( len > 0?len:0 );

    if( pos < 0 || pos + len - 1 >= maxSize || len < 0 ){
        temp->curLength = 0; temp->ch[0] = '\0';
    }else{
        if( pos + len - 1 >= curLength ) len = curLength - pos;
        temp->curLength = len;
        for( int i = 0, j = pos; i < len; ++i, ++j ) temp->ch[i] = ch[j];
        temp->ch[len] = '\0';
    }
    return temp;
}
*/

/*
// Method 2
void AString::operator()( int pos, int len, AString & temp){
    if( pos < 0 || pos + len - 1 >= maxSize || len < 0 ){
        temp.curLength = 0; temp.ch[0] = '\0';
    }else{
        if( pos + len - 1 >= curLength ) len = curLength - pos;

        // <1> To ensure sufficient memory
        if( temp.maxSize < len ){
            delete [] temp.ch;
            temp.ch = new char[len + 1];
            if( !temp.ch ){ std::cerr << __func__ << ": Failed to alloc memory\n"; exit(EXIT_FAILURE); }
            temp.maxSize = len;
        }

        temp.curLength = len;
        for( int i = 0, j = pos; i < len; ++i, ++j ) temp.ch[i] = ch[j];
        temp.ch[len] = '\0';
    }
}
*/


// Method 3
AString AString::operator()( int pos, int len ){
    AString temp( len > 0?len:0 );    // <1> To ensure sufficient memory
    if( pos < 0 || pos + len - 1 >= maxSize || len < 0 ){
        temp.curLength = 0; temp.ch[0] = '\0';
    }else{
        if( pos + len - 1 >= curLength ) len = curLength - pos;
        temp.curLength = len;
        for( int i = 0, j = pos; i < len; ++i, ++j ) temp.ch[i] = ch[j];
        temp.ch[len] = '\0';
    }
    return temp;
}

AString::AString(AString &&ob) noexcept
    :ch(ob.ch),curLength(ob.curLength),maxSize(ob.maxSize){
    ob.ch = NULL;
    ob.curLength = 0;
    ob.maxSize = 0;
}

AString &AString::operator=(AString &&ob) noexcept{
    //<3> swap works well for self-assignment
    swap( ch, ob.ch );
    swap( curLength, ob.curLength );
    swap( maxSize, ob.maxSize );
    return *this;
}



#endif
