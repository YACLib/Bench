#pragma once

#include "bind/yaclib/intrusive_list.hpp"

#include <yaclib/algo/when_all.hpp>
#include <yaclib/algo/when_any.hpp>
#include <yaclib/async/contract.hpp>
#include <yaclib/async/future.hpp>
#include <yaclib/executor/inline.hpp>

#include <condition_variable>
#include <memory>
#include <thread>

#include <benchmark/benchmark.h>
#include <folly/synchronization/Baton.h>
#include <folly/synchronization/NativeSemaphore.h>

namespace bench {
namespace detail::yb {

template <typename T>
yaclib::Future<T> FGen() {
  auto [f, p] = yaclib::MakeContract<T>();

  if constexpr (std::is_void_v<T>) {
    f = std::move(f)
            .ThenInline([] {
            })
            .ThenInline([](yaclib::Result<T>&&) {
              return yaclib::MakeFuture();
            })
            .ThenInline([] {
            })
            .ThenInline([](yaclib::Result<T>&&) {
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

template <typename T>
std::vector<yaclib::Future<T>> FsGen() {
  std::vector<yaclib::Future<T>> fs;
  fs.reserve(10);
  for (auto i = 0; i < 10; i++) {
    fs.emplace_back(FGen<T>());
  }
  return fs;
}

}  // namespace detail::yb

struct YACLib {
  static void NoContention(benchmark::State& state);
  static void Contention(benchmark::State& state);
  static yaclib::Future<int> Thens(yaclib::Future<int> f, size_t n, bool runInline = false);
  static void SomeThens(size_t n);
  static void SomeThensOnThread(size_t n, bool run_inline = false);
  static void PromiseAndFuture();

  template <typename T = void>
  static void ComplexBenchmark() {
    {
      auto fs = detail::yb::FsGen<T>();
      (void)yaclib::WhenAll(fs.begin(), fs.end()).Get().Ok();
    }
    {
      auto fs = detail::yb::FsGen<T>();
      (void)yaclib::WhenAny(fs.begin(), fs.end()).Get().Ok();
    }
    {
      auto fs = detail::yb::FsGen<T>();
      for (auto& f : fs) {
        if constexpr (std::is_void_v<T>) {
          (void)std::move(f).ThenInline([] {
          });
        } else {
          (void)std::move(f).ThenInline([](T&& t) {
            return std::move(t);
          });
        }
      }
    }
    {
      auto fs = detail::yb::FsGen<T>();
      for (auto& f : fs) {
        if constexpr (std::is_void_v<T>) {
          f = std::move(f).ThenInline([](yaclib::Result<T>&&) {
            return yaclib::MakeFuture();
          });
        } else {
          f = std::move(f).ThenInline([](T&& t) {
            return yaclib::MakeFuture(std::move(t));
          });
        }
      }
    }
  }

  template <typename T>
  static void CreateFuture(T&& value) {
    (void)yaclib::MakeFuture(std::forward<T>(value)).Get();
  }
};

}  // namespace bench
