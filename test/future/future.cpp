#include <bench/complex.hpp>
#include <bench/contention.hpp>
#include <bench/creation.hpp>
#include <bench/thens.hpp>
#include <bind/all.hpp>
#include <util/bench.hpp>

#include <benchmark/benchmark.h>

namespace {

using namespace bench;

BENCH_STD(ConstantFuture)->UseRealTime();
BENCH_YACLIB(ConstantFuture)->UseRealTime();
BENCH_FOLLY(ConstantFuture)->UseRealTime();
BENCH_ARANGODB(ConstantFuture)->UseRealTime();
BENCH_QT(ConstantFuture)->UseRealTime();
BENCH_BOOST_THREAD(ConstantFuture)->UseRealTime();
BENCH_EXPERIMENTAL(ConstantFuture)->UseRealTime();

BENCH_STD(PromiseAndFuture)->UseRealTime();
BENCH_YACLIB(PromiseAndFuture)->UseRealTime();
BENCH_FOLLY(PromiseAndFuture)->UseRealTime();
BENCH_ARANGODB(PromiseAndFuture)->UseRealTime();
BENCH_BOOST_THREAD(PromiseAndFuture)->UseRealTime();
BENCH_QT(PromiseAndFuture)->UseRealTime();
BENCH_EXPERIMENTAL(PromiseAndFuture)->UseRealTime();

BENCH_YACLIB(Then)->ArgsProduct({{0, 1, 2, 4, 8, 16, 32, 64}, {0}})->UseRealTime();
BENCH_FOLLY(Then)->ArgsProduct({{0, 1, 2, 4, 8, 16, 32, 64}, {0, 1, 2}})->UseRealTime();
BENCH_ARANGODB(Then)->ArgsProduct({{0, 1, 2, 4, 8, 16, 32, 64}, {0, 1, 2}})->UseRealTime();
BENCH_BOOST_THREAD(Then)->ArgsProduct({{0, 1, 2, 4, 8, 16, 32, 64}, {0, 1, 2}})->UseRealTime();
BENCH_QT(Then)->ArgsProduct({{0, 1, 2, 4, 8, 16, 32, 64}, {0, 1, 2}})->UseRealTime();
BENCH_EXPERIMENTAL(Then)->ArgsProduct({{0, 1, 2, 4, 8, 16, 32, 64}, {0, 1, 2}})->UseRealTime();
/*

BENCH_YACLIB(ComplexBlob, 0)->UseRealTime();
BENCH_FOLLY(ComplexBlob, 0)->UseRealTime();
BENCH_ARANGODB(ComplexBlob, 0)->UseRealTime();
BENCH_BOOST_THREAD(ComplexBlob, 0)->UseRealTime();
BENCH_QT(ComplexBlob, 0)->UseRealTime();
BENCH_EXPERIMENTAL(ComplexBlob, 0)->UseRealTime();

BENCH_YACLIB(ComplexBlob, 2)->UseRealTime();
BENCH_FOLLY(ComplexBlob, 2)->UseRealTime();
BENCH_ARANGODB(ComplexBlob, 2)->UseRealTime();
BENCH_BOOST_THREAD(ComplexBlob, 2)->UseRealTime();
BENCH_QT(ComplexBlob, 2)->UseRealTime();
BENCH_EXPERIMENTAL(ComplexBlob, 2)->UseRealTime();

BENCH_YACLIB(ComplexBlob, 4)->UseRealTime();
BENCH_FOLLY(ComplexBlob, 4)->UseRealTime();
BENCH_ARANGODB(ComplexBlob, 4)->UseRealTime();
BENCH_BOOST_THREAD(ComplexBlob, 4)->UseRealTime();
BENCH_QT(ComplexBlob, 4)->UseRealTime();
BENCH_EXPERIMENTAL(ComplexBlob, 4)->UseRealTime();

BENCH_YACLIB(ComplexBlob, 8)->UseRealTime();
BENCH_FOLLY(ComplexBlob, 8)->UseRealTime();
BENCH_ARANGODB(ComplexBlob, 8)->UseRealTime();
BENCH_BOOST_THREAD(ComplexBlob, 8)->UseRealTime();
BENCH_QT(ComplexBlob, 8)->UseRealTime();
BENCH_EXPERIMENTAL(ComplexBlob, 8)->UseRealTime();

BENCH_YACLIB(ComplexBlob, 16)->UseRealTime();
BENCH_FOLLY(ComplexBlob, 16)->UseRealTime();
BENCH_ARANGODB(ComplexBlob, 16)->UseRealTime();
BENCH_BOOST_THREAD(ComplexBlob, 16)->UseRealTime();
BENCH_QT(ComplexBlob, 16)->UseRealTime();
BENCH_EXPERIMENTAL(ComplexBlob, 16)->UseRealTime();

BENCH_YACLIB(ComplexBlob, 32)->UseRealTime();
BENCH_FOLLY(ComplexBlob, 32)->UseRealTime();
BENCH_ARANGODB(ComplexBlob, 32)->UseRealTime();
BENCH_BOOST_THREAD(ComplexBlob, 32)->UseRealTime();
BENCH_QT(ComplexBlob, 32)->UseRealTime();
BENCH_EXPERIMENTAL(ComplexBlob, 32)->UseRealTime();

BENCH_YACLIB(ComplexBlob, 64)->UseRealTime();
BENCH_FOLLY(ComplexBlob, 64)->UseRealTime();
BENCH_ARANGODB(ComplexBlob, 64)->UseRealTime();
BENCH_BOOST_THREAD(ComplexBlob, 64)->UseRealTime();
BENCH_QT(ComplexBlob, 64)->UseRealTime();
BENCH_EXPERIMENTAL(ComplexBlob, 64)->UseRealTime();

BENCH_YACLIB(ComplexBlob, 128)->UseRealTime();
BENCH_FOLLY(ComplexBlob, 128)->UseRealTime();
BENCH_ARANGODB(ComplexBlob, 128)->UseRealTime();
BENCH_BOOST_THREAD(ComplexBlob, 128)->UseRealTime();
BENCH_QT(ComplexBlob, 128)->UseRealTime();
BENCH_EXPERIMENTAL(ComplexBlob, 128)->UseRealTime();

BENCH_YACLIB(ComplexBlob, 256)->UseRealTime();
BENCH_FOLLY(ComplexBlob, 256)->UseRealTime();
BENCH_ARANGODB(ComplexBlob, 256)->UseRealTime();
BENCH_BOOST_THREAD(ComplexBlob, 256)->UseRealTime();
BENCH_QT(ComplexBlob, 256)->UseRealTime();
BENCH_EXPERIMENTAL(ComplexBlob, 256)->UseRealTime();

BENCH_YACLIB(ComplexBlob, 512)->UseRealTime();
BENCH_FOLLY(ComplexBlob, 512)->UseRealTime();
BENCH_ARANGODB(ComplexBlob, 512)->UseRealTime();
BENCH_BOOST_THREAD(ComplexBlob, 512)->UseRealTime();
BENCH_QT(ComplexBlob, 512)->UseRealTime();
BENCH_EXPERIMENTAL(ComplexBlob, 512)->UseRealTime();

BENCH_YACLIB(ComplexBlob, 1024)->UseRealTime();
BENCH_FOLLY(ComplexBlob, 1024)->UseRealTime();
BENCH_ARANGODB(ComplexBlob, 1024)->UseRealTime();
BENCH_BOOST_THREAD(ComplexBlob, 1024)->UseRealTime();
BENCH_QT(ComplexBlob, 1024)->UseRealTime();
BENCH_EXPERIMENTAL(ComplexBlob, 1024)->UseRealTime();

BENCH_YACLIB(ComplexBlob, 2048)->UseRealTime();
BENCH_FOLLY(ComplexBlob, 2048)->UseRealTime();
BENCH_ARANGODB(ComplexBlob, 2048)->UseRealTime();
BENCH_BOOST_THREAD(ComplexBlob, 2048)->UseRealTime();
BENCH_QT(ComplexBlob, 2048)->UseRealTime();
BENCH_EXPERIMENTAL(ComplexBlob, 2048)->UseRealTime();

BENCH_YACLIB(ComplexBlob, 4096)->UseRealTime();
BENCH_FOLLY(ComplexBlob, 4096)->UseRealTime();
BENCH_ARANGODB(ComplexBlob, 4096)->UseRealTime();
BENCH_BOOST_THREAD(ComplexBlob, 4096)->UseRealTime();
BENCH_QT(ComplexBlob, 4096)->UseRealTime();
BENCH_EXPERIMENTAL(ComplexBlob, 4096)->UseRealTime();

BENCH_YACLIB(ComplexBlob, 8192)->UseRealTime();
BENCH_FOLLY(ComplexBlob, 8192)->UseRealTime();
BENCH_ARANGODB(ComplexBlob, 8192)->UseRealTime();
BENCH_BOOST_THREAD(ComplexBlob, 8192)->UseRealTime();
BENCH_QT(ComplexBlob, 8192)->UseRealTime();
BENCH_EXPERIMENTAL(ComplexBlob, 8192)->UseRealTime();

BENCH_YACLIB(NoContention)->UseRealTime()->Args({10000});
BENCH_FOLLY(NoContention)->UseRealTime()->Args({10000});
BENCH_ARANGODB(NoContention)->UseRealTime()->Args({10000});
BENCH_BOOST_THREAD(NoContention)->UseRealTime()->Args({10000});
BENCH_QT(NoContention)->UseRealTime()->Args({10000});
BENCH_EXPERIMENTAL(NoContention)->UseRealTime()->Args({10000});

BENCH_YACLIB(Contention)->UseRealTime()->Args({10000});
BENCH_FOLLY(Contention)->UseRealTime()->Args({10000});
BENCH_ARANGODB(Contention)->UseRealTime()->Args({10000});
BENCH_BOOST_THREAD(Contention)->UseRealTime()->Args({10000});
BENCH_QT(Contention)->UseRealTime()->Args({10000});
BENCH_EXPERIMENTAL(Contention)->UseRealTime()->Args({10000});
*/

}  // namespace

int main(int argc, char** argv) {
  benchmark::Initialize(&argc, argv);
  if (benchmark::ReportUnrecognizedArguments(argc, argv)) {
    return 1;
  }
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
  return 0;
}
