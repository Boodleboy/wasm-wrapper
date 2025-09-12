#!/bin/sh

cd modules;

../wasi-sdk-build/bin/clang \
	--target=wasm32-wasi \
	--sysroot=../wasi-libc/sysroot \
	-o hello.wasm \
	hello.c
	
	
