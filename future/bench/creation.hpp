#include <benchmark/benchmark.h>

namespace bench {

template <typename Library>
void ConstantFuture(benchmark::State& state) {
  for (auto _ : state) {
    Library::CreateFuture();
  }
}

template <typename Library>
void PromiseAndFuture(benchmark::State& state) {
  for (auto _ : state) {
    Library::PromiseAndFuture();
  }
}

}  // namespace bench
