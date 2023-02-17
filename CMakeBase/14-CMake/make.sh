#/bin/bash
rm -r build
mkdir build && cd build
cmake .. -Dvar_2=yangguo -L
make
cd ..
# ./build/Sample 2 3