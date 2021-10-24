//
//
//#include <benchmark/benchmark.h>
//
// namespace {
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void OneThen(benchmark::State& state) {
//  for (auto _ : state) {
//    SomeThens(1);
//  }
//}
// void TwoThens(benchmark::State& state) {
//  for (auto _ : state) {
//    SomeThens(2);
//  }
//}
// void FourThens(benchmark::State& state) {
//  for (auto _ : state) {
//    SomeThens(4);
//  }
//}
// void HundredThens(benchmark::State& state) {
//  for (auto _ : state) {
//    SomeThens(100);
//  }
//}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void FourThensOnThread(benchmark::State& state) {
//  for (auto _ : state) {
//    SomeThensOnThread(4);
//  }
//}
//
// void FourThensOnThreadInline(benchmark::State& state) {
//  for (auto _ : state) {
//    SomeThensOnThread(4, true);
//  }
//}
//
// void HundredThensOnThread(benchmark::State& state) {
//  for (auto _ : state) {
//    SomeThensOnThread(100);
//  }
//}
//
// void HundredThensOnThreadInline(benchmark::State& state) {
//  for (auto _ : state) {
//    SomeThensOnThread(100, true);
//  }
//}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//}  // namespace
//
// BENCHMARK(ConstantFuture);
// BENCHMARK(PromiseAndFuture);
// BENCHMARK(WithThen);
//
// BENCHMARK(OneThen);
// BENCHMARK(TwoThens);      // look for >= 50% relative
// BENCHMARK(FourThens);     // look for >= 25% relative
// BENCHMARK(HundredThens);  // look for >= 1% relative
//
// BENCHMARK(FourThensOnThread);           // look for >= 25% relative
// BENCHMARK(FourThensOnThreadInline);     // look for >= 25% relative
// BENCHMARK(HundredThensOnThread);        // look for >= 1% relative
// BENCHMARK(HundredThensOnThreadInline);  // look for >= 1% relative
//
// BENCHMARK_MAIN();
