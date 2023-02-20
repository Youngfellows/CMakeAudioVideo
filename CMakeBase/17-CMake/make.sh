#/bin/bash
rm -r build
mkdir build && cd build
cmake .. -DRELEASE=OFF -L
make
cd ..
# ./build/Sample 2 3