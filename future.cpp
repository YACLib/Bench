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

void YACLibNoContention(benchmark::State& state) {
  for (auto _ : state) {
    yb::NoContention(state);
  }
}

void FollyNoContention(benchmark::State& state) {
  for (auto _ : state) {
    fy::NoContention(state);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibContention(benchmark::State& state) {
  for (auto _ : state) {
    yb::Contention(state);
  }
}

void FollyContention(benchmark::State& state) {
  for (auto _ : state) {
    fy::Contention(state);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibComplexVoid(benchmark::State& state) {
  for (auto _ : state) {
    yb::ComplexBenchmark<void>();
  }
}

void FollyComplexUnit(benchmark::State& state) {
  for (auto _ : state) {
    fy::ComplexBenchmark<folly::Unit>();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibComplexBlob4(benchmark::State& state) {
  for (auto _ : state) {
    yb::ComplexBenchmark<yb::Blob<4>>();
  }
}

void FollyComplexBlob4(benchmark::State& state) {
  for (auto _ : state) {
    fy::ComplexBenchmark<fy::Blob<4>>();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibComplexBlob8(benchmark::State& state) {
  for (auto _ : state) {
    yb::ComplexBenchmark<yb::Blob<8>>();
  }
}

void FollyComplexBlob8(benchmark::State& state) {
  for (auto _ : state) {
    fy::ComplexBenchmark<fy::Blob<8>>();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibComplexBlob64(benchmark::State& state) {
  for (auto _ : state) {
    yb::ComplexBenchmark<yb::Blob<64>>();
  }
}

void FollyComplexBlob64(benchmark::State& state) {
  for (auto _ : state) {
    fy::ComplexBenchmark<fy::Blob<64>>();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibComplexBlob128(benchmark::State& state) {
  for (auto _ : state) {
    yb::ComplexBenchmark<yb::Blob<128>>();
  }
}

void FollyComplexBlob128(benchmark::State& state) {
  for (auto _ : state) {
    fy::ComplexBenchmark<fy::Blob<128>>();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibComplexBlob256(benchmark::State& state) {
  for (auto _ : state) {
    yb::ComplexBenchmark<yb::Blob<256>>();
  }
}

void FollyComplexBlob256(benchmark::State& state) {
  for (auto _ : state) {
    fy::ComplexBenchmark<fy::Blob<256>>();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibComplexBlob512(benchmark::State& state) {
  for (auto _ : state) {
    yb::ComplexBenchmark<yb::Blob<512>>();
  }
}

void FollyComplexBlob512(benchmark::State& state) {
  for (auto _ : state) {
    fy::ComplexBenchmark<fy::Blob<512>>();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibComplexBlob1024(benchmark::State& state) {
  for (auto _ : state) {
    yb::ComplexBenchmark<yb::Blob<1024>>();
  }
}

void FollyComplexBlob1024(benchmark::State& state) {
  for (auto _ : state) {
    fy::ComplexBenchmark<fy::Blob<1024>>();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibComplexBlob2048(benchmark::State& state) {
  for (auto _ : state) {
    yb::ComplexBenchmark<yb::Blob<2048>>();
  }
}

void FollyComplexBlob2048(benchmark::State& state) {
  for (auto _ : state) {
    fy::ComplexBenchmark<fy::Blob<2048>>();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void YACLibComplexBlob4096(benchmark::State& state) {
  for (auto _ : state) {
    yb::ComplexBenchmark<yb::Blob<4096>>();
  }
}

void FollyComplexBlob4096(benchmark::State& state) {
  for (auto _ : state) {
    fy::ComplexBenchmark<fy::Blob<4096>>();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace

BENCHMARK(STLConstantFuture)->UseRealTime();
BENCHMARK(YACLibConstantFuture)->UseRealTime();
BENCHMARK(FollyConstantFuture)->UseRealTime();

BENCHMARK(STLPromiseAndFuture)->UseRealTime();
BENCHMARK(YACLibPromiseAndFuture)->UseRealTime();
BENCHMARK(FollyPromiseAndFuture)->UseRealTime();

BENCHMARK(YACLibOneThen)->UseRealTime();
BENCHMARK(FollyOneThen)->UseRealTime();

BENCHMARK(YACLibTwoThen)->UseRealTime();
BENCHMARK(FollyTwoThen)->UseRealTime();

BENCHMARK(YACLibFourThen)->UseRealTime();
BENCHMARK(FollyFourThen)->UseRealTime();

BENCHMARK(YACLibHundredThen)->UseRealTime();
BENCHMARK(FollyHundredThen)->UseRealTime();

BENCHMARK(YACLibFourThenOnThread)->UseRealTime();
BENCHMARK(FollyFourThenOnThread)->UseRealTime();

BENCHMARK(YACLibFourThenOnThreadInline)->UseRealTime();
BENCHMARK(FollyFourThenOnThreadInline)->UseRealTime();

BENCHMARK(YACLibHundredThenOnThread)->UseRealTime();
BENCHMARK(FollyHundredThenOnThread)->UseRealTime();

BENCHMARK(YACLibHundredThenOnThreadInline)->UseRealTime();
BENCHMARK(FollyHundredThenOnThreadInline)->UseRealTime();

BENCHMARK(YACLibComplexVoid)->UseRealTime();
BENCHMARK(FollyComplexUnit)->UseRealTime();

BENCHMARK(YACLibComplexBlob4)->UseRealTime();
BENCHMARK(FollyComplexBlob4)->UseRealTime();

BENCHMARK(YACLibComplexBlob8)->UseRealTime();
BENCHMARK(FollyComplexBlob8)->UseRealTime();

BENCHMARK(YACLibComplexBlob64)->UseRealTime();
BENCHMARK(FollyComplexBlob64)->UseRealTime();

BENCHMARK(YACLibComplexBlob128)->UseRealTime();
BENCHMARK(FollyComplexBlob128)->UseRealTime();

BENCHMARK(YACLibComplexBlob256)->UseRealTime();
BENCHMARK(FollyComplexBlob256)->UseRealTime();

BENCHMARK(YACLibComplexBlob512)->UseRealTime();
BENCHMARK(FollyComplexBlob512)->UseRealTime();

BENCHMARK(YACLibComplexBlob1024)->UseRealTime();
BENCHMARK(FollyComplexBlob1024)->UseRealTime();

BENCHMARK(YACLibComplexBlob2048)->UseRealTime();
BENCHMARK(FollyComplexBlob2048)->UseRealTime();

BENCHMARK(YACLibComplexBlob4096)->UseRealTime();
BENCHMARK(FollyComplexBlob4096)->UseRealTime();

BENCHMARK(YACLibNoContention)->UseRealTime();
BENCHMARK(FollyNoContention)->UseRealTime();

BENCHMARK(YACLibContention)->UseRealTime();
BENCHMARK(FollyContention)->UseRealTime();

BENCHMARK_MAIN();
