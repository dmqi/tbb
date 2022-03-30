#include <benchmark/benchmark.h>

#include "for.h"

static void BM_normal(benchmark::State& state) {
  int n = state.range(0);
  for (auto _ : state) {
    normal();
  }
}

static void BM_parallel_for(benchmark::State& state) {
  int n = state.range(0);
  for (auto _ : state) {
    parallel_for();
  }
}

static void BM_parallel_for_range(benchmark::State& state) {
  int n = state.range(0);
  for (auto _ : state) {
    parallel_for_range();
  }
}

static void BM_parallel_for_range2d(benchmark::State& state) {
  int n = state.range(0);
  for (auto _ : state) {
    parallel_for_range2d();
  }
}

static void BM_parallel_for_range3d(benchmark::State& state) {
  int n = state.range(0);
  for (auto _ : state) {
    parallel_for_range3d();
  }
}

BENCHMARK(BM_normal);
BENCHMARK(BM_parallel_for);
BENCHMARK(BM_parallel_for_range);
BENCHMARK(BM_parallel_for_range2d);
BENCHMARK(BM_parallel_for_range3d);
BENCHMARK_MAIN();

// CPU Caches:
//   L1 Data 32 KiB (x8)
//   L1 Instruction 32 KiB (x8)
//   L2 Unified 256 KiB (x8)
//   L3 Unified 16384 KiB (x1)
// Load Average: 8.69, 7.50, 10.43
// ------------------------------------------------------------------
// Benchmark                        Time             CPU   Iterations
// ------------------------------------------------------------------
// BM_normal                586261072 ns    583862000 ns            1
// BM_parallel_for           65506566 ns     52234000 ns           11
// BM_parallel_for_range     61803430 ns     52529667 ns           12
// BM_parallel_for_range2d   42665629 ns     34828100 ns           20
// BM_parallel_for_range3d   44765264 ns     38385579 ns           19
