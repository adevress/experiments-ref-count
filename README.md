# In Brief

Toy experiment about reference counting and their implementations.

We compare here different reference counting implementation and their performance in single-threaded and  multi-threaded environment.


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
|        5,307,901.67 |              188.40 |    0.1% |   29,000,676.03 |   25,153,147.32 |  1.153 |   8,000,160.15 |    0.0% |     13.22 | `Copy atomic std shared_ptr`
|        3,683,044.23 |              271.51 |    0.2% |   14,000,551.15 |   17,489,332.04 |  0.801 |   3,000,119.77 |    0.0% |      8.83 | `Copy atomic boost shared_ptr`
|        1,948,787.78 |              513.14 |    0.9% |    7,000,510.59 |    8,988,406.28 |  0.779 |   1,000,108.95 |    0.0% |      4.64 | `Copy atomic Dummy unsafe reference counter`
|        1,191,089.46 |              839.57 |    3.4% |   18,000,427.74 |    5,447,747.62 |  3.304 |   3,000,089.68 |    0.0% |      3.04 | `Copy non-atomic boost shared_ptr`
|          116,751.95 |            8,565.17 |    1.3% |    1,250,472.23 |      537,950.80 |  2.325 |     250,100.18 |    0.0% |      0.28 | `Copy non-atomic Dummy unsafe reference counter (uint32)`
|          118,484.79 |            8,439.90 |    2.4% |    1,250,478.25 |      547,523.95 |  2.284 |     250,100.20 |    0.0% |      0.29 | `Copy non-atomic Dummy unsafe reference counter (uint64)`
|          116,310.15 |            8,597.70 |    4.0% |    1,250,240.30 |      534,255.40 |  2.340 |     250,050.19 |    0.0% |      0.14 | `raw ptr`

