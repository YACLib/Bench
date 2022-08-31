#pragma once

#include <thread>

#include <benchmark/benchmark.h>

namespace bench {

template <typename Library>
void Fibonacci(benchmark::State& state) {
  const auto n = state.range(0);
  auto* executor = Library::AcquireExecutor(std::thread::hardware_concurrency());
  for (auto _ : state) {
    Library::Fibonacci(executor, n);
    executor->Restart();
  }
  Library::ReleaseExecutor(executor);
}

}  // namespace bench
