#include <memory>

#include <benchmark/benchmark.h>

namespace bench {

template <typename Library>
void Then(benchmark::State& state) {
  auto const count = state.range(0);
  auto const type = state.range(1);
  auto* executor = Library::AcquireExecutor(/*threads*/ static_cast<size_t>(type != 0));
  for (auto _ : state) {
    Library::SomeThens(executor, count, type == 2);
    if (executor != nullptr) {
      executor->Restart();
    }
  }
  Library::ReleaseExecutor(/*threads*/ static_cast<size_t>(type != 0), executor);
}

}  // namespace bench
