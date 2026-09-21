#!/usr/bin/env bash

set -eu

case_name=$1
shift

cmg_root=/share/Hyper/git/CMG_PIP
input_root=/share/Hyper/git/PublicRandomLittleThings/experiments/generation_benchmark/CMG_PIP
result_root=/share/Hyper/experiments/generation_benchmark

export OMP_NUM_THREADS=1
export OPENBLAS_NUM_THREADS=1
export MKL_NUM_THREADS=1
export BLIS_NUM_THREADS=1
export NUMEXPR_NUM_THREADS=1

if [ "$#" -eq 0 ]; then
    set -- 3 4 5 6
fi

for order in "$@"; do
    input="$input_root/${case_name}_order${order}.txt"
    run_dir="$result_root/$case_name/CMG_PIP/order${order}"
    mkdir -p "$run_dir/output"
    echo "Starting CMG $case_name through order $order"
    /usr/bin/time -v -o "$run_dir/time.txt" \
        "$cmg_root/Pikaqiu.exe" "$input" "$run_dir/output" \
        >"$run_dir/stdout.log" 2>"$run_dir/stderr.log"
    echo "Finished CMG $case_name through order $order"
done
