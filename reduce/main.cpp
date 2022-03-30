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
