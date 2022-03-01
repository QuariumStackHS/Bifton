gcc -c -o./src/SQLite3/sqlite3.o ./src/SQLite3/sqlite3.c -std=c17
g++ -c -o./src/BiftonCxx/BiftonCxx.o ./src/BiftonCxx/BiftonCxx.cpp -std=c++17
g++ -c -o./src/SimpleExecuter.o ./src/SimpleExecuter.cpp -std=c++17
g++ -c -o./src/Bifton.o ./src/Bifton.cpp -std=c++17
gcc -lstdc++ ./src/SQLite3/sqlite3.o ./src/BiftonCxx/BiftonCxx.o ./src/SimpleExecuter.o ./src/Bifton.o  -O3  -oBifton

