#/bin/bash
rm -r build
mkdir build && cd build
cmake .. -L -DBUILD_RELEASE:BOOL=OFF
make
cd ..
# ./build/Sample 2 3