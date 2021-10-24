#include "yaclib/future.hpp"

#include "folly/future.hpp"
#include "std/future.hpp"

#include <benchmark/benchmark.h>

namespace {

using namespace bench;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void STLConstantFuture(benchmark::State& state) {
  for (auto _ : state) {
    sd::MakeFuture(42);
  }
}

void YACLibConstantFuture(benchmark::State& state) {
  for (auto _ : state) {
    yaclib::MakeFuture(42);
  }
}

void FollyConstantFuture(benchmark::State& state) {
  for (auto _ : state) {
    folly::makeFuture(42);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void STLPromiseAndFuture(benchmark::State& state) {
  for (auto _ : state) {
    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::move(p).set_value(42);
    std::move(f).get();
  }
}

void YACLibPromiseAndFuture(benchmark::State& state) {
  for (auto _ : state) {
    yaclib::Promise<int> p;
    yaclib::Future<int> f = p.MakeFuture();
    std::move(p).Set(42);
    std::move(f).Get().Ok();
  }
}

void FollyPromiseAndFuture(benchmark::State& state) {
  for (auto _ : state) {
    folly::Promise<int> p;
    folly::Future<int> f = p.getFuture();
    std::move(p).setValue(42);
    std::move(f).value();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibOneThen(benchmark::State& state) {
  for (auto _ : state) {
    yb::SomeThens(1);
  }
}

void FollyOneThen(benchmark::State& state) {
  for (auto _ : state) {
    fy::SomeThens(1);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibTwoThen(benchmark::State& state) {
  for (auto _ : state) {
    yb::SomeThens(2);
  }
}

void FollyTwoThen(benchmark::State& state) {
  for (auto _ : state) {
    fy::SomeThens(2);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibFourThen(benchmark::State& state) {
  for (auto _ : state) {
    yb::SomeThens(4);
  }
}

void FollyFourThen(benchmark::State& state) {
  for (auto _ : state) {
    fy::SomeThens(4);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibHundredThen(benchmark::State& state) {
  for (auto _ : state) {
    yb::SomeThens(100);
  }
}

void FollyHundredThen(benchmark::State& state) {
  for (auto _ : state) {
    fy::SomeThens(100);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibFourThenOnThread(benchmark::State& state) {
  for (auto _ : state) {
    yb::SomeThensOnThread(4);
  }
}

void FollyFourThenOnThread(benchmark::State& state) {
  for (auto _ : state) {
    fy::SomeThensOnThread(4);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibFourThenOnThreadInline(benchmark::State& state) {
  for (auto _ : state) {
    yb::SomeThensOnThread(4, true);
  }
}

void FollyFourThenOnThreadInline(benchmark::State& state) {
  for (auto _ : state) {
    fy::SomeThensOnThread(4, true);
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibHundredThenOnThread(benchmark::State& state) {
  for (auto _ : state) {
    yb::SomeThensOnThread(100);
  }
}

void FollyHundredThenOnThread(benchmark::State& state) {
  for (auto _ : state) {
    fy::SomeThensOnThread(100);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibHundredThenOnThreadInline(benchmark::State& state) {
  for (auto _ : state) {
    yb::SomeThensOnThread(100, true);
  }
}

void FollyHundredThenOnThreadInline(benchmark::State& state) {
  for (auto _ : state) {
    fy::SomeThensOnThread(100, true);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace

BENCHMARK(STLConstantFuture);
BENCHMARK(YACLibConstantFuture);
BENCHMARK(FollyConstantFuture);
BENCHMARK(STLPromiseAndFuture);
BENCHMARK(YACLibPromiseAndFuture);
BENCHMARK(FollyPromiseAndFuture);

BENCHMARK(YACLibOneThen);
BENCHMARK(FollyOneThen);

BENCHMARK(YACLibTwoThen);
BENCHMARK(FollyTwoThen);

BENCHMARK(YACLibFourThen);
BENCHMARK(FollyFourThen);

BENCHMARK(YACLibHundredThen);
BENCHMARK(FollyHundredThen);

BENCHMARK(YACLibFourThenOnThread);
BENCHMARK(FollyFourThenOnThread);

BENCHMARK(YACLibFourThenOnThreadInline);
BENCHMARK(FollyFourThenOnThreadInline);

BENCHMARK(YACLibHundredThenOnThread);
BENCHMARK(FollyHundredThenOnThread);

BENCHMARK(YACLibHundredThenOnThreadInline);
BENCHMARK(FollyHundredThenOnThreadInline);

BENCHMARK_MAIN();
