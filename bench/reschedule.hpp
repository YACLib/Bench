#pragma once

#include <benchmark/benchmark.h>

namespace bench {

template <typename Library>
void Reschedule(benchmark::State& state) {
  auto* executor = Library::AcquireExecutor(/*threads*/ 1);
  for (auto _ : state) {
    Library::Reschedule(executor);
    executor->Restart();
  }
  Library::ReleaseExecutor(executor);
}

}  // namespace bench
