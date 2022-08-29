#include "SimpleExecuter.hpp"
#include <iostream>
void SimpleExecuter::Pass(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        Args.push_back(string(argv[i]));
    }
}
SimpleExecuter::SimpleExecuter() {}
string SimpleExecuter::GetNextArg() { return (this->CurrentArgsIndex < this->Args.size()) ? Args[++CurrentArgsIndex] : ""; }
void SimpleExecuter::Register(string Sw, void (*PtrAddress)(SimpleExecuter *))
{
    Tasks[Sw] = PtrAddress;
}
int main(int,char**);
void SimpleExecuter::PrintHelp()
{
    u_int64_t valg =(u_int64_t) &main;
    for (auto const &[key, val] : this->Tasks)
    {

        //if (key.size() != 1)
        //{
            std::cout << getCurrentTime() << MAGENTA << " " << sizetoK((valg - (u_int64_t)val), 1024).data << BOLDMAGENTA << sizetoK((valg - (u_int64_t)val), 1024).c << "B " << RESET << "<-" << key // string (key)
                      << std::endl;
        //}
        valg = (u_int64_t)val;
    }
}
void SimpleExecuter::Run()
{

    void (*PtrAddress)(SimpleExecuter *);
    bool KnownError = 0;
    string CurrentArg;
    while (this->CurrentArgsIndex + 1 < this->Args.size())
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
            else if (CurrentArg.size() > 0)
                cout << "Unknows Arg: " << CurrentArg << endl;
        }
    }
}