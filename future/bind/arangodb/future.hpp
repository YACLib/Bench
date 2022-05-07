#pragma once

#include <arangodb/futures/function2.hpp>

#include <queue>
#include <vector>

#include <arangodb/futures/Future.h>
#include <arangodb/futures/Unit.h>
#include <arangodb/futures/Utilities.h>
#include <benchmark/benchmark.h>

namespace bench {
namespace detail::adb {

class TestExecutor final {
 public:
  explicit TestExecutor(std::size_t num_threads);

  void Restart();
  void Join();

  ~TestExecutor();

  using Job = fu2::unique_function<void()>;
  void add(Job job);

 private:
  std::mutex _m;
  std::condition_variable _cv;
  std::queue<Job> _jobs;
  std::vector<std::thread> _workers;
  bool _stop = false;
};

template <typename T>
arangodb::futures::Future<T> FGen() {
  arangodb::futures::Promise<T> p;
  auto f = p.getFuture();
  f = std::move(f)
        .thenValue([](T&& t) {
          return std::move(t);
        })
        .thenValue([](T&& t) {
          return arangodb::futures::makeFuture(std::move(t));
        })
        .thenValue([](T&& t) {
          return std::move(t);
        })
        .thenValue([](T&& t) {
          return arangodb::futures::makeFuture(std::move(t));
        });
  p.setValue(T{});
  return f;
}

template <typename T, std::size_t Size = 10>
std::vector<arangodb::futures::Future<T>> FsGen() {
  std::vector<arangodb::futures::Future<T>> fs;
  fs.reserve(Size);
  for (std::size_t i = 0; i < Size; ++i) {
    fs.emplace_back(FGen<T>());
  }
  return fs;
}

}  // namespace detail::adb

struct ArangoDB {
  static void CreateFuture();
  static void PromiseAndFuture();

  static detail::adb::TestExecutor* AcquireExecutor(std::size_t threads);
  static void SomeThens(detail::adb::TestExecutor* executor, size_t n, bool no_inline);
  static void ReleaseExecutor(std::size_t threads, detail::adb::TestExecutor* e);

  template <typename T = arangodb::futures::Unit>
  static void ComplexBenchmark();

  static constexpr std::size_t kContentionIteration = 10000;
  static void NoContention(benchmark::State& state);
  static void Contention(benchmark::State& state);
};

template <typename T>
void ArangoDB::ComplexBenchmark() {
  auto fs = detail::adb::FsGen<T>();
  std::ignore = arangodb::futures::collectAll(fs.begin(), fs.end()).value();
  fs = detail::adb::FsGen<T>();
  std::ignore = arangodb::futures::collectAll /*should be Any, but we don't have it*/ (fs.begin(), fs.end()).value();
  fs = detail::adb::FsGen<T>();
  for (auto& f : fs) {
    f = std::move(f).thenValue([](T&& t) {
      return std::move(t);
    });
  }
  fs = detail::adb::FsGen<T>();
  for (auto& f : fs) {
    f = std::move(f).thenValue([](T&& t) {
      return arangodb::futures::makeFuture(T{std::move(t)});
    });
  }
}

}  // namespace bench
