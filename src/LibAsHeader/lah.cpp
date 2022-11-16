#include "lah.hpp"
namespace LAH
{
    using namespace std;
string cuttree(string K)
{
    string reversed = "", unreversed = "";
    for (int i = K.size() - 1; K[i] != '/'; i--)
        reversed.push_back(K[i]);
    for (int i = reversed.size(); i != -1; i--)
        unreversed.push_back(reversed[i]);
    return unreversed;
}
void SetStackLimit(int MB)
{
    const rlim_t kStackSize = MB * 1000 * 1024;
    assert(0 == getrlimit(RLIMIT_STACK, &rl));
    isNOTfatal(assert(rl.rlim_cur < kStackSize) isfatal);
    rl.rlim_cur = kStackSize;
    assert(0 == setrlimit(RLIMIT_STACK, &rl)) isfatal;
}
};
void BeforeMain(){
    
}