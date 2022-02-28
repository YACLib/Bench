#include <memory>

#include <benchmark/benchmark.h>

namespace bench {

template <typename Library>
void Then(benchmark::State& state) {
  auto const count = state.range(0);
  auto const type = state.range(1);
  std::unique_ptr<typename Library::Executor> executor;
  if (type != 0) {
    executor = std::make_unique<typename Library::Executor>(1);
  }
  for (auto _ : state) {
    if (type == 0) {
      Library::SomeThens(nullptr, count, false);
    } else {
      Library::SomeThens(executor.get(), count, type == 2);
      executor->Restart();
    }
  }
}

}  // namespace bench
