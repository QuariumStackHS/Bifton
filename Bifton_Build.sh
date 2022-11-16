g++ -c -o./src/Tasks/BCXX/BiftonCxx/BiftonCxx.o ./src/Tasks/BCXX/BiftonCxx/BiftonCxx.cpp -std=c++17
g++ -c -o./src/Tasks/BCXX/BiftonCxx/SHA1/SHA1.o ./src/Tasks/BCXX/BiftonCxx/SHA1/SHA1.cpp -std=c++17
g++ -c -o./src/Tasks/SimpleExecuter.o ./src/Tasks/SimpleExecuter.cpp -std=c++17
g++ -c -o./src/Tasks/BCXX/BCXX.o ./src/Tasks/BCXX/BCXX.cpp -std=c++17
g++ -c -o./src/Tasks/Registry.o ./src/Tasks/Registry.cpp -std=c++17
g++ -c -o./src/Tasks/ADV/ADV.o ./src/Tasks/ADV/ADV.cpp -std=c++17
g++ -c -o./src/Tasks/Install/install.o ./src/Tasks/Install/install.cpp -std=c++17
g++ -c -o./src/Bifton.o ./src/Bifton.cpp -std=c++17
gcc -lstdc++ ./src/Tasks/BCXX/BiftonCxx/BiftonCxx.o ./src/Tasks/BCXX/BiftonCxx/SHA1/SHA1.o ./src/Tasks/SimpleExecuter.o ./src/Tasks/BCXX/BCXX.o ./src/Tasks/Registry.o ./src/Tasks/ADV/ADV.o ./src/Tasks/Install/install.o ./src/Bifton.o -O3  -oBifton

