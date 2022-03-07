#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "../SimpleExecuter.hpp"
#include <filesystem>
using namespace filesystem;
__RegisterHPP(XOR)

#define GetK getKint(i, key)
#define XorerTask(WHAT, A, B)               \
    string Xorer ::WHAT(string A, string B) \
    {                                       \
        string output = "";
#define ENDXorTask \
    return output; \
    }
static inline int K = 0;
using namespace std;
class Xorer
{
public:
    static string Encrypt(string Data, string key);
    static string Decrypt(string Data, string key);
    static string GenKey(int Size);
};