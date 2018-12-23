class AString{
public:
    // <1>
    AString operator()( int pos, int len );
    // <2> Moving operations;
    AString(AString &&ob)noexcept;
    AString &operator=(AString &&ob)noexcept;
    // <3> Safe deallocation;
    ~AString(){ if( ch ){ delete [] ch;} }
    // ....
};

AString AString::operator()( int pos, int len ){
    AString temp( len > 0?len:0 );      // <1> To ensure sufficient memory;
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
    //<3> swap works well for self-assignment;
    swap( ch, ob.ch );
    swap( curLength, ob.curLength );
    swap( maxSize, ob.maxSize );
    return *this;
}

AString str("Tsinghua University");
AString temp_str = std::move(str(5,5));
std::cout << temp_str << std::endl;      // Output shoud be "hua U";
