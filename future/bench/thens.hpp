#include <benchmark/benchmark.h>

namespace bench {

template <typename Library>
void Then(benchmark::State& state) {
  for (auto _ : state) {
    if (state.range(1) == 0) {
      Library::SomeThens(state.range(0));
    } else if (state.range(1) == 1) {
      Library::SomeThensOnThread(state.range(0));
    } else if (state.range(1) == 2) {
      Library::SomeThensOnThread(state.range(0), true);
    }
  }
}

}  // namespace bench
