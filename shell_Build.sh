gcc -c -o./src/SQLite3/sqlite3.o ./src/SQLite3/sqlite3.c -std=c17
gcc -c -o./src/SQLite3/shell.o ./src/SQLite3/shell.c -std=c17
gcc -lstdc++ ./src/SQLite3/sqlite3.o ./src/SQLite3/shell.o  -O3  -oshell

