#!/bin/sh

cd modules

../sub/wasi-sdk/build/install/bin/clang \
  --target=wasm32-wasi \
  --sysroot=../sub/wasi-sdk/build/install/share/wasi-sysroot \
  -o hello.wasm \
  hello.c
