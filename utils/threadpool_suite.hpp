#pragma once
#include <functional>
#include <future>
#include <string>

namespace bench::tp {

class Suite {
 public:
  virtual void Run(std::function<std::future<void>(std::function<void(void)>&&)>&& f) = 0;

  virtual std::string Name() const = 0;

  virtual bool CheckResult() = 0;

  virtual void Prepare() = 0;

  virtual void Teardown() = 0;

  virtual size_t ProblemSize() const = 0;

  virtual ~Suite();
};

}  // namespace bench::tp
