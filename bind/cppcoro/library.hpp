#pragma once

#include <bind/yaclib/intrusive_list.hpp>
#include <cppcoro/coroutine.hpp>

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

#include <benchmark/benchmark.h>

namespace bench {
namespace detail::co {

class TestExecutor {
 public:
  explicit TestExecutor(std::size_t num_threads);

  ~TestExecutor();

  struct schedule_operation : yaclib::detail::Node {
    schedule_operation(TestExecutor* tp) noexcept : _tp{tp} {
    }

    bool await_ready() noexcept {
      return false;
    }

    void await_suspend(cppcoro::coroutine_handle<> awaitingCoroutine) noexcept {
      _awaitingCoroutine = awaitingCoroutine;
      _tp->Submit(this);
    }

    void await_resume() noexcept {
    }

    TestExecutor* _tp;
    cppcoro::coroutine_handle<> _awaitingCoroutine;
  };

  [[nodiscard]] schedule_operation schedule() noexcept {
    return schedule_operation{this};
  }

  void Restart();
  void Join();

 private:
  friend class schedule_operation;

  void Submit(schedule_operation* job) noexcept;

  std::mutex _m;
  std::condition_variable _cv;
  detail::yb::List<schedule_operation> _jobs;
  std::vector<std::thread> _workers;
  bool _stop = false;
};

}  // namespace detail::co

struct CppCoro {
  static detail::co::TestExecutor* AcquireExecutor(std::size_t threads);
  static void ReleaseExecutor(detail::co::TestExecutor* e);

  static void CollatzLazy(std::size_t x);
  static void Fibonacci(detail::co::TestExecutor* tp, std::size_t n);
  static void AsyncMutex(detail::co::TestExecutor* tp);
  static void Latch(detail::co::TestExecutor* tp, std::size_t task_count);
  static void Reschedule(detail::co::TestExecutor* tp);
};

}  // namespace bench
