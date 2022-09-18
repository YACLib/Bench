#include <bind/yaclib/intrusive_list.hpp>
#include <bind/yaclib/library.hpp>
#include <util/semaphore.hpp>
#include <yaclib/algo/wait_group.hpp>
#include <yaclib/async/future.hpp>
#include <yaclib/coro/await.hpp>
#include <yaclib/coro/future.hpp>
#include <yaclib/coro/mutex.hpp>
#include <yaclib/coro/on.hpp>
#include <yaclib/coro/task.hpp>
#include <yaclib/exe/inline.hpp>

#include <future>
#include <thread>

#include <benchmark/benchmark.h>

namespace bench {
namespace {

template <typename T>
T Incr(yaclib::Result<T>&& r) {
  return std::move(r).Ok() + 1;
}

yaclib::FutureOn<int> Thens(yaclib::FutureOn<int> f, std::size_t n, bool is_executor) {
  for (std::size_t i = 0; i != n; ++i) {
    if (is_executor) {
      f = std::move(f).Then(Incr<int>);
    } else {
      f = std::move(f).ThenInline(Incr<int>);
    }
  }
  return f;
}

yaclib::Future<> Reschedule100(yaclib::IExecutor& tp) {
  for (int i = 0; i < 100; ++i) {
    co_await On(tp);
  }
  co_return{};
}

yaclib::Future<> LatchAwait(yaclib::IExecutor& tp, yaclib::WaitGroup<>& wg) {
  co_await On(tp);
  co_await wg;
  co_return{};
}

yaclib::Future<> LatchDone(yaclib::IExecutor& tp, yaclib::WaitGroup<>& wg) {
  co_await On(tp);
  wg.Done();
  co_return{};
}

constexpr std::size_t kClients = 128;
constexpr std::size_t kQperClient = 100;

yaclib::Future<> MutexWork(yaclib::IExecutor& tp, auto& m, std::size_t& shared_id) {
  co_await On(tp);
  for (std::size_t i = 0; i < kQperClient; ++i) {
    co_await m.Lock();
    ++shared_id;
    co_await m.Unlock();
    std::this_thread::sleep_for(std::chrono::nanoseconds{10});
  }
  co_return{};
}

yaclib::Future<> ComputeCollatzEager(std::size_t x) {
  if (x <= 1) {
    co_return{};
  }
  if (x % 2 == 0) {
    auto foo = ComputeCollatzEager(x / 2);
    co_await Await(foo);
    co_return{};
  }
  auto foo = ComputeCollatzEager(3 * x + 1);
  co_await Await(foo);
  co_return{};
}

/*yaclib::Task<> ComputeCollatzLazy(std::size_t x) {
  if (x <= 1) {
    co_return{};
  }
  if (x % 2 == 0) {
    auto foo = ComputeCollatzLazy(x / 2);
    co_await Await(foo);
    co_return{};
  }
  auto foo = ComputeCollatzLazy(3 * x + 1);
  co_await Await(foo);
  co_return{};
}*/

yaclib::Future<std::size_t> ComputeFibonacciAsync(yaclib::IExecutor& e, std::size_t n);

yaclib::Future<std::size_t> ComputeFibonacciSync(yaclib::IExecutor& e, std::size_t n) {
  if (n <= 1) {
    co_return 1;
  }
  auto f1 = ComputeFibonacciAsync(e, n - 1);
  auto f2 = ComputeFibonacciSync(e, n - 2);
  co_await Await(f1, f2);
  co_return std::move(f1).Touch().Ok() + std::move(f2).Touch().Ok();
}

yaclib::Future<std::size_t> ComputeFibonacciAsync(yaclib::IExecutor& e, std::size_t n) {
  if (n <= 1) {
    co_return 1;
  }
  co_await On(e);
  auto f1 = ComputeFibonacciAsync(e, n - 1);
  auto f2 = ComputeFibonacciSync(e, n - 2);
  co_await Await(f1, f2);
  co_return std::move(f1).Touch().Ok() + std::move(f2).Touch().Ok();
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
        while (!_jobs.Empty()) {
          auto& job = _jobs.PopFront();
          lock.unlock();
          static_cast<yaclib::Job&>(job).Call();
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

yaclib::IExecutor::Type TestExecutor::Tag() const noexcept {
  return Type::Custom;
}

void TestExecutor::Submit(yaclib::Job& job) noexcept {
  {
    std::lock_guard guard{_m};
    _jobs.PushBack(job);
  }
  _cv.notify_one();
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

detail::yb::TestExecutor* YACLib::AcquireExecutor(std::size_t threads) {
  if (threads != 0) {
    return new detail::yb::TestExecutor{threads};
  }
  return nullptr;
}

void YACLib::ReleaseExecutor(detail::yb::TestExecutor* e) {
  delete e;
}

void YACLib::SomeThens(detail::yb::TestExecutor* executor, size_t n, bool no_inline) {
  bool is_executor = executor != nullptr;
  // hack for old api
  auto core = std::move(yaclib::MakeFuture(42).GetCore());
  core->_executor = executor != nullptr ? executor : &yaclib::MakeInline();
  auto f = yaclib::FutureOn{std::move(core)};
  f = Thens(std::move(f), n, is_executor && no_inline);
  f = Thens(std::move(f), 1, is_executor);
  f = Thens(std::move(f), n, is_executor && no_inline);
  Wait(f);
}

void YACLib::NoContention(benchmark::State& state, size_t iterations) {
  state.PauseTiming();

  std::vector<yaclib::Promise<int>> promises;
  std::vector<yaclib::Future<int>> futures;
  promises.reserve(iterations);
  futures.reserve(iterations);

  std::promise<void> p_producer;
  auto f_producer = p_producer.get_future();

  for (std::size_t i = 0; i != iterations; ++i) {
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

void YACLib::Contention(benchmark::State& state, size_t iterations) {
  state.PauseTiming();

  std::vector<yaclib::Promise<int>> promises;
  std::vector<yaclib::Future<int>> futures;
  promises.reserve(iterations);
  futures.reserve(iterations);

  for (std::size_t i = 0; i != iterations; ++i) {
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

template <typename T>
void YACLib::ComplexBenchmark() {
  auto fs = detail::yb::FsGen<T>();
  (void)WhenAll(fs.begin(), fs.end()).Get().Ok();
  fs = detail::yb::FsGen<T>();
  (void)WhenAny(fs.begin(), fs.end()).Get().Ok();
  fs = detail::yb::FsGen<T>();
  for (auto& f : fs) {
    if constexpr (std::is_void_v<T>) {
      f = std::move(f).ThenInline([] {
      });
    } else {
      f = std::move(f).ThenInline([](T&& t) {
        return std::move(t);
      });
    }
  }
  fs = detail::yb::FsGen<T>();
  for (auto& f : fs) {
    if constexpr (std::is_void_v<T>) {
      f = std::move(f).ThenInline([](yaclib::Result<T>&& /*TODO(MBkkt) remove this*/) {
        return yaclib::MakeFuture();
      });
    } else {
      f = std::move(f).ThenInline([](T&& t) {
        return yaclib::MakeFuture(std::move(t));
      });
    }
  }
}

template void YACLib::ComplexBenchmark<void>();
template void YACLib::ComplexBenchmark<Blob<2>>();
template void YACLib::ComplexBenchmark<Blob<4>>();
template void YACLib::ComplexBenchmark<Blob<8>>();
template void YACLib::ComplexBenchmark<Blob<16>>();
template void YACLib::ComplexBenchmark<Blob<32>>();
template void YACLib::ComplexBenchmark<Blob<64>>();
template void YACLib::ComplexBenchmark<Blob<128>>();
template void YACLib::ComplexBenchmark<Blob<256>>();
template void YACLib::ComplexBenchmark<Blob<512>>();
template void YACLib::ComplexBenchmark<Blob<1024>>();
template void YACLib::ComplexBenchmark<Blob<2048>>();
template void YACLib::ComplexBenchmark<Blob<4096>>();
template void YACLib::ComplexBenchmark<Blob<8192>>();

void YACLib::CollatzEager(std::size_t x) {
  auto future = ComputeCollatzEager(x);
  std::ignore = std::move(future).Get().Ok();
}

void YACLib::Fibonacci(detail::yb::TestExecutor* tp, std::size_t n) {
  auto future = ComputeFibonacciAsync(*tp, n);
  std::ignore = std::move(future).Get().Ok();
}

void YACLib::AsyncMutex(detail::yb::TestExecutor* tp) {
  yaclib::Mutex<false, 255> m;
  std::size_t shared_id = 0;
  yaclib::WaitGroup<> wg{kClients};
  for (std::size_t i = 0; i < kClients; ++i) {
    wg.Consume<false>(MutexWork(*tp, m, shared_id));
  }
  wg.Wait();
}

void YACLib::Latch(detail::yb::TestExecutor* tp, std::size_t tasks_count) {
  yaclib::WaitGroup<> wg;
  wg.Add(tasks_count);
  auto all = [&]() -> yaclib::Future<> {
    for (std::size_t i = 0; i < tasks_count * 2; ++i) {
      if (i % 2 == 0) {
        LatchAwait(*tp, wg).Detach();
      } else {
        LatchDone(*tp, wg).Detach();
      }
    }
    co_await wg;
    co_return{};
  };
  std::ignore = all().Get();
}

void YACLib::Reschedule(detail::yb::TestExecutor* tp) {
  auto task = Reschedule100(*tp);
  std::ignore = std::move(task).Get().Ok();
}

}  // namespace bench
