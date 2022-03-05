#include "Registry.hpp"
#include "ADV/ADV.hpp"
void Register(SimpleExecuter*SE){
    BCXX::Register(SE);
    ADV::Register(SE);

}