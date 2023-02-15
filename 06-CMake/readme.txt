一、内部编译方式，当前目录下，编译CMake,执行 cmake & make 编译
    1. 执行 cmake . 命令
        cmake .
    2. 执行 make 命令
        make 
    3. 运行
        Sample 5 3
    备注: 以上方式会把

二、外部编译方式，编译CMake,执行 cmake & make 编译
    1. 新建build文件夹
        mkdir build
        cd build 
    2. 执行 cmake .. 命令，cmake 指定 USE_MY_MATH=ON
        cmake -DUSE_MY_MATH=ON ..
        cmake -DUSE_MY_MATH=OFF ..
    3. 执行 make 命令
        make 
    4. 运行
        cd ..
        ./build/Sample 5 3
    

