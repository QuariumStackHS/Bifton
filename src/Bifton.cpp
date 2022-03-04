#include "ADV/AdvancedReltt.hpp"
//#include "DLLReader.hpp"
//#include "SQLite3/sqlite3.h"
#include "Tasks/Registry.hpp"
#include <iomanip>


#include <regex.h>
// argv[0] run PATH:MainFile



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




int main(int argc, char **argv)
{
    string CPPStandardVersion;
    Get_Version(CPPStandardVersion);
    // cout << "Bifton on " << getOsName() << ": Build done using " << CPPStandardVersion << "\n";
    SimpleExecuter *Session = new SimpleExecuter;
    Register(Session);
    Session->Register("adv", &RunScript);
    //LoadAllDlls(Session,"DLLs");
    Session->Pass(argc, argv);
    Session->Run();
    return 0;
}