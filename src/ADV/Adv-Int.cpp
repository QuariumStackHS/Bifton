#include "AdvancedReltt.hpp"

int main(int argc,char**argv){
    int ret=1;
    if(argc!=1){
        ifstream F(argv[1]);
        stringstream ss;
        ss<<
        F.rdbuf();
        string *Code=new string(ss.str());
        RFI *R=new RFI(Code);
        R->INIT();
        R->Execute();
        ret=R->DataSegm->This;
    }
    return ret;
}