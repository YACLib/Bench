#include "threadpool.hpp"

#include "../utils/threadpool_runner.hpp"

#include <yaclib/executor/thread_pool.hpp>

#include <functional>
#include <future>
#include <memory>
#include <string>

namespace bench::tp::yb {

void YaclibOldRunner::Teardown() {
  _pool = nullptr;
}

void YaclibOldRunner::Prepare() {
  _pool = yaclib::MakeThreadPool(4);
}

std::string YaclibOldRunner::Name() const {
  return "YACLib's Old ThreadPool";
}

YaclibOldRunner::YaclibOldRunner()
    : Runner([this](std::function<void()>&& f) {
        std::promise<void> barrier;
        std::future<void> future_barrier = barrier.get_future();
        _pool->Execute([barrier = std::move(barrier), f = std::move(f)]() mutable {
          f();
          std::move(barrier).set_value();
        });
        return future_barrier;
      }) {
}

RunnerPtr MakeYaclibOldRunner() {
  return std::make_unique<YaclibOldRunner>();
}

}  // namespace bench::tp::yb
