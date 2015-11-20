#!/bin/sh -e

rm -f results_dynamique.txt
RESULT_FILE=results_dynamique.txt

for file in `find ../MiseEnBoite -type f | sort -n`; do
    echo $file
    ./dynamique -pf $file | tee -a $RESULT_FILE
done;
