#!/usr/bin/env bash

set -eu

case_name=$1
input_file=$2
result_root=$3
cpu=${4:-7}
sample_frequency=${5:-19}
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
    perf record -F "$sample_frequency" -e cycles:u \
    --call-graph dwarf,4096 -o "$run_dir/perf.data" \
    -- taskset -c "$cpu" env \
    OMP_NUM_THREADS="$OMP_NUM_THREADS" \
    OPENBLAS_NUM_THREADS="$OPENBLAS_NUM_THREADS" \
    MKL_NUM_THREADS="$MKL_NUM_THREADS" \
    BLIS_NUM_THREADS="$BLIS_NUM_THREADS" \
    NUMEXPR_NUM_THREADS="$NUMEXPR_NUM_THREADS" \
    stdbuf -oL -eL ./Pikaqiu.exe "$input_file" "$run_dir/output" \
    >"$run_dir/stdout.log" 2>"$run_dir/stderr.log"

perf report --stdio --no-children --percent-limit 0.01 \
    -i "$run_dir/perf.data" >"$run_dir/perf_report_self.txt"
perf report --stdio --children --percent-limit 0.01 \
    -i "$run_dir/perf.data" >"$run_dir/perf_report_children.txt"

uptime >"$run_dir/uptime_after.txt"
date -Ins >"$run_dir/COMPLETE"
