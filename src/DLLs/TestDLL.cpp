#include "../SimpleExecuter.hpp"
Task(Test,SE){
    cout<<"Test"<<endl;
}
DLLExport(Registry)(SimpleExecuter*SE){
SE->Register("Test",&Test);

}