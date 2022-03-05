#include "BCXX.hpp"
namespace BCXX
{
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
Task(Bifton_Clean,SE)
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
}
    Task(Bifton_build, SE)
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
            if (!SE->Switchs["--Silence"])
                ShowBand("Analysing");
            Deter->Bifton(Path, file, !SE->Switchs["--Silence"], SHA);
            cout <<getCurrentTime()<<BOLDYELLOW<<" Analysed  -> "<<RESET<<MAGENTA<< Deter->AnalysedFiles<<BOLDYELLOW<<" Files"<<RESET<<endl;
            string CPATE = current_path();
            string Tempcomand="";
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

            Sizer SeS = Sizer(' ', ' ');

            for (int i = 0; i < Deter->CodePath.size(); i++)
            {
                OK = 0;
                outputFile = (SE->Switchs["--Assembly"]) ? get_S_name(CurrentoutFile) : get_o_name(CurrentoutFile);
                if (Deter->CodePath[i].size() > 0)
                {

                    Compiler = (CurrentFile[CurrentFile.size() - 1] == 'c') ? GCC : GXX;
                    CompilerStandard = (Compiler == 1) ? "-std=c++17" : "-std=c17";
                    Command = getCompiler(Compiler) + " " + Type + " -o" + outputFile + " " + CurrentFile + " " + CompilerStandard;
                    
                    Tempcomand=Command;    
                    replace(Tempcomand, CPATE, ".");
                    Commands.push_back(Command);
                    OK = system(Command.c_str());
                    RSize = filesize(outputFile.c_str());
                    SeS = sizetoK(RSize, 1024);
                    cout << getCurrentTime() << BOLDBLUE << " ~> " << YELLOW << Tempcomand<< RESET << " -> " << setprecision(3) << MAGENTA << SeS.data << BOLDMAGENTA << SeS.c << "B" << RESET << endl;
                }

                else
                {
                    Tempcomand=Deter->objPath[i];
                    replace(Tempcomand, CPATE, ".");
                    cout << getCurrentTime() << setprecision(3) << BOLDMAGENTA << " ~> Object " << YELLOW << Tempcomand << BOLDMAGENTA << " Have been skipped" << RESET << endl;
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
            Sizer S = sizetoK(Deter->LineAprox);
            Sizer SFE = sizetoK(Deter->RealLine);

            if ((Commands.size() >= 1) ||(!exists(get_E_name(file))))
            {
                ShowBand("!Linking!");
                LinkCommand = "gcc -lstdc++ " + ObjsPathName + "-O3" + Deter->get_ALL_LinkageSwitch(' ') + " -o" + get_E_name(file);
                Commands.push_back(LinkCommand);
                    Tempcomand=LinkCommand;    
                    replace(Tempcomand, CPATE, ".");

                cout << getCurrentTime() << BOLDMAGENTA << " ~> " << YELLOW << Tempcomand << RESET << endl;
            }
            else
            {
                cout << getCurrentTime() << BOLDGREEN " ~> Nothing To link" << RESET << endl;
            }

            ShowBand("Task Done");
            cout << setprecision(3) << "\t -> Line of Code : " << MAGENTA << S.data << BOLDMAGENTA << S.c << RESET << " / " << MAGENTA << SFE.data << BOLDMAGENTA << SFE.c << RESET << " ( " << RED<< 100 * ((double)Deter->RealLine / (double)Deter->LineAprox) << RESET << "% )" << endl;
            string FullFile = "";

            for (int i = 0; i < Commands.size(); i++)
                FullFile.append(Commands[i]).append("\n");
            CPATE = current_path();
            replace(FullFile, CPATE, ".");
            system(LinkCommand.c_str());
            RSize = filesize(get_E_name(file).c_str());
            Sizer Se = sizetoK(RSize, 1024);
            cout << setprecision(3) << "\t -> Executable Size \t\t  : " << MAGENTA << Se.data << BOLDMAGENTA << Se.c << "B" << RESET << endl;

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
    void Register(SimpleExecuter*SE){
        SE->Register("build",&Bifton_build);
        SE->Register("clean",&Bifton_Clean);
    }
}