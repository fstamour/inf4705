#!/bin/sh -e

rm -f results_vorace.txt
RESULT_FILE=results_vorace.txt

for file in `find ../MiseEnBoite -type f | sort -n`; do
    echo $file
    ./vorace -pf $file | tee -a $RESULT_FILE
    echo "---" >> $RESULT_FILE
done;
