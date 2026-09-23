#!/usr/bin/env bash

set -eu

case_name=$1
input_file=$2
result_root=$3
cpu=${4:-7}
fi_root=${FI_ROOT:-/share/Hyper/git/FIgenerator}
run_dir="$result_root/$case_name"

export OMP_NUM_THREADS=1
export OPENBLAS_NUM_THREADS=1
export MKL_NUM_THREADS=1
export BLIS_NUM_THREADS=1
export NUMEXPR_NUM_THREADS=1

mkdir -p "$run_dir/output"
date -Ins >"$run_dir/started.txt"
uptime >"$run_dir/uptime_before.txt"

cd "$fi_root"
/usr/bin/time -v -o "$run_dir/time.txt" \
    perf stat -x ';' -o "$run_dir/perf_stat.csv" \
    -e task-clock,cycles,instructions,stalled-cycles-frontend,branches,branch-misses,cache-references,cache-misses,l1_dtlb_misses,l2_dtlb_misses,page-faults,minor-faults,major-faults,context-switches,cpu-migrations \
    -- taskset -c "$cpu" env \
    OMP_NUM_THREADS="$OMP_NUM_THREADS" \
    OPENBLAS_NUM_THREADS="$OPENBLAS_NUM_THREADS" \
    MKL_NUM_THREADS="$MKL_NUM_THREADS" \
    BLIS_NUM_THREADS="$BLIS_NUM_THREADS" \
    NUMEXPR_NUM_THREADS="$NUMEXPR_NUM_THREADS" \
    stdbuf -oL -eL ./Pikaqiu.exe "$input_file" "$run_dir/output" \
    >"$run_dir/stdout.log" 2>"$run_dir/stderr.log"

uptime >"$run_dir/uptime_after.txt"
date -Ins >"$run_dir/COMPLETE"
