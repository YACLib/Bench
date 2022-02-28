#include <bind/yaclib/future.hpp>
#include <bind/yaclib/intrusive_list.hpp>
#include <semaphore.hpp>
#include <yaclib/async/future.hpp>
#include <yaclib/executor/inline.hpp>

#include <future>
#include <thread>

#include <benchmark/benchmark.h>

namespace bench {
namespace {

template <typename T>
T Incr(yaclib::Result<T>&& r) {
  return std::move(r).Ok() + 1;
}

yaclib::Future<int> Thens(yaclib::Future<int> f, std::size_t n, bool is_executor) {
  for (std::size_t i = 0; i != n; ++i) {
    if (is_executor) {
      f = std::move(f).Then(Incr<int>);
    } else {
      f = std::move(f).ThenInline(Incr<int>);
    }
  }
  return f;
}

}  // namespace
namespace detail::yb {

TestExecutor::TestExecutor(std::size_t num_threads) {
  num_threads = std::max(std::size_t{1}, num_threads);
  _workers.reserve(num_threads);
  for (std::size_t i = 0; i != num_threads; ++i) {
    _workers.emplace_back([this] {
      std::unique_lock lock{_m};
      while (true) {
        while (!_tasks.Empty()) {
          auto& task = _tasks.PopFront();
          lock.unlock();
          task.Call();
          task.DecRef();
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

yaclib::IExecutor::Type TestExecutor::Tag() const {
  return Type::Custom;
}

bool TestExecutor::Submit(yaclib::ITask& task) noexcept {
  task.IncRef();
  {
    std::lock_guard guard{_m};
    _tasks.PushBack(task);
  }
  _cv.notify_one();
  return true;
}

}  // namespace detail::yb

void YACLib::CreateFuture() {
  std::ignore = yaclib::MakeFuture(42);
}

void YACLib::PromiseAndFuture() {
  auto [f, p] = yaclib::MakeContract<int>();
  std::move(p).Set(42);
  std::ignore = std::move(f).Get().Ok();
}

void YACLib::SomeThens(YACLib::Executor* executor, size_t n, bool no_inline) {
  const bool is_executor = executor != nullptr;
  auto f = yaclib::MakeFuture(42).Via(executor);
  f = Thens(std::move(f), n, is_executor && no_inline);
  f = Thens(std::move(f), 1, is_executor);
  f = Thens(std::move(f), n, is_executor && no_inline);
  Wait(f);
}

void YACLib::NoContention(benchmark::State& state) {
  state.PauseTiming();

  std::vector<yaclib::Promise<int>> promises;
  std::vector<yaclib::Future<int>> futures;
  promises.reserve(kContentionIteration);
  futures.reserve(kContentionIteration);

  std::promise<void> p_producer;
  auto f_producer = p_producer.get_future();

  for (std::size_t i = 0; i != kContentionIteration; ++i) {
    auto [f, p] = yaclib::MakeContract<int>();
    promises.emplace_back(std::move(p));
    futures.emplace_back(std::move(f).ThenInline(Incr<int>));
  }

  auto producer = std::thread([&]() mutable {
    p_producer.set_value();

    for (auto& p : promises) {
      std::move(p).Set(42);
    }
  });

  f_producer.wait();

  state.ResumeTiming();

  producer.join();
}

void YACLib::Contention(benchmark::State& state) {
  state.PauseTiming();

  std::vector<yaclib::Promise<int>> promises;
  std::vector<yaclib::Future<int>> futures;
  promises.reserve(kContentionIteration);
  futures.reserve(kContentionIteration);

  for (std::size_t i = 0; i != kContentionIteration; ++i) {
    auto [f, p] = yaclib::MakeContract<int>();
    futures.push_back(std::move(f));
    promises.push_back(std::move(p));
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
      std::move(p).Set(42);
    }
  });
  auto consumer = std::thread([&] {
    p_consumer.set_value();
    for (auto& f : futures) {
      semaphore.Acquire();
      f = std::move(f).ThenInline(Incr<int>);
    }
  });

  f_consumer.wait();
  f_producer.wait();

  state.ResumeTiming();

  producer.join();
  consumer.join();
}

}  // namespace bench
