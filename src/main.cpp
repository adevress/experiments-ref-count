#include <cassert>
#include <memory>
#include <stdexcept>
#include <thread>

#include <boost/smart_ptr/local_shared_ptr.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

#include <fmt/format.h>

#include "rc.hpp"

#include "nanobench.h"

using under_type = int;
constexpr std::size_t iterations = 1000000;

std::size_t run_bench_raw_ptr(under_type val) {
  std::size_t res = 0;
  ankerl::nanobench::Bench bench;

  {
    std::vector<under_type*> ptr_space;
    ptr_space.resize(iterations);

    bench.minEpochIterations(100).run("raw ptr", [&]() {
      int* ptr = new under_type{val++};

      for (std::size_t i = 0; i < iterations; ++i) {
        ptr_space[i] = ptr;
      }
    });

    for (std::size_t i = 0; i < iterations; ++i) {
      res += *ptr_space[i];
    }
  }
  return res;
}

template <typename ptrType> std::size_t run_bench_shptr(under_type val, const std::string& name) {
  std::size_t res = 0;
  ankerl::nanobench::Bench bench;

  {

    std::vector<ptrType> ptr_space;
    ptr_space.resize(iterations);

    bench.minEpochIterations(20).run(name, [&]() {
      ptrType ptr(new int{val++});

      for (std::size_t i = 0; i < iterations; ++i) {
        ptr_space[i] = ptr;
      }
    });

    for (const auto& v : ptr_space) {
      res += *v;
    }
  }

  return res;
}

int main() {
  std::size_t res = 0;
  ankerl::nanobench::Rng rng;
  const under_type init_value = rng();

  // force the execution in a separated thread to
  // avoid any side effect related to the stripping
  // of atomic ops in single threaded programs
  std::thread runner([&res, init_value]() {
    res += run_bench_shptr<std::shared_ptr<under_type>>(init_value, "Copy atomic std shared_ptr");
    res += run_bench_shptr<boost::shared_ptr<under_type>>(init_value, "Copy atomic boost shared_ptr");
    res += run_bench_shptr<boost::local_shared_ptr<under_type>>(init_value, "Copy non-atomic boost shared_ptr");
    res += run_bench_shptr<Durc<under_type>>(init_value, "Copy non-atomic Dummy unsafe shared ptr shared_ptr");
    res += run_bench_raw_ptr(init_value);
  });

  runner.join();

  fmt::print("Optimizer bypass val {0}\n", res);

  return 0;
}
