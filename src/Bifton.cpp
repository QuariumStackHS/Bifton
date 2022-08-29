#include "Tasks/Registry.hpp"
#define Main
#include <iomanip>
#include "Tasks/BCXX/BiftonCxx/Signataire.hpp"


int main(int argc, char **argv)
{
    string SigFile = argv[0];
    SigFile.append(".Sig");
    RSA V;

    if (exists(SigFile))
    {
        RSA S(argv[0]);
        
        if (!S.VerifySig(argv[0]) || !exists(string(argv[0]) + ".Sig"))
        {
            cout << "Signature Altered!\nSign it!" << endl;

            V.SaveSig(argv[0]);
            //cout << "Private D:" << double2longlong(V.d) << endl;
        }
        else
            cout << "Signature UnAltered!" << endl;
    }
    else
    {

        cout << "Signing Executable..." << endl;
        RSA V;
        //cout << double2longlong(V.d) << endl;
    }
    string CPPStandardVersion;
    Get_Version(CPPStandardVersion);
    SimpleExecuter *Session = new SimpleExecuter;
    Register(Session);
    Session->Pass(argc, argv);
    Session->Run();
    return 0;
}