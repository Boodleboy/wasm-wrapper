cmake_minimum_required(VERSION 3.16)  # pick something not ancient
project(my_wamr_app C)

# Tell CMake to use gcc explicitly (optional if it's the default)
set(CMAKE_C_COMPILER gcc)

# use lld linker
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld")

# WAMR build settings
set(WAMR_BUILD_PLATFORM "linux")
set(WAMR_BUILD_TARGET "X86_64")
set(WAMR_BUILD_INTERP 1)
set(WAMR_BUILD_FAST_INTERP 1)
set(WAMR_BUILD_AOT 1)
set(WAMR_BUILD_LIBC_BUILTIN 1)
set(WAMR_BUILD_LIBC_WASI 1)
set(WAMR_BUILD_SIMD 1)
set(WAMR_BUILD_REF_TYPES 1)

# Path to WAMR source root
set(WAMR_ROOT_DIR sub/wamr)

# Pull in WAMR's cmake file which sets WAMR_RUNTIME_LIB_SOURCE
include(${WAMR_ROOT_DIR}/build-scripts/runtime_lib.cmake)

# Build the WAMR runtime as a static library
add_library(vmlib ${WAMR_RUNTIME_LIB_SOURCE})

# Optional: include some shared uncommon utils from WAMR if you want them
set(SHARED_DIR ${WAMR_ROOT_DIR}/core/shared)
include(${SHARED_DIR}/utils/uncommon/shared_uncommon.cmake)

# Build your own app
add_executable(my_wamr_app main.c ${UNCOMMON_SHARED_SOURCE})

# Link your app with vmlib and the math library
target_link_libraries(my_wamr_app vmlib m)
