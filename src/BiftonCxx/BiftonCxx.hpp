#ifndef BIFTONCXX_HPP
#define BIFTONCXX_HPP

#include <filesystem>
#include "Data/ComputerInfo.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */
#define RESET "\033[0m"
#define BLACK "\033[30m"   /* Black */
#define RED "\033[31m"     /* Red */
#define GREEN "\033[32m"   /* Green */
#define YELLOW "\033[33m"  /* Yellow */
#define BLUE "\033[34m"    /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m"
using namespace std;
using namespace filesystem;
string FMP(string g);
inline void replace(string &input, const string &from, const string &to)
{
    auto pos = 0;
    while (true)
    {
        size_t startPosition = input.find(from, pos);
        if (startPosition == string::npos)
            return;
        input.replace(startPosition, from.length(), to);
        pos += to.length();
    }
}
inline string get_c_name(string name)
{
    string ret = name;
    replace(ret, ".h", ".c");
    return ret;
}
string getCurrentTime();
inline string get_o_name(string name)
{
    string ret = name;
    replace(ret, ".cpp", ".o");
    replace(ret, ".c", ".o");
    return ret;
}
inline string get_E_name(string name)
{
    string ret = name;
    replace(ret, ".cpp", "");
    replace(ret, ".c", "");
    return ret;
}
inline string get_S_name(string name)
{
    string ret = name;
    replace(ret, ".cpp", ".s");
    replace(ret, ".c", ".s");
    return ret;
}
class Deterministix
{
protected:
    // s1=#include "includename" s2=added switch for linkage
    map<string, string> I2SL; // Include2linkageswitchToAdd
    map<string, bool> I2SLB;  // Include2IfOrNotIsPresent
    map<string, bool> Treated;
    map<string, string> C2SC;
    map<string, bool> C2SB;

public:
int LineAprox=0;
    vector<string> CodePath;
    vector<string> objPath;
    Deterministix();
    void Register(string, string);
    void print();
    string get_ALL_LinkageSwitch(char Separator);
    void Bifton(string, string, bool Print = 0);
};
string GetFName(string path);
#endif