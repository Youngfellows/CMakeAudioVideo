#/bin/bash
rm -r build
mkdir build && cd build
cmake .. -DDEBUG=YES -L
make
cd ..
# ./build/Sample 2 3