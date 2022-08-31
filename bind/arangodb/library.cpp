#include <bind/arangodb/library.hpp>
#include <util/semaphore.hpp>

#include <future>
#include <latch>
#include <vector>

#include <arangodb/futures/Future.h>
#include <arangodb/futures/Promise.h>
#include <arangodb/futures/Try.h>
#include <arangodb/futures/Utilities.h>
#include <benchmark/benchmark.h>

namespace bench {
namespace {

template <typename T>
T Incr(arangodb::futures::Try<T>&& t) {
  return std::move(t).get() + 1;
}

arangodb::futures::Future<int> Thens(arangodb::futures::Future<int> f, std::size_t n,
                                     detail::adb::TestExecutor* executor) {
  for (std::size_t i = 0; i != n; ++i) {
    if (executor != nullptr) {
      arangodb::futures::Promise<int> outer_p;
      auto outer_f = outer_p.getFuture();
      std::move(f).then([executor, outer_p = std::move(outer_p)](arangodb::futures::Try<int>&& t) mutable {
        executor->add([outer_p = std::move(outer_p), t = std::move(t)]() mutable {
          std::move(outer_p).setValue(Incr<int>(std::move(t)));
          // TODO possible exception ignored now
        });
      }) /*implicit detach*/;
      f = std::move(outer_f);
    } else {
      f = std::move(f).then /*inline*/ (Incr<int>);
    }
  }
  return f;
}

}  // namespace
namespace detail::adb {

TestExecutor::TestExecutor(std::size_t num_threads) {
  num_threads = std::max(std::size_t{1}, num_threads);
  _workers.reserve(num_threads);
  for (std::size_t i = 0; i != num_threads; ++i) {
    _workers.emplace_back([this] {
      std::unique_lock lock{_m};
      while (true) {
        while (!_jobs.empty()) {
          auto work = std::move(_jobs.front());
          _jobs.pop();
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
  _jobs = {};
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

void TestExecutor::add(Job job) {
  {
    std::lock_guard lock{_m};
    _jobs.push(std::move(job));
  }
  _cv.notify_one();
}

}  // namespace detail::adb

void ArangoDB::CreateFuture() {
  std::ignore = arangodb::futures::makeFuture<int>(42);
}

void ArangoDB::PromiseAndFuture() {
  arangodb::futures::Promise<int> p;
  arangodb::futures::Future<int> f = p.getFuture();
  std::move(p).setValue(42);
  std::ignore = std::move(f).get();
}

detail::adb::TestExecutor* ArangoDB::AcquireExecutor(std::size_t threads) {
  if (threads != 0) {
    return new detail::adb::TestExecutor{threads};
  }
  return nullptr;
}

void ArangoDB::ReleaseExecutor(detail::adb::TestExecutor* e) {
  delete e;
}

void ArangoDB::SomeThens(detail::adb::TestExecutor* executor, size_t n, bool no_inline) {
  const bool is_executor = executor != nullptr;
  auto f = arangodb::futures::makeFuture(42);
  f = Thens(std::move(f), n, (is_executor && no_inline ? executor : nullptr));
  f = Thens(std::move(f), 1, (is_executor ? executor : nullptr));
  f = Thens(std::move(f), n, (is_executor && no_inline ? executor : nullptr));
  f.wait();
}

void ArangoDB::NoContention(benchmark::State& state) {
  state.PauseTiming();

  std::vector<arangodb::futures::Promise<int>> promises(kContentionIteration);
  std::vector<arangodb::futures::Future<int>> futures;
  futures.reserve(kContentionIteration);

  std::promise<void> p_producer;
  auto f_producer = p_producer.get_future();

  for (auto& p : promises) {
    futures.push_back(p.getFuture().then(Incr<int>));
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

void ArangoDB::Contention(benchmark::State& state) {
  state.PauseTiming();

  std::vector<arangodb::futures::Promise<int>> promises(kContentionIteration);
  std::vector<arangodb::futures::Future<int>> futures;
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
      f = std::move(f).then(Incr<int>);
    }
  });

  f_consumer.wait();
  f_producer.wait();

  state.ResumeTiming();

  producer.join();
  consumer.join();
}

template <typename T>
void ArangoDB::ComplexBenchmark() {
  auto fs = detail::adb::FsGen<T>();
  std::ignore = arangodb::futures::collectAll(fs.begin(), fs.end()).get();
  fs = detail::adb::FsGen<T>();
  std::ignore = arangodb::futures::collectAll /*should be Any, but we don't have it*/ (fs.begin(), fs.end()).get();
  fs = detail::adb::FsGen<T>();
  for (auto& f : fs) {
    f = std::move(f).thenValue([](T&& t) {
      return std::move(t);
    });
  }
  fs = detail::adb::FsGen<T>();
  for (auto& f : fs) {
    f = std::move(f).thenValue([](T&& t) {
      return arangodb::futures::makeFuture(T{std::move(t)});
    });
  }
}

template void ArangoDB::ComplexBenchmark<arangodb::futures::Unit>();
template void ArangoDB::ComplexBenchmark<Blob<2>>();
template void ArangoDB::ComplexBenchmark<Blob<4>>();
template void ArangoDB::ComplexBenchmark<Blob<8>>();
template void ArangoDB::ComplexBenchmark<Blob<16>>();
template void ArangoDB::ComplexBenchmark<Blob<32>>();
template void ArangoDB::ComplexBenchmark<Blob<64>>();
template void ArangoDB::ComplexBenchmark<Blob<128>>();
template void ArangoDB::ComplexBenchmark<Blob<256>>();
template void ArangoDB::ComplexBenchmark<Blob<512>>();
template void ArangoDB::ComplexBenchmark<Blob<1024>>();
template void ArangoDB::ComplexBenchmark<Blob<2048>>();
template void ArangoDB::ComplexBenchmark<Blob<4096>>();
template void ArangoDB::ComplexBenchmark<Blob<8192>>();

std::size_t ComputeCollatz(std::size_t x) {
  if (x <= 1) {
    return 0;
  }
  if (x % 2 == 0) {
    return ComputeCollatz(x / 2) + 1;
  }
  return ComputeCollatz(3 * x + 1) + 1;
}

void ArangoDB::Collatz(std::size_t x) {
  benchmark::DoNotOptimize(ComputeCollatz(x));
}

std::size_t ComputeFibonacci(std::size_t n) {
  if (n <= 1) {
    return 1;
  }
  return ComputeFibonacci(n - 2) + ComputeFibonacci(n - 1);
}

void ArangoDB::Fibonacci(detail::adb::TestExecutor* tp, std::size_t n) {
  benchmark::DoNotOptimize(ComputeFibonacci(n));
}

constexpr std::size_t kClients = 128;
constexpr std::size_t kQperClient = 100;

void MutexWork(std::latch& latch, std::mutex& m, std::size_t& shared_id) {
  for (std::size_t i = 0; i < kQperClient; ++i) {
    m.lock();
    ++shared_id;
    m.unlock();
    std::this_thread::sleep_for(std::chrono::nanoseconds{10});
  }
  latch.count_down();
}

void ArangoDB::AsyncMutex(detail::adb::TestExecutor* tp) {
  std::latch latch{kClients};
  std::mutex m;
  std::size_t shared_id = 0;
  for (std::size_t i = 0; i < kClients; ++i) {
    tp->add([&] {
      MutexWork(latch, m, shared_id);
    });
  }
  latch.wait();
}

}  // namespace bench
