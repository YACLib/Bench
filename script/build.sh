#!/usr/bin/env bash

set -eou pipefail

cmake -S . -B ./build_clang_libcxx \
  -GNinja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
  -DLIBCXX=ON -DSTD=ON -DYACLIB=main

cmake -S . -B ./build_clang_libstdcxx \
  -GNinja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
  -DSTD=ON -DYACLIB=main -DFOLLY=ON -DBOOST_THREAD=ON

cmake -S . -B ./build_gcc_libstdcxx \
  -GNinja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ \
  -DSTD=ON -DYACLIB=main -DFOLLY=ON -DBOOST_THREAD=ON

ninja -C ./build_clang_libcxx

ninja -C ./build_clang_libstdcxx

ninja -C ./build_gcc_libstdcxx
