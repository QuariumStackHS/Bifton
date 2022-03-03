g++ -c -o./src/BiftonCxx/BiftonCxx.o ./src/BiftonCxx/BiftonCxx.cpp -std=c++17
g++ -c -o./src/BiftonCxx/SHA1/SHA1.o ./src/BiftonCxx/SHA1/SHA1.cpp -std=c++17
g++ -c -o./src/SimpleExecuter.o ./src/SimpleExecuter.cpp -std=c++17
g++ -c -o./src/Bifton.o ./src/Bifton.cpp -std=c++17
gcc -lstdc++ ./src/BiftonCxx/BiftonCxx.o ./src/BiftonCxx/SHA1/SHA1.o ./src/SimpleExecuter.o ./src/Bifton.o  -O3  -oBifton

