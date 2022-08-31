#pragma once

#include <cstdint>
#include <initializer_list>

#include <benchmark/benchmark.h>

#define BENCH2(name, library, arg)                                                                                     \
  BENCHMARK_PRIVATE_DECLARE(name) = (::benchmark::internal::RegisterBenchmarkInternal(                                 \
    new ::benchmark::internal::FunctionBenchmark(#name "/" #library "/" #arg, name<library, arg>)))

#define BENCH1(name, library)                                                                                          \
  BENCHMARK_PRIVATE_DECLARE(name) = (::benchmark::internal::RegisterBenchmarkInternal(                                 \
    new ::benchmark::internal::FunctionBenchmark(#name "/" #library, name<library>)))

#define GET_MACRO(_1, _2, _3, NAME, ...) NAME

#define BENCH(...) GET_MACRO(__VA_ARGS__, BENCH2, BENCH1)(__VA_ARGS__)

struct EmptyBenchmark {
  constexpr const EmptyBenchmark* ArgsProduct(const std::initializer_list<std::initializer_list<std::int64_t>>&) const {
    return this;
  }

  constexpr const EmptyBenchmark* Args(const std::initializer_list<std::int64_t>&) const {
    return this;
  }

  constexpr const EmptyBenchmark* UseRealTime() const {
    return this;
  }

  constexpr const EmptyBenchmark* UseManualTime() const {
    return this;
  }

  constexpr const EmptyBenchmark* Threads(int) const {
    return this;
  }

  constexpr const EmptyBenchmark* ThreadRange(int, int) const {
    return this;
  }

  constexpr const EmptyBenchmark* ThreadPerCpu() const {
    return this;
  }

  constexpr const EmptyBenchmark* Iterations(std::int64_t) const {
    return this;
  }
};

static constexpr EmptyBenchmark kEmptyBenchmark;

#define EMPTY_BENCH(name)                                                                                              \
  static constexpr const EmptyBenchmark* BENCHMARK_PRIVATE_NAME(name) = std::addressof(kEmptyBenchmark)

#ifdef STD_ENABLE
#  define BENCH_STD(name, ...) BENCH(name, Std, ##__VA_ARGS__)
#else
#  define BENCH_STD(name, ...) EMPTY_BENCH(name)
#endif

#ifdef YACLIB_ENABLE
#  define BENCH_YACLIB(name, ...) BENCH(name, YACLib, ##__VA_ARGS__)
#else
#  define BENCH_YACLIB(name, ...) EMPTY_BENCH(name)
#endif

#ifdef CPPCORO_ENABLE
#  define BENCH_CPPCORO(name, ...) BENCH(name, CppCoro, ##__VA_ARGS__)
#else
#  define BENCH_CPPCORO(name, ...) EMPTY_BENCH(name)
#endif

#ifdef FOLLY_ENABLE
#  define BENCH_FOLLY(name, ...) BENCH(name, Folly, ##__VA_ARGS__)
#else
#  define BENCH_FOLLY(name, ...) EMPTY_BENCH(name)
#endif

#ifdef ARANGODB_ENABLE
#  define BENCH_ARANGODB(name, ...) BENCH(name, ArangoDB, ##__VA_ARGS__)
#else
#  define BENCH_ARANGODB(name, ...) EMPTY_BENCH(name)
#endif

#ifdef QT_ENABLE
#  define BENCH_QT(name, ...) BENCH(name, QT, ##__VA_ARGS__)
#else
#  define BENCH_QT(name, ...) EMPTY_BENCH(name)
#endif

#ifdef BOOST_THREAD_ENABLE
#  define BENCH_BOOST_THREAD(name, ...) BENCH(name, BoostThread, ##__VA_ARGS__)
#else
#  define BENCH_BOOST_THREAD(name, ...) EMPTY_BENCH(name)
#endif

#ifdef EXPERIMENTAL_ENABLE
#  define BENCH_EXPERIMENTAL(name, ...) BENCH(name, Experimental, ##__VA_ARGS__)
#else
#  define BENCH_EXPERIMENTAL(name, ...) EMPTY_BENCH(name)
#endif
