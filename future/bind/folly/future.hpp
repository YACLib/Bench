#pragma once

#include <vector>

#include <benchmark/benchmark.h>
#include <folly/futures/Future.h>
#include <folly/futures/Promise.h>

namespace bench {
namespace detail::fy {

class TestExecutor final : public folly::Executor {
 public:
  explicit TestExecutor(std::size_t num_threads);

  void Restart();
  void Join();

  ~TestExecutor() final;

 private:
  void add(folly::Func f) final;

  std::mutex _m;
  std::condition_variable _cv;
  std::queue<folly::Func> _tasks;
  std::vector<std::thread> _workers;
  bool _stop = false;
};

template <typename T>
folly::Future<T> FGen() {
  folly::Promise<T> p;
  auto f = p.getFuture();
  f = std::move(f)
        .thenValueInline([](T&& t) {
          return std::move(t);
        })
        .thenValueInline([](T&& t) {
          return folly::makeFuture(std::move(t));
        })
        .thenValueInline([](T&& t) {
          return std::move(t);
        })
        .thenValueInline([](T&& t) {
          return folly::makeFuture(std::move(t));
        });
  p.setValue(T{});
  return f;
}

template <typename T, std::size_t Size = 10>
std::vector<folly::Future<T>> FsGen() {
  std::vector<folly::Future<T>> fs;
  fs.reserve(Size);
  for (std::size_t i = 0; i < Size; ++i) {
    fs.emplace_back(FGen<T>());
  }
  return fs;
}

}  // namespace detail::fy

struct Folly {
  static void CreateFuture();
  static void PromiseAndFuture();

  using Executor = detail::fy::TestExecutor;
  static void SomeThens(Executor* executor, size_t n, bool no_inline);

  template <typename T = folly::Unit>
  static void ComplexBenchmark();

  static constexpr std::size_t kContentionIteration = 10000;
  static void NoContention(benchmark::State& state);
  static void Contention(benchmark::State& state);
};

template <typename T>
void Folly::ComplexBenchmark() {
  auto fs = detail::fy::FsGen<T>();
  std::ignore = folly::collectAll(fs.begin(), fs.end()).value();
  fs = detail::fy::FsGen<T>();
  std::ignore = folly::collectAny(fs.begin(), fs.end()).value();
  fs = detail::fy::FsGen<T>();
  for (auto& f : fs) {
    f = std::move(f).thenValueInline([](T&& t) {
      return std::move(t);
    });
  }
  fs = detail::fy::FsGen<T>();
  for (auto& f : fs) {
    f = std::move(f).thenValueInline([](T&& t) {
      return folly::makeFuture(T{std::move(t)});
    });
  }
}

}  // namespace bench
