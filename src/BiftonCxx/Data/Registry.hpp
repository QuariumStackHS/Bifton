#include "../BiftonCxx.hpp"

void RegisterDet(Deterministix *This)
{
    This->Register(FMP("thread"), "-lpthread");
    This->Register(FMP("gmpxx.h"), "-lgmp");
    This->Register(FMP("gmp.h"), "-lgmp");
    This->Register(FMP("dlfcn.h"),"-ldl");
}