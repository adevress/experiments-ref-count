#include <memory>
#include "nanobench.h"

int main() {
    ankerl::nanobench::Bench bench;
    
    bench.run("shared_ptr_incr", [] {
        std::shared_ptr<int> ptr = std::make_shared<int>(42);
        for (int i = 0; i < 1000000; ++i) {
            ptr = std::make_shared<int>(*ptr);
        }
    });

    return 0;
}

