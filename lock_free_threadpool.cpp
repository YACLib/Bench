#include "folly/threadpool.hpp"
#include "std/threadpool.hpp"
#include "threadpool_problems/fluid_solver.hpp"
#include "utils/threadpool_runner.hpp"
#include "utils/threadpool_suite.hpp"
#include "yaclib/threadpool.hpp"

#include <functional>
#include <utility>

#include <benchmark/benchmark.h>

namespace {

using namespace bench::tp;

void RunBenchmark(benchmark::State& state, Runner* runner, Suite* suite) {
  runner->Prepare();

  suite->Prepare();
  auto callback = runner->Callback();
  auto async_call = [&callback](std::function<void()>&& task) {
    auto future = callback(std::move(task));
    return future;
  };
  suite->Run(std::move(async_call));
  suite->Teardown();

  runner->Teardown();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DoesItWork(benchmark::State& state) {
  for (auto _ : state) {
    // Do nothing
  }
}

void ProgschjFluid(benchmark::State& state) {
  auto runner = sd::ProgschjRunner();
  auto suite = FluidSolverSuite();
  for (auto _ : state) {
    RunBenchmark(state, &runner, &suite);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace

BENCHMARK(DoesItWork);
BENCHMARK(ProgschjFluid);

BENCHMARK_MAIN();
