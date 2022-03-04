g++ -c -o./src/Tasks/BiftonCxx/BiftonCxx.o ./src/Tasks/BiftonCxx/BiftonCxx.cpp -std=c++17
g++ -c -o./src/Tasks/BiftonCxx/SHA1/SHA1.o ./src/Tasks/BiftonCxx/SHA1/SHA1.cpp -std=c++17
g++ -c -o./src/Tasks/SimpleExecuter.o ./src/Tasks/SimpleExecuter.cpp -std=c++17
g++ -c -o./src/Tasks/BCXX.o ./src/Tasks/BCXX.cpp -std=c++17
g++ -c -o./src/Tasks/ADV.o ./src/Tasks/ADV.cpp -std=c++17
g++ -c -o./src/Tasks/Registry.o ./src/Tasks/Registry.cpp -std=c++17
g++ -c -o./src/Bifton.o ./src/Bifton.cpp -std=c++17
gcc -lstdc++ ./src/Tasks/BiftonCxx/BiftonCxx.o ./src/Tasks/BiftonCxx/SHA1/SHA1.o ./src/Tasks/SimpleExecuter.o ./src/Tasks/BCXX.o ./src/Tasks/ADV.o ./src/Tasks/Registry.o ./src/Bifton.o  -O3  -oBifton

