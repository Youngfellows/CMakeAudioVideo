#/bin/bash
rm -r build
mkdir build && cd build
cmake -D TEST_DEBUG=ON -DTEST_RELEASE=OFF -DUSE_MY_MATH=ON -L ..
make
cd ..
./build/Sample 2 3