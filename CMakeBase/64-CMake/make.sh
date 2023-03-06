#/bin/bash
rm -r build
mkdir build && cd build
cmake .. -Dcache_entry_input=ON -Dmypath=sub
make
cd ..
# ./build/Sample 2 3