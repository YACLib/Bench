#include "bind/folly/future.hpp"

#include <vector>

#include <benchmark/benchmark.h>
#include <folly/executors/InlineExecutor.h>
#include <folly/futures/Future.h>
#include <folly/futures/Promise.h>
#include <folly/portability/GFlags.h>
#include <folly/synchronization/Baton.h>
#include <folly/synchronization/NativeSemaphore.h>

namespace bench {
namespace {

template <typename T>
T Incr(folly::Try<T>&& t) {
  return t.value() + 1;
}

}  // namespace

namespace detail {

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

}  // namespace detail

folly::Future<int> Folly::Thens(folly::Future<int> f, size_t n, bool run_inline) {
  for (size_t i = 0; i < n; i++) {
    if (run_inline) {
      f = std::move(f).thenInline(Incr<int>);
    } else {
      f = std::move(f).then(Incr<int>);
    }
  }
  return f;
}

void Folly::SomeThens(size_t n) {
  auto f = folly::makeFuture<int>(42);
  f = Thens(std::move(f), n);
  f.wait();
}

void Folly::SomeThensOnThread(size_t n, bool run_inline) {
  auto executor = std::make_unique<detail::TestExecutor>(1);
  auto f = folly::makeFuture<int>(42).via(executor.get());
  f = Thens(std::move(f), n / 2, run_inline);
  f = Thens(std::move(f), 1, false);
  f = Thens(std::move(f), n / 2, run_inline);
  f.wait();
}

void Folly::NoContention(benchmark::State& state) {
  state.PauseTiming();

  std::vector<folly::Promise<int>> promises(10000);
  std::vector<folly::Future<int>> futures;
  futures.reserve(10000);
  folly::Baton<> b2;
  for (auto& p : promises) {
    futures.push_back(p.getFuture().then(Incr<int>));
  }
  auto producer = std::thread([&] {
    b2.post();
    for (auto& p : promises) {
      std::move(p).setValue(42);
    }
  });
  b2.wait();

  state.ResumeTiming();

  producer.join();
}

void Folly::Contention(benchmark::State& state) {
  state.PauseTiming();

  std::vector<folly::Promise<int>> promises(10000);
  std::vector<folly::Future<int>> futures;
  futures.reserve(10000);
  folly::NativeSemaphore sem;
  folly::Baton<> b1;
  folly::Baton<> b2;
  for (auto& p : promises) {
    futures.push_back(p.getFuture());
  }
  auto producer = std::thread([&] {
    b2.post();
    for (auto& p : promises) {
      sem.post();
      std::move(p).setValue(42);
    }
  });
  auto consumer = std::thread([&] {
    b1.post();
    for (auto& f : futures) {
      sem.wait();
      f = std::move(f).then(Incr<int>);
    }
  });
  b1.wait();
  b2.wait();

  state.ResumeTiming();

  consumer.join();
  producer.join();
}
void Folly::PromiseAndFuture() {
  folly::Promise<int> p;
  folly::Future<int> f = p.getFuture();
  std::move(p).setValue(42);
  std::move(f).value();
}

}  // namespace bench
