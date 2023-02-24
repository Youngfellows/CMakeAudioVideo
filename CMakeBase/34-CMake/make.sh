#/bin/bash
rm -r build
mkdir build && cd build
cmake -DTEST_DEBUG=OFF -D TEST_RELEASE=ON -DUSE_MY_MATH=OFF -L ..
make
cd ..
./build/Sample 3 2