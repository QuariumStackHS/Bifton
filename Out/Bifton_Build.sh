gcc -c -o/Users/christopherclement/asF/src/SQLite3/sqlite3.o /Users/christopherclement/asF/src/SQLite3/sqlite3.c -std=c17
g++ -c -o/Users/christopherclement/asF/src/BiftonCxx/BiftonCxx.o /Users/christopherclement/asF/src/BiftonCxx/BiftonCxx.cpp -std=c++17
g++ -c -o/Users/christopherclement/asF/src/SimpleExecuter.o /Users/christopherclement/asF/src/SimpleExecuter.cpp -std=c++17
g++ -c -o/Users/christopherclement/asF/src/Bifton.o /Users/christopherclement/asF/src/Bifton.cpp -std=c++17
gcc -lstdc++ /Users/christopherclement/asF/src/SQLite3/sqlite3.o /Users/christopherclement/asF/src/BiftonCxx/BiftonCxx.o /Users/christopherclement/asF/src/SimpleExecuter.o /Users/christopherclement/asF/src/Bifton.o  -O3  -oBifton

