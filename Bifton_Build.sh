g++ -c -o./src/Bifton.o ./src/Bifton.cpp -std=c++17
gcc -lstdc++ ./src/SQLite3/sqlite3.o ./src/BiftonCxx/BiftonCxx.o ./src/BiftonCxx/SHA1/SHA1.o ./src/SimpleExecuter.o ./src/Bifton.o  -O3  -oBifton

