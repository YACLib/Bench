#pragma once

#include <vector>

#include <benchmark/benchmark.h>

#define BENCH2(name, library, arg)                                                     \
  BENCHMARK_PRIVATE_DECLARE(name) = (::benchmark::internal::RegisterBenchmarkInternal( \
      new ::benchmark::internal::FunctionBenchmark(#name "(" #library ")"              \
                                                         "/" #arg,                     \
                                                   name<library, arg>)))

#define BENCH1(name, library)                                                          \
  BENCHMARK_PRIVATE_DECLARE(name) = (::benchmark::internal::RegisterBenchmarkInternal( \
      new ::benchmark::internal::FunctionBenchmark(#name "(" #library ")", name<library>)))

#define GET_MACRO(_1, _2, _3, NAME, ...) NAME

#define BENCH(...) GET_MACRO(__VA_ARGS__, BENCH2, BENCH1)(__VA_ARGS__)

struct EmptyBenchmark {
  EmptyBenchmark* ArgsProduct(const std::vector<std::vector<int64_t>>&) {
    return this;
  }
  EmptyBenchmark* UseRealTime() {
    return this;
  }

  EmptyBenchmark* UseManualTime() {
    return this;
  }

  EmptyBenchmark* Threads(int) {
    return this;
  }

  EmptyBenchmark* ThreadRange(int, int) {
    return this;
  }
  EmptyBenchmark* ThreadPerCpu() {
    return this;
  }
};

#define EMPTY_BENCH(name) static auto* BENCHMARK_PRIVATE_NAME(name) = (new EmptyBenchmark{})

#ifdef QT_ENABLE
#define BENCH_QT(name, ...) BENCH(name, QT, ##__VA_ARGS__)
#else
#define BENCH_QT(name, ...) EMPTY_BENCH(name)
#endif

#ifdef FOLLY_ENABLE
#define BENCH_FOLLY(name, ...) BENCH(name, Folly, ##__VA_ARGS__)
#else
#define BENCH_FOLLY(name, ...) EMPTY_BENCH(name)
#endif

#ifdef YACLIB_ENABLE
#define BENCH_YACLIB(name, ...) BENCH(name, YACLib, ##__VA_ARGS__)
#else
#define BENCH_YACLIB(name, ...) EMPTY_BENCH(name)
#endif

#ifdef STD_ENABLE
#define BENCH_STD(name, ...) BENCH(name, Std, ##__VA_ARGS__)
#else
#define BENCH_STD(name, ...) EMPTY_BENCH(name)
#endif
