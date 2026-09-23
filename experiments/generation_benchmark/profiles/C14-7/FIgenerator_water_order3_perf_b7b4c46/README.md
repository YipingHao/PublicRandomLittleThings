# FIgenerator water order-3 `perf stat` comparison

This directory archives a single-run comparison of the `n=2` and `n=3`
water inputs through order 3. The run was intended to distinguish an
algorithmic-work increase from a TLB/page-walk explanation for the sharp
FIgenerator slowdown.

## Environment

- Date: 2026-09-23
- Node: `C14-7`
- CPU: two AMD EPYC 7502 sockets, 64 cores, 8 NUMA nodes
- Cache topology: 16 L3 instances totalling 256 MiB (16 MiB per L3 domain)
- Pinned CPU: 7
- FIgenerator commit: `b7b4c4601aeb330de74ec87c15edf2262241a5e2`
- Compiler: GCC 11.5.0
- Build flags: `-O2 -std=c++11`
- `perf`: 5.14.0
- Thread-limit environment variables: all set to 1
- Output files: disabled by the FIgenerator parameters

The runs used `perf stat`, not sampling or instrumentation. The hardware
events were multiplexed and the CSV files retain the event-enabled and
event-running times used by `perf` to scale each count. Both processes exited
with status 0 and produced empty stderr logs.

## Raw results

| Metric | `n=2`, 12 atoms | `n=3`, 24 atoms | Ratio `n=3/n=2` |
|---|---:|---:|---:|
| Order-3 expanded length | 150,348 | 10,626,828 | 70.68 |
| Order-3 program CPU time | 0.037192 s | 3,858.036524 s | 103,732.97 |
| Full-process wall time | 0.10 s | 3,890 s | 38,900.00 |
| Cycles | 142,797,589 | 12,885,661,099,742 | 90,237.25 |
| Instructions | 349,416,312 | 36,219,144,530,840 | 103,656.14 |
| Instructions per cycle | 2.45 | 2.81 | — |
| Generic cache references | 1,922,527 | 861,002,939,270 | 447,849.60 |
| Generic cache misses | 123,017 | 25,313,020,506 | 205,768.48 |
| L1 DTLB misses | 160,895 | 585,011,019 | 3,635.98 |
| L2 DTLB misses / data page walks | 9,671 | 6,189,558 | 640.01 |
| Page faults | 1,763 | 28,283 | 16.04 |
| Peak RSS | 11,264 KiB | 136,968 KiB | 12.16 |

The `n=2` full-process wall time is dominated by fixed startup and profiling
costs, so its wall-time ratio is not used in the diagnosis. The program's
order-3 CPU time and the hardware counts are the relevant comparisons.

## Normalized results

| Metric per final expanded entry | `n=2` | `n=3` | Ratio `n=3/n=2` |
|---|---:|---:|---:|
| Cycles | 949.78 | 1,212,559.49 | 1,276.67 |
| Instructions | 2,324.05 | 3,408,274.28 | 1,466.52 |
| Generic cache references | 12.79 | 81,021.63 | 6,336.16 |
| Generic cache misses | 0.818 | 2,381.99 | 2,911.21 |
| L1 DTLB misses | 1.070 | 55.050 | 51.44 |
| L2 DTLB misses / data page walks | 0.0643 | 0.5824 | 9.05 |

The time per final expanded entry increased by about 1,468 times, while the
instruction count per entry increased by about 1,467 times. IPC improved from
2.45 to 2.81 instead of collapsing. The `n=3` run performed only about 0.58
L2-DTLB misses/page walks per final entry, or one page walk per approximately
5.85 million retired instructions. A single page walk per hash or hundreds of
page walks per final entry therefore did not occur.

Generic cache misses per thousand retired instructions increased only from
0.352 to 0.699. Exact AMD L3 uncore events were not available to the benchmark
user, so the generic cache event must not be described as a precise LLC count.
Cache behavior may still contribute, but the observed slowdown is primarily
an explosion in executed algorithmic work, not a collapse in IPC caused by
TLB page walks.

## Sampling follow-up and hash diagnosis

A later 30-second `perf record` snapshot attached to the still-running `n=3`
process at 49 Hz.  It retained 1,000+ `cycles:u` samples and lost no samples.
The children report attributes 99.93% of the sampled cycles to
`HomogeneousPolynomial<unsigned int>::searchRaw` below
`console::Next -> processPartition -> split`; the self report attributes
81.71% to `compareMonomial` and another 18.02% to `searchRaw` itself.  The raw
snapshot and both reports are in `n3/hotspot_snapshot/`.

`analyze_figenerator_hash.py` reconstructs all ten degree-3 block partitions
from this run's actual order-1 blocks (sizes 28, 128, and 120).  Their
3,542,276 monomials exactly match the reported expanded scalar length divided
by degree: 10,626,828 / 3.  Although the open-addressing tables have final load
factors of only 0.14--0.25, the current hash plus power-of-two masking produces
a support-weighted mean of 39,874.346 successful linear probes per lookup.  In
the worst `112` partition, the mean is 92,128.506 probes and the longest
resulting cluster spans 730,484 buckets.  Applying a SplitMix64 final avalanche
to the same existing hash values, without changing table size or probing,
reduces the weighted mean to 2.041 probes and the longest per-partition cluster
to 45 buckets.

This explains the instruction explosion: `split` applies every permutation
generator to every support monomial and looks the result up in the table.  A
group generator permutes the support bijectively, so the pathological
successful-probe distribution is repeatedly traversed.  The design failure is
the combination of weak low-bit mixing, a power-of-two bucket mask, linear
probing, and highly structured sorted monomial keys; it is not evidence that
the table is too full or that TLB misses dominate.

## Input-encoding equivalence

The archived inputs encode every atom as a one-atom molecule whose molecule
label equals its atom label. The chemically clearer representation would use
one molecule label and assign every atom to that molecule. For these bond-only
tests the two encodings produce the same atom permutation generators in the
same order:

- the archived encoding creates star transpositions through inter-molecule
  `SwapSetGenerator` entries;
- the one-molecule encoding creates the same star transpositions through
  intra-molecule `SwapGenerator` entries.

After `ActionAndRepresentation` merges the generators, both represent
$S_{N_O} \times S_{N_H}$ and produce identical feature permutations. The archived
files are retained verbatim so the exact executed inputs remain auditable.

## Files

- `inputs/`: exact inputs copied to the execution node.
- `n2/` and `n3/`: program stdout, perf CSV, GNU `time -v`, load snapshots,
  completion metadata, and the later sampling snapshot.
- `metadata/`: compiler, CPU, commit, build logs, and perf version.
- `run_figenerator_order3_perf.sh`: exact runner used for the long `n=3` run.
