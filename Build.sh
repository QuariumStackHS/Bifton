#!
g++ src/Bifton.cpp -c -S -osrc/main.s -std=c++17 -O3
g++ src/BiftonCxx/BiftonCxx.cpp -c -S -osrc/BiftonCxx/BiftonCxx.s -std=c++17 -O3
gcc src/BiftonCxx/BiftonCxx.s src/main.s -oBifton -lstdc++