#include "bind/qt/future.hpp"

#include <QFuture>
#include <QPromise>
#include <queue>
#include <thread>

#include <benchmark/benchmark.h>
#include <folly/synchronization/Baton.h>
#include <folly/synchronization/NativeSemaphore.h>
#include <qtconcurrentrun.h>

namespace bench {
namespace {

template <typename T>
T Incr(int&& r) {
  return r + 1;
}

}  // namespace

void QT::PromiseAndFuture() {
  auto [f, p] = detail::qt::MakeContract<int>();
  p.addResult(42);
  (void)f.result();
}

QFuture<int> QT::Thens(QFuture<int> f, size_t n, bool runInline, QThreadPool* pool) {
  for (size_t i = 0; i < n; i++) {
    if (runInline || !pool) {
      f = f.then(QtFuture::Launch::Sync, Incr<int>);
    } else {
      f = f.then(pool, Incr<int>);
    }
  }
  return f;
}

void QT::SomeThens(size_t n) {
  auto f = QtFuture::makeReadyFuture(42);
  f = Thens(std::move(f), n);
  f.result();
}

void QT::SomeThensOnThread(size_t n, bool run_inline) {
  QThreadPool pool;
  pool.setMaxThreadCount(1);
  QFuture<int> future = QtFuture::makeReadyFuture(42);

  auto f = QtFuture::makeReadyFuture(42);
  f = Thens(std::move(f), n / 2, run_inline, &pool);
  f = Thens(std::move(f), 1, false);
  f = Thens(std::move(f), n / 2, run_inline, &pool);
  f.waitForFinished();
}

void QT::NoContention(benchmark::State& state) {
  state.PauseTiming();
  std::vector<QPromise<int>> promises(10000);
  std::vector<QFuture<int>> futures;
  futures.reserve(10000);

  auto [f2, p2] = detail::qt::MakeContract<void>();

  for (auto& p : promises) {
    futures.push_back(p.future().then(QtFuture::Launch::Sync, Incr<int>));
  }

  auto producer = std::thread([&, p2 = std::move(p2)]() mutable {
    p2.finish();
    for (auto& p : promises) {
      std::move(p).addResult(42);
    }
  });
  f2.waitForFinished();

  state.ResumeTiming();
  producer.join();
}

void QT::Contention(benchmark::State& state) {
  state.PauseTiming();

  std::vector<QPromise<int>> promises(10000);
  std::vector<QFuture<int>> futures;
  futures.reserve(10000);
  folly::NativeSemaphore sem;
  folly::Baton<> b1;
  folly::Baton<> b2;
  for (auto& p : promises) {
    futures.push_back(p.future());
  }
  auto producer = std::thread([&] {
    b2.post();
    for (auto& p : promises) {
      sem.post();
      p.addResult(42);
      p.finish();
    }
  });
  auto consumer = std::thread([&] {
    b1.post();
    for (auto& f : futures) {
      sem.wait();
      f = f.then(QtFuture::Launch::Sync, Incr<int>);
    }
  });
  b1.wait();
  b2.wait();

  state.ResumeTiming();

  consumer.join();
  producer.join();
}

}  // namespace bench
