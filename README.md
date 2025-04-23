# RC experiments


Disclaimer: These benches are not representative of the performance of RC or ARC in the realistic use cases. They are first and foremost an evaluation of the cost of copying / inc for different implementations.


# Compile from source

## Update submodule
```
    git submodule update --recursive --init
```

## Compilation

```bash
    mkdir -p build; cd build;
    cmake -G Ninja ../
    ninja -v
```

# How to run

./experiments-ref-count
|               ns/op |                op/s |    err% |          ins/op |          cyc/op |    IPC |         bra/op |   miss% |     total | benchmark
|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|---------------:|--------:|----------:|:----------
|           77,116.02 |           12,967.47 |    4.8% |      500,241.20 |      342,800.07 |  1.459 |     100,050.09 |    0.0% |      0.09 | `raw ptr`
|          626,526.23 |            1,596.10 |    0.3% |    3,200,697.59 |    2,924,799.44 |  1.094 |     800,147.69 |    0.0% |      0.75 | `Copy atomic std shared_ptr`
|          514,661.25 |            1,943.03 |    1.4% |    1,700,486.37 |    2,389,429.06 |  0.712 |     300,097.43 |    0.0% |      0.62 | `Copy atomic boost shared_ptr`
|          327,036.92 |            3,057.76 |    3.5% |    1,000,507.30 |    1,480,823.22 |  0.676 |     100,104.46 |    0.0% |      0.39 | `Copy atomic Dummy unsafe reference counter`
|          667,760.65 |            1,497.54 |    0.7% |    2,100,426.97 |    3,077,058.22 |  0.683 |     300,088.85 |    0.0% |      0.80 | `Copy non-atomic boost shared_ptr`
|           76,365.32 |           13,094.95 |    1.9% |      500,472.20 |      343,353.57 |  1.458 |     100,100.09 |    0.0% |      0.09 | `Copy non-atomic Dummy unsafe reference counter (uint32)`
|           79,716.89 |           12,544.39 |    0.8% |      600,479.21 |      358,836.51 |  1.673 |     100,100.10 |    0.0% |      0.10 | `Copy non-atomic Dummy unsafe reference counter (uint64)`
|          671,856.22 |            1,488.41 |    0.3% |    4,300,743.17 |    3,097,921.95 |  1.388 |     900,150.79 |    0.0% |      0.80 | `Copy / Defer atomic std shared_ptr`
|          553,775.59 |            1,805.79 |    0.4% |    2,700,483.53 |    2,568,509.77 |  1.051 |     400,096.31 |    0.0% |      0.66 | `Copy / Defer atomic boost shared_ptr`
|          124,094.28 |            8,058.39 |    1.0% |    1,300,476.23 |      567,362.69 |  2.292 |     200,101.12 |    0.0% |      0.15 | `Copy / Defer Dummy unsafe reference counter`