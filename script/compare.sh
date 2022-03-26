#!/usr/bin/env bash

for i in "$@"; do
  case $i in
  --branch=*)
    branch="${i#*=}"
    shift
    ;;
  -* | --*)
    echo "Unknown option $i"
    exit 1
    ;;
  *) ;;
  esac
done

if [[ -z "$branch" ]]; then
  echo "You should specify --branch=... option"
  exit 1
fi

cmake -S . -B ./build_folly \
  -GNinja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ \
  -DFOLLY=ON
cmake -S . -B ./build_main \
  -GNinja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ \
  -DYACLIB="main"
if [ "$branch" != "main" ]; then
  cmake -S . -B "./build_$branch" \
    -GNinja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ \
    -DYACLIB="$branch"
fi

ninja -C ./build_folly
ninja -C ./build_main
if [ "$branch" != "main" ]; then
  ninja -C "./build_$branch"
fi

./build_folly/future/future
./build_main/future/future
if [ "$branch" != "main" ]; then
  ./build_$branch/future/future
fi
