#include "LibAsHeader/lah.hpp"

int main(int argc,char**argv){
if(argc==1)
cout<<"Specify Target like main.cpp"<<endl,exit(0);
string Bifton_args="--SkipSHA1 --FileCreate build ";
Bifton_args.append(argv[1]);
string BiftonC="./Bifton "+Bifton_args;
system(BiftonC.c_str());
return 0;
}