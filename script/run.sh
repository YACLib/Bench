#!/usr/bin/env bash

for i in "$@"; do
  case $i in
  --proc=*)
    proc="${i#*=}"
    shift
    ;;
  -* | --*)
    echo "Unknown option $i"
    exit 1
    ;;
  *) ;;
  esac
done

if [[ -z "$proc" ]]; then
  echo "You should specify --proc="" option"
  exit 1
fi

dir="./future/result/$proc"

mkdir -p "$dir/clang_libcxx"
mkdir -p "$dir/clang_libstdcxx"
mkdir -p "$dir/gcc_libstdcxx"

./build_clang_libcxx/future/future --benchmark_out_format="json" --benchmark_out="$dir/clang_libcxx/data.json"

./build_clang_libstdcxx/future/future --benchmark_out_format="json" --benchmark_out="$dir/clang_libstdcxx/data.json"

./build_gcc_libstdcxx/future/future --benchmark_out_format="json" --benchmark_out="$dir/gcc_libstdcxx/data.json"

echo "- [$proc]($proc/)" >> future/result/RESULTS.md

git add .
