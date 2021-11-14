#pragma once

#include "../std/progschj_threadpool.hpp"
#include "../utils/threadpool_runner.hpp"

#include <memory>
#include <string>
#include <utility>

namespace bench::tp::sd {

class ProgschjRunner final : public Runner {
 public:
  ProgschjRunner();

  std::string Name() const final;

  void Prepare() final;

  void Teardown() final;

 private:
  std::unique_ptr<progschj::ThreadPool> _pool;
};

}  // namespace bench::tp::sd
