#/bin/bash
rm -r build
mkdir build && cd build
cmake .. -DCMAKE_LIBRARY_PATH=./lib -L
make
cd ..
./output/Sample 3 4