#include <benchmark/benchmark.h>

#include "reduce.h"

static void BM_normal(benchmark::State& state) {
  int n = state.range(0);
  for (auto _ : state) {
    normal();
  }
}

static void BM_task_group(benchmark::State& state) {
  int n = state.range(0);
  for (auto _ : state) {
    task_group();
  }
}

static void BM_parallel_reduce(benchmark::State& state) {
  int n = state.range(0);
  for (auto _ : state) {
    parallel_reduce();
  }
}

static void BM_parallel_deterministic_reduce(benchmark::State& state) {
  int n = state.range(0);
  for (auto _ : state) {
    parallel_deterministic_reduce();
  }
}

BENCHMARK(BM_normal);
BENCHMARK(BM_task_group);
BENCHMARK(BM_parallel_reduce);
BENCHMARK(BM_parallel_deterministic_reduce);
BENCHMARK_MAIN();

// Run on (16 X 2300 MHz CPU s)
// CPU Caches:
//   L1 Data 32 KiB (x8)
//   L1 Instruction 32 KiB (x8)
//   L2 Unified 256 KiB (x8)
//   L3 Unified 16384 KiB (x1)
// Load Average: 21.70, 11.17, 9.13
// ---------------------------------------------------------------------------
// Benchmark                                 Time             CPU   Iterations
// ---------------------------------------------------------------------------
// BM_normal                             0.000 ns        0.000 ns   1000000000
// BM_task_group                    1999130623 ns   1330935000 ns            1
// BM_parallel_reduce               1027959974 ns    349212000 ns            2
// BM_parallel_deterministic_reduce 5703160448 ns   1793450000 ns            1
