#!/bin/bash

CORE_ID='3'
BENCHMARKS=(copy dotprod load memcpy ntstore pc reduc store triad)
CACHES=(L1 L2)
CACHES_SIZES=(24576 1048576)
REPETITIONS=1000
FREQUENCY='1.0GHz'

echo "sudo cpupower -c 3 frequency-set --governor performance"
#echo "cpupower -c $CORE_ID frequency-set -f $FREQUENCY"


for cache in $(seq 0 1)
do
    for benchmark in "${BENCHMARKS[@]}"
    do
        echo "cd ${benchmark}/"
        echo "make"
        echo "taskset -c $CORE_ID ./${benchmark}_${CACHES[$cache]}_SSE_AVX ${CACHES_SIZES[$cache]} $REPETITIONS | cut -d';' -f1,9 > ${benchmark}_${CACHES[$cache]}.dat"
        echo "cd -"
    done
done


