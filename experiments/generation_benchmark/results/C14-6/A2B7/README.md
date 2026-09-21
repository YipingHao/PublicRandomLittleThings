# A2B7 generation benchmark: first workflow run

This directory contains the raw logs from the first A2B7 benchmark workflow run on 2026-09-21.
The values are intended for manual rerun and verification, not as repeated-run statistics.

## Environment

- Node: `C14-6`
- CPU: Intel Xeon Platinum 8375C, 64 logical CPUs visible on the node
- Memory: approximately 1 TiB
- Compiler: GCC 4.8.5
- Build flags: `-O2 -std=c++11`
- FIgenerator commit: `67f120b` (locally modified descendant of FI-2025, not the published FI-2025 program)
- CMG_PIP commit: `93b2405`
- PublicRandomLittleThings input/runner commit: `7cdc140`
- Thread limits: `OMP_NUM_THREADS=1`, `OPENBLAS_NUM_THREADS=1`, `MKL_NUM_THREADS=1`,
  `BLIS_NUM_THREADS=1`, and `NUMEXPR_NUM_THREADS=1`
- The two programs ran strictly serially; no benchmark instances overlapped.
- All result-file print switches were disabled. The current FIgenerator still emits extensive diagnostic text
  to stdout; it is preserved verbatim in `FIgenerator/stdout.log`.

## Timing definitions and raw values

FIgenerator was run once through order 7. Its reported values are separate per-order generation times and
must not be converted to cumulative values in the benchmark tables.

| Target order | FIgenerator reported per-order time |
|---:|---:|
| 3 | 0.000 s |
| 4 | 0.050 s |
| 5 | 0.610 s |
| 6 | 7.700 s |
| 7 | 108.360 s |

CMG_PIP was started as a fresh process for every target order. Its reported value is the cumulative wall-clock
time from program start through completion of that target order.

| Target order | CMG internal cumulative time | External wall time | Peak RSS |
|---:|---:|---:|---:|
| 3 | 0.008 s | 0.01 s | 2,104 KiB |
| 4 | 0.060 s | 0.06 s | 4,604 KiB |
| 5 | 0.683 s | 0.68 s | 34,556 KiB |
| 6 | 19.037 s | 19.04 s | 463,696 KiB |
| 7 | 947.604 s | 947.60 s | 6,866,316 KiB |

The complete FIgenerator process took 117.16 s externally and reached a peak RSS of 1,874,800 KiB.

## Files

- `FIgenerator/stdout.log`: complete program stdout, including all per-order values.
- `FIgenerator/time.txt`: GNU `time -v` resource report.
- `CMG_PIP/orderN/stdout.log`: CMG parameters, counts, and internal program timer for a fresh run through order N.
- `CMG_PIP/orderN/time.txt`: GNU `time -v` resource report for that run.

Empty stderr logs and empty output directories are not tracked by Git.
