# Brief

Toy experiment about reference counting and their implementations.

We compare here different reference counting implementation and their performance in single-threaded and  multi-threaded environment.


# Performance

./experiments-ref-count 
|               ns/op |                op/s |    err% |          ins/op |          cyc/op |    IPC |         bra/op |   miss% |     total | benchmark
|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|---------------:|--------:|----------:|:----------
|        3,736,683.79 |              267.62 |    0.1% |   14,000,504.25 |   17,494,405.65 |  0.800 |   3,000,109.19 |    0.0% |      4.47 | `atomic boost shared ptr`
|        5,367,951.75 |              186.29 |    0.4% |   29,000,699.38 |   25,048,238.04 |  1.158 |   8,000,165.71 |    0.0% |      1.28 | `atomic shared ptr`
|        1,133,949.33 |              881.87 |    1.3% |   18,000,428.46 |    5,194,012.10 |  3.466 |   3,000,089.90 |    0.0% |      0.30 | `non-atomic boost shared ptr`
|          117,318.14 |            8,523.83 |    2.6% |    1,250,240.28 |      537,592.89 |  2.326 |     250,050.17 |    0.0% |      0.15 | `raw ptr`

