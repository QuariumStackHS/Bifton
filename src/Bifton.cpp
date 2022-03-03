#include "ADV/AdvancedReltt.hpp"
//#include "DLLReader.hpp"
//#include "SQLite3/sqlite3.h"
#include "SimpleExecuter.hpp"
#include <iomanip>
void ShowBand(string Var)
{
    cout << "\t ";
    for (int i = 0; i < 20 - (Var.size() - 1); i++)
        cout << RED << "═";
    cout << BOLDGREEN << Var << RESET;
    for (int i = 0; i < 20 - (Var.size() - 1); i++)
        cout << RED << "═" << RESET;
    cout << endl;
}

#include <regex.h>
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
    if (Path.size() == 0)
        Path = "./";
    if (exists(Path))
    {
        current_path(Path);
        if (exists(file))
        {
            ifstream F(file);
            stringstream ss;
            ss << F.rdbuf();
            string cancer = ss.str();
            // cout<<cancer<<endl;
            RFI *ADVInterpreter = new RFI(&cancer);
            ADVInterpreter->INIT();
            ADVInterpreter->Execute();
        }
        else
            cout << "File=0" << endl;
    }
}
std::ifstream::pos_type filesize(const char *filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
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
        cout << YELLOW << "Bad Syntaxe: " << BOLDRED << Path << RESET << BLUE << " -> [try \"(--Assembly/--FileCreate) build  'Path:MainFile'\" as syntaxe]" << RESET << endl;
    }
    else
    {

        Deterministix *Deter = new Deterministix;
        
        bool SHA = !SE->Switchs["--SkipSHA1"];
        Deter->Bifton(Path, file,!SE->Switchs["--Silence"], SHA);
        if(!SE->Switchs["--Silence"])
        ShowBand("Analysing");
        string Command;
        string ObjsPathName = "";
        string outputFile;
        int Compiler;
        string CompilerStandard;
        int OK = 0;
        vector<string> Commands;
#define CurrentFile Deter->CodePath[i]
#define CurrentoutFile Deter->objPath[i]
        ShowBand("Compiling");
        long long RSize;
        
        Sizer SeS=Sizer(' ',' ');
         
        for (int i = 0; i < Deter->CodePath.size(); i++)
        {
            OK = 0;
            outputFile = (SE->Switchs["--Assembly"]) ? get_S_name(CurrentoutFile) : get_o_name(CurrentoutFile);
            if (Deter->CodePath[i].size() > 0)
            {
                
                Compiler = (CurrentFile[CurrentFile.size() - 1] == 'c') ? GCC : GXX;
                CompilerStandard = (Compiler == 1) ? "-std=c++17" : "-std=c17";
                Command = getCompiler(Compiler) + " " + Type + " -o" + outputFile + " " + CurrentFile + " " + CompilerStandard;

                Commands.push_back(Command);
                OK = system(Command.c_str());
                RSize= filesize(outputFile.c_str());
                SeS= sizetoK(RSize, 1024);
                cout << getCurrentTime() << BOLDBLUE << " ~> " << YELLOW << Command << RESET<<" -> "<<setprecision(3)<<MAGENTA<<SeS.data<<BOLDMAGENTA<<SeS.c<<"B"<<RESET<< endl;
            }

            else
            {
                cout << getCurrentTime() << setprecision(3) << BOLDMAGENTA << " ~> Object " << YELLOW << Deter->objPath[i] << BOLDMAGENTA << " Have been skipped" << RESET << endl;
            }

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
        string LinkCommand;
        Sizer S=sizetoK(Deter->LineAprox);
        Sizer SFE=sizetoK(Deter->RealLine);
        if (Commands.size() >= 1)
        {
            ShowBand("!Linking!");
            LinkCommand = "gcc -lstdc++ " + ObjsPathName + " -O3 " + Deter->get_ALL_LinkageSwitch(' ') + " -o" + get_E_name(file);
            Commands.push_back(LinkCommand);
            cout << getCurrentTime() << BOLDMAGENTA << " ~> " << YELLOW << LinkCommand << RESET << endl;
        }
        else{
            cout<<getCurrentTime()<<BOLDGREEN" ~> Nothing To link"<<RESET<<endl;
        }

        ShowBand("Task Done");
        cout <<setprecision(6)<< "\t -> Line of Code : " << MAGENTA << S.data << BOLDMAGENTA << S.c << RESET<<" / "<< MAGENTA << SFE.data << BOLDMAGENTA << SFE.c<<RESET<<" ( "<<RED<<setprecision(3)<<100*((double)Deter->RealLine/(double)Deter->LineAprox)<<RESET<<"% )" << endl;
        string FullFile = "";
        for (int i = 0; i < Commands.size(); i++)
            FullFile.append(Commands[i]).append("\n");
        string CPATE = current_path();
        replace(FullFile, CPATE, ".");
        system(LinkCommand.c_str());
        RSize = filesize(get_E_name(file).c_str());
        Sizer Se = sizetoK(RSize, 1024);
        cout <<setprecision(3)<< "\t -> Executable Size \t\t  : " << MAGENTA << Se.data << BOLDMAGENTA << Se.c << "B" << RESET << endl;
        if (SE->Switchs["--FileCreate"])
        {
            ofstream Cout(get_E_name(file) + "_Build.sh");
            Cout << FullFile << endl;
            Cout.close();
        }
        Deter->print();
        delete Deter;
    }
}

int main(int argc, char **argv)
{
    string CPPStandardVersion;
    Get_Version(CPPStandardVersion);
    // cout << "Bifton on " << getOsName() << ": Build done using " << CPPStandardVersion << "\n";
    SimpleExecuter *Session = new SimpleExecuter;
    Session->Register("build", &Bifton_Run);
    Session->Register("adv", &RunScript);
    Session->Register("clean", &Bifton_Clean);
    //LoadAllDlls(Session,"DLLs");
    Session->Pass(argc, argv);
    Session->Run();
    return 0;
}