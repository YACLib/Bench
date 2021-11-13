#pragma once
#include <functional>
#include <future>
#include <string>
#include <utility>

namespace bench::tp {

class Runner {
 public:
  Runner(std::function<std::future<void>(std::function<void(void)>&&)>&& callback);

  virtual std::string Name() const = 0;
  virtual void Prepare() = 0;
  virtual void Teardown() = 0;

 private:
  std::function<std::future<void>(std::function<void(void)>&&)> _run;
};

}  // namespace bench::tp
