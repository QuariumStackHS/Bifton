#include "AdvancedReltt.hpp"
#include "SimpleExecuter.hpp"
#include <regex.h>
#include <thread>
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
        Deter->Bifton(Path, file);
        string Command;
        string ObjsPathName = "";
        string outputFile;
        int Compiler;
        string CompilerStandard;
#define CurrentFile Deter->CodePath[i]
#define OBJCurrent (SE->Switchs["--Assembly"]) ? get_S_name(CurrentFile) : get_o_name(CurrentFile)
        int OK = 0;
        string por;
        for (int i = 0; i < Deter->CodePath.size(); i++)
        {
            if (exists(OBJCurrent))
            {
                remove(OBJCurrent);
                por = OBJCurrent;
                cout << getCurrentTime() << BOLDBLUE << " Removed -> " << YELLOW << GetFName(por) << RESET << endl;
            }
        }
    }
    // Deter->Bifton(Path, file);
}
inline bool ends_with(std::string const &value, std::string const &ending)
{
    if (ending.size() > value.size())
        return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}
Task(RunScript, SE)
{
    string eArg = SE->GetNextArg();
    string Path = "";
    string file = "";
    SplitPATHSFromCommand(&Path, &file, &eArg);
    if(Path.size()==0)Path="./";
    if (exists(Path))
    {
        current_path(Path);
        if (exists(file))
        {
            ifstream F(file);
            stringstream ss;
            ss << F.rdbuf();
            string cancer=ss.str();
            //cout<<cancer<<endl;
            RFI *ADVInterpreter = new RFI(&cancer);
            ADVInterpreter->INIT();
            ADVInterpreter->Execute();
        }
        else
        cout<<"File=0"<<endl;
    }
}
Task(Bifton_Run, SE)
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
        Deter->Bifton(Path, file, 1);
        string Command;
        string ObjsPathName = "";
        string outputFile;
        int Compiler;
        string CompilerStandard;
        int OK;
#define CurrentFile Deter->CodePath[i]
        for (int i = 0; i < Deter->CodePath.size(); i++)
        {
            Compiler = (CurrentFile[CurrentFile.size() - 1] == 'c') ? GCC : GXX;
            CompilerStandard = (Compiler == 1) ? "-std=c++17" : "-std=c17";
            outputFile = (SE->Switchs["--Assembly"]) ? get_S_name(CurrentFile) : get_o_name(CurrentFile);
            Command = getCompiler(Compiler) + " " + Type + " -o" + outputFile + " " + CurrentFile + " " + CompilerStandard;
            OK = system(Command.c_str());
            cout << getCurrentTime() << BOLDBLUE << " ~> " << YELLOW << Command << RESET << endl;
            if (OK == 0)
            {
                if (i < Deter->objPath.size())
                    ObjsPathName.append(outputFile).append(" ");
            }
            else
            {

                cout << getCurrentTime() << BOLDRED << " Error Exiting Compiler reported: " << OK / 256 << endl;
                exit(OK);
            }
        }
        string LinkCommand = "gcc -lstdc++ " + ObjsPathName + " -O3 " + Deter->get_ALL_LinkageSwitch(' ') + " -o" + get_E_name(file);
        cout << getCurrentTime() << BOLDMAGENTA << " ~> " << YELLOW << LinkCommand << RESET << endl
             << BOLDMAGENTA << "\t" << Deter->LineAprox << RESET << " Line of Code Analysed " << endl;

        system(LinkCommand.c_str());
        Deter->print();
        delete Deter;
    }
}

int main(int argc, char **argv)
{
    string CPPStandardVersion;
    Get_Version(CPPStandardVersion);
    cout << "Bifton on " << getOsName() << ": Build done using " << CPPStandardVersion << "\n";
    SimpleExecuter *Session = new SimpleExecuter;
    Session->Register("build", &Bifton_Run);
    Session->Register("adv", &RunScript);
    Session->Register("clean", &Bifton_Clean);
    Session->Pass(argc, argv);
    Session->Run();

    return 0;
}