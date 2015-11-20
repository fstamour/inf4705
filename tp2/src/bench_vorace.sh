#!/bin/sh -e

rm -f results_vorace.txt
RESULT_FILE=results_vorace.txt

for file in `find ../MiseEnBoite -type f | sort -n`; do
    echo $file #>> $RESULT_FILE
    ./vorace -pf $file | tee -a $RESULT_FILE
done;
