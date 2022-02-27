#include <benchmark/benchmark.h>

namespace bench {

template <typename Library>
void NoContention(benchmark::State& state) {
  for (auto _ : state) {
    Library::NoContention(state);
  }
}

template <typename Library>
void Contention(benchmark::State& state) {
  for (auto _ : state) {
    Library::Contention(state);
  }
}

}  // namespace bench
