#pragma once

#include <thread>

#include <benchmark/benchmark.h>

namespace bench {

template <typename Library>
void Latch(benchmark::State& state) {
  const auto tasks_count = state.range(0);
  auto* executor = Library::AcquireExecutor(std::thread::hardware_concurrency());
  for (auto _ : state) {
    Library::Latch(executor, tasks_count);
    executor->Restart();
  }
  Library::ReleaseExecutor(executor);
}

}  // namespace bench
