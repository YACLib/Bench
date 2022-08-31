#pragma once

#include <benchmark/benchmark.h>

namespace bench {

template <typename Library>
void CollatzEager(benchmark::State& state) {
  const auto x = state.range(0);
  for (auto _ : state) {
    Library::CollatzEager(x);
  }
}

template <typename Library>
void CollatzLazy(benchmark::State& state) {
  const auto x = state.range(0);
  for (auto _ : state) {
    Library::CollatzLazy(x);
  }
}

}  // namespace bench
