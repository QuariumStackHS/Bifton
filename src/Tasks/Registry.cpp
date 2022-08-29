#include "Registry.hpp"
#include "ADV/ADV.hpp"
#include "Install/install.hpp"

void Register(SimpleExecuter*SE){
    __GRegister(BCXX)(SE);
    __GRegister(ADV)(SE);
    __GRegister(NONEXX)(SE);

}