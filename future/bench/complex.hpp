#include <cstddef>

#include <benchmark/benchmark.h>

namespace bench {

template <std::size_t Size>
struct Blob {
  std::byte buffer[Size];
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
