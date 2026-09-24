# Hash-avalanche plus append-growth candidate

This directory records the second C14-7 candidate run.  Starting from the
SplitMix64-finalized hash candidate, append-like monomial storage no longer
calls `vector::recount(old_count + order)`.  It uses `vector::append()`, whose
capacity grows geometrically, and polynomial multiplication allocates its
fixed-size product scratch vector once and overwrites it for every product.
`recount()` remains available for genuine resize operations.

## Environment and result

- Date: 2026-09-24
- Node: `C14-7`, pinned to CPU 6
- Baseline source commit: `b7b4c4601aeb330de74ec87c15edf2262241a5e2`
- Compiler: GCC 11.5.0, `-O2 -std=c++11`
- Input: the archived `n=3`, through-order-3 water input
- Thread-limit environment variables: all set to 1

The uninstrumented candidate completed Order 3 in 4.130247 s and printed an
Order 2--3 CPU-time sum of 4.148382 s.  Full-process wall time was 4.34 s and
peak RSS was 147,080 KiB.  Relative to the hash-only candidate, Order-3 CPU
time decreased from 5.358578 s by 22.92%; relative to the original program's
3,858.036524 s, the combined candidate is 934.09 times faster.

After normalizing timing and output-path fields, all 70,481 stdout lines are
exactly equal to the original archived run.

## `realloc` probe

The same glibc `LD_PRELOAD` probe as the earlier diagnosis reported:

```text
REALLOC_PROBE total_calls=6606 null_pointer_calls=1809 zero_size_calls=1 failed_calls=0 same_pointer_calls=2149 moved_calls=2647 growth_calls=4747 in_place_growth_calls=2100 moved_growth_calls=2647 moved_copy_upper_bound=198195640 largest_moved_copy_upper_bound=8687080
```

The hash-only candidate made 13,514,181 `realloc` calls.  The append-growth
candidate therefore removes 99.9511% of those calls, a 2,045.74-fold
reduction.  The remaining calls are ordinary initial allocations and
geometric growth operations rather than one allocator call per appended
monomial.  `moved_copy_upper_bound` remains an upper bound because glibc may
service large reallocations with `mremap`.

## Files

- `stdout_appendfix.log`, `stderr_appendfix.log`, `time_appendfix.txt`:
  uninstrumented candidate run.
- `stdout_realloc_probe.log`, `stderr_realloc_probe.log`,
  `time_realloc_probe.txt`: allocator-instrumented run.
- `src/polynomial.cpp`: exact candidate source used for both runs.
