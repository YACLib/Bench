#include <bind/experimental/future.hpp>
#include <semaphore.hpp>

#include <experimental/future>
#include <thread>

#include <benchmark/benchmark.h>

namespace bench {
namespace detail::el {}  // namespace detail::el

void Experimental::CreateFuture() {
  auto f = std::experimental::make_ready_future(42);
}
void Experimental::PromiseAndFuture() {
}
void Experimental::SomeThens(Experimental::Executor* executor, size_t n, bool no_inline) {
}

void Experimental::NoContention(benchmark::State& state) {
}

void Experimental::Contention(benchmark::State& state) {
}

}  // namespace bench
