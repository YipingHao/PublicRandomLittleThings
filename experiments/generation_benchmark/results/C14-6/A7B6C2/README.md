# A7B6C2 generation benchmark: partial workflow results

This directory contains the completed raw logs from the A7B6C2 benchmark workflow on 2026-09-22.
The values are intended for manual rerun and verification, not as repeated-run statistics.

## Environment

- Node: `C14-6`
- CPU: Intel Xeon Platinum 8375C, 64 logical CPUs visible on the node
- Memory: approximately 1 TiB
- Compiler: GCC 4.8.5
- Build flags: `-O2 -std=c++11`
- FIgenerator commit: `67f120b` (locally modified descendant of FI-2025, not the published FI-2025 program)
- CMG_PIP commit: `93b2405`
- PublicRandomLittleThings input/runner commit: `967dcc0`
- Thread limits: `OMP_NUM_THREADS=1`, `OPENBLAS_NUM_THREADS=1`, `MKL_NUM_THREADS=1`,
  `BLIS_NUM_THREADS=1`, and `NUMEXPR_NUM_THREADS=1`
- The two programs ran strictly serially; no benchmark instances overlapped.
- All result-file print switches were disabled. FIgenerator diagnostic stdout is preserved verbatim.

## Timing definitions and raw values

FIgenerator was run once through order 6. Its reported values are separate per-order generation times.

| Target order | FIgenerator reported per-order time |
|---:|---:|
| 3 | 0.100 s |
| 4 | 3.580 s |
| 5 | 137.360 s |
| 6 | 6148.740 s |

The complete FIgenerator process took 1:45:50 externally and reached a peak RSS of 52,789,412 KiB.

CMG_PIP was started as a fresh process for every target order. Its reported value is the cumulative wall-clock
time from program start through completion of that target order.

| Target order | CMG internal cumulative time | External wall time | Peak RSS |
|---:|---:|---:|---:|
| 3 | 0.052 s | 0.05 s | 7,244 KiB |
| 4 | 4.609 s | 4.61 s | 180,924 KiB |
| 5 | 1072.225 s | 17:52.22 | 6,925,908 KiB |

The order-6 CMG_PIP process was still running when these completed results were archived, so its growing logs
are intentionally not included here and no order-6 value is reported.

Empty stderr logs and empty output directories are retained only when representable by Git.
