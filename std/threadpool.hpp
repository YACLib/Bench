#pragma once
#include "std/progschj_threadpool.hpp"
#include "utils/threadpool_runner.hpp"

namespace bench::tp::sd {

class ProgschjRunner final : Runner {
 public:
  [[nodiscard]] std::string Name() const override;

  void Prepare() override;

  void Teardown() override;

 private:
  std::unique_ptr<progschj::ThreadPool> _pool;
};

}  // namespace bench::tp::sd
