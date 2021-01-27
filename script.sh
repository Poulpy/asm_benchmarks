#!/bin/bash

CORE_ID='3'
# Removed pc and memcpy, dotprod & triad
BENCHMARKS=(copy load ntstore reduc store)
CACHES=(L1 L2)
CACHES_SIZES=(24576 1048576)
REPETITIONS=1000
# Can't set frequency, because there's only performance & powersave governor
# modes
FREQUENCY='2.0GHz'
GNUPLOT_SCRIPT='create_plots_bw.gp'
GNUPLOT_PLOTNAME='plots_bw.png'

sudo cpupower -c $CORE_ID frequency-set --governor performance
sudo cpupower -c $CORE_ID frequency-set --min $FREQUENCY

echo ""
echo "* Compiling benchmarks *"
echo ""
for benchmark in "${BENCHMARKS[@]}"
do
    echo "[$benchmark] make"
    cd ${benchmark}
    make
    cd -
done

echo ""
echo "* Running the benchmarks *"
echo ""
# set loop for the number of caches
# Only one iteration here (L1) because L2 takes too much time :/
for cache in {0..0}
do
    for benchmark in "${BENCHMARKS[@]}"
    do
        echo "[$benchmark] cache: ${CACHES_SIZES[$cache]}"
        cd ${benchmark}/
        taskset -c $CORE_ID ./${benchmark}_SSE_AVX ${CACHES_SIZES[$cache]} $REPETITIONS | cut -d';' -f1,9 > ${benchmark}_${CACHES[$cache]}.dat
        cd -
    done
done

echo ""
echo "* Benchmarks done *"
echo ""

echo ""
echo "* Creating the plots *"
echo ""

gnuplot -c "$GNUPLOT_SCRIPT" > $GNUPLOT_PLOTNAME

echo ""
echo "* Done * "
echo ""

