#!/bin/sh -e

rm -f results_recuit.txt
RESULT_FILE=results_recuit.txt

for file in `find ../MiseEnBoite -type f | sort -n`; do
    echo $file
    ./recuitSimule -pf $file | tee -a $RESULT_FILE
   
done;
