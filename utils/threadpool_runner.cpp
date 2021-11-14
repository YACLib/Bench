#include "threadpool_runner.hpp"

namespace bench::tp {

Runner::Runner(std::function<std::future<void>(std::function<void()>&&)>&& callback) : _callback{std::move(callback)} {
}

Runner::~Runner() = default;

std::function<std::future<void>(std::function<void()>&&)>& Runner::Callback() {
  return _callback;
}

}  // namespace bench::tp
