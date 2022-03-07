#include "Registry.hpp"
#include "ADV/ADV.hpp"
#include "xor/Xor.hpp"
#include "Install/install.hpp"

void Register(SimpleExecuter*SE){
    __GRegister(BCXX)(SE);
    __GRegister(ADV)(SE);
    __GRegister(INSTALL)(SE);
    __GRegister(XOR)(SE);
}