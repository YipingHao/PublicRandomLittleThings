# CMG_PIP generation benchmark with sparse exact transforms

This directory archives the CMG_PIP rerun performed on C14-6 on 2026-09-22
after the per-degree exact forward and inverse transforms were changed from
dense `BigIntMatrix` storage to `SparseUnitLowerBigIntMatrix` storage.

## Environment

- Node: `C14-6`
- CPU: Intel Xeon Platinum 8375C, 64 logical CPUs visible
- Compiler: GCC 4.8.5
- Build flags: `-O2 -std=c++03`
- CMG_PIP commit: `e5c38d3ce7010b5ec621b573e0c9f71900ba469d`
- PublicRandomLittleThings commit at execution: `813b630c387793abc88b44e6b5bc71f124755e62`
- Exact transform validation: disabled (release build)
- Thread limits: `OMP_NUM_THREADS=1`, `OPENBLAS_NUM_THREADS=1`,
  `MKL_NUM_THREADS=1`, `BLIS_NUM_THREADS=1`, and `NUMEXPR_NUM_THREADS=1`
- All 21 CMG_PIP processes ran strictly serially. The node was not reserved
  exclusively and its load average was approximately 9--11 during the batch.
- All result-file print switches were disabled.

The executable was rebuilt from a clean tree immediately before the batch.
`metadata/` contains the commit, compiler, CPU, load, repository-status, and
complete build records. Every target was run as a fresh process. The internal
time is the cumulative monotonic wall-clock time from program start through
completion of the target order. GNU `time -v` supplied the independent wall
time, peak RSS, and exit status.

## Table 2: A2B7

| Target order | Layout outputs | Internal cumulative time | External wall time | Peak RSS (KiB) |
|---:|---:|---:|---:|---:|
| 3 | 59 | 0.008 s | 0.00 s | 2,056 |
| 4 | 229 | 0.052 s | 0.05 s | 2,940 |
| 5 | 881 | 0.376 s | 0.37 s | 6,916 |
| 6 | 3,446 | 2.575 s | 2.57 s | 28,772 |
| 7 | 13,499 | 16.738 s | 16.73 s | 146,688 |

## Table 2: A3B9

| Target order | Layout outputs | Internal cumulative time | External wall time | Peak RSS (KiB) |
|---:|---:|---:|---:|---:|
| 3 | 76 | 0.010 s | 0.01 s | 2,148 |
| 4 | 329 | 0.096 s | 0.09 s | 3,416 |
| 5 | 1,420 | 0.962 s | 0.96 s | 10,208 |
| 6 | 6,271 | 11.612 s | 11.61 s | 56,088 |

## Table 2: A7B6C2

| Target order | Layout outputs | Internal cumulative time | External wall time | Peak RSS (KiB) |
|---:|---:|---:|---:|---:|
| 3 | 304 | 0.033 s | 0.03 s | 3,144 |
| 4 | 1,936 | 0.342 s | 0.34 s | 10,932 |
| 5 | 12,284 | 4.640 s | 4.64 s | 72,700 |
| 6 | 78,778 | 70.830 s | 1:10.83 | 645,944 |

## Table 3: fixed fifth-order water-cluster scan

| n | Water molecules | Total atoms | Layout outputs | Internal cumulative time | External wall time | Peak RSS (KiB) |
|---:|---:|---:|---:|---:|---:|---:|
| 0 | 1 | 3 | 33 | 0.015 s | 0.01 s | 2,112 |
| 1 | 2 | 6 | 608 | 0.110 s | 0.11 s | 4,872 |
| 2 | 4 | 12 | 1,827 | 1.034 s | 1.03 s | 12,760 |
| 3 | 8 | 24 | 2,180 | 2.365 s | 2.36 s | 16,248 |
| 4 | 16 | 48 | 2,183 | 2.951 s | 2.95 s | 16,368 |
| 5 | 32 | 96 | 2,183 | 2.951 s | 2.95 s | 16,368 |
| 19 | 524,288 | 1,572,864 | 2,183 | 2.973 s | 2.97 s | 16,368 |
| 20 | 1,048,576 | 3,145,728 | 2,183 | 2.975 s | 2.97 s | 16,368 |

All runs exited with status 0 and produced empty stderr logs. Table 2 layout
counts are unchanged from the `190b1b8` rerun. In the largest A7B6C2 order-6
case, peak RSS fell from 283,714,476 KiB to 645,944 KiB (about 439 times
smaller). A3B9 order 6 changed from 1,593,744 KiB and 13.969 s to 56,088 KiB
and 11.612 s: its time changed modestly, while its peak memory fell by about
28 times.

Each result directory contains the complete `stdout.log`, empty `stderr.log`,
and GNU `time -v` report in `time.txt`.
