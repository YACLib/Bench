#pragma once

#include <condition_variable>
#include <future>
#include <thread>

namespace bench::future::sd {

std::future<int> MakeFuture(int x) {
  std::promise<int> p;
  std::future<int> f = p.get_future();
  std::move(p).set_value(42);
  return f;
}

}  // namespace bench::future::sd
