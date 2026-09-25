# FIgenerator hash-and-append fix rerun on C14-6

This directory archives the single-run benchmark of FIgenerator commit
`040910054a2291c4061c92defbfa6e18cb6bd27c` after the monomial-hash avalanche
and amortized append-growth fixes.  It preserves the earlier benchmark rows
instead of replacing them.

## Environment

- Date: 2026-09-24 through 2026-09-25
- Node: `compute-14-6`
- CPU: Intel Xeon Platinum 8375C, 64 logical CPUs
- Memory visible to the process: approximately 1 TiB
- Compiler: GCC 4.8.5
- Build flags: `-O2 -std=c++11`
- Thread-limit environment variables: all set to 1
- Result-file output: disabled; diagnostic stdout retained verbatim
- Repetitions: one run per point

The build used a clean `git archive` of commit `0409100`.  Its SHA-256 and the
input-archive SHA-256 are recorded under `metadata/`.  `A7B6C2_order5` was a
staged resource check; its exact input is also copied under `metadata/`.

## Table-1 and table-2 systems

The values below are the program's per-order CPU times.  Wall time and RSS are
for the complete process through the highest listed order.

| Case | Order 3 | Order 4 | Order 5 | Order 6 | Order 7 | Complete wall time | Peak RSS |
|---|---:|---:|---:|---:|---:|---:|---:|
| `A2B7_order7` | 0.000 s | 0.040 s | 0.430 s | 5.190 s | 76.130 s | 81.84 s | 1,242,228 KiB |
| `A3B9_order6` | 0.020 s | 0.500 s | 10.730 s | 213.840 s | — | 225.41 s | 5,169,868 KiB |
| `A7B6C2_order6` | 0.070 s | 2.940 s | 101.180 s | 3,043.720 s | — | 3,160.31 s | 52,674,864 KiB |

For all three systems, the per-order FI/PIP counts, scalar lengths, and
cumulative values exactly match the earlier archived runs.  Relative to the
earlier FIgenerator rows, the highest-order per-order times changed as follows:

- `A2B7` Order 7: 108.360 s to 76.130 s (1.42 times faster).
- `A3B9` Order 6: 695.230 s to 213.840 s (3.25 times faster).
- `A7B6C2` Order 6: 6,148.740 s to 3,043.720 s (2.02 times faster).

## Water systems

| Case | Order 2 | Order 3 | Order 4 | Order 5 | Program CPU-time sum | Complete wall time | Peak RSS |
|---|---:|---:|---:|---:|---:|---:|---:|
| `water_n0_order5` | 0.000 s | 0.000 s | 0.000 s | 0.000 s | 0.000 s | 0.00 s | 1,552 KiB |
| `water_n1_order5` | 0.000 s | 0.000 s | 0.000 s | 0.020 s | 0.020 s | 0.02 s | 2,020 KiB |
| `water_n2_order5` | 0.000 s | 0.020 s | 0.480 s | 10.150 s | 10.650 s | 10.66 s | 460,816 KiB |
| `water_n3_order3` | 0.020 s | 3.020 s | — | — | 3.040 s | 3.23 s | 142,256 KiB |
| `water_n3_order4` | 0.010 s | 2.920 s | 547.820 s | — | 550.750 s | 552.31 s | 7,308,848 KiB |

The independent `n=3` Order-3 and Order-4 runs agree on counts; their small
timing difference is ordinary single-run variation.  The Order-4 run is used
for the detailed benchmark table because all of its per-order numbers share
one process.  Order 5 was not started: extrapolating the observed 187.6-fold
Order-3-to-Order-4 time increase gives roughly 28.5 hours, so it is not a
routine completion point even though C14-6 has sufficient physical memory.

After the hash fix, the `n=3` Order-3 time is 2.920 s rather than the earlier
2,324.260 s on C14-6.  The result counts and scalar lengths are unchanged.

## Files

Each case directory contains exact stdout, stderr, GNU `time -v`, start/end
timestamps, load snapshots, and a `COMPLETE` marker.  `metadata/` contains the
environment, build logs, source commit, archive hashes, exact runner scripts,
and the staged `A7B6C2` Order-5 input.
