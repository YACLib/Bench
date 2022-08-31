#pragma once

#include <bind/yaclib/intrusive_list.hpp>
#include <util/blob.hpp>
#include <yaclib/async/contract.hpp>
#include <yaclib/async/future.hpp>
#include <yaclib/async/make.hpp>
#include <yaclib/async/when_all.hpp>
#include <yaclib/async/when_any.hpp>
#include <yaclib/exe/inline.hpp>

#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>

#include <benchmark/benchmark.h>

namespace bench {
namespace detail::yb {

class TestExecutor final : public yaclib::IExecutor {
 public:
  explicit TestExecutor(std::size_t num_threads);

  void Restart();
  void Join();

  ~TestExecutor() final;

 private:
  void IncRef() noexcept final {
  }
  void DecRef() noexcept final {
  }

  [[nodiscard]] Type Tag() const noexcept final;

  void Submit(yaclib::Job& job) noexcept final;

  std::mutex _m;
  std::condition_variable _cv;
  List<yaclib::Job> _jobs;
  std::vector<std::thread> _workers;
  bool _stop = false;
};

template <typename T>
yaclib::Future<T> FGen() {
  auto [f, p] = yaclib::MakeContract<T>();
  if constexpr (std::is_void_v<T>) {
    f = std::move(f)
          .ThenInline([] {
          })
          .ThenInline([] {
            return yaclib::MakeFuture();
          })
          .ThenInline([] {
          })
          .ThenInline([] {
            return yaclib::MakeFuture();
          });
    std::move(p).Set();
  } else {
    f = std::move(f)
          .ThenInline([](T&& t) {
            return std::move(t);
          })
          .ThenInline([](T&& t) {
            return yaclib::MakeFuture(std::move(t));
          })
          .ThenInline([](T&& t) {
            return std::move(t);
          })
          .ThenInline([](T&& t) {
            return yaclib::MakeFuture(std::move(t));
          });
    std::move(p).Set(T{});
  }
  return std::move(f);
}

template <typename T, std::size_t Size = 10>
std::vector<yaclib::Future<T>> FsGen() {
  std::vector<yaclib::Future<T>> fs;
  fs.reserve(Size);
  for (std::size_t i = 0; i != Size; ++i) {
    fs.emplace_back(FGen<T>());
  }
  return fs;
}

}  // namespace detail::yb

struct YACLib {
  static void CreateFuture();
  static void PromiseAndFuture();

  static detail::yb::TestExecutor* AcquireExecutor(std::size_t threads);
  static void ReleaseExecutor(detail::yb::TestExecutor* e);

  static void SomeThens(detail::yb::TestExecutor* executor, size_t n, bool no_inline);

  template <typename T = void>
  static void ComplexBenchmark();

  static void NoContention(benchmark::State& state, std::size_t iterations = 10'000);
  static void Contention(benchmark::State& state, std::size_t iterations = 10'000);

  static void CollatzEager(std::size_t x);
  static void Fibonacci(detail::yb::TestExecutor* tp, size_t n);
  static void AsyncMutex(detail::yb::TestExecutor* tp);
  static void Latch(detail::yb::TestExecutor* tp, std::size_t task_count);
  static void Reschedule(detail::yb::TestExecutor* tp);
};

}  // namespace bench
