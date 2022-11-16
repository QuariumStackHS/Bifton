#include "inma.hpp"

int main(int argc, char **argv)
{
    Pack Sa = Pack();
    // PackThisfile("./inma");
    for (int i = 0; i < argc; i++)
    { // cout<<argv[i]<<endl;
        if (strcmp(argv[i], "add") == 0)
        {
            Sa.Append(argv[i + 1], FileContent(argv[i + 1]));
            // Sa.WritePack(argv[i+2]);
        }
        else if (strcmp(argv[i], "write") == 0)
        {
            Sa.WritePack(argv[i + 1]);
        }
        else if (strcmp(argv[i], "read") == 0)
        {
            Sa.openPack(argv[i + 1]);
        }
        else if (strcmp(argv[i], "extract") == 0)
        {
            Sa.Dump(argv[i + 1]);
        }
        else if (strcmp(argv[i], "remove") == 0)
        {
            Sa.remove(argv[i + 1]);
        }
        else if (strcmp(argv[i], "extractall") == 0)
        {
            Sa.Dump();
        }
        else if (strcmp(argv[i], "list") == 0)
        {
            Sa.list();
        }
        else if (strcmp(argv[i], "help") == 0)
        {
            cout << "read [packname]\nwrite [packname]\nextract [fileFromPack]\nextractall\nremove [fileFromPack]\nlist\nhelp" << endl;
        }
    }

    return 0;
}
