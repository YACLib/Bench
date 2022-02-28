#pragma once

#include <QFuture>
#include <QPromise>
#include <QtGlobal>
#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>

#include <benchmark/benchmark.h>
#include <folly/synchronization/Baton.h>
#include <folly/synchronization/NativeSemaphore.h>
#include <qtconcurrentrun.h>

namespace bench {
namespace detail::qt {

template <typename T>
std::pair<QFuture<T>, QPromise<T>> MakeContract() {
  QPromise<T> p;
  return {p.future(), std::move(p)};
}

struct Unit {};

template <typename T>
QFuture<T> FGen() {
  auto [f, p] = MakeContract<T>();

  if constexpr (std::is_void_v<T>) {
    f = f.then(QtFuture::Launch::Sync,
               [] {
               })
          .then(QtFuture::Launch::Sync,
                [](T) {
                  return QtFuture::makeReadyFuture();
                })
          .then(QtFuture::Launch::Sync,
                [](QFuture<void>&& f1) {
                  f1.waitForFinished();
                })
          .then(QtFuture::Launch::Sync, [] {
            return QtFuture::makeReadyFuture();
          });
    p.finish();
  } else {
    f = f.then(QtFuture::Launch::Sync,
               [](T&& t) {
                 return std::move(t);
               })
          .then(QtFuture::Launch::Sync,
                [](T&& t) {
                  return QtFuture::makeReadyFuture(std::move(t));
                })
          .then(QtFuture::Launch::Sync,
                [](QFuture<T>&& t) {
                  return QtFuture::makeReadyFuture(t.result());
                })
          .then(QtFuture::Launch::Sync, [](QFuture<T>&& t) {
            auto f1 = QtFuture::makeReadyFuture(std::move(t.result()));
            return f1.result();
          });
    p.addResult(T{});
    p.finish();
  }

  return std::move(f);
}

template <typename T>
std::vector<QFuture<T>> FsGen() {
  std::vector<QFuture<T>> fs;
  fs.reserve(10);
  for (auto i = 0; i < 10; i++) {
    fs.push_back(FGen<T>());
  }
  return fs;
}
}  // namespace detail::qt

struct QT {
  struct Unit {
    constexpr bool operator==(const Unit& /*other*/) const {
      return true;
    }
    constexpr bool operator!=(const Unit& /*other*/) const {
      return false;
    }
  };

  static void PromiseAndFuture();

  static QFuture<int> MakeFuture(int x);

  static void NoContention(benchmark::State& state);

  static void Contention(benchmark::State& state);

  static QFuture<int> Thens(QFuture<int> f, size_t n, bool runInline = false, QThreadPool* pool = nullptr);

  static void SomeThens(size_t n);

  static void SomeThensOnThread(size_t n, bool run_inline = false);

  template <typename T = Unit>
  static void ComplexBenchmark() {
    {
      auto fs = detail::qt::FsGen<T>();
#if QT_VERSION >= QT_VERSION_CHECK(6, 3, 0)
      (void)whenAll(fs.begin(), fs.end()).result();
#else
      for (auto& el : fs) {
        (void)el.result();
      }
#endif
    }
    {
      auto fs = detail::qt::FsGen<T>();
#if QT_VERSION >= QT_VERSION_CHECK(6, 3, 0)
      (void)whenAny(fs.begin(), fs.end()).result();
#else
      for (auto& el : fs) {
        (void)el.result();
      }
#endif
    }

    {
      auto fs = detail::qt::FsGen<T>();
      for (auto& f : fs) {
        if constexpr (std::is_void_v<T>) {
          f.then(QtFuture::Launch::Sync, [] {
          });
        } else {
          f.then(QtFuture::Launch::Sync, [](T&& t) {
            return std::move(t);
          });
        }
      }
    }

    {
      auto fs = detail::qt::FsGen<T>();
      for (auto& f : fs) {
        if constexpr (std::is_void_v<T>) {
          f.then([](T&&) {
            return QtFuture::makeReadyFuture();
          });
        } else {
          f.then([](T&& t) {
            return QtFuture::makeReadyFuture(std::move(t));
          });
        }
      }
    }
  }

  template <typename T>
  static void CreateFuture(T&& value) {
    (void)QtFuture::makeReadyFuture(std::forward<T>(value)).result();
  }
};

}  // namespace bench
