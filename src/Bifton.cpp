#include "Tasks/Registry.hpp"
#include <iomanip>
#include <regex.h>
inline bool ends_with(std::string const &value, std::string const &ending)
{
    if (ending.size() > value.size())
        return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}





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