#include <bind/folly/future.hpp>
#include <semaphore.hpp>

#include <future>
#include <vector>

#include <benchmark/benchmark.h>
#include <folly/executors/InlineExecutor.h>
#include <folly/futures/Future.h>
#include <folly/futures/Promise.h>

namespace bench {
namespace {

template <typename T>
T Incr(folly::Try<T>&& t) {
  return t.value() + 1;
}

folly::Future<int> Thens(folly::Future<int> f, std::size_t n, bool is_executor) {
  for (std::size_t i = 0; i != n; ++i) {
    if (is_executor) {
      f = std::move(f).then(Incr<int>);
    } else {
      f = std::move(f).thenInline(Incr<int>);
    }
  }
  return f;
}

}  // namespace
namespace detail::fy {

TestExecutor::TestExecutor(std::size_t num_threads) {
  num_threads = std::max(std::size_t{1}, num_threads);
  _workers.reserve(num_threads);
  for (std::size_t i = 0; i != num_threads; ++i) {
    _workers.emplace_back([this] {
      std::unique_lock lock{_m};
      while (true) {
        while (!_tasks.empty()) {
          auto work = std::move(_tasks.front());
          _tasks.pop();
          lock.unlock();
          work();
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
  _tasks = {};
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

void TestExecutor::add(folly::Func f) {
  {
    std::lock_guard lock{_m};
    _tasks.push(std::move(f));
  }
  _cv.notify_one();
}

}  // namespace detail::fy

void Folly::CreateFuture() {
  std::ignore = folly::makeFuture<int>(42);
}

void Folly::PromiseAndFuture() {
  folly::Promise<int> p;
  folly::Future<int> f = p.getFuture();
  std::move(p).setValue(42);
  std::ignore = std::move(f).get();
}

detail::fy::TestExecutor* Folly::AcquireExecutor(std::size_t threads) {
  if (threads != 0) {
    return new detail::fy::TestExecutor{threads};
  }
  return nullptr;
}

void Folly::ReleaseExecutor(std::size_t threads, detail::fy::TestExecutor* e) {
  if (threads != 0) {
    delete e;
  }
}

void Folly::SomeThens(detail::fy::TestExecutor* executor, size_t n, bool no_inline) {
  const bool is_executor = executor != nullptr;
  auto f = folly::makeFuture(42).via(executor);
  f = Thens(std::move(f), n, is_executor && no_inline);
  f = Thens(std::move(f), 1, is_executor);
  f = Thens(std::move(f), n, is_executor && no_inline);
  f.wait();
}

void Folly::NoContention(benchmark::State& state) {
  state.PauseTiming();

  std::vector<folly::Promise<int>> promises(kContentionIteration);
  std::vector<folly::Future<int>> futures;
  futures.reserve(kContentionIteration);

  std::promise<void> p_producer;
  auto f_producer = p_producer.get_future();

  for (auto& p : promises) {
    futures.push_back(p.getFuture().thenInline(Incr<int>));
  }

  std::thread producer{[&] {
    p_producer.set_value();
    for (auto& p : promises) {
      std::move(p).setValue(42);
    }
  }};

  f_producer.wait();

  state.ResumeTiming();

  producer.join();
}

void Folly::Contention(benchmark::State& state) {
  state.PauseTiming();

  std::vector<folly::Promise<int>> promises(kContentionIteration);
  std::vector<folly::Future<int>> futures;
  futures.reserve(kContentionIteration);

  for (auto& p : promises) {
    futures.push_back(p.getFuture());
  }

  BusySemaphoreSPSC semaphore;
  std::promise<void> p_consumer;
  auto f_consumer = p_consumer.get_future();
  std::promise<void> p_producer;
  auto f_producer = p_producer.get_future();

  auto producer = std::thread([&] {
    p_producer.set_value();
    for (auto& p : promises) {
      semaphore.Release();
      std::move(p).setValue(42);
    }
  });
  auto consumer = std::thread([&] {
    p_consumer.set_value();
    for (auto& f : futures) {
      semaphore.Acquire();
      f = std::move(f).thenInline(Incr<int>);
    }
  });

  f_consumer.wait();
  f_producer.wait();

  state.ResumeTiming();

  producer.join();
  consumer.join();
}

}  // namespace bench
