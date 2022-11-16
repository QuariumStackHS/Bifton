#include<string>
#include <cstring>
inline std::string getOsName()
{
#ifdef _WIN32
    return "Windows 32-bit";
#elif _WIN64
    return "Windows 64-bit";
#elif __APPLE__ || __MACH__
    return "Mac OSX";
#elif __linux__
    return "Linux";
#elif __FreeBSD__
    return "FreeBSD";
#elif __unix || __unix__
    return "Unix";
#else
    return "Other";
#endif
}
#define Get_Version(Version)\
if (__cplusplus == 201703)\
    Version = "C++17";\
else if (__cplusplus == 201402)\
    Version = "C++14";\
else if (__cplusplus == 201103)\
    Version = "C++11";\
else if (__cplusplus == 199711)\
    Version = "C++98";\
else if (__cplusplus == 201707)\
    Version = "C++20";\
else\
    Version = "pre-standard C++";