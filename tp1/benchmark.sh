#!/bin/sh -e
# The -e flag make the script stop on error (when something as a return value != 0)

DATA=data

# Check if the "data" directory exists
if [ ! -d "$DATA" ]; then
    echo "Directoy '${DATA}' not found"
    exit 1
fi

FILES="$(find ${DATA} -mindepth 1)"

# Check if the "data" directory is not empty
if [ -z "$FILES" ]; then
    echo "Directory '${DATA}' is empty"
    exit 1
fi

# Remove all previous results
if [ -d results ]; then
    rm -r results > /dev/null 2>&1
fi
# Create the "results" directory.
mkdir -p results

# From main.cpp
# algo_0 -> quicksort.
# algo_1 -> quicksort with random pivot.

for file in $FILES; do
    for algo in {0..1}; do
            echo "Algo $algo, threshold: 1, file: $file"
            ./sort $file $algo 1 >> results/result_${algo}_1.csv
            echo "Algo $algo, threshold: 8, file: $file"
            ./sort $file $algo 8 >> results/result_${algo}_8.csv
    done
    echo "Algo 2, file: $file"
    ./sort $file 2 -1 >> results/result_2.csv
done

