#include "BiftonCxx/BiftonCxx.hpp"

class SimpleExecuter
{
protected:
    map<string, void (*)(SimpleExecuter *)> Tasks;

    vector<string> Args;

public:
    map<string, bool> Switchs;
    int CurrentArgsIndex = 0;

    SimpleExecuter()
    {
    }
    void Pass(int argc, char **argv)
    {
        for (int i = 0; i < argc; i++)
        {
            Args.push_back(string(argv[i]));
        }
    }
    string GetNextArg() { return (this->CurrentArgsIndex < this->Args.size()) ? Args[++CurrentArgsIndex] : ""; }
    void Register(string Sw, void (*PtrAddress)(SimpleExecuter *))
    {
        Tasks[Sw] = PtrAddress;
    }
    void Run()
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
};
// argv[0] run PATH:MainFile
#define GCC 0
#define GXX 1
string getCompiler(int C)
{
    switch (C)
    {
    case GCC:
        return "gcc";
        break;
    case GXX:
        return "g++";
        break;
    default:
        return "None";
        break;
    }
}
void SplitPATHSFromCommand(string *Path, string *file, string *eArg)
{
    for (int i = 0; (eArg->at(i) != (':')) && (i != eArg->size()); i++)
    {
        Path->push_back(eArg->at(i));
    }
    for (int i = Path->size() + 1; i < eArg->size(); i++)
    {
        file->push_back(eArg->at(i));
    }
}
void Bifton_Clean(SimpleExecuter *SE)
{
    string eArg = SE->GetNextArg();
    string Path = "";
    string file = "";
    Deterministix *Deter = new Deterministix;
    SplitPATHSFromCommand(&Path, &file, &eArg);
    Deter->Bifton(Path, file);
    if (strcmp(file.c_str(), "") == 0)
    {
        cout << YELLOW << "Bad Syntaxe: " << BOLDRED << Path << RESET << BLUE << " -> [try 'Path:MainFile' as syntaxe]" << RESET << endl;
    }
    else
    {
    }
    // Deter->Bifton(Path, file);
}
inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}
void Bifton_Run(SimpleExecuter *SE)
{
    string eArg = SE->GetNextArg();
    string Path = "";
    string file = "";
    SplitPATHSFromCommand(&Path, &file, &eArg);
    string Type = (SE->Switchs["--Assembly"]) ? "-S" : "-c";

    if (strcmp(file.c_str(), "") == 0)
    {
        cout << YELLOW << "Bad Syntaxe: " << BOLDRED << Path << RESET << BLUE << " -> [try 'Path:MainFile' as syntaxe]" << RESET << endl;
    }
    else
    {

        Deterministix *Deter = new Deterministix;
        Deter->Bifton(Path, file);
        string Command;
        string ObjsPathName = "";
        string outputFile;
        int Compiler;
        string CompilerStandard;
#define CurrentFile Deter->CodePath[i]
        for (int i = 0; i < Deter->CodePath.size(); i++)
        {
                Compiler = (CurrentFile[CurrentFile.size() - 1] == 'c') ? GCC : GXX;
                CompilerStandard = (Compiler == 1) ? "-std=c++17" : "-std=c17";
                outputFile = (SE->Switchs["--Assembly"]) ? get_S_name(CurrentFile) : get_o_name(CurrentFile);
                Command = getCompiler(Compiler) + " " + Type + " -o" + outputFile + " " + CurrentFile + " " + CompilerStandard;
                cout << BOLDBLUE "~> " << YELLOW << Command << RESET << endl;
            

            if (system(Command.c_str()) == 0)
            {
                if (i < Deter->objPath.size())
                    ObjsPathName.append(outputFile).append(" ");
            }
        }
        string LinkCommand = "gcc -lstdc++ " + ObjsPathName + " -O3 " + Deter->get_ALL_LinkageSwitch(' ') + " -o" + get_E_name(file);
        cout << BOLDBLUE << "Final ~> " << YELLOW << LinkCommand << RESET << endl;
        system(LinkCommand.c_str());
        Deter->print();
        delete Deter;
    }
}

int main(int argc, char **argv)
{
    SimpleExecuter *Session = new SimpleExecuter;
    Session->Register("build", &Bifton_Run);
    Session->Register("clean", &Bifton_Clean);
    Session->Pass(argc, argv);
    Session->Run();
    return 0;
}