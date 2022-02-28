gcc -c -o/Users/christopherclement/asF/src/SQLite3/sqlite3.o /Users/christopherclement/asF/src/SQLite3/sqlite3.c -std=c17
gcc -c -o/Users/christopherclement/asF/src/SQLite3/shell.o /Users/christopherclement/asF/src/SQLite3/shell.c -std=c17
gcc -lstdc++ /Users/christopherclement/asF/src/SQLite3/sqlite3.o /Users/christopherclement/asF/src/SQLite3/shell.o  -O3  -oshell

