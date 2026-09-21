#!/usr/bin/env bash

set -eu

case_name=$1
order=${2:-6}

fi_root=/share/Hyper/git/FIgenerator
input_root=/share/Hyper/git/PublicRandomLittleThings/experiments/generation_benchmark/FIgenerator
result_root=/share/Hyper/experiments/generation_benchmark
run_dir="$result_root/$case_name/FIgenerator"

export OMP_NUM_THREADS=1
export OPENBLAS_NUM_THREADS=1
export MKL_NUM_THREADS=1
export BLIS_NUM_THREADS=1
export NUMEXPR_NUM_THREADS=1

mkdir -p "$run_dir/output"
echo "Starting FIgenerator $case_name through order $order"
cd "$fi_root"
/usr/bin/time -v -o "$run_dir/time.txt" \
    ./Pikaqiu.exe "$input_root/${case_name}_order${order}.txt" "$run_dir/output" \
    >"$run_dir/stdout.log" 2>"$run_dir/stderr.log"
echo "Finished FIgenerator $case_name through order $order"
