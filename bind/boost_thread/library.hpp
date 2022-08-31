#pragma once

#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <queue>
#include <thread>

#define BOOST_THREAD_VERSION 5
#include <boost/thread/executors/inline_executor.hpp>
#include <boost/thread/future.hpp>

#include <benchmark/benchmark.h>

namespace bench {
namespace detail::bd {

class TestExecutor final : public boost::executors::executor {
 public:
  explicit TestExecutor(std::size_t num_threads);

  void Restart();
  void Join();

  ~TestExecutor() final;

  void submit(work&& closure) final;

  bool try_executing_one() final {
    return false;
  }
  void close() final {
  }
  bool closed() final {
    return false;
  }

  std::mutex _m;
  std::condition_variable _cv;
  std::queue<work> _tasks;
  std::vector<std::thread> _workers;
  bool _stop = false;
};

class InlineExecutor final : public boost::executors::executor {
 public:
  void submit(work&& closure) final {
    closure();
  }
  bool try_executing_one() final {
    return false;
  }
  void close() final {
  }
  bool closed() final {
    return false;
  }
};

static InlineExecutor sInline;

template <typename T>
boost::future<T> FGen() {
  boost::promise<T> p;
  auto f = p.get_future();
  f = std::move(f)
        .then(sInline,
              [](boost::future<T>&& t) {
                return std::move(t).get();
              })
        .then(sInline,
              [](boost::future<T>&& t) {
                return std::move(t).get();
                // return boost::make_ready_future(std::move(t).get()); // TODO(MBkkt) Future unwrapping
              })
        .then(sInline,
              [](boost::future<T>&& t) {
                return std::move(t).get();
              })
        .then(sInline, [](boost::future<T>&& t) {
          return std::move(t).get();
          // return boost::make_ready_future(std::move(t).get());// TODO(MBkkt) Future unwrapping
        });
  p.set_value(T{});
  return f;
}

template <typename T, std::size_t Size = 10>
std::vector<boost::future<T>> FsGen() {
  std::vector<boost::future<T>> fs;
  fs.reserve(Size);
  for (std::size_t i = 0; i != Size; ++i) {
    fs.emplace_back(FGen<T>());
  }
  return fs;
}

}  // namespace detail::bd

struct BoostThread {
  static void CreateFuture();
  static void PromiseAndFuture();

  using Executor = detail::bd::TestExecutor;
  static void SomeThens(Executor* executor, size_t n, bool no_inline);

  struct Unit {};
  template <typename T = Unit>
  static void ComplexBenchmark();

  static constexpr std::size_t kContentionIteration = 10000;
  static void NoContention(benchmark::State& state);
  static void Contention(benchmark::State& state);
};

template <typename T>
void BoostThread::ComplexBenchmark() {
  auto fs = detail::bd::FsGen<T>();
  std::ignore = boost::when_all(fs.begin(), fs.end()).get();
  fs = detail::bd::FsGen<T>();
  std::ignore = boost::when_any(fs.begin(), fs.end()).get();
  fs = detail::bd::FsGen<T>();
  for (auto& f : fs) {
    f = std::move(f).then(detail::bd::sInline, [](boost::future<T>&& t) {
      return std::move(t).get();
    });
  }
  fs = detail::bd::FsGen<T>();
  for (auto& f : fs) {
    f = std::move(f).then(detail::bd::sInline, [](boost::future<T>&& t) {
      return std::move(t).get();
      // return boost::make_ready_future(std::move(t).get()); TODO(MBkkt) Future unwrapping
    });
  }
}

}  // namespace bench