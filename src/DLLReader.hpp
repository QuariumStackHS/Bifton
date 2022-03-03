#include "SimpleExecuter.hpp"
#include <dlfcn.h>
#include <filesystem>
void splitString(vector<string> &FP, string str, string delimiter = " ");
inline void LoadAllDlls(SimpleExecuter *SE, string Path)
{
    string tempPath = current_path();
    const std::filesystem::path sandbox{Path};
    if (exists(Path))
    {DLLInit(PTR);
        void*handle;
        vector<string> Files;
        for (const std::filesystem::directory_entry &dir_entry :
             std::filesystem::directory_iterator{sandbox})
        {
                cout<<dir_entry.path();
                handle = dlopen(dir_entry.path().c_str(), RTLD_LAZY);
                
                PTR = (void (*)(SimpleExecuter *))dlsym(handle, "Registry");
                PTR(SE);
        }
        current_path(tempPath);
    }
}
