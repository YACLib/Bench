#pragma once

#include "../utils/threadpool_runner.hpp"

#include <yaclib/executor/thread_pool.hpp>

#include <string>

namespace bench::tp::yb {

class YaclibOldRunner final : public Runner {
 public:
  YaclibOldRunner();

  std::string Name() const final;

  void Prepare() final;

  void Teardown() final;

 private:
  yaclib::IThreadPoolPtr _pool;
};

RunnerPtr MakeYaclibOldRunner();

}  // namespace bench::tp::yb
