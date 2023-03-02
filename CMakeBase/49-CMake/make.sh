#/bin/bash
rm -r build
mkdir build && cd build
cmake ..
make
cd ..
./build/output/Sample 4 3