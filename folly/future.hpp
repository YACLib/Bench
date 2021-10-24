#pragma once

#include <folly/Executor.h>
#include <folly/futures/Future.h>
#include <folly/futures/Promise.h>

namespace bench::fy {

class TestExecutor final : public folly::Executor {
 public:
  explicit TestExecutor(size_t num_threads) {
    num_threads = std::max(size_t{1}, num_threads);
    _workers.reserve(num_threads);
    for (auto idx = size_t{0}; idx != num_threads; ++idx) {
      _workers.emplace_back([this] {
        while (true) {
          folly::Func work;
          {
            std::unique_lock guard{_m};
            while (_work_items.empty()) {
              _cv.wait(guard);
            }
            work = std::move(_work_items.front());
            _work_items.pop();
          }
          if (!work) {
            break;
          }
          work();
        }
      });
    }
  }

  ~TestExecutor() final {
    for (auto& worker : _workers) {
      (void)worker;
      AddImpl({});
    }
    for (auto& worker : _workers) {
      worker.join();
    }
  }

  void add(folly::Func f) final {
    if (f) {
      AddImpl(std::move(f));
    }
  }

 private:
  void AddImpl(folly::Func f) {
    {
      std::lock_guard guard{_m};
      _work_items.push(std::move(f));
    }
    _cv.notify_one();
  }

  std::mutex _m;
  std::queue<folly::Func> _work_items;
  std::condition_variable _cv;
  std::vector<std::thread> _workers;
};

template <typename T>
T Incr(folly::Try<T>&& t) {
  return t.value() + 1;
}

folly::Future<int> Thens(folly::Future<int> f, size_t n, bool run_inline = false) {
  for (size_t i = 0; i < n; i++) {
    if (run_inline) {
      f = std::move(f).thenInline(Incr<int>);
    } else {
      f = std::move(f).then(Incr<int>);
    }
  }
  return f;
}

void SomeThens(size_t n) {
  auto f = folly::makeFuture<int>(42);
  f = Thens(std::move(f), n);
  f.wait();
}

void SomeThensOnThread(size_t n, bool run_inline = false) {
  auto executor = std::make_unique<TestExecutor>(1);
  auto f = folly::makeFuture<int>(42).via(executor.get());
  f = Thens(std::move(f), n / 2, run_inline);
  f = Thens(std::move(f), 1, false);
  f = Thens(std::move(f), n / 2, run_inline);
  f.wait();
}

}  // namespace bench::fy
