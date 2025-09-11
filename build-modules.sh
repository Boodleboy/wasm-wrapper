#!/bin/sh

cd modules;

../wasi-sdk-build/bin/clang \
	--target=wasm32-wasi \
	--sysroot=../wasi-sdk/build/install/share/wasi-sysroot \
	-o hello.wasm \
	hello.c
	
	
