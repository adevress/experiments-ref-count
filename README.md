# Brief

Toy experiment about reference counting and their implementations.

We compare here different reference counting implementation and their performance in single-threaded and  multi-threaded environment.


# Performance

|               ns/op |                op/s |    err% |          ins/op |          cyc/op |    IPC |         bra/op |   miss% |     total | benchmark
|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|---------------:|--------:|----------:|:----------
|        7,980,295.04 |              125.31 |    0.1% |   29,000,930.79 |   25,142,773.79 |  1.153 |   8,000,224.38 |    0.0% |      1.88 | `Copy atomic std shared_ptr`
|        3,670,007.14 |              272.48 |    0.1% |   14,000,577.91 |   17,476,089.57 |  0.801 |   3,000,121.78 |    0.0% |      0.88 | `Copy atomic boost shared_ptr`
|          989,957.13 |            1,010.14 |    0.9% |   18,000,427.96 |    4,626,401.45 |  3.891 |   3,000,089.39 |    0.0% |      0.27 | `Copy non-atomic boost shared_ptr`
|          116,711.55 |            8,568.13 |    0.9% |    1,250,240.28 |      548,031.44 |  2.281 |     250,050.18 |    0.0% |      0.15 | `raw ptr`

