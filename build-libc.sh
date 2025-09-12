#!/bin/sh

cd wasi-libc;

make CC=../wasi-sdk-build/bin/clang \
     AR=../wasi-sdk-build/bin/llvm-ar \
     NM=../wasi-sdk-build/bin/llvm-nm

