# CMG_PIP generation benchmark after disabling release validation

This directory archives the CMG_PIP rerun performed on C14-6 on 2026-09-22
after exact transform multiplication validation was gated behind the debug
build.

## Environment

- Node: `C14-6`
- CPU: Intel Xeon Platinum 8375C, 64 logical CPUs visible
- Compiler: GCC 4.8.5
- Build flags: `-O2 -std=c++03`
- CMG_PIP commit: `190b1b8`
- PublicRandomLittleThings commit at execution: `813b630`
- Exact transform validation: disabled (release build)
- Thread limits: `OMP_NUM_THREADS=1`, `OPENBLAS_NUM_THREADS=1`,
  `MKL_NUM_THREADS=1`, `BLIS_NUM_THREADS=1`, and `NUMEXPR_NUM_THREADS=1`
- All 13 CMG_PIP processes ran strictly serially. The node was not reserved
  exclusively and other users had unrelated jobs running.
- All result-file print switches were disabled.

Every target order was run as a fresh process. The internal value is the
cumulative monotonic wall-clock time from program start through completion of
that target order. GNU `time -v` supplied the independent external wall time,
peak RSS, and exit status.

## A2B7

| Target order | Layout outputs | Internal cumulative time | External wall time | Peak RSS (KiB) |
|---:|---:|---:|---:|---:|
| 3 | 59 | 0.008 s | 0.00 s | 2,056 |
| 4 | 229 | 0.054 s | 0.05 s | 4,620 |
| 5 | 881 | 0.404 s | 0.40 s | 34,764 |
| 6 | 3,446 | 3.194 s | 3.19 s | 463,852 |
| 7 | 13,499 | 31.887 s | 31.88 s | 6,866,396 |

## A3B9

| Target order | Layout outputs | Internal cumulative time | External wall time | Peak RSS (KiB) |
|---:|---:|---:|---:|---:|
| 3 | 76 | 0.010 s | 0.01 s | 2,308 |
| 4 | 329 | 0.089 s | 0.09 s | 7,416 |
| 5 | 1,420 | 1.049 s | 1.05 s | 87,564 |
| 6 | 6,271 | 13.969 s | 13.97 s | 1,593,744 |

## A7B6C2

| Target order | Layout outputs | Internal cumulative time | External wall time | Peak RSS (KiB) |
|---:|---:|---:|---:|---:|
| 3 | 304 | 0.036 s | 0.03 s | 7,204 |
| 4 | 1,936 | 0.511 s | 0.51 s | 180,688 |
| 5 | 12,284 | 12.934 s | 12.93 s | 6,925,904 |
| 6 | 78,778 | 449.633 s | 7:29.63 | 283,714,476 |

All runs exited with status 0 and produced empty stderr logs. For every point
available in the first C14-6 workflow run, the `layout outputs` count is
unchanged. A stale A7B6C2 order-6 process from the old binary was stopped before
this rerun; it had run for about 4 h 35 min without finishing and is not part of
the measurements above.

Each `CMG_PIP/orderN/` directory contains the complete `stdout.log`, empty
`stderr.log`, and GNU `time -v` report in `time.txt`.
