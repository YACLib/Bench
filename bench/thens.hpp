#pragma once

#include <memory>

#include <benchmark/benchmark.h>

namespace bench {

template <typename Library>
void Then(benchmark::State& state) {
  const auto count = state.range(0);
  const auto type = state.range(1);
  auto* executor = Library::AcquireExecutor(/*threads*/ static_cast<size_t>(type != 0));
  for (auto _ : state) {
    Library::SomeThens(executor, count, type == 2);
    if (executor != nullptr) {
      executor->Restart();
    }
  }
  Library::ReleaseExecutor(executor);
}

}  // namespace bench
