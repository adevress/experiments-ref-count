# Brief

Toy experiment about reference counting and their implementations.

We compare here different reference counting implementation and their performance in single-threaded and  multi-threaded environment.


# Performance

|               ns/op |                op/s |    err% |          ins/op |          cyc/op |    IPC |         bra/op |   miss% |     total | benchmark
|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|---------------:|--------:|----------:|:----------
|        5,463,840.70 |              183.02 |    0.3% |   29,000,945.13 |   25,232,013.74 |  1.149 |   8,000,227.87 |    0.0% |      1.31 | `Copy atomic std shared_ptr`
|        3,703,209.48 |              270.04 |    0.1% |   14,000,546.33 |   17,496,791.87 |  0.800 |   3,000,117.18 |    0.0% |      0.89 | `Copy atomic boost shared_ptr`
|        1,042,647.19 |              959.10 |    0.9% |   18,000,428.30 |    4,786,883.26 |  3.760 |   3,000,089.71 |    0.0% |      0.26 | `Copy non-atomic boost shared_ptr`
|          112,978.48 |            8,851.24 |    1.8% |    1,250,240.32 |      523,232.52 |  2.389 |     250,050.21 |    0.0% |      0.14 | `raw ptr`

