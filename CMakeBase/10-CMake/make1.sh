#/bin/bash
rm -r build
mkdir build && cd build
cmake .. -DDEBUG=YES -DRELEASE=Release.apk -DMY_ADDRESS=N -L
make
cd ..
# ./build/Sample 2 3