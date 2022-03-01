#include "AdvancedReltt.hpp"

int main(int argc,char**argv){
    if(argc==1){
        Help();
        cout<<"Usage : "<<argv[0]<<" File.Adv"<<endl;
    }
    else{
        ifstream F(argv[1]);
        stringstream ss;
        ss<<
        F.rdbuf();
        string *Code=new string(ss.str());
        RFI *R=new RFI(Code);
        R->INIT();
        R->Execute();

    }
}