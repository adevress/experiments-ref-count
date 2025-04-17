#include <memory>
#include <thread>
#include <stdexcept>
#include <cassert>

#include <boost/shared_ptr.hpp>

#include <fmt/format.h>

#include "nanobench.h"


using under_type = int;



std::size_t  run_bench_raw_ptr(under_type val){
    std::size_t res = 0;
    ankerl::nanobench::Bench bench;
    constexpr std::size_t iterations = 1000000;

    {
        std::vector<under_type*> ptr_space;
        ptr_space.resize(iterations);

        bench
            .minEpochIterations(100)
            .run("raw ptr", [&]() {

            int*  ptr = new under_type{val++};        

            for (std::size_t i = 0; i < iterations; ++i) {
                ptr_space[i] = ptr;              
            }

        });

        
        for(std::size_t i = 0; i < iterations; ++i){
            res += * ptr_space[i];
        }    

    }
    return res;

}

std::size_t run_bench_shared_ptr(under_type val){
    std::size_t res = 0;
    ankerl::nanobench::Bench bench;
    constexpr std::size_t iterations = 1000000;

    {
        
        std::vector<std::shared_ptr<under_type>> ptr_space;
        ptr_space.resize(iterations);

        bench
            .minEpochIterations(100)
            .run("shared ptr", [&]() {

            std::shared_ptr<int> ptr = std::make_shared<under_type>(val++);                

            for (std::size_t i = 0; i < iterations; ++i) {
                ptr_space[i] = ptr;              
            }

        });

        for(const auto & v : ptr_space){
            res += *v;            
        }    

    }

    return res;
}


std::size_t run_bench_boost_shared_ptr(under_type val){
    std::size_t res = 0;
    ankerl::nanobench::Bench bench;
    constexpr std::size_t iterations = 1000000;

    {
        
        std::vector<boost::shared_ptr<under_type>> ptr_space;
        ptr_space.resize(iterations);

        bench
            .minEpochIterations(100)
            .run("boost shared ptr", [&]() {

                boost::shared_ptr<int> ptr(new int{val++});                

            for (std::size_t i = 0; i < iterations; ++i) {
                ptr_space[i] = ptr;              
            }

        });

        for(const auto & v : ptr_space){
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
    std::thread runner([&res, init_value](){
        res += run_bench_boost_shared_ptr(init_value);        
        res += run_bench_shared_ptr(init_value);
        res += run_bench_raw_ptr(init_value);
    });

    runner.join();

    fmt::print("Optimizer bypass val {0}\n", res);

    return 0;
}

