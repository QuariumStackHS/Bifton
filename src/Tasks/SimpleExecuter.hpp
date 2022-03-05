#ifndef SEMPLEEXECUTER_HPP
#define SEMPLEEXECUTER_HPP
#include "BCXX/BiftonCxx/BiftonCxx.hpp"

class SimpleExecuter
{
protected:
    map<string, void (*)(SimpleExecuter *)> Tasks;

    vector<string> Args;

public:
    map<string, bool> Switchs;
    int CurrentArgsIndex = 0;

    SimpleExecuter();
    virtual void Pass(int argc, char **argv);
    virtual string GetNextArg();
    virtual void Register(string Sw, void (*PtrAddress)(SimpleExecuter *));
    virtual void Run();
};
#define Task(FNCNAME,SimpleExecuterVarName)void FNCNAME(SimpleExecuter *SimpleExecuterVarName)
#define DLLExport(FNCNAME) extern "C" void FCNAME

#define DLLInit(Name) void (* Name )(SimpleExecuter*)

#endif