#include "BiftonCxx/BiftonCxx.hpp"

class SimpleExecuter
{
protected:
    map<string, void (*)(SimpleExecuter *)> Tasks;

    vector<string> Args;

public:
    map<string, bool> Switchs;
    int CurrentArgsIndex = 0;

    SimpleExecuter();
    void Pass(int argc, char **argv);
    string GetNextArg();
    void Register(string Sw, void (*PtrAddress)(SimpleExecuter *));
    void Run();
};
#define Task(FNCNAME,SimpleExecuterVarName)void FNCNAME(SimpleExecuter *SimpleExecuterVarName)