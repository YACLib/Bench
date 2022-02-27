#pragma once

#include <vector>

#include <benchmark/benchmark.h>
#include <folly/executors/InlineExecutor.h>
#include <folly/futures/Future.h>
#include <folly/futures/Promise.h>
#include <folly/portability/GFlags.h>
#include <folly/synchronization/Baton.h>
#include <folly/synchronization/NativeSemaphore.h>

namespace bench {
namespace detail {

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

template <typename T>
std::vector<folly::Future<T>> FsGen() {
  std::vector<folly::Future<T>> fs;
  fs.reserve(10);
  for (auto i = 0; i < 10; i++) {
    fs.push_back(FGen<T>());
  }
  return fs;
}
}  // namespace detail

struct Folly {
  template <typename T = folly::Unit>
  static void ComplexBenchmark() {
    (void)folly::collectAll(detail::FsGen<T>()).value();
    (void)folly::collectAny(detail::FsGen<T>()).value();
    folly::futures::mapValue(detail::FsGen<T>(), [](T&& t) {
      return std::move(t);
    });
    folly::futures::mapValue(detail::FsGen<T>(), [](T&& t) {
      return folly::makeFuture(T{std::move(t)});
    });
  }

  template <typename T>
  static void CreateFuture(T&& value) {
    (void)folly::makeFuture(std::forward<T>(value)).get();
  }

  static void PromiseAndFuture();

  static folly::Future<int> Thens(folly::Future<int> f, size_t n, bool run_inline = false);

  static void SomeThens(size_t n);

  static void SomeThensOnThread(size_t n, bool run_inline = false);

  static void NoContention(benchmark::State& state);

  static void Contention(benchmark::State& state);
};

}  // namespace bench
