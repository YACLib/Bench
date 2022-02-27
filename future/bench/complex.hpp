#include <benchmark/benchmark.h>

namespace bench {

template <size_t S>
struct Blob {
  char buf[S];
};

template <typename Library, size_t N>
void ComplexBlob(benchmark::State& state) {
  for (auto _ : state) {
    if constexpr (N == 0) {
      Library::ComplexBenchmark();
    } else {
      Library::template ComplexBenchmark<Blob<N>>();
    }
  }
}

}  // namespace bench
