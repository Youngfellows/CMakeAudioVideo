#/bin/bash
rm -r build
mkdir build && cd build
cmake .. -DDEBUG=Y -DRELEASE=YES -DCITY=BeiJing -DBRAND=Jeep -L
make
cd ..
# ./build/Sample 2 3