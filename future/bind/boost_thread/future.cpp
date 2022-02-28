#include <bind/boost_thread/future.hpp>
#include <semaphore.hpp>

#include <future>

#include <benchmark/benchmark.h>

namespace bench {
namespace {

template <typename T>
T Incr(boost::future<T>&& f) {
  return std::move(f).get() + 1;
}

boost::future<int> Thens(BoostThread::Executor* executor, boost::future<int> f, std::size_t n, bool is_executor) {
  for (std::size_t i = 0; i != n; ++i) {
    if (is_executor) {
      f = std::move(f).then(*executor, Incr<int>);
    } else {
      f = std::move(f).then(detail::bd::sInline, Incr<int>);
    }
  }
  return f;
}

}  // namespace
namespace detail::bd {

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

void TestExecutor::submit(work&& closure) {
  {
    std::lock_guard lock{_m};
    _tasks.push(std::move(closure));
  }
  _cv.notify_one();
}

}  // namespace detail::bd

void BoostThread::CreateFuture() {
  std::ignore = boost::make_ready_future(42);
}

void BoostThread::PromiseAndFuture() {
  boost::promise<int> p;
  boost::future<int> f = p.get_future();
  std::move(p).set_value(42);
  std::ignore = std::move(f).get();
}

void BoostThread::SomeThens(BoostThread::Executor* executor, size_t n, bool no_inline) {
  const bool is_executor = executor != nullptr;
  auto f = boost::make_ready_future(42);
  f = Thens(executor, std::move(f), n, is_executor && no_inline);
  f = Thens(executor, std::move(f), 1, is_executor);
  f = Thens(executor, std::move(f), n, is_executor && no_inline);
  f.wait();
}

void BoostThread::NoContention(benchmark::State& state) {
  state.PauseTiming();

  std::vector<boost::promise<int>> promises(kContentionIteration);
  std::vector<boost::future<int>> futures;
  futures.reserve(kContentionIteration);

  std::promise<void> p_producer;
  auto f_producer = p_producer.get_future();

  for (auto& p : promises) {
    futures.push_back(p.get_future().then(detail::bd::sInline, Incr<int>));
  }

  std::thread producer{[&] {
    p_producer.set_value();
    for (auto& p : promises) {
      std::move(p).set_value(42);
    }
  }};

  f_producer.wait();

  state.ResumeTiming();

  producer.join();
}

void BoostThread::Contention(benchmark::State& state) {
  state.PauseTiming();

  std::vector<boost::promise<int>> promises(kContentionIteration);
  std::vector<boost::future<int>> futures;
  futures.reserve(kContentionIteration);

  for (auto& p : promises) {
    futures.push_back(p.get_future());
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
      std::move(p).set_value(42);
    }
  });
  auto consumer = std::thread([&] {
    p_consumer.set_value();
    for (auto& f : futures) {
      semaphore.Acquire();
      f = std::move(f).then(detail::bd::sInline, Incr<int>);
    }
  });

  f_consumer.wait();
  f_producer.wait();

  state.ResumeTiming();

  producer.join();
  consumer.join();
}

}  // namespace bench
