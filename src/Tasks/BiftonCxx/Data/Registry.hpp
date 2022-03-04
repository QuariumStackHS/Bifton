#include "../BiftonCxx.hpp"

void RegisterDet(Deterministix *This)
{
    This->Register(FMP("thread"), "-lpthread")
        ->Register(FMP("gmpxx.h"), "-lgmp")
        ->Register(FMP("gmp.h"), "-lgmp")
        ->Register(FMP("dlfcn.h"), "-ldl");
}
