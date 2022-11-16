#include "Tasks/Registry.hpp"
#define Main
#include <iomanip>
#include "Tasks/BCXX/BiftonCxx/Signataire.hpp" // test


int main(int argc, char **argv)
{



    string CPPStandardVersion;
    Get_Version(CPPStandardVersion);
    SimpleExecuter *Session = new SimpleExecuter;
    Register(Session);
    Session->Pass(argc, argv);
    Session->Run();
    return 0;
}

/*

*/