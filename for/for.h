#include <tbb/blocked_range2d.h>
#include <tbb/blocked_range3d.h>
#include <tbb/parallel_for.h>
#include <tbb/task_group.h>

#include <algorithm>
#include <cmath>
#include <vector>

constexpr size_t n = 1 << 24;
constexpr size_t m = 1 << 12;
constexpr size_t d = 1 << 8;

std::vector<float> a(n);

void normal() {
  for (size_t i = 0; i < n; i++) {
    a[i] = std::sin(i) * sin(i);
  }
}

void parallel_for() {
  tbb::parallel_for((size_t)0, (size_t)n,
                    [&](size_t i) { a[i] = std::sin(i); });
}

void parallel_for_range() {
  tbb::parallel_for(tbb::blocked_range<size_t>(0, n),
                    [&](tbb::blocked_range<size_t> r) {
                      for (size_t i = r.begin(); i < r.end(); i++) {
                        a[i] = std::sin(i);
                      }
                    });
}

void parallel_for_range2d() {
  tbb::parallel_for(
      tbb::blocked_range2d<size_t>(0, m, 0, m),
      [&](tbb::blocked_range2d<size_t> r) {
        for (size_t i = r.cols().begin(); i < r.cols().end(); i++) {
          for (size_t j = r.rows().begin(); j < r.rows().end(); j++) {
            a[i * m + j] = std::sin(i) * std::sin(j);
          }
        }
      });
}

void parallel_for_range3d() {
  tbb::parallel_for(
      tbb::blocked_range3d<size_t>(0, d, 0, d, 0, d),
      [&](tbb::blocked_range3d<size_t> r) {
        for (size_t i = r.pages().begin(); i < r.pages().end(); i++) {
          for (size_t j = r.cols().begin(); j < r.cols().end(); j++) {
            for (size_t k = r.rows().begin(); k < r.rows().end(); k++) {
              a[(i * d + j) * d + k] = std::sin(i) * std::sin(j) * std::sin(k);
            }
          }
        }
      });
}
