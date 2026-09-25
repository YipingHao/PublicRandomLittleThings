#!/usr/bin/env bash

set -eu

action=${1:-}
work=/tmp/figenerator-postfix-0409100-20260924
source_archive=/tmp/figenerator-0409100.tar.gz
input_archive=/tmp/figenerator-benchmark-inputs-20260924.tar.gz
result_root=/share/Hyper/experiments/generation_benchmark/FIgenerator-postfix-0409100-C14-6
input_root="$work/benchmark-inputs/FIgenerator"

prepare() {
    if [ -e "$work/PREPARED" ]; then
        echo "Already prepared: $work"
        return
    fi

    mkdir -p "$work/source" "$work/benchmark-inputs" "$work/source/obj" "$result_root/metadata"
    tar -xzf "$source_archive" -C "$work/source"
    tar -xzf "$input_archive" -C "$work/benchmark-inputs"

    {
        hostname
        date --iso-8601=seconds
        g++ --version
        uname -a
        free -h
        lscpu
    } >"$result_root/metadata/environment.txt"
    printf '%s\n' '040910054a2291c4061c92defbfa6e18cb6bd27c' >"$result_root/metadata/figenerator_commit.txt"
    sha256sum "$source_archive" "$input_archive" >"$result_root/metadata/archive_sha256.txt"

    make -C "$work/source/tools" libFI.a OPTION="-O2 -std=c++11" \
        >"$result_root/metadata/build.stdout.log" \
        2>"$result_root/metadata/build.stderr.log"
    make -C "$work/source/tools" Pikaqiu.exe OPTION="-O2 -std=c++11" \
        >>"$result_root/metadata/build.stdout.log" \
        2>>"$result_root/metadata/build.stderr.log"
    touch "$work/PREPARED"
}

run_case() {
    case_name=$1
    input_name=$2
    run_dir="$result_root/$case_name"

    if [ -e "$run_dir/COMPLETE" ]; then
        echo "Already complete: $case_name"
        return
    fi

    mkdir -p "$run_dir/output"
    date --iso-8601=seconds >"$run_dir/started.txt"
    uptime >"$run_dir/uptime_before.txt"
    /usr/bin/time -v -o "$run_dir/time.txt" \
        env OMP_NUM_THREADS=1 OPENBLAS_NUM_THREADS=1 MKL_NUM_THREADS=1 \
            BLIS_NUM_THREADS=1 NUMEXPR_NUM_THREADS=1 \
        stdbuf -oL -eL "$work/source/Pikaqiu.exe" \
        "$input_root/$input_name" "$run_dir/output" \
        >"$run_dir/stdout.log" 2>"$run_dir/stderr.log"
    uptime >"$run_dir/uptime_after.txt"
    date --iso-8601=seconds >"$run_dir/completed.txt"
    touch "$run_dir/COMPLETE"
}

case "$action" in
    prepare)
        prepare
        ;;
    water_n0_order5)
        run_case "$action" water_n0_order5.txt
        ;;
    water_n1_order5)
        run_case "$action" water_n1_order5.txt
        ;;
    water_n2_order5)
        run_case "$action" water_n2_order5.txt
        ;;
    water_n3_order3)
        run_case "$action" water_n3_order3.txt
        ;;
    water_n3_order4)
        run_case "$action" water_n3_order4.txt
        ;;
    water_n3_order5)
        run_case "$action" water_n3_order5.txt
        ;;
    A2B7_order7)
        run_case "$action" A2B7_order7.txt
        ;;
    A3B9_order6)
        run_case "$action" A3B9_order6.txt
        ;;
    A7B6C2_order5)
        run_case "$action" A7B6C2_order5.txt
        ;;
    A7B6C2_order6)
        run_case "$action" A7B6C2_order6.txt
        ;;
    *)
        echo "Usage: $0 {prepare|water_n0_order5|water_n1_order5|water_n2_order5|water_n3_order3|water_n3_order4|water_n3_order5|A2B7_order7|A3B9_order6|A7B6C2_order5|A7B6C2_order6}" >&2
        exit 2
        ;;
esac
