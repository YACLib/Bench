#pragma once

#include <future>

namespace bench {

struct Std {
  template <typename T>
  static void CreateFuture(T&& value) {
    std::promise<T> p;
    std::future<T> f = p.get_future();
    std::move(p).set_value(42);
    (void)f.get();
  }

  static void PromiseAndFuture() {
    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::move(p).set_value(42);
    std::move(f).get();
  }
};

}  // namespace bench
