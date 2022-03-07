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
#define EndTask(FNCNAME,NMFNCNAME) namespace NMFNCNAME {void (*PtrAddress)(SimpleExecuter *)= &FNCNAME;}
#define __Register(NameSpace,SimpleExecuterVarName)void NameSpace::Register(SimpleExecuter *SimpleExecuterVarName)
#define __GRegister(NameSpace) NameSpace :: Register
#define __RegisterHPP(NameSpace)namespace NameSpace{ void Register(SimpleExecuter *);}
#define DLLExport(FNCNAME) extern "C" void FCNAME

#define DLLInit(Name) void (* Name )(SimpleExecuter*)

#endif