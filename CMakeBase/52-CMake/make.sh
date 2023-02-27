#/bin/bash
rm -r build
mkdir build && cd build
cmake ..
make
cd ..
# ./build/Sample 2 3
./build/Sample