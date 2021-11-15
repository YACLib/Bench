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
using namespace std::placeholders;

void ForkingBenchmark(benchmark::State& state, Runner* runner, Suite* suite) {
  state.PauseTiming();

  runner->Prepare();
  suite->Prepare();

  auto callback = runner->Callback();
  auto async_call = [&callback, &state](std::function<void()>&& task) {
    state.ResumeTiming();
    auto future = callback(std::move(task));
    state.PauseTiming();

    return future;
  };
  suite->Run(std::move(async_call));

  suite->Teardown();
  runner->Teardown();
}

void JoiningBenchmark(benchmark::State& state, Runner* runner, Suite* suite) {
  state.PauseTiming();

  runner->Prepare();
  suite->Prepare();

  auto callback = runner->Callback();
  auto async_call = [&callback, &state](std::function<void()>&& task) {
    state.PauseTiming();
    auto future = callback(std::move(task));
    state.ResumeTiming();

    return future;
  };

  state.ResumeTiming();
  suite->Run(std::move(async_call));
  state.PauseTiming();

  suite->Teardown();
  runner->Teardown();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ProgschjForkingFluid(benchmark::State& state) {
  auto runner = sd::MakeProgschjRunner();
  auto suite = MakeFluidSolverSuite();
  for (auto _ : state) {
    ForkingBenchmark(state, runner.get(), suite.get());
  }
}

void ProgschjJoiningFluid(benchmark::State& state) {
  auto runner = sd::MakeProgschjRunner();
  auto suite = MakeFluidSolverSuite();
  for (auto _ : state) {
    JoiningBenchmark(state, runner.get(), suite.get());
  }
}

void YaclibOldForkingFluid(benchmark::State& state) {
  auto runner = sd::MakeProgschjRunner();
  auto suite = MakeFluidSolverSuite();
  for (auto _ : state) {
    ForkingBenchmark(state, runner.get(), suite.get());
  }
}

void YaclibOldJoiningFluid(benchmark::State& state) {
  auto runner = yb::MakeYaclibOldRunner();
  auto suite = MakeFluidSolverSuite();
  for (auto _ : state) {
    JoiningBenchmark(state, runner.get(), suite.get());
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace

BENCHMARK(ProgschjForkingFluid);
BENCHMARK(ProgschjJoiningFluid);

BENCHMARK(YaclibOldForkingFluid);
BENCHMARK(YaclibOldJoiningFluid);

BENCHMARK_MAIN();
