#include <bind/yaclib/future.hpp>
#include <bind/yaclib/intrusive_list.hpp>
#include <semaphore.hpp>
#include <yaclib/async/future.hpp>
#include <yaclib/exe/inline.hpp>

#include <future>
#include <thread>

#include <benchmark/benchmark.h>

namespace bench {
namespace {

#ifdef HEAVY
auto Incr = [SIZEOF_F](yaclib::Result<int>&& r) -> int {
  return std::move(r).Ok() + 1;
};
#else
int Incr(yaclib::Result<int>&& r) {
  return std::move(r).Ok() + 1;
}
#endif

yaclib::FutureOn<int> Thens(yaclib::FutureOn<int> f, std::size_t n, bool is_executor) {
  for (std::size_t i = 0; i != n; ++i) {
    if (is_executor) {
      f = std::move(f).Then(Incr);
    } else {
      f = std::move(f).ThenInline(Incr);
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

yaclib::IExecutor::Type TestExecutor::Tag() const {
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

void YACLib::SomeThens(detail::yb::TestExecutor* executor, size_t n, bool no_inline) {
  bool is_executor = executor != nullptr;
  auto f = yaclib::MakeFuture(42).On(executor != nullptr ? *executor : yaclib::MakeInline());
  f = Thens(std::move(f), n, is_executor && no_inline);
  f = Thens(std::move(f), 1, is_executor);
  f = Thens(std::move(f), n, is_executor && no_inline);
  Wait(f);
}

void YACLib::ReleaseExecutor(std::size_t threads, detail::yb::TestExecutor* e) {
  if (threads != 0) {
    delete e;
  }
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
    futures.emplace_back(std::move(f).ThenInline(Incr));
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
      f = std::move(f).ThenInline(Incr);
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
      f = std::move(f).ThenInline([SIZEOF_F] {
      });
    } else {
      f = std::move(f).ThenInline([SIZEOF_F](T&& t) {
        return std::move(t);
      });
    }
  }
  fs = detail::yb::FsGen<T>();
  for (auto& f : fs) {
    if constexpr (std::is_void_v<T>) {
      f = std::move(f).ThenInline([SIZEOF_F](yaclib::Result<T>&& /*TODO(MBkkt) remove this*/) {
        return yaclib::MakeFuture();
      });
    } else {
      f = std::move(f).ThenInline([SIZEOF_F](T&& t) {
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

}  // namespace bench
