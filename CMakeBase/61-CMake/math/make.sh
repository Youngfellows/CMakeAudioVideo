#/bin/bash
rm -r build
mkdir build && cd build
cmake ..
make
# make install
# cd ..
# ./build/Sample 2 3