#/bin/bash
rm -r build
mkdir build && cd build
cmake .. -DDEBUG=NO -DRELEASE=Sample20230217.apk -L
make
cd ..
# ./build/Sample 2 3