#!/bin/sh

cd wasi-libc

make CC=../sub/wasi-sdk/build/install/bin/clang \
  AR=../sub/wasi-sdk/build/install/bin/llvm-ar \
  NM=../sub/wasi-sdk/build/install/bin/llvm-nm
