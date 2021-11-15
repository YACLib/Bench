#include "folly/threadpool.hpp"
#include "std/threadpool.hpp"
#include "threadpool_problems/simple_fluid_solver.hpp"
#include "utils/threadpool_runner.hpp"
#include "utils/threadpool_suite.hpp"

#include <yaclib/algo/wait_group.hpp>
#include <yaclib/async/run.hpp>
#include <yaclib/executor/thread_pool.hpp>

#include <functional>
#include <utility>

#include <benchmark/benchmark.h>

namespace {

using namespace bench::tp;
using namespace std::placeholders;

// void ForkingBenchmark(benchmark::State& state, Runner* runner, Suite* suite) {
//   state.PauseTiming();
//
//   runner->Prepare();
//   suite->Prepare();
//
//   auto callback = runner->Callback();
//   auto async_call = [&callback, &state](std::function<void()>&& task) {
//     state.ResumeTiming();
//     auto future = callback(std::move(task));
//     state.PauseTiming();
//
//     return future;
//   };
//   suite->Run(std::move(async_call));
//
//   suite->Teardown();
//   runner->Teardown();
// }
//
// void JoiningBenchmark(benchmark::State& state, Runner* runner, Suite* suite) {
//   state.PauseTiming();
//
//   runner->Prepare();
//   suite->Prepare();
//
//   auto callback = runner->Callback();
//   auto async_call = [&callback, &state](std::function<void()>&& task) {
//     state.PauseTiming();
//     auto future = callback(std::move(task));
//     state.ResumeTiming();
//
//     return future;
//   };
//
//   state.ResumeTiming();
//   suite->Run(std::move(async_call));
//   state.PauseTiming();
//
//   suite->Teardown();
//   runner->Teardown();
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// void ProgschjForkingFluid(benchmark::State& state) {
//   auto runner = sd::MakeProgschjRunner();
//   auto suite = MakeFluidSolverSuite();
//   for (auto _ : state) {
//     ForkingBenchmark(state, runner.get(), suite.get());
//   }
// }
//
// void ProgschjJoiningFluid(benchmark::State& state) {
//   auto runner = sd::MakeProgschjRunner();
//   auto suite = MakeFluidSolverSuite();
//   for (auto _ : state) {
//     JoiningBenchmark(state, runner.get(), suite.get());
//   }
// }
//
// void YaclibOldForkingFluid(benchmark::State& state) {
//   auto runner = sd::MakeProgschjRunner();
//   auto suite = MakeFluidSolverSuite();
//   for (auto _ : state) {
//     ForkingBenchmark(state, runner.get(), suite.get());
//   }
// }
//
// void YaclibOldJoiningFluid(benchmark::State& state) {
//   auto runner = yb::MakeYaclibOldRunner();
//   auto suite = MakeFluidSolverSuite();
//   for (auto _ : state) {
//     JoiningBenchmark(state, runner.get(), suite.get());
//   }
// }

void ProgschjForkingFluid(benchmark::State& state) {
  auto suite = SimpleFluidSolverSuite();
  auto pool = std::make_unique<progschj::ThreadPool>(4);

  for (auto _ : state) {
    state.PauseTiming();

    auto create_task = [&](std::function<void()>&& f) {
      state.ResumeTiming();
      auto future = pool->enqueue(std::move(f));
      state.PauseTiming();
      return future;
    };

    suite.Prepare();

    suite._solver = suite._solver_blank;

    for (size_t i = 0; i < 4; ++i) {
      auto tasks = std::vector<std::future<void>>();
      tasks.reserve(suite._grid_size);

      suite._solver.BuildRhs();
      suite._solver.Project(1000);
      suite._solver.ApplyPressure();

      for (size_t j = 0; j < suite._grid_size; ++j) {
        auto d_advect = create_task([&suite, j] {
          size_t idx = 0;
          size_t iy = j;
          for (int ix = 0; ix < suite._solver.w; ix++, idx++) {
            double x = ix + suite._solver.d.ox;
            double y = iy + suite._solver.d.oy;
            suite._solver.d.RungeKutta3(x, y, suite._solver.u, suite._solver.v);
            suite._solver.d.dst[idx] = suite._solver.d.CERP(x, y);
          }
        });

        tasks.emplace_back(std::move(d_advect));
      }

      for (size_t j = 0; j < suite._grid_size; ++j) {
        auto u_advect = create_task([&suite, j] {
          size_t idx = 0;
          size_t iy = j;
          for (int ix = 0; ix < suite._solver.w; ix++, idx++) {
            double x = ix + suite._solver.u.ox;
            double y = iy + suite._solver.u.oy;
            suite._solver.u.RungeKutta3(x, y, suite._solver.u, suite._solver.v);
            suite._solver.u.dst[idx] = suite._solver.u.CERP(x, y);
          }
        });

        tasks.emplace_back(std::move(u_advect));
      }

      for (size_t j = 0; j < suite._grid_size; ++j) {
        auto v_advect = create_task([&suite, j] {
          size_t idx = 0;
          size_t iy = j;
          for (int ix = 0; ix < suite._solver.w; ix++, idx++) {
            double x = ix + suite._solver.v.ox;
            double y = iy + suite._solver.v.oy;
            suite._solver.v.RungeKutta3(x, y, suite._solver.u, suite._solver.v);
            suite._solver.v.dst[idx] = suite._solver.v.CERP(x, y);
          }
        });

        tasks.emplace_back(std::move(v_advect));
      }

      for (auto& task : tasks) {
        task.wait();
      }

      suite._solver.u.Flip();
      suite._solver.d.Flip();
      suite._solver.v.Flip();
    }

    state.ResumeTiming();
  }
}

void ProgschjJoiningFluid(benchmark::State& state) {
  auto suite = SimpleFluidSolverSuite();
  auto pool = std::make_unique<progschj::ThreadPool>(4);
  for (auto _ : state) {
    state.PauseTiming();
    std::atomic<int> flag{0};

    auto create_task = [&](std::function<void()>&& f) {
      //      state.PauseTiming();
      auto future = pool->enqueue([f = std::move(f), &flag] {
        while (flag.load() != 1) {
        }
        std::move(f)();
      });
      //      state.ResumeTiming();
      return future;
    };

    suite.Prepare();

    //    state.ResumeTiming();

    suite._solver = suite._solver_blank;

    for (size_t i = 0; i < 4; ++i) {
      auto tasks = std::vector<std::future<void>>();
      tasks.reserve(suite._grid_size);

      suite._solver.BuildRhs();
      suite._solver.Project(1000);
      suite._solver.ApplyPressure();

      for (size_t j = 0; j < suite._grid_size; ++j) {
        auto d_advect = create_task([&suite, j] {
          size_t idx = 0;
          size_t iy = j;
          for (int ix = 0; ix < suite._solver.w; ix++, idx++) {
            double x = ix + suite._solver.d.ox;
            double y = iy + suite._solver.d.oy;
            suite._solver.d.RungeKutta3(x, y, suite._solver.u, suite._solver.v);
            suite._solver.d.dst[idx] = suite._solver.d.CERP(x, y);
          }
        });

        tasks.emplace_back(std::move(d_advect));
      }

      for (size_t j = 0; j < suite._grid_size; ++j) {
        auto u_advect = create_task([&suite, j] {
          size_t idx = 0;
          size_t iy = j;
          for (int ix = 0; ix < suite._solver.w; ix++, idx++) {
            double x = ix + suite._solver.u.ox;
            double y = iy + suite._solver.u.oy;
            suite._solver.u.RungeKutta3(x, y, suite._solver.u, suite._solver.v);
            suite._solver.u.dst[idx] = suite._solver.u.CERP(x, y);
          }
        });

        tasks.emplace_back(std::move(u_advect));
      }

      for (size_t j = 0; j < suite._grid_size; ++j) {
        auto v_advect = create_task([&suite, j] {
          size_t idx = 0;
          size_t iy = j;
          for (int ix = 0; ix < suite._solver.w; ix++, idx++) {
            double x = ix + suite._solver.v.ox;
            double y = iy + suite._solver.v.oy;
            suite._solver.v.RungeKutta3(x, y, suite._solver.u, suite._solver.v);
            suite._solver.v.dst[idx] = suite._solver.v.CERP(x, y);
          }
        });

        tasks.emplace_back(std::move(v_advect));
      }

      state.ResumeTiming();
      flag.store(1);

      for (auto& task : tasks) {
        task.wait();
      }
      state.PauseTiming();
      flag.store(0);

      suite._solver.u.Flip();
      suite._solver.d.Flip();
      suite._solver.v.Flip();
    }
    state.ResumeTiming();
  }
}

void YaclibOldForkingFluid(benchmark::State& state) {
  auto suite = SimpleFluidSolverSuite();
  auto pool = yaclib::MakeThreadPool(4);
  for (auto _ : state) {
    state.PauseTiming();

    auto create_task = [&](std::function<void()>&& f) {
      state.ResumeTiming();
      auto future = yaclib::Run(pool, f);
      state.PauseTiming();
      return future;
    };

    suite.Prepare();

    suite._solver = suite._solver_blank;

    for (size_t i = 0; i < 4; ++i) {
      auto tasks = yaclib::WaitGroup();

      suite._solver.BuildRhs();
      suite._solver.Project(1000);
      suite._solver.ApplyPressure();

      for (size_t j = 0; j < suite._grid_size; ++j) {
        auto d_advect = create_task([&suite, j] {
          size_t idx = 0;
          size_t iy = j;
          for (int ix = 0; ix < suite._solver.w; ix++, idx++) {
            double x = ix + suite._solver.d.ox;
            double y = iy + suite._solver.d.oy;
            suite._solver.d.RungeKutta3(x, y, suite._solver.u, suite._solver.v);
            suite._solver.d.dst[idx] = suite._solver.d.CERP(x, y);
          }
        });

        tasks.Add(d_advect);
      }

      for (size_t j = 0; j < suite._grid_size; ++j) {
        auto u_advect = create_task([&suite, j] {
          size_t idx = 0;
          size_t iy = j;
          for (int ix = 0; ix < suite._solver.w; ix++, idx++) {
            double x = ix + suite._solver.u.ox;
            double y = iy + suite._solver.u.oy;
            suite._solver.u.RungeKutta3(x, y, suite._solver.u, suite._solver.v);
            suite._solver.u.dst[idx] = suite._solver.u.CERP(x, y);
          }
        });

        tasks.Add(u_advect);
      }

      for (size_t j = 0; j < suite._grid_size; ++j) {
        auto v_advect = create_task([&suite, j] {
          size_t idx = 0;
          size_t iy = j;
          for (int ix = 0; ix < suite._solver.w; ix++, idx++) {
            double x = ix + suite._solver.v.ox;
            double y = iy + suite._solver.v.oy;
            suite._solver.v.RungeKutta3(x, y, suite._solver.u, suite._solver.v);
            suite._solver.v.dst[idx] = suite._solver.v.CERP(x, y);
          }
        });

        tasks.Add(v_advect);
      }

      tasks.Wait();

      suite._solver.u.Flip();
      suite._solver.d.Flip();
      suite._solver.v.Flip();
    }

    state.ResumeTiming();
  }
}

void YaclibOldJoiningFluid(benchmark::State& state) {
  auto suite = SimpleFluidSolverSuite();
  auto pool = yaclib::MakeThreadPool(4);
  for (auto _ : state) {
    state.PauseTiming();
    std::atomic<int> flag{0};
    auto create_task = [&](std::function<void()>&& f) {
      auto future = yaclib::Run(pool, [f = std::move(f), &flag] {
        while (flag.load() != 1) {
        }
        std::move(f)();
      });
      return future;
    };

    suite.Prepare();

    suite._solver = suite._solver_blank;

    for (size_t i = 0; i < 4; ++i) {
      auto tasks = yaclib::WaitGroup();

      suite._solver.BuildRhs();
      suite._solver.Project(1000);
      suite._solver.ApplyPressure();

      for (size_t j = 0; j < suite._grid_size; ++j) {
        auto d_advect = create_task([&suite, j] {
          size_t idx = 0;
          size_t iy = j;
          for (int ix = 0; ix < suite._solver.w; ix++, idx++) {
            double x = ix + suite._solver.d.ox;
            double y = iy + suite._solver.d.oy;
            suite._solver.d.RungeKutta3(x, y, suite._solver.u, suite._solver.v);
            suite._solver.d.dst[idx] = suite._solver.d.CERP(x, y);
          }
        });

        tasks.Add(d_advect);
        std::move(d_advect).Detach();
      }

      for (size_t j = 0; j < suite._grid_size; ++j) {
        auto u_advect = create_task([&suite, j] {
          size_t idx = 0;
          size_t iy = j;
          for (int ix = 0; ix < suite._solver.w; ix++, idx++) {
            double x = ix + suite._solver.u.ox;
            double y = iy + suite._solver.u.oy;
            suite._solver.u.RungeKutta3(x, y, suite._solver.u, suite._solver.v);
            suite._solver.u.dst[idx] = suite._solver.u.CERP(x, y);
          }
        });

        tasks.Add(u_advect);
        std::move(u_advect).Detach();
      }

      for (size_t j = 0; j < suite._grid_size; ++j) {
        auto v_advect = create_task([&suite, j] {
          size_t idx = 0;
          size_t iy = j;
          for (int ix = 0; ix < suite._solver.w; ix++, idx++) {
            double x = ix + suite._solver.v.ox;
            double y = iy + suite._solver.v.oy;
            suite._solver.v.RungeKutta3(x, y, suite._solver.u, suite._solver.v);
            suite._solver.v.dst[idx] = suite._solver.v.CERP(x, y);
          }
        });

        tasks.Add(v_advect);
        std::move(v_advect).Detach();
      }

      state.ResumeTiming();
      flag.store(1);
      tasks.Wait();
      state.PauseTiming();
      flag.store(0);

      suite._solver.u.Flip();
      suite._solver.d.Flip();
      suite._solver.v.Flip();
    }
    state.ResumeTiming();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace

// BENCHMARK(ProgschjForkingFluid);
//BENCHMARK(ProgschjJoiningFluid);

// BENCHMARK(YaclibOldForkingFluid);
BENCHMARK(YaclibOldJoiningFluid);

BENCHMARK_MAIN();
