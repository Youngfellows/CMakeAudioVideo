#/bin/bash
rm -r build
mkdir build && cd build
export MY_TEST_ENV_VAR="env var"
cmake .. -DPRICE=88 -L
make
cd ..
# ./build/Sample 2 3