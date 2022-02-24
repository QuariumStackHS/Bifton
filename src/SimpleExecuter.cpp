#include "SimpleExecuter.hpp"

    void SimpleExecuter::Pass(int argc, char **argv)
    {
        for (int i = 0; i < argc; i++)
        {
            Args.push_back(string(argv[i]));
        }
    }
    SimpleExecuter::SimpleExecuter(){}
string SimpleExecuter::GetNextArg() { return (this->CurrentArgsIndex < this->Args.size()) ? Args[++CurrentArgsIndex] : ""; }
    void SimpleExecuter::Register(string Sw, void (*PtrAddress)(SimpleExecuter *))
    {
        Tasks[Sw] = PtrAddress;
    }
    void SimpleExecuter::Run()
    {

        void (*PtrAddress)(SimpleExecuter *);
        bool KnownError = 0;
        string CurrentArg;
        while (this->CurrentArgsIndex < this->Args.size())
        {
            CurrentArg = GetNextArg();
            if (CurrentArg[0] == '-')
                this->Switchs[CurrentArg] = 1;
            else
            {
                PtrAddress = this->Tasks[CurrentArg];
                KnownError = (PtrAddress == 0) ? 1 : 0;
                if (!KnownError)
                    (*PtrAddress)(this);
            }
        }
    }