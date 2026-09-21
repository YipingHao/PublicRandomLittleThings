# A3B9 generation benchmark: first workflow run

This directory contains the raw logs from the first A3B9 benchmark workflow run on 2026-09-21.
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
| 3 | 0.030 s |
| 4 | 0.860 s |
| 5 | 16.160 s |
| 6 | 695.230 s |

CMG_PIP was started as a fresh process for every target order. Its reported value is the cumulative wall-clock
time from program start through completion of that target order.

| Target order | CMG internal cumulative time | External wall time | Peak RSS |
|---:|---:|---:|---:|
| 3 | 0.011 s | 0.01 s | 2,300 KiB |
| 4 | 0.106 s | 0.10 s | 7,364 KiB |
| 5 | 2.298 s | 2.29 s | 87,656 KiB |
| 6 | 117.793 s | 117.79 s | 1,593,728 KiB |

The complete FIgenerator process took 734.55 s externally and reached a peak RSS of 7,344,232 KiB.

Empty stderr logs and empty output directories are retained only when representable by Git.
