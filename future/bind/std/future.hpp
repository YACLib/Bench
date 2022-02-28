#pragma once

#include <future>

namespace bench {

struct Std {
  static void CreateFuture() {
    std::promise<int> p;
    p.set_value(42);
    std::future<int> f = p.get_future();
  }

  static void PromiseAndFuture() {
    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::move(p).set_value(42);
    std::ignore = std::move(f).get();
  }
};

}  // namespace bench
