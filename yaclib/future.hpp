#pragma once

#include "../cmake-build-release/_deps/yaclib-src/src/util/intrusive_list.hpp"
#include "yaclib/algo/when_all.hpp"
#include "yaclib/algo/when_any.hpp"

#include <yaclib/async/future.hpp>
#include <yaclib/executor/inline.hpp>

#include <condition_variable>
#include <thread>

#include <benchmark/benchmark.h>
#include <folly/synchronization/Baton.h>
#include <folly/synchronization/NativeSemaphore.h>

namespace bench::yb {

class TestExecutor final : public yaclib::IExecutor {
 public:
  explicit TestExecutor(size_t numThreads) {
    numThreads = std::max(size_t{1}, numThreads);
    _workers.reserve(numThreads);
    for (auto idx = size_t{0}; idx != numThreads; ++idx) {
      _workers.emplace_back([this] {
        std::unique_lock guard{_m};
        while (true) {
          while (auto* task = _tasks.PopFront()) {
            guard.unlock();
            task->Call();
            task->DecRef();
            guard.lock();
          }
          if (_stop) {
            return;
          }
          _cv.wait(guard);
        }
      });
    }
  }

  ~TestExecutor() final {
    {
      std::lock_guard guard{_m};
      _stop = true;
    }
    _cv.notify_all();
    for (auto& worker : _workers) {
      worker.join();
    }
  }

 private:
  void IncRef() noexcept final {
  }
  void DecRef() noexcept final {
  }

  [[nodiscard]] Type Tag() const final {
    return Type::Custom;
  }

  bool Execute(yaclib::ITask& task) final {
    task.IncRef();
    {
      std::lock_guard guard{_m};
      _tasks.PushBack(&task);
    }
    _cv.notify_one();
    return true;
  }

  std::mutex _m;
  std::condition_variable _cv;
  yaclib::util::List<yaclib::ITask> _tasks;
  std::vector<std::thread> _workers;
  bool _stop{false};
};

template <typename T>
T Incr(yaclib::util::Result<T>&& r) {
  return std::move(r).Ok() + 1;
}

yaclib::Future<int> Thens(yaclib::Future<int> f, size_t n, bool runInline = false) {
  for (size_t i = 0; i < n; i++) {
    if (runInline) {
      f = std::move(f).ThenInline(Incr<int>);
    } else {
      f = std::move(f).Then(Incr<int>);
    }
  }
  return f;
}

void SomeThens(size_t n) {
  auto f = yaclib::MakeFuture(42);
  f = Thens(std::move(f), n);
  Wait(f);
}

void SomeThensOnThread(size_t n, bool run_inline = false) {
  auto executor = std::make_unique<TestExecutor>(1);
  auto f = yaclib::MakeFuture(42).Via(executor.get());
  f = Thens(std::move(f), n / 2, run_inline);
  f = Thens(std::move(f), 1, false);
  f = Thens(std::move(f), n / 2, run_inline);
  Wait(f);
}

void NoContention(benchmark::State& state) {
  state.PauseTiming();
  std::vector<yaclib::Promise<int>> promises(10000);
  std::vector<yaclib::Future<int>> futures;
  futures.reserve(10000);

  auto [f2, p2] = yaclib::MakeContract<void>();

  for (auto& p : promises) {
    futures.push_back(p.MakeFuture().Then(Incr<int>));
  }

  auto producer = std::thread([&, p2 = std::move(p2)]() mutable {
    std::move(p2).Set();
    for (auto& p : promises) {
      std::move(p).Set(42);
    }
  });
  Wait(f2);

  state.ResumeTiming();
  producer.join();
  state.PauseTiming();
}

void Contention(benchmark::State& state) {
  state.PauseTiming();

  std::vector<yaclib::Promise<int>> promises(10000);
  std::vector<yaclib::Future<int>> futures;
  futures.reserve(10000);
  folly::NativeSemaphore sem;
  folly::Baton<> b1;
  folly::Baton<> b2;
  for (auto& p : promises) {
    futures.push_back(p.MakeFuture());
  }
  auto producer = std::thread([&] {
    b2.post();
    for (auto& p : promises) {
      sem.post();
      std::move(p).Set(42);
    }
  });
  auto consumer = std::thread([&] {
    b1.post();
    for (auto& f : futures) {
      sem.wait();
      f = std::move(f).Then(Incr<int>);
    }
  });
  b1.wait();
  b2.wait();

  state.ResumeTiming();

  consumer.join();
  producer.join();

  state.PauseTiming();
}

template <typename T>
yaclib::Future<T> FGen() {
  yaclib::Promise<T> p;
  auto f = p.MakeFuture()
               .Then([](T&& t) {
                 return std::move(t);
               })
               .Then([](T&& t) {
                 return yaclib::MakeFuture(std::move(t));
               })
               .Then([](T&& t) {
                 return std::move(t);
               })
               .Then([](T&& t) {
                 return yaclib::MakeFuture(std::move(t));
               });
  std::move(p).Set(T());
  return f;
}

template <typename T>
std::vector<yaclib::Future<T>> FsGen() {
  std::vector<yaclib::Future<T>> fs;
  fs.reserve(10);
  for (auto i = 0; i < 10; i++) {
    fs.push_back(FGen<T>());
  }
  return fs;
}

template <typename T>
void ComplexBenchmark() {
  {
    auto fs = FsGen<T>();
    yaclib::WhenAll(fs.begin(), fs.end()).Get().Ok();
  }
  {
    auto fs = FsGen<T>();
    yaclib::WhenAny(fs.begin(), fs.end()).Get().Ok();
  }
  {
    auto fs = FsGen<T>();
    for (auto& f : fs) {
      f = std::move(f).Then([](const T& t) {
        return t;
      });
    }
  }
  {
    auto fs = FsGen<T>();
    for (auto& f : fs) {
      f = std::move(f).Then([](const T& t) {
        return yaclib::MakeFuture(T(t));
      });
    }
  }
}

template <size_t S>
struct Blob {
  char buf[S];
};

}  // namespace bench::yb
