#!/bin/sh

DATA=data

# Check if the "data" directory exists
if [ ! -d "$DATA" ]; then
    echo "Directoy '${DATA}' not found"
    exit 1
fi

FILES="$(ls -A ${DATA})"

# Check if the "data" directory is not empty
if [ -z "$FILES" ]; then
    echo "Directory '${DATA}' is empty"
    exit 1
fi

# Create the "results" directory.
mkdir -p results
# Remove all previous results
rm results/*.csv > /dev/null 2>&1

# From main.cpp
# algo_0 -> quicksort.
# algo_1 -> quicksort with random pivot.

for file in $FILES; do
    for algo in {0..1}; do
        for threshold in {1..15}; do
            echo "Algo $algo, threshold: $threshold, file: $file"
            ./sort $file $algo $threshold >> results/result_${algo}_${threshold}.csv
        done
    done
done

