#pragma once

#include <bind/yaclib/intrusive_list.hpp>
#include <yaclib/algo/when_all.hpp>
#include <yaclib/algo/when_any.hpp>
#include <yaclib/async/contract.hpp>
#include <yaclib/async/future.hpp>
#include <yaclib/executor/inline.hpp>

#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>

#include <benchmark/benchmark.h>

namespace bench {
namespace detail::el {

class TestExecutor final {
 public:
  explicit TestExecutor(std::size_t num_threads);

  void Restart();
  void Join();

  ~TestExecutor();

 private:
};

}  // namespace detail::el

struct Experimental {
  static void CreateFuture();
  static void PromiseAndFuture();

  using Executor = detail::el::TestExecutor;
  static void SomeThens(Executor* executor, size_t n, bool no_inline);

  template <typename T = void>
  static void ComplexBenchmark();

  static constexpr std::size_t kContentionIteration = 10000;
  static void NoContention(benchmark::State& state);
  static void Contention(benchmark::State& state);
};

template <typename T>
void Experimental::ComplexBenchmark() {
}

}  // namespace bench
