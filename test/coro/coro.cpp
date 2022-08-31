#include <bench/async_mutex.hpp>
#include <bench/collatz.hpp>
#include <bench/fibonacci.hpp>
#include <bench/latch.hpp>
#include <bench/reschedule.hpp>
#include <bind/all.hpp>
#include <util/bench.hpp>

#include <benchmark/benchmark.h>

namespace {

using namespace bench;

BENCH_YACLIB(Reschedule)->UseRealTime();
BENCH_CPPCORO(Reschedule)->UseRealTime();
BENCH_FOLLY(Reschedule)->UseRealTime();

BENCH_YACLIB(Latch)->UseRealTime()->Args({600});
BENCH_CPPCORO(Latch)->UseRealTime()->Args({600});
// BENCH_FOLLY(Latch)->UseRealTime()->Args({600});

// BENCH_STD(AsyncMutex)->UseRealTime();
BENCH_YACLIB(AsyncMutex)->UseRealTime();
BENCH_CPPCORO(AsyncMutex)->UseRealTime();
// BENCH_FOLLY(AsyncMutex)->UseRealTime();

// BENCH_STD(Collatz)->UseRealTime()->ArgsProduct({{1, 2, 3, 7, 9, 25, 27, 313, 871, 2463, 6171}, {0}});
BENCH_YACLIB(CollatzEager)->UseRealTime()->ArgsProduct({{1, 2, 3, 7, 9, 25, 27, 313, 871, 2463, 6171}, {0}});
BENCH_CPPCORO(CollatzLazy)->UseRealTime()->ArgsProduct({{1, 2, 3, 7, 9, 25, 27, 313, 871, 2463, 6171}, {0}});
BENCH_FOLLY(CollatzLazy)->UseRealTime()->ArgsProduct({{1, 2, 3, 7, 9, 25, 27, 313, 871, 2463, 6171}, {0}});

// BENCH_STD(Fibonacci)->UseRealTime()->ArgsProduct({{1, 2, 4, 8, 16}, {0}});
BENCH_YACLIB(Fibonacci)->UseRealTime()->ArgsProduct({{1, 2, 4, 8, 16}, {0}});
BENCH_CPPCORO(Fibonacci)->UseRealTime()->ArgsProduct({{1, 2, 4, 8, 16}, {0}});
BENCH_FOLLY(Fibonacci)->UseRealTime()->ArgsProduct({{1, 2, 4, 8, 16}, {0}});

}  // namespace

int main(int argc, char** argv) {
  benchmark::Initialize(&argc, argv);
  if (benchmark::ReportUnrecognizedArguments(argc, argv)) {
    return 1;
  }
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
  return 0;
}
