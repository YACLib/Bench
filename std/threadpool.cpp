#include "threadpool.hpp"

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

}  // namespace bench::tp::sd
