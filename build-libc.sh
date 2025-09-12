#!/bin/sh

cd wasi-sdk

cmake -G Ninja -B build/sysroot -S . \
    -DCMAKE_INSTALL_PREFIX=build/install \
    -DCMAKE_TOOLCHAIN_FILE=../wasi-sdk-build/share/cmake/wasi-sdk.cmake \
    -DCMAKE_C_COMPILER_WORKS=ON \
    -DCMAKE_CXX_COMPILER_WORKS=ON
cmake --build build/sysroot --target install
