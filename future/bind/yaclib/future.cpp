#include "bind/yaclib/future.hpp"

#include "bind/yaclib/intrusive_list.hpp"

#include <yaclib/async/future.hpp>
#include <yaclib/executor/inline.hpp>

#include <thread>

#include <benchmark/benchmark.h>

namespace bench {
namespace {

template <typename T>
T Incr(yaclib::Result<T>&& r) {
  return std::move(r).Ok() + 1;
}

}  // namespace
namespace detail::yb {

class TestExecutor final : public yaclib::IExecutor {
 public:
  explicit TestExecutor(size_t numThreads) {
    numThreads = std::max(size_t{1}, numThreads);
    _workers.reserve(numThreads);
    for (auto idx = size_t{0}; idx != numThreads; ++idx) {
      _workers.emplace_back([this] {
        std::unique_lock guard{_m};
        while (true) {
          while (!_tasks.Empty()) {
            auto& task = _tasks.PopFront();
            guard.unlock();
            task.Call();
            task.DecRef();
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

  bool Submit(yaclib::ITask& task) noexcept {
    task.IncRef();
    {
      std::lock_guard guard{_m};
      _tasks.PushBack(task);
    }
    _cv.notify_one();
    return true;
  }

  std::mutex _m;
  std::condition_variable _cv;
  List<yaclib::ITask> _tasks;
  std::vector<std::thread> _workers;
  bool _stop{false};
};

}  // namespace detail::yb

void YACLib::SomeThens(size_t n) {
  auto f = yaclib::MakeFuture(42).Via(yaclib::MakeInline());
  f = Thens(std::move(f), n);
  Wait(f);
}

void YACLib::SomeThensOnThread(size_t n, bool run_inline) {
  auto executor = std::make_unique<detail::yb::TestExecutor>(1);
  auto f = yaclib::MakeFuture(42).Via(executor.get());
  f = Thens(std::move(f), n / 2, run_inline);
  f = Thens(std::move(f), 1, false);
  f = Thens(std::move(f), n / 2, run_inline);
  Wait(f);
}

yaclib::Future<int> YACLib::Thens(yaclib::Future<int> f, size_t n, bool runInline) {
  for (size_t i = 0; i < n; i++) {
    if (runInline) {
      f = std::move(f).ThenInline(Incr<int>);
    } else {
      f = std::move(f).Then(Incr<int>);
    }
  }
  return f;
}

void YACLib::NoContention(benchmark::State& state) {
  state.PauseTiming();
  std::vector<yaclib::Promise<int>> promises;
  std::vector<yaclib::Future<int>> futures;
  promises.reserve(10000);
  futures.reserve(10000);

  auto [f2, p2] = yaclib::MakeContract<void>();

  for (std::size_t i = 0; i < 10000; ++i) {
    auto [f, p] = yaclib::MakeContract<int>();
    promises.emplace_back(std::move(p));
    futures.emplace_back(std::move(f).ThenInline(Incr<int>));
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
}

void YACLib::Contention(benchmark::State& state) {
  state.PauseTiming();

  std::vector<yaclib::Promise<int>> promises;
  std::vector<yaclib::Future<int>> futures;
  promises.reserve(10000);
  futures.reserve(10000);
  folly::NativeSemaphore sem;
  folly::Baton<> b1;
  folly::Baton<> b2;
  for (std::size_t i = 0; i < 10000; ++i) {
    auto [f, p] = yaclib::MakeContract<int>();
    futures.push_back(std::move(f));
    promises.push_back(std::move(p));
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
      f = std::move(f).ThenInline(Incr<int>);
    }
  });
  b1.wait();
  b2.wait();

  state.ResumeTiming();

  consumer.join();
  producer.join();
}
void YACLib::PromiseAndFuture() {
  auto [f, p] = yaclib::MakeContract<int>();
  std::move(p).Set(42);
  std::move(f).Get().Ok();
}

}  // namespace bench
