#include "install.hpp"
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
Task(Main,SE){
    string RP="";
    string oldins;
    if (exists("APath"))
    {
        ifstream in("APath", ios::out);

        in >> oldins;
    }
    else{
        cout<<"Cant find previous installation Path exiting"<<endl;exit(0);
    }
    string cmd="./Bifton build src/:Bifton.cpp";
            system(cmd.c_str());

            cout<<"Updated cgp at: "<<oldins<<endl;
            ofstream i("APath",ios::out);
            i<<oldins<<endl;
            i.close();
}

    __Register(INSTALL,SE){

    }
