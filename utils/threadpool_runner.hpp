#pragma once
#include <functional>
#include <future>
#include <memory>
#include <string>
#include <utility>

namespace bench::tp {

class Runner {
 public:
  Runner(std::function<std::future<void>(std::function<void()>&&)>&& callback);

  virtual std::string Name() const = 0;

  virtual void Prepare() = 0;

  virtual void Teardown() = 0;

  std::function<std::future<void>(std::function<void()>&&)>& Callback();

  virtual ~Runner();

 private:
  std::function<std::future<void>(std::function<void()>&&)> _callback;
};

using RunnerPtr = std::unique_ptr<Runner>;

}  // namespace bench::tp
