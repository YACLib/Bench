#include "threadpool.hpp"

#include "progschj_threadpool.hpp"

#include <functional>
#include <memory>
#include <string>
#include <utility>

namespace bench::tp::sd {

void ProgschjRunner::Teardown() {
  _pool = nullptr;
}

void ProgschjRunner::Prepare() {
  _pool = std::make_unique<progschj::ThreadPool>(4);
}

std::string ProgschjRunner::Name() const {
  return "progschj's ThreadPool";
}

ProgschjRunner::ProgschjRunner()
    : Runner([this](std::function<void()>&& f) {
        return _pool->enqueue(std::move(f));
      }) {
}

RunnerPtr MakeProgschjRunner() {
  return std::make_unique<ProgschjRunner>();
}

}  // namespace bench::tp::sd
