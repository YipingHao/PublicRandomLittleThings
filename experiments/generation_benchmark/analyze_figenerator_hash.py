#!/usr/bin/env python3
"""Analyze FIgenerator's degree-3 monomial hash distribution from a run log."""

from __future__ import annotations

import argparse
import itertools
import math
import re
from pathlib import Path

import numpy as np


MASK64 = np.uint64(0xFFFFFFFFFFFFFFFF)
SEED = np.uint64(1469598103934665603)
MIX = np.uint64(0x9E3779B97F4A7C15)


def read_order1_blocks(path: Path) -> list[np.ndarray]:
    blocks: dict[int, np.ndarray] = {}
    current: int | None = None
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        match = re.search(r"Block No\.(\d+) \[order=1, terms=(\d+)\]", line)
        if match:
            current = int(match.group(1))
            continue
        if current is not None and line.lstrip().startswith("features:"):
            values = [int(value) for value in re.findall(r"\d+", line.split(":", 1)[1])]
            blocks[current] = np.asarray(values, dtype=np.uint64)
            current = None
        if len(blocks) == 3:
            break
    if sorted(blocks) != [0, 1, 2]:
        raise RuntimeError(f"expected order-1 blocks 0, 1, 2; got {sorted(blocks)}")
    return [blocks[i] for i in range(3)]


def tuples_for_partition(blocks: list[np.ndarray], part: tuple[int, int, int]) -> np.ndarray:
    values = [blocks[index] for index in part]
    if part[0] == part[2]:
        return np.asarray(list(itertools.combinations_with_replacement(values[0], 3)), dtype=np.uint64)
    if part[0] == part[1]:
        pair = np.asarray(list(itertools.combinations_with_replacement(values[0], 2)), dtype=np.uint64)
        left = np.repeat(pair, len(values[2]), axis=0)
        right = np.tile(values[2], len(pair))
        return np.column_stack((left, right))
    if part[1] == part[2]:
        pair = np.asarray(list(itertools.combinations_with_replacement(values[1], 2)), dtype=np.uint64)
        left = np.repeat(values[0], len(pair))
        right = np.tile(pair, (len(values[0]), 1))
        return np.column_stack((left, right))
    grid = np.meshgrid(values[0], values[1], values[2], indexing="ij")
    return np.column_stack(tuple(component.ravel() for component in grid))


def hash_rows(rows: np.ndarray) -> np.ndarray:
    h = np.full(len(rows), SEED, dtype=np.uint64)
    with np.errstate(over="ignore"):
        for column in range(rows.shape[1]):
            h ^= rows[:, column] + MIX + (h << np.uint64(6)) + (h >> np.uint64(2))
    return h & MASK64


def avalanche_hash(hashes: np.ndarray) -> np.ndarray:
    """Apply the SplitMix64 finalizer before power-of-two bucket masking."""
    z = hashes.copy()
    with np.errstate(over="ignore"):
        z ^= z >> np.uint64(30)
        z *= np.uint64(0xBF58476D1CE4E5B9)
        z ^= z >> np.uint64(27)
        z *= np.uint64(0x94D049BB133111EB)
        z ^= z >> np.uint64(31)
    return z & MASK64


def final_capacity(length: int) -> int:
    capacity = 8
    while length > capacity // 4:
        capacity *= 2
    return capacity


def linear_probe_metrics(home_counts: np.ndarray) -> tuple[int, int, int]:
    # Find the periodic queue state at bucket 0.  Starting with zero can leave a
    # carry at the array boundary when a cluster wraps around the power-of-two
    # table; iterating whole cycles converges because the table is not full.
    boundary_carry = 0
    while True:
        carry = boundary_carry
        for count_value in home_counts:
            carry = max(0, carry + int(count_value) - 1)
        if carry == boundary_carry:
            break
        boundary_carry = carry

    carry = boundary_carry
    displacement = 0
    max_carry = 0
    longest_cluster = 0
    cluster = 0
    for count_value in home_counts:
        count = int(count_value)
        queued = carry + count
        if queued:
            cluster += 1
            carry = queued - 1
            displacement += carry
            max_carry = max(max_carry, carry)
            longest_cluster = max(longest_cluster, cluster)
        else:
            carry = 0
            cluster = 0
    if carry != boundary_carry:
        raise RuntimeError(f"probe queue did not reach a periodic state: {boundary_carry} -> {carry}")
    return displacement, max_carry, longest_cluster


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("stdout_log", type=Path)
    args = parser.parse_args()
    blocks = read_order1_blocks(args.stdout_log)
    print("block sizes:", ", ".join(str(len(block)) for block in blocks))
    print("hash part support capacity load unique_home max_home mean_success_probe max_queue longest_cluster")
    total_support = 0
    weighted_probes = {"current": 0.0, "avalanched": 0.0}
    for part in itertools.combinations_with_replacement(range(3), 3):
        rows = tuples_for_partition(blocks, part)
        base_hashes = hash_rows(rows)
        capacity = final_capacity(len(rows))
        total_support += len(rows)
        variants = (("current", base_hashes), ("avalanched", avalanche_hash(base_hashes)))
        for name, hashes in variants:
            homes = np.bitwise_and(hashes, np.uint64(capacity - 1)).astype(np.int64, copy=False)
            counts = np.bincount(homes, minlength=capacity)
            displacement, max_queue, longest_cluster = linear_probe_metrics(counts)
            mean_probe = 1.0 + displacement / len(rows)
            weighted_probes[name] += len(rows) * mean_probe
            print(
                f"{name} {''.join(map(str, part))} {len(rows)} {capacity} {len(rows)/capacity:.6f} "
                f"{np.count_nonzero(counts)} {counts.max()} {mean_probe:.3f} "
                f"{max_queue} {longest_cluster}"
            )
    print(f"total support: {total_support}")
    for name in ("current", "avalanched"):
        print(f"{name} support-weighted mean successful probes: {weighted_probes[name] / total_support:.3f}")


if __name__ == "__main__":
    main()
