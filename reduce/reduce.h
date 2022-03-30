#include <tbb/blocked_range.h>
#include <tbb/parallel_reduce.h>
#include <tbb/task_group.h>

#include <cmath>
#include <iostream>
#include <vector>

constexpr size_t n = 1 << 26;

void normal() {
  float res = 0;
  for (int i = 0; i < n; i++) {
    res += std::sin(i);
  }
}

void task_group() {
  float res = 0;
  size_t maxt = 4;
  tbb::task_group tg;
  std::vector<float> tmp_res(maxt);
  for (size_t i = 0; i < maxt; i++) {
    size_t beg = i * n / maxt;
    size_t end = std::min(n, (i + 1) * n / maxt);
    tg.run([&, i, beg, end] {
      float local_res = 0;
      for (size_t k = beg; k < end; k++) {
        local_res += std::sin(k);
      }
      tmp_res[i] = local_res;
    });
  }
  tg.wait();
  for (size_t t = 0; t < maxt; t++) {
    res += tmp_res[t];
  }
}

void parallel_reduce() {
  float res = tbb::parallel_reduce(
      tbb::blocked_range<size_t>(0, n), (float)0,
      [&](tbb::blocked_range<size_t> r, float local_res) {
        for (int i = r.begin(); i < r.end(); i++) {
          local_res += std::sin(i);
        }
        return local_res;
      },
      [](float x, float y) { return x + y; });
}

void parallel_deterministic_reduce() {
  float res = tbb::parallel_deterministic_reduce(
      tbb::blocked_range<size_t>(0, n), (float)0,
      [&](tbb::blocked_range<size_t> r, float local_res) {
        for (size_t i = r.begin(); i < r.end(); i++) {
          local_res += std::sin(i);
        }
        return local_res;
      },
      [](float x, float y) { return x + y; });
}
