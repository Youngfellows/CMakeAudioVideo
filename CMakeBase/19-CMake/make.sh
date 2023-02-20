#/bin/bash
rm -r build
mkdir build && cd build
cmake .. -Ddate=20230220 -DPRICE=123 -L
make
cd ..
./build/Sample 4 2