#pragma once

#include "../cmake-build-release/_deps/yaclib-src/src/util/intrusive_list.hpp"

#include <yaclib/async/future.hpp>
#include <yaclib/executor/inline.hpp>

#include <condition_variable>
#include <thread>

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
      f = std::move(f).Then(yaclib::MakeInline(), Incr<int>);
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
  auto f = yaclib::MakeFuture(42);
  f.Via(executor.get());
  f = Thens(std::move(f), n / 2, run_inline);
  f.Via(executor.get());
  f = Thens(std::move(f), 1, false);
  f = Thens(std::move(f), n / 2, run_inline);
  Wait(f);
}

}  // namespace bench::yb
