#include "SimpleExecuter.hpp"
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
int OK=0;
string por;
        for (int i = 0; i < Deter->CodePath.size(); i++)
        {
            if(exists(OBJCurrent)){
                remove(OBJCurrent);
                por=OBJCurrent;
                cout<<BOLDBLUE<<"Removed -> "<<YELLOW<<por<<RESET<<endl;
            }
        }
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
int OK=0;
        for (int i = 0; i < Deter->CodePath.size(); i++)
        {
                Compiler = (CurrentFile[CurrentFile.size() - 1] == 'c') ? GCC : GXX;
                CompilerStandard = (Compiler == 1) ? "-std=c++17" : "-std=c17";
                outputFile = (SE->Switchs["--Assembly"]) ? get_S_name(CurrentFile) : get_o_name(CurrentFile);
                Command = getCompiler(Compiler) + " " + Type + " -o" + outputFile + " " + CurrentFile + " " + CompilerStandard;
                cout << BOLDBLUE "~> " << YELLOW << Command << RESET<< endl;


            OK=system(Command.c_str());
            if(0==OK){
                if (i < Deter->objPath.size())
                    ObjsPathName.append(outputFile).append(" ");
            }
            else{

                cout<<BOLDRED<<"Error Exiting Compiler reported: "<<OK/256<<endl;
                exit(OK);
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