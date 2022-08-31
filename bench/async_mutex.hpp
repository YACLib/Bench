#pragma once

#include <thread>

#include <benchmark/benchmark.h>

namespace bench {

template <typename Library>
void AsyncMutex(benchmark::State& state) {
  auto* executor = Library::AcquireExecutor(std::thread::hardware_concurrency());
  for (auto _ : state) {
    Library::AsyncMutex(executor);
    executor->Restart();
  }
  Library::ReleaseExecutor(executor);
}

}  // namespace bench
