#include <atomic>
#include <cassert>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <thread>

#include <boost/smart_ptr/local_shared_ptr.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

#include <fmt/format.h>

#include "rc.hpp"

#include "nanobench.h"

using under_type = unsigned int;
constexpr std::size_t iterations = 100000;

// create a randomized vector of index
// to trick a little to aggressive optimizer
std::vector<std::size_t> create_random_mapper(std::size_t total_size) {
  std::vector<std::size_t> result{};
  ankerl::nanobench::Rng rng;

  result.resize(total_size);
  std::iota(result.begin(), result.end(), 0);
  std::shuffle(result.begin(), result.end(), rng);
  return result;
}

std::size_t run_bench_raw_ptr(under_type val) {
  std::size_t res = 0;
  ankerl::nanobench::Bench bench;

  {
    std::vector<under_type*> ptr_space;
    ptr_space.resize(iterations);
    const auto index_vector = create_random_mapper(iterations);

    bench.minEpochIterations(100).run("raw ptr", [&]() {
      under_type* ptr = new under_type{val++};

      for (std::size_t i = 0; i < iterations; ++i) {
        ptr_space[index_vector[i]] = ptr;
      }
    });

    for (std::size_t i = 0; i < iterations; ++i) {
      res += *ptr_space[i];
    }
  }
  return res;
}

template <typename ptrType> std::size_t bench_copy_rc(under_type val, const std::string& name) {
  std::size_t res = 0;
  ankerl::nanobench::Bench bench;

  {

    std::vector<ptrType> ptr_space;
    ptr_space.resize(iterations);
    const auto index_vector = create_random_mapper(iterations);

    bench.minEpochIterations(100).run(name, [&]() {
      ptrType ptr(new under_type{val++});

      for (std::size_t i = 0; i < iterations; ++i) {
        ptr_space[index_vector[i]] = ptr;
      }
    });

    for (const auto& v : ptr_space) {
      res += *v;
    }
  }

  return res;
}

template <typename ptrType> std::size_t bench_copy_defer_rc(under_type val, const std::string& name) {
  std::size_t res = 0;
  ankerl::nanobench::Bench bench;

  {

    std::vector<ptrType> ptr_space;
    ptr_space.resize(iterations);
    const auto index_vector = create_random_mapper(iterations);

    bench.minEpochIterations(100).run(name, [&]() {
      ptrType ptr(new under_type{val++});

      for (std::size_t i = 0; i < iterations; ++i) {
        ptr_space[index_vector[i]] = ptr;
      }

      for (std::size_t i = 0; i < iterations; ++i) {
        *(ptr_space[i]) = (i + *(ptr_space[i])) / 2;
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
    // Just copy single-threaded
    res += run_bench_raw_ptr(init_value);
    res += bench_copy_rc<std::shared_ptr<under_type>>(init_value, "Copy atomic std shared_ptr");
    res += bench_copy_rc<boost::shared_ptr<under_type>>(init_value, "Copy atomic boost shared_ptr");
    res += bench_copy_rc<Durc<under_type, std::atomic<std::uint32_t>>>(init_value,
                                                                       "Copy atomic Dummy unsafe reference counter");
    res += bench_copy_rc<boost::local_shared_ptr<under_type>>(init_value, "Copy non-atomic boost shared_ptr");
    res += bench_copy_rc<Durc<under_type>>(init_value, "Copy non-atomic Dummy unsafe reference counter (uint32)");
    res += bench_copy_rc<Durc<under_type, std::uint64_t>>(init_value,
                                                          "Copy non-atomic Dummy unsafe reference counter (uint64)");

    // Just copy and defer single-threaded
    res += bench_copy_defer_rc<std::shared_ptr<under_type>>(init_value, "Copy / Defer atomic std shared_ptr");
    res += bench_copy_defer_rc<boost::shared_ptr<under_type>>(init_value, "Copy / Defer atomic boost shared_ptr");
    res += bench_copy_defer_rc<Durc<under_type>>(init_value, "Copy / Defer Dummy unsafe reference counter");
  });

  runner.join();

  fmt::print("Optimizer bypass val {0}\n", res);

  return 0;
}
