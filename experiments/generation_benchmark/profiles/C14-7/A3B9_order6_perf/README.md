# A3B9 order-6 CMG_PIP perf profile

This directory contains a sampling profile collected on `C14-7` on 2026-09-22.

## Build and run

- CMG_PIP commit: `93b2405b2ae3559caee55103dbbb8f351158b2f3`
- Input: A3B9 through order 6, with all result-file print switches disabled
- Build flags: `-O2 -g -fno-omit-frame-pointer -std=c++11`
- Thread limits: `OMP_NUM_THREADS=1`, `OPENBLAS_NUM_THREADS=1`, `MKL_NUM_THREADS=1`,
  `BLIS_NUM_THREADS=1`, and `NUMEXPR_NUM_THREADS=1`
- Profiler: `perf record -F 99 -g --call-graph fp`
- Samples: 13,273 cycles samples; zero lost samples
- Wall time: 2:14.72
- Peak RSS: 1,595,464 KiB

## Main observation

The exact unit-lower-triangular inversion itself accounts for approximately 0.88% of sampled cycles.
Approximately 90.6% is attributable to the subsequent full transform-pair validation, including inlined
`ValidateMatrixPair` work. The order-6 transform dimension is 4,851, so the validation's triangular triple
loop visits 19,037,552,226 candidate `(i, j, k)` positions even though most products are structural zeros.

The largest self-cost symbols are repeated `BigInt::isZero()` calls, checked matrix element access, and the
per-access storage-shape validation. The raw `perf.data`, self-cost report, call-tree report, program logs,
input snapshot, and `/usr/bin/time -v` output are preserved in this directory.
