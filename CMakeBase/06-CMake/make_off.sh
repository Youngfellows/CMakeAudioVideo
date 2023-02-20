#/bin/bash
rm -r build
mkdir build && cd build
cmake -DUSE_MY_MATH=OFF ..
make
cd ..
./build/Sample 2 3