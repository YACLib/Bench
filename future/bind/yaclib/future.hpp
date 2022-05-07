#pragma once

#include <bind/blob.hpp>
#include <bind/heavy.hpp>
#include <bind/yaclib/intrusive_list.hpp>
#include <yaclib/algo/when_all.hpp>
#include <yaclib/algo/when_any.hpp>
#include <yaclib/async/contract.hpp>
#include <yaclib/async/future.hpp>
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

  [[nodiscard]] Type Tag() const final;

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
          .ThenInline([SIZEOF_F] {
          })
          .ThenInline([SIZEOF_F](yaclib::Result<T>&& /*TODO(MBkkt) remove this*/) {
            return yaclib::MakeFuture();
          })
          .ThenInline([SIZEOF_F] {
          })
          .ThenInline([SIZEOF_F](yaclib::Result<T>&& /*TODO(MBkkt) remove this*/) {
            return yaclib::MakeFuture();
          });
    std::move(p).Set();
  } else {
    f = std::move(f)
          .ThenInline([SIZEOF_F](T&& t) {
            return std::move(t);
          })
          .ThenInline([SIZEOF_F](T&& t) {
            return yaclib::MakeFuture(std::move(t));
          })
          .ThenInline([SIZEOF_F](T&& t) {
            return std::move(t);
          })
          .ThenInline([SIZEOF_F](T&& t) {
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
  static void SomeThens(detail::yb::TestExecutor* executor, size_t n, bool no_inline);
  static void ReleaseExecutor(std::size_t threads, detail::yb::TestExecutor* e);

  template <typename T = void>
  static void ComplexBenchmark();

  static constexpr std::size_t kContentionIteration = 10000;
  static void NoContention(benchmark::State& state);
  static void Contention(benchmark::State& state);
};

extern template void YACLib::ComplexBenchmark<void>();
extern template void YACLib::ComplexBenchmark<Blob<2>>();
extern template void YACLib::ComplexBenchmark<Blob<4>>();
extern template void YACLib::ComplexBenchmark<Blob<8>>();
extern template void YACLib::ComplexBenchmark<Blob<16>>();
extern template void YACLib::ComplexBenchmark<Blob<32>>();
extern template void YACLib::ComplexBenchmark<Blob<64>>();
extern template void YACLib::ComplexBenchmark<Blob<128>>();
extern template void YACLib::ComplexBenchmark<Blob<256>>();
extern template void YACLib::ComplexBenchmark<Blob<512>>();
extern template void YACLib::ComplexBenchmark<Blob<1024>>();
extern template void YACLib::ComplexBenchmark<Blob<2048>>();
extern template void YACLib::ComplexBenchmark<Blob<4096>>();
extern template void YACLib::ComplexBenchmark<Blob<8192>>();

}  // namespace bench
