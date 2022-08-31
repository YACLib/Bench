#!/usr/bin/env bash

for i in "$@"; do
  case $i in
  --name=*)
    name="${i#*=}"
    shift
    ;;
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

if [[ -z "$name" ]]; then
  echo "You should specify --name=... option"
  exit 1
fi

if [[ -z "$proc" ]]; then
  echo "You should specify --proc=... option"
  exit 1
fi

dir="./$name/result/$proc"

mkdir -p "$dir/clang_libcxx"
mkdir -p "$dir/clang_libstdcxx"
mkdir -p "$dir/gcc_libstdcxx"

./build_clang_libcxx/$name/$name --benchmark_out_format="json" --benchmark_out="$dir/clang_libcxx/data.json"

./build_clang_libstdcxx/$name/$name --benchmark_out_format="json" --benchmark_out="$dir/clang_libstdcxx/data.json"

./build_gcc_libstdcxx/$name/$name --benchmark_out_format="json" --benchmark_out="$dir/gcc_libstdcxx/data.json"

echo "- [$proc]($proc/)" >> $name/result/RESULTS.md

git add .
