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

#ifdef HEAVY
auto Incr = [SIZEOF_F](folly::Try<int>&& r) -> int {
  return std::move(r).value() + 1;
};
#else
int Incr(folly::Try<int>&& r) {
  return std::move(r).value() + 1;
}
#endif

folly::Future<int> Thens(folly::Future<int> f, std::size_t n, bool is_executor) {
  for (std::size_t i = 0; i != n; ++i) {
    if (is_executor) {
      f = std::move(f).then(Incr);
    } else {
      f = std::move(f).thenInline(Incr);
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
    futures.push_back(p.getFuture().thenInline(Incr));
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
      f = std::move(f).thenInline(Incr);
    }
  });

  f_consumer.wait();
  f_producer.wait();

  state.ResumeTiming();

  producer.join();
  consumer.join();
}

template <typename T>
void Folly::ComplexBenchmark() {
  auto fs = detail::fy::FsGen<T>();
  std::ignore = folly::collectAll(fs.begin(), fs.end()).value();
  fs = detail::fy::FsGen<T>();
  std::ignore = folly::collectAny(fs.begin(), fs.end()).value();
  fs = detail::fy::FsGen<T>();
  for (auto& f : fs) {
    f = std::move(f).thenValueInline([SIZEOF_F](T&& t) {
      return std::move(t);
    });
  }
  fs = detail::fy::FsGen<T>();
  for (auto& f : fs) {
    f = std::move(f).thenValueInline([SIZEOF_F](T&& t) {
      return folly::makeFuture(T{std::move(t)});
    });
  }
}

template void Folly::ComplexBenchmark<folly::Unit>();
template void Folly::ComplexBenchmark<Blob<2>>();
template void Folly::ComplexBenchmark<Blob<4>>();
template void Folly::ComplexBenchmark<Blob<8>>();
template void Folly::ComplexBenchmark<Blob<16>>();
template void Folly::ComplexBenchmark<Blob<32>>();
template void Folly::ComplexBenchmark<Blob<64>>();
template void Folly::ComplexBenchmark<Blob<128>>();
template void Folly::ComplexBenchmark<Blob<256>>();
template void Folly::ComplexBenchmark<Blob<512>>();
template void Folly::ComplexBenchmark<Blob<1024>>();
template void Folly::ComplexBenchmark<Blob<2048>>();
template void Folly::ComplexBenchmark<Blob<4096>>();
template void Folly::ComplexBenchmark<Blob<8192>>();

}  // namespace bench
