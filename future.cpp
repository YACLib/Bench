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

void YACLibComplexUnit(benchmark::State& state) {
  for (auto _ : state) {
    yb::ComplexBenchmark<folly::Unit>();
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

BENCHMARK(YACLibComplexUnit);
BENCHMARK(FollyComplexUnit);

BENCHMARK(YACLibComplexBlob4);
BENCHMARK(FollyComplexBlob4);

BENCHMARK(YACLibComplexBlob8);
BENCHMARK(FollyComplexBlob8);

BENCHMARK(YACLibComplexBlob64);
BENCHMARK(FollyComplexBlob64);

BENCHMARK(YACLibComplexBlob128);
BENCHMARK(FollyComplexBlob128);

//BENCHMARK(YACLibComplexBlob256);
//BENCHMARK(FollyComplexBlob256);
//
//BENCHMARK(YACLibComplexBlob512);
//BENCHMARK(FollyComplexBlob512);
//
//BENCHMARK(YACLibComplexBlob1024);
//BENCHMARK(FollyComplexBlob1024);
//
//BENCHMARK(YACLibComplexBlob2048);
//BENCHMARK(FollyComplexBlob2048);
//
//BENCHMARK(YACLibComplexBlob4096);
//BENCHMARK(FollyComplexBlob4096);

BENCHMARK(YACLibNoContention);
BENCHMARK(FollyNoContention);

BENCHMARK(YACLibContention);
BENCHMARK(FollyContention);

BENCHMARK_MAIN();
