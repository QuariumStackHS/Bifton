g++ -c -o./src/LibAsHeader/lah.o ./src/LibAsHeader/lah.cpp -std=c++17
g++ -c -o./src/build.o ./src/build.cpp -std=c++17
gcc -lstdc++ ./src/LibAsHeader/lah.o ./src/build.o -O3  -obuild

