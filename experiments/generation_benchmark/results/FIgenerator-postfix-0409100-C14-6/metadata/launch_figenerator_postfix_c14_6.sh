#!/usr/bin/env bash

set -eu

case_name=${1:-}
case "$case_name" in
    A7B6C2_order6|water_n3_order5)
        ;;
    *)
        echo "Usage: $0 {A7B6C2_order6|water_n3_order5}" >&2
        exit 2
        ;;
esac

runner=/tmp/run_figenerator_postfix_c14_6.sh
result_root=/share/Hyper/experiments/generation_benchmark/FIgenerator-postfix-0409100-C14-6
run_dir="$result_root/$case_name"

mkdir -p "$run_dir"
if [ -e "$run_dir/COMPLETE" ]; then
    echo "Already complete: $case_name"
    exit 0
fi
if [ -s "$run_dir/supervisor.pid" ] && kill -0 "$(cat "$run_dir/supervisor.pid")" 2>/dev/null; then
    echo "Already running: $case_name PID $(cat "$run_dir/supervisor.pid")"
    exit 0
fi

nohup bash "$runner" "$case_name" >"$run_dir/supervisor.log" 2>&1 &
pid=$!
printf '%s\n' "$pid" >"$run_dir/supervisor.pid"
echo "Started: $case_name PID $pid"
