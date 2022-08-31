#include "cppcoro/async_mutex.hpp"
#include "cppcoro/schedule_on.hpp"
#include "cppcoro/when_all.hpp"

#include <bind/cppcoro/library.hpp>
#include <cppcoro/async_latch.hpp>
#include <cppcoro/static_thread_pool.hpp>
#include <cppcoro/sync_wait.hpp>
#include <cppcoro/task.hpp>
#include <cppcoro/when_all_ready.hpp>

#include <cstddef>

namespace bench {
namespace {

cppcoro::task<> ComputeCollatz(std::size_t x) {
  if (x <= 1) {
    co_return;
  }
  if (x % 2 == 0) {
    co_await ComputeCollatz(x / 2);
    co_return;
  }
  co_await ComputeCollatz(3 * x + 1);
  co_return;
}

cppcoro::task<std::size_t> ComputeFibonacciAsync(detail::co::TestExecutor& e, std::size_t n) {
  if (n <= 1) {
    co_return 1;
  }
  // same results
  // co_await e.schedule();
  // auto f0 = ComputeFibonacciAsync(e, n - 1);
  // auto f1 = ComputeFibonacciAsync(e, n - 2);
  auto f0 = ComputeFibonacciAsync(e, n - 1) | cppcoro::schedule_on(e);
  auto f1 = ComputeFibonacciAsync(e, n - 2);
  auto [r0, r1] = co_await cppcoro::when_all(std::move(f0), std::move(f1));
  co_return r0 + r1;
}

cppcoro::task<void> LatchDone(detail::co::TestExecutor& tp, cppcoro::async_latch& wg) {
  co_await tp.schedule();
  wg.count_down();
}

cppcoro::task<void> LatchAwait(detail::co::TestExecutor& tp, cppcoro::async_latch& wg) {
  co_await tp.schedule();
  co_await wg;
}

constexpr std::size_t kClients = 128;
constexpr std::size_t kQperClient = 100;

cppcoro::task<void> MutexWork(detail::co::TestExecutor& tp, auto& m, std::size_t& shared_id) {
  co_await tp.schedule();
  for (std::size_t i = 0; i < kQperClient; ++i) {
    co_await m.lock_async();
    ++shared_id;
    m.unlock();
    std::this_thread::sleep_for(std::chrono::nanoseconds{10});
  }
}

cppcoro::task<void> Reschedule100(detail::co::TestExecutor& tp) {
  for (int i = 0; i < 100; ++i) {
    co_await tp.schedule();
  }
}

}  // namespace
namespace detail::co {

TestExecutor::TestExecutor(std::size_t num_threads) {
  num_threads = std::max(std::size_t{1}, num_threads);
  _workers.reserve(num_threads);
  for (std::size_t i = 0; i != num_threads; ++i) {
    _workers.emplace_back([this] {
      std::unique_lock lock{_m};
      while (true) {
        while (!_jobs.Empty()) {
          auto& job = _jobs.PopFront();
          lock.unlock();
          static_cast<schedule_operation&>(job)._awaitingCoroutine.resume();
          lock.lock();
        }
        if (_stop) {
          return;
        }
        _cv.wait(lock);
      }
    });
  }
}

void TestExecutor::Restart() {
  std::lock_guard lock{_m};
}

void TestExecutor::Join() {
  {
    std::lock_guard lock{_m};
    _stop = true;
  }
  _cv.notify_all();
  for (auto& worker : _workers) {
    if (worker.joinable()) {
      worker.join();
    }
  }
}

TestExecutor::~TestExecutor() {
  Join();
}

void TestExecutor::Submit(TestExecutor::schedule_operation* job) noexcept {
  {
    std::lock_guard guard{_m};
    _jobs.PushBack(*job);
  }
  _cv.notify_one();
}

}  // namespace detail::co

detail::co::TestExecutor* CppCoro::AcquireExecutor(std::size_t threads) {
  if (threads != 0) {
    return new detail::co::TestExecutor{threads};
  }
  return nullptr;
}

void CppCoro::ReleaseExecutor(detail::co::TestExecutor* e) {
  delete e;
}

void CppCoro::CollatzLazy(std::size_t x) {
  auto task = ComputeCollatz(x);
  cppcoro::sync_wait(std::move(task));
}

void CppCoro::Fibonacci(detail::co::TestExecutor* tp, std::size_t n) {
  auto task = ComputeFibonacciAsync(*tp, n);
  std::ignore = cppcoro::sync_wait(std::move(task));
}

void CppCoro::AsyncMutex(detail::co::TestExecutor* tp) {
  cppcoro::async_mutex m;
  std::size_t shared_id = 0;
  auto all = [&]() -> cppcoro::task<void> {
    std::vector<cppcoro::task<void>> tasks;
    tasks.reserve(kClients);
    for (std::size_t i = 0; i < kClients; ++i) {
      tasks.push_back(MutexWork(*tp, m, shared_id));
    }
    co_await cppcoro::when_all_ready(std::move(tasks));
  };
  cppcoro::sync_wait(all());
}

void CppCoro::Latch(detail::co::TestExecutor* tp, std::size_t tasks_count) {
  cppcoro::async_latch wg{static_cast<ptrdiff_t>(tasks_count)};
  auto all = [&]() -> cppcoro::task<void> {
    std::vector<cppcoro::task<void>> tasks;
    tasks.reserve(tasks_count * 2);
    for (std::size_t i = 0; i < tasks_count * 2; ++i) {
      if (i % 2 == 0) {
        tasks.push_back(LatchAwait(*tp, wg));
      } else {
        tasks.push_back(LatchDone(*tp, wg));
      }
    }
    co_await cppcoro::when_all_ready(std::move(tasks));
  };
  cppcoro::sync_wait(all());
}

void CppCoro::Reschedule(detail::co::TestExecutor* tp) {
  auto task = Reschedule100(*tp);
  cppcoro::sync_wait(std::move(task));
}

}  // namespace bench
