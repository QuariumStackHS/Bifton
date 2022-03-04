#include "ADV.hpp"
#include "ADV/AdvancedReltt.hpp"
namespace ADV
{
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
                
                RFI *ADVInterpreter = new RFI(&cancer);
                ADVInterpreter->INIT();
                ADVInterpreter->Execute();
            }
            else
                cout << "File=0" << endl;
        }
    }
    void Register(SimpleExecuter *SE)
    {
        SE->Register("adv", &ADV::RunScript);
    }
}